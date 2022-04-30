/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30.04.2022 12:40:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>




int main(int argc, char *argv[])
{
	
	pid_t pid;
	pid_t sid;

	pid = fork();

	if(pid == 0)
	{
		chdir("/");
		sid = setsid();
		printf("%i\n",getpid());
		fclose(stdout);
		fclose(stdin);
		fclose(stderr);
		while(1) {
			sleep(60);
		}
	} else {
		return 1;			
	}


}
