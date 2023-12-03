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

void send_file(int sockfd)
{
	int size;
	char buff[BUF_SIZE];
	char filename[BUF_SIZE];
	char *str1 = "Enter filename: ";

	write(sockfd, str1, strlen(str1));
	size = read(sockfd, buff, BUF_SIZE);
	if (size < 0)
		error("read\n");

	strncpy(filename, "server_", BUF_SIZE);
	strncat(filename, buff, BUF_SIZE);
	printf("Create new file: %s\n", filename);

	FILE *file = fopen(filename, "w+");
	if (file == NULL)
		error(NULL);

	while ((size = recv(sockfd, buff, BUF_SIZE, 0)) > 0)
	{
		fwrite(buff, BUF_SIZE, 1, file);
	}

	if (fclose(file))
		error(NULL);

	num_clients--;
	printf("Disconnect\n");
	print_users();
}
