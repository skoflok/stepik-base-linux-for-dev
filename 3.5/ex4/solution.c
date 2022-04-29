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
	FILE *fd;
	char buf[256];
	snprintf(buf, sizeof(buf),"/proc/%s/stat",spid);
	int ppid;
	if( (fd = fopen(buf, "r")) != NULL) {
		fscanf(fd, "%*i %*s %*c %i", &ppid);
		if(ppid==etalon_pid) {
			return 1;

		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	const char *start_path;
	const char *spid = argv[1];

	int n;
	struct dirent **namelist;

	char *end;
	int pid = (int) strtol(spid, &end, 10);

	int count = 0;

	n = scandir("/proc/", &namelist, &is_int, alphasort);
	if (n < 0){

		perror("scandir");
	}
	else {
		while(n--){
			if(is_parent(namelist[n]->d_name, pid)==1) {
				count = count + 1;
			}
			free(namelist[n]);
		}
	}
	free(namelist);

	printf("%i\n", count);
}
