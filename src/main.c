/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/10/20 20:44:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Freyja Walberg (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "launch_game.h"


#include	<stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char **argv )
{
	char *gameargs[] = {"/fast_access/Steam/steamapps/common/Crusader Kings III/binaries/ck3", NULL};
	pid_t pid = launch_game(gameargs);
	printf("child pid is %d\n", pid);
	int status;
	while(1)
	{
		pid_t return_pid = waitpid(pid, &status, WNOHANG);
		if(return_pid == 0)
		{
			printf("game is running\n");
		}
		else if(WIFEXITED(status))
		{
			printf("exited with code %d\n", WEXITSTATUS(status));
			break;
		}
		else if(WIFSIGNALED(status))
		{
			printf("game terminated with signal %d\n", WTERMSIG(status));
			break;
		}

	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */