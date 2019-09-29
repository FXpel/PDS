/* mshell - a job manager */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <sys/wait.h>
#include "pipe.h"
#include "common.h"
#include "cmd.h"
#include "jobs.h"


void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
  
	pid_t pid, child;

	/*
	 * Two pipe variable is required to
	 * create a pipe network between process like that
	 * cmd 1		->	 	cmd 2		 ->		 cmd 3
	 * 		  output  input		   output  input
	 *			  Pipe 1			   Pipe 2
	 */
	pipe_t pipe_fid[2];
	int i;

	pid = fork();
	if(pid == 0){

		/* create an new groupe */
		setpgid(0,0);

		/* create an process by command required */
		for(i = 0; i < nbcmd; i++){

			/* open an new pipe */
			if(i < nbcmd-1)
				assert(pipe(pipe_fid[1]) != -1);

			/* create process parent of the command continue */
			child = fork();
			if(child != 0){

				/* close the old pipe on parent */
				if( i > 0 ){
					close(pipe_fid[0][PIPE_READ]);
					close(pipe_fid[0][PIPE_WRITE]);
				}

				/* copy the new pipe into the old */
				if(i < nbcmd-1)
					memcpy(pipe_fid[0], pipe_fid[1], sizeof(pipe_t));

				/* put his child in his group */
				setpgid(child, getpid());
				continue;
			}

			/* redirect input if is not the first command */
			if(i > 0){
				dup2(pipe_fid[0][PIPE_READ], STDIN_FILENO);
				/* close unused pipe */
				close(pipe_fid[0][PIPE_WRITE]);
			}

			/* redirect output if is not the last command */
			if(i < nbcmd - 1){
				dup2(pipe_fid[1][PIPE_WRITE], STDOUT_FILENO);
				/* close unused pipe */
				close(pipe_fid[1][PIPE_READ]);
			}

			execvp(cmds[i][0], cmds[i]);
		}

		/* wait child created */
		for(i = 0; i < nbcmd; i++)
			wait(NULL);

		exit(EXIT_SUCCESS);
	}

	/* create an job */
	jobs_addjob(pid, FG - bg, "pipe");

	if(!bg)
		waitfg(pid);
}
