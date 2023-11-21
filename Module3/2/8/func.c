#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include "func.h"

int File_Access = 0; // 0 - disable; 1 - enable;

void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		fprintf(stderr, "Couldn't close fd!\n");
		exit(EXIT_FAILURE);
	}
}

void handler_usr(int sig)
{
	File_Access = (sig == SIGUSR1) ? 0 : 1;
}

void pipectl_child(int *pipefd, int nums)
{
	close_fd(pipefd[0]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDONLY)) == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", PIPE_OUT);
		_exit(EXIT_FAILURE);
	}

	int num;
	for (int i = 0; i < nums; i++)
	{
		num = rand() % 1000;
		write(pipefd[1], &num, sizeof(num));
		sleep(1);	// delay;
		while (File_Access != 1)
			sleep(1);
		read(fd, &num, sizeof(num));
		printf("from file: %d\n", num);
	}

	close_fd(fd);
	close_fd(pipefd[1]);
}

void pipectl_parent(int *pipefd, int nums)
{
	close_fd(pipefd[1]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDWR | O_CREAT, 0644)) == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", PIPE_OUT);
		exit(EXIT_FAILURE);
	}

	int num;
	for (int i = 0; i < nums; i++)
	{
		read(pipefd[0], &num, sizeof(num));
		kill(0, SIGUSR1);
		sleep(1);	// delay;
		write(fd, &num, sizeof(num));
		kill(0, SIGUSR2);
		printf("%d\n", num);
	}

	close_fd(fd);
	close_fd(pipefd[0]);
}
