#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "server.h"

int num_clients = 0;

int sum(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}
int mult(int a, int b)
{
	return a * b;
}
int divs(int a, int b)
{
	if (b == 0)
		return -1;
	return a / b;
}

void print_users()
{
	if (num_clients)
		printf("%d online clients\n", num_clients);
	else
		printf("No online clients\n");
}

void error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void set_nonblock(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}

void calculator(int sockfd)
{
	int size, a, b, op, res;
	int (*operations[])(int, int) = {sum, sub, mult, divs};
	char buff[BUF_SIZE];
	char *str1 = "Enter 1 parametr: ";
	char *str2 = "Enter 2 parametr: ";
	char *str3 = "Enter operation:\n1.+\n2.-\n3.*\n4./\nEnter: ";

	write(sockfd, str1, strlen(str1));
	size = read(sockfd, buff, BUF_SIZE);
	if (size < 0)
		error("read\n");
	a = atoi(buff);

	write(sockfd, str2, strlen(str2));
	size = read(sockfd, buff, BUF_SIZE);
	if (size < 0)
		error("read\n");
	b = atoi(buff);

	write(sockfd, str3, strlen(str3));
	size = read(sockfd, buff, BUF_SIZE);
	if (size < 0)
		error("read\n");
	op = atoi(buff);
	if (op < 1 || op > 4)
		printf("Wrong action!\n");
	else
	{
		res = operations[op - 1](a, b);
		snprintf(buff, BUF_SIZE, "Result: %d\n", res);
		buff[BUF_SIZE - 1] = '\n';
		write(sockfd, buff, BUF_SIZE);
	}

	num_clients--;
	printf("Disconnect\n");
	print_users();
}
