#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 100
#define OWN_PORT 51001

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char sendbuff[BUF_SIZE], recvbuff[BUF_SIZE];
	int client_len;
	struct sockaddr_in server_addr, client_addr;

	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}

	// client;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(OWN_PORT);
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	// server;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	while (1)
	{
		client_len = sizeof(client_addr);
		if (recvfrom(sockfd, recvbuff, BUF_SIZE, 0,
			(struct sockaddr *) NULL, NULL) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(EXIT_FAILURE);
		}

		if (strcmp(recvbuff, "q\n") == 0)
			break;

		printf("New message: %s", recvbuff);
		printf("Enter message: ");
		fgets(sendbuff, BUF_SIZE, stdin);

		if (sendto(sockfd, sendbuff, BUF_SIZE, 0,
			(struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(EXIT_FAILURE);
		}

		if (strcmp(sendbuff, "q\n") == 0)
			break;

	}
	printf("Goodbye!\n");
	close(sockfd);

	return 0;
}
