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

int main(int argc, char *argv[])
{
	char buff[BUF_SIZE];
	int client_len;
	struct sockaddr_in server_addr, client_addr;

	// server;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(51000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", server_addr.sin_addr.s_addr);

	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		client_len = sizeof(client_addr);
		if (recvfrom(sockfd, buff, BUF_SIZE, 0,
			(struct sockaddr *) &client_addr, &client_len) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(EXIT_FAILURE);
		}

		if (strcmp(buff, "q\n") == 0)
		{
			printf("Goodbye!\n");
			break;
		}
		printf("Message from client: %s\n", buff);

		if (sendto(sockfd, buff, BUF_SIZE, 0,
			(struct sockaddr *) &client_addr, client_len) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(EXIT_FAILURE);
		}

	}
	close(sockfd);

	return 0;
}
