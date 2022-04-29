/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23.04.2022 16:04:38
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
//	printf("Extracted '%.*s', strtol returned %ld : %i.\n", num , s, i);
	s = end;

	if (range_error) {
		printf("%s\n", strerror(errno));
		return 0;
	}

	return (num > 0);
}

int is_genenv(char *pid)
{
	FILE *fd;
	char buf[256];
	snprintf(buf, sizeof(buf),"/proc/%s/stat",pid);
	char name[100];
	const char * proc = "(genenv)";
	if( (fd = fopen(buf, "r")) != NULL) {
		fscanf(fd, "%*i %s", &name);
		if(strcmp(proc,name) == 0) {
			return 1;

		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	struct dirent **namelist;
	int n;
	int count = 0;
	n = scandir("/proc/", &namelist, &is_int, alphasort);

	if (n < 0)
		perror("scandir");
	else {
		while(n--) {
			// printf("%s\n", namelist[n]->d_name);
			// is_int(namelist[n]->d_name);
			if(is_genenv(namelist[n]->d_name)==1) {
				count = count + 1;
			}
			free(namelist[n]);
		}
		free(namelist);
	}
	printf("%i\n",count);
}

