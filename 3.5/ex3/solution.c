/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  iкоторая по заданному pid, осуществляет поиск пути в дереве процессов до процесса с идентификатором 1 (init). Для каждого найденного процесса печатается в отдельной строке его идентификатор.
 *
 *
 *
 *        Version:  1.0
 *        Created:  27.04.2022 16:28:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

int get_ppid(int pid)
{
	FILE *fd;
	int ppid;
	char spid[100];
	sprintf(spid, "%d", pid);
	char buf[256];
	snprintf(buf, sizeof(buf),"/proc/%s/stat",spid);

	//printf("%s\n", buf);

	if( (fd = fopen(buf, "r")) != NULL) {
		fscanf(fd, "%*i %*s %*c %i", &ppid);
//		printf("%d\n", ppid);
		
		//sprintf(sppid, "%d", ppid);
		return ppid;
	} else {
		return 0;
	}

}

int main(int argc, char *argv[]) 
{
	const char *start_path;
	const char *spid = argv[1];
	char *end;
	int pid = (int) strtol(spid, &end, 10);
	printf("%i\n", pid);	

	while( (pid = get_ppid(pid))!=0 ) {
		printf("%i\n", pid);
	}

}
