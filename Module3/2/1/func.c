#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "func.h"

void pipectl_child(int *pipefd, int nums)
{
	if (close(pipefd[0]) == -1)
	{
		perror("Couln't close pipefd!\n");
		_exit(EXIT_FAILURE);
	}

	int num;
	for (int i = 0; i < nums; i++)
	{
		num = rand() % 1000;
		write(pipefd[1], &num, sizeof(num));
	}

	if (close(pipefd[1]) == -1)
	{
		perror("Couldn't close pipefd!\n");
		_exit(EXIT_FAILURE);
	}
}

void pipectl_parent(int *pipefd, int nums)
{
	if (close(pipefd[1]) == -1)
	{
		perror("Couln't close pipefd!\n");
		exit(EXIT_FAILURE);
	}

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
		write(fd, &num, sizeof(num));
		printf("%d\n", num);
	}

	if (close(fd) == -1)
	{
		perror("Couldn't close fd!\n");
		exit(EXIT_FAILURE);
	}

	if (close(pipefd[0]) == -1)
	{
		perror("Couldn't close pipefd!\n");
		exit(EXIT_FAILURE);
	}
}
