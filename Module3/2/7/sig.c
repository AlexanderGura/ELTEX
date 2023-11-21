#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void handler(int sig)
{
	if (sig == SIGINT)
		printf("signal - SIGINT(2)\n");
	else if (sig == SIGQUIT)
		printf("signal - SIGQUIT(3)\n");
}

int main()
{
	int fd = open("signal.txt", O_RDWR | O_CREAT, 0664);
	if (fd == -1)
	{
		fprintf(stderr, "Couln't open file!\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGINT, handler) == SIG_ERR)
		exit(EXIT_FAILURE);

	if (signal(SIGQUIT, handler) == SIG_ERR)
		exit(EXIT_FAILURE);

	int count = 1;
	while (1)
	{
		if (write(fd, &count, sizeof(count)) == -1)
			exit(EXIT_FAILURE);
		count++;
		sleep(1);
	}

	if (close(fd) == -1)
	{
		fprintf(stderr, "Couln't close file!\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
