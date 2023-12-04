#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUF_SIZE 512

int is_active = 1;

void error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void print_package(char *buff)
{
	static int count = 0;
	short tmp;
	struct in_addr ip;

	bcopy(&buff[12], &ip.s_addr, 4);
	char *ip_dst = inet_ntoa(ip);
	bcopy(&buff[16], &ip.s_addr, 4);
	char *ip_src = inet_ntoa(ip);

	printf("Package #%d:\n", ++count);

	printf("\nIP Package:\n");
	printf("Version: %d\n", buff[0] >> 4);
	printf("Size: %d\n", (buff[0] & 15) * 4);
	printf("DSCP: %d\n", buff[1] >> 6);
	printf("ECN: %d\n", buff[1] & 3);
	bcopy(&buff[2], &tmp, 2);
	printf("Length: %d\n", ntohs(tmp));
	bcopy(&buff[4], &tmp, 2);
	printf("ID: %d\n", ntohs(tmp));
	bcopy(&buff[6], &tmp, 2);
	printf("Flags: %d\n", tmp & 0xE000);
	printf("Offset: %d\n", tmp & 0x1FFF);
	printf("TTL: %d\n", buff[8]);
	printf("Protocol: %d\n", buff[9]);
	bcopy(&buff[10], &tmp, 2);
	printf("Checksum: %d\n", ntohs(tmp));

	printf("IP dest: %s\n", ip_dst);
	printf("IP source: %s\n", ip_src);

	printf("\nUDP Package:\n");
	bcopy(&buff[20], &tmp, 2);
	printf("Port dest: %d\n", ntohs(tmp));
	bcopy(&buff[22], &tmp, 2);
	printf("Port source: %d\n", ntohs(tmp));
	bcopy(&buff[24], &tmp, 2);
	printf("Length of datagram: %d\n", ntohs(tmp));
	bcopy(&buff[26], &tmp, 2);
	printf("Checksum: %d\n", ntohs(tmp));

	printf("\nData: %s\n", &buff[28]);
}

int main()
{
	char buff[BUF_SIZE];
	int rawfd;
	rawfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (rawfd == -1)
		error("socket");

	struct sockaddr_in socket_addr;
	bzero(&socket_addr, sizeof(socket_addr));
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(51111);
	socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(rawfd, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) < 0)
	{
		close(rawfd);
		error("bind");
	}

	int fd = open("sniff.bin", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		error("open");

	while (is_active)
	{
		if (recv(rawfd, buff, BUF_SIZE, 0) < 0)
		{
			close(rawfd);
			error("recvfrom");
		}
		print_package(buff);

		if (write(fd, buff, strlen(buff)) < 0)
			error("write");
	}


	if (close(fd) == -1)
		error("close");

	if (close(rawfd) == -1)
		error("close");

	return 0;
}
