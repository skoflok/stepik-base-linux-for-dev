/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29.04.2022 15:36:18
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

int is_int(const struct dirent *entry)
{
	errno = 0;
	const char *s = entry->d_name;
	char *end;
	const long i = strtol(s, &end, 10);
	int num = (int)(end-s);

	const bool range_error = errno == ERANGE;
	s = end;

	if (range_error) {
		printf("%s\n", strerror(errno));
		return 0;
	}

	return (num > 0);
}

int is_parent(char *spid, int etalon_pid)
{
	return 0;
}

int get_parent(const char *spid)
{
	FILE *fd;
	char buf[256];
	snprintf(buf, sizeof(buf),"/proc/%s/stat",spid);
	int ppid;
	if( (fd = fopen(buf, "r")) != NULL) {
		fscanf(fd, "%*i %*s %*c %i", &ppid);
			return ppid;
	}
	return 0;
}

int count_children(int pid)
{
	int count = 0;
	int ccount = 0;
	struct dirent **namelist;
	int n;
	int ppid;
	const char * sppid;

	const char * scpid;
       	int cpid;	

	if(pid==0) {
		return 0;
	}

	const char *a[100];

	n = scandir("/proc/", &namelist, &is_int, alphasort);
	if (n < 0){

		perror("scandir");
	}
	else {
		while(n--){
			scpid = namelist[n]->d_name;
			cpid = char_to_int(scpid); 
			ppid = get_parent(scpid);
			// printf("%i %i \n", cpid, ppid);
			if(ppid==pid) {
				ccount = count_children(cpid);
				//printf("%i\n",ccount);
				if(ccount < 0 ) {
					printf("%i\n", ccount);
				}
				count = count + 1 + ccount;
			}
			free(namelist[n]);
		}
	}
	free(namelist);
	return count;
}

int char_to_int(const char * str)
{	
	char *end;
	int integer = (int) strtol(str, &end, 10);
	return integer;
}

int main(int argc, char *argv[])
{
	const char *spid = argv[1];

	int pid = char_to_int(spid);

	int count = 0;
	count = count_children(pid);

	printf("%i\n", count);
}
