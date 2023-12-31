#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int count = 0;

void handler(int sig)
{
	if (++count == 3)
		exit(EXIT_SUCCESS);
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

	int cnt = 1;
	while (1)
	{
		if (write(fd, &cnt, sizeof(cnt)) == -1)
			exit(EXIT_FAILURE);
		cnt++;
		sleep(1);
	}

	if (close(fd) == -1)
	{
		fprintf(stderr, "Couln't close file!\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
