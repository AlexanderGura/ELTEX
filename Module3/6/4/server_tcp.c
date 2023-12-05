#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "server.h"

#define BUF_SIZE 256
#define CLIENT_NUM 5
#define MAX_EVENTS 5

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

	struct epoll_event ev, events[MAX_EVENTS];
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = sockfd;

	int epollfd, count_fd;
	if ((epollfd = epoll_create(CLIENT_NUM)) < 0)
		error("epoll_create");

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0)
		error("epoll_ctl");

	socklen_t client_len = sizeof(client_addr);
	struct hostent *host;
	while (1)
	{
		count_fd = epoll_wait(epollfd, events, MAX_EVENTS, 10);
		if (count_fd < 0)
			error("epoll_wait");

		for (int i = 0; i < count_fd; i++)
		{
			if (events[i].data.fd == sockfd)
			{
				newsockfd = accept(sockfd,
				 (struct sockaddr *)&client_addr, &client_len);
				if (newsockfd == -1)
					error("accept");
				//set_nonblock(newsockfd);

				printf("Socket %d accepted!\n", events[i].data.fd);
				num_clients++;
				print_users();
				ev.events = EPOLLIN | EPOLLET | EPOLLOUT;
				ev.data.fd = newsockfd;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, newsockfd, &ev) < 0)
					error("epoll_ctl");
			}
			else
			{
				calculator(events[i].data.fd);
			}
		}
	}

	if (close(epollfd) == -1)
		error("close");

	if (close(sockfd) == -1)
		error("close");
	return 0;
}
