#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include "func.h"

volatile int File_Access = 0;

void handler_usr1(int sig)
{
	File_Access = 0;
}

void handler_usr2(int sig)
{
	File_Access = 1;
}

void pipectl_child(int *pipefd, int nums)
{
	if (close(pipefd[0]) == -1)
	{
		perror("Couln't close pipefd!\n");
		_exit(EXIT_FAILURE);
	}

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

	if (close(fd) == -1)
	{
		perror("Couldn't close fd!\n");
		_exit(EXIT_FAILURE);
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
		kill(0, SIGUSR1);
		sleep(1);	// delay;
		write(fd, &num, sizeof(num));
		kill(0, SIGUSR2);
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
