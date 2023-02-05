/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.02.2023 11:39:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{

	if (argc < 2) {
		printf("Usage: solution {hostname}\n");
		return -1;
	}

	struct hostent *h;
	
	h = gethostbyname(argv[1]);

	if (h == NULL) {
		printf("Error\n");
		return -1;
	}

	int i = 0;


	while (h->h_addr_list[i] != NULL) {
		
		struct in_addr *a = (struct in_addr*) h->h_addr_list[i]; 
		printf("%s\n", inet_ntoa(*a));
		i++;
	}


}
