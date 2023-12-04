#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <IP-addres> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_addr, client_addr;

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (sockfd < 0)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}

	// client;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(51000);
	if (inet_aton("10.0.2.15", &server_addr.sin_addr) == 0)
	{
		fprintf(stderr, "Invalid IP-addres!\n");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	// server;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	if (inet_aton(argv[1], &server_addr.sin_addr) == 0)
	{
		fprintf(stderr, "Invalid IP-addres!\n");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	char datagram[1024];
	bzero(datagram, 1023);
	struct iphdr *ip_head = (struct iphdr *) datagram;
	ip_head->version = 4;
	ip_head->ihl = 5;
	ip_head->tos = 0;
	ip_head->tot_len = htons(sizeof(ip_head) + sizeof(struct udphdr) + BUF_SIZE);
	ip_head->check = 0;
	ip_head->id = htonl(54321);
	ip_head->frag_off = 0;
	ip_head->ttl = 64;
	ip_head->protocol = IPPROTO_UDP;
	ip_head->saddr = client_addr.sin_addr.s_addr;
	ip_head->daddr = server_addr.sin_addr.s_addr;

	struct udphdr *udp_head = (struct udphdr *) (datagram + sizeof(ip_head));
	udp_head->source = htons(51000);
	udp_head->dest = htons(atoi(argv[2]));
	udp_head->len = htons(8 + BUF_SIZE);
	udp_head->check = 0;

	char *buff = datagram + sizeof(udp_head) + sizeof(ip_head);
	printf("Enter message to server: ");
	fgets(buff, BUF_SIZE, stdin);

	if (sendto(sockfd, datagram, 1024, 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	close(sockfd);

	return 0;
}
