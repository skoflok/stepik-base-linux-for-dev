/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19.04.2022 15:37:06
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

int main()
{
	FILE *fd;
	char *path = "/proc/self/stat";
	char *ad;
	int pid;
	int ppid;
	if( (fd = fopen(path, "r")) != NULL) {
		fscanf(fd, "%*i %*s %*c %i", &pid);
		printf("%d\n", pid);

	}
	return 1;
}
