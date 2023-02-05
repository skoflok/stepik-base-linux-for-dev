/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:  
 *    Разработайте UDP сервер для логирования (сбора и записи) сообщений. Сервер при запуске принимает параметр -- номер порта, на котором будут приниматься запросы. Каждый запрос приходящий к серверу - строка, не превышающая размер 5K.  Задача сервера -- выводить приходящие строки в стандартный поток ввода-вывода, завершающиеся символом конца строки.

Сервер завершает работу, когда получает строку содержащую только текст 'OFF', и заканчивающуюся символом перевода строки '\n'.

Сервер использует локальный адрес 127.0.0.1

Пример вызова


./solution 22476
foo
bar
foo bar baz


Представление решения

Решение предоставляется в виде двух файлов solution.c и Makefile, в последнем предполагается цель по умолчанию, которая приводит к сборке Вашего приложения. Бинарный файл вашего решения должен иметь имя solution.

Вывод

Программа выводит в стандартный поток строки, причем каждая строка должна оканчиваться символом конца строки.


 *
 *        Version:  1.0
 *        Created:  05.02.2023 13:08:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

struct sockaddr_in l;


void cl(char *buf, int s)
{
	int i = 0;
	while (i < s) {
		buf[i] = '\0';
		i += 1;
	}
}


int main(int argc, char **argv)
{

	int bufsize = 5000;
	if(argc != 2) {
//		printf("Usage: solution {port}\n");
		return -1;
	}

	int s = socket(PF_INET, SOCK_DGRAM, 0);
//	printf("Socket %d\n", s);

	inet_aton("127.0.0.1", &l.sin_addr);
//	printf("set &l\n");
	l.sin_port = htons(atoi(argv[1]));
	l.sin_family = PF_INET;

//	printf("bindings...\n" );

	int result = bind(s, (struct sockaddr*) &l, sizeof(l));

//	printf("%d\n", result);

	char buf[bufsize];

	while(1) {

		cl(buf, bufsize);

		read(s, buf, bufsize);
		if(strcmp(buf,"OFF\n")==0) {
			close(s);
			return 0;
		}
		printf("%s\n", buf);
	}
}
