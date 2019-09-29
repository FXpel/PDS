#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "makeargv.h"

static int opt_cc=0;
static int opt_kill=0;
static int isAnd=0;

void killRemainingProcess(pid_t *tab,int size, int opt_kill){
	/*kills the children if the option 'kill' has been called*/
	int i ; 
	if (opt_kill)
	{
		for ( i = 0; i <size; ++i)
		{
			kill(tab[i],SIGINT);
			wait(NULL);
		}

	}

}

int orAndFinder(int andOrFound){
	/*prevents the user from using both options 'and' and 'or'  returns 1 if only one option between 'and' or 'or' has been called */
	if(!andOrFound){
		return 1;
	}
	else{
		perror("Already found a 'And' or a 'Or' ");
		exit(EXIT_FAILURE);
	}
}

int mdo(int argc,char *argv[],int nbOpt){
	/*executes the commands typed in the standard input 
	* By default the 'and' option is called  
	* returns 0 or 1 according to the options and the exit status of the commands
	*/
	int i , status, finalStatus ; 
	char **tab ; /*Contains the arguments typed */
	pid_t tabPid[argc-nbOpt+1]; /* Contains all the pid of the children */
	finalStatus=1; 
	if (!isAnd)
	{
		finalStatus=0; 
	}
	/*  Create a child for each command typed in the standard input */
	for ( i = nbOpt+1; i < argc; i++)
	{
		switch (fork()){
			case -1:
				perror("Failed to fork"); 
				exit(EXIT_FAILURE); 
			case 0: 
				tabPid[i-nbOpt-1]=getpid();
				tab=makeargv(argv[i]); 
				execvp(tab[0],tab);
				perror("Failed to exec"); 
				exit(EXIT_FAILURE); 
			default: 
				break;  
		}
	}
	/* When all the children are terminated , computes the final status */
	for (i = nbOpt+1; i < argc; i++)
	{
		wait(&status);
		if(WIFEXITED(status)){
			if ( isAnd) /*when option 'and' was called */
			{
				if (status && opt_cc)
				{
					killRemainingProcess(tabPid,argc-nbOpt+1,opt_kill); 
					return 0; 
				}
				finalStatus= finalStatus & WEXITSTATUS(status); 

			}
			else { /* when option 'or ' was called  */
				if (status && opt_cc)
				{
					killRemainingProcess(tabPid,argc-nbOpt+1,opt_kill);
					return 1 ; 
				}
				finalStatus=finalStatus || WEXITSTATUS(status);
			}
		}
	}
	return finalStatus ;/*
	if (finalStatus)
	{
		return 1==1; 
	}
	return 0==0; */
}	


int main(int argc, char const *argv[]){
	int character;/*the read option */
	int andOrFound ; 
	int nbOptions; 
	/*handles the differents options (as they are strings )*/
	static struct option long_options[] = {
       {"and", 0, NULL,  'a' },
       {"or", 0, NULL, 'o' },
       {"cc",0,NULL, 'c' },
       {"k",0,NULL,'k'},
       {NULL,0,NULL,0}
  };
  if (argc<2)
  {
  	perror("Need at least 2 arguments"); 
	exit(EXIT_FAILURE); 
  }
  andOrFound=0;
  nbOptions=0;
  while((character=getopt_long(argc,argv,"aock",long_options,NULL))!=-1){
  	switch(character){
  	case 'o': /*option 'or' */
  		andOrFound=orAndFinder(andOrFound);
  		isAnd=0; 
  		nbOptions++; 
  		break;
  	case 'a': /* option 'and' */
  		andOrFound=orAndFinder(andOrFound);
  		nbOptions++; 
  		break;
  	case 'c':
  		opt_cc=1; 
  		nbOptions++; 
  		break;
  	case 'k':
  		if (opt_cc=1){
  		 	opt_kill=1;
  		} 
  		else {
  			perror("Only valid with --cc");
  			exit(EXIT_FAILURE); 
  		}
  		nbOptions++; 
  		break ; 
  	default:
  		printf("the only options are --and , --or, --cc followed or not by kill \n");
  	}
  }
	/*printf("%d \n",mdo(argc,argv,nbOptions)) */
	exit(mdo(argc,argv,nbOptions));
}
