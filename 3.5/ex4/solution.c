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
#include <sys/types.h>


#define MAX_SIZE 100

struct pids {
	int pid;
	int ppid;
};

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
	int n;
	int max;
	int count = 0;
	int ccount = 0;
	struct dirent **namelist;
	int i;
	int ppid;
	const char * sppid;

	const char * scpid;
       	int cpid;	

	if(pid==0) {
		return 0;
	}

	const char *a[MAX_SIZE];

	n = scandir("/proc/", &namelist, &is_int, alphasort);
	max = n;
	if (n < 0){

		perror("scandir");
	}
	else {
		while(n--){
			scpid = namelist[n]->d_name;
			a[n] = scpid;
			free(namelist[n]);
		}
	}
	free(namelist);

	for(i = 0;i<=max;i++ ) {
		cpid = char_to_int(a[i]);
		ppid = get_parent(a[i]);
		if(ppid == pid) {
			ccount = count_children(cpid); 
			count = count + 1;
		}
	}

	return count;
}


int char_to_int(const char * str)
{	
	char *end;
	int integer = (int) strtol(str, &end, 10);
	return integer;
}

int get_pids(struct pids *a)
{
	int n = 0;
	struct pids p;
	struct dirent **namelist;
	int max = 0;
	const char *scpid;
	int pid;

	n = scandir("/proc/", &namelist, &is_int, alphasort);
	max = n;
	if (n < 0){

		perror("scandir");
	}
	else {
		while(n--){
			scpid = namelist[n]->d_name;
			pid = char_to_int(scpid);
			p.pid = pid;
			p.ppid = get_parent(scpid);
			a[n] = p;
			free(namelist[n]);
		}
	}
	free(namelist);
	return max;
}

int main(int argc, char *argv[])
{
	const char *spid = argv[1];
	struct pids a[MAX_SIZE];
	int pid = char_to_int(spid);
	int n;	
	int i;
	int count = 0;
	n = get_pids(a);
	for(i=0; i<n-1; i++) {
		printf("{%i,%i}\n",a[i].pid, a[i].ppid);	
	}
	//count = count_children(pid);

	printf("%i\n", count);
}
