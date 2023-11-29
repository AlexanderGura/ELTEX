#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "server.h"

#define BUF_SIZE 256
#define CLIENT_NUM 5

extern int num_clients;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int port, sockfd, newsockfd;
	char buff[BUF_SIZE];
	struct sockaddr_in server_addr, client_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		error("socket\n");

	port = atoi(argv[1]);
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *)&server_addr,
	  sizeof(server_addr)) < 0)
		perror("bind\n");

	listen(sockfd, CLIENT_NUM);
	socklen_t client_len = sizeof(client_addr);
	struct hostent *host;
	while (1)
	{
		newsockfd = accept(sockfd,
			(struct sockaddr *) &client_addr, &client_len);
		if (newsockfd < 0)
			error("accept\n");
		num_clients++;
		print_users();

		pid_t pid = fork();
		switch(pid)
		{
			case -1:
				error("fork\n");

			case 0:
				close(sockfd);
				calculator(newsockfd);
				exit(EXIT_SUCCESS);

			default:
				close(newsockfd);
				break;
		}
	}


	close(sockfd);
	return 0;
}
