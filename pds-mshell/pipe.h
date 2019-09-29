/* mshell - a job manager */

#ifndef _PIPE_H_
#define _PIPE_H_

#include "common.h"

/*
 * Simplification of pipe using
 * this type then an int[2]
 */
typedef int pipe_t[2];

/* Explicit the fd using */
typedef enum {
	PIPE_READ,
	PIPE_WRITE
} pipe_mode;
extern void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg);

#endif
