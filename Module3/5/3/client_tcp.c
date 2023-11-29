#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 256

void error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int port, sockfd, size;
	char buff[BUF_SIZE];
	struct hostent *server;
	struct sockaddr_in server_addr;

	port = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		error("socket\n");

	server = gethostbyname(argv[1]);
	if (server == NULL)
		error("gethostbyname\n");

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&server_addr.sin_addr.s_addr, server->h_length);
	server_addr.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) < 0)
		error("connect\n");

	while ((size = recv(sockfd, buff, BUF_SIZE - 1, 0)) > 0)
	{
		buff[size] = 0;
		printf("%s", buff);
		fgets(buff, BUF_SIZE - 1, stdin);

		if (strcmp(buff, "q\n") == 0)
		{
			printf("Good bye!");
			close(sockfd);
			return 0;
		}
		send(sockfd, buff, BUF_SIZE, 0);
	}
	fprintf(stderr, "recv\n");
	close(sockfd);
	exit(EXIT_FAILURE);
}
