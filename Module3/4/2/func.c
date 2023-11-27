#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>
#include "func.h"

static struct sembuf lock = {0, -1, 0};
static struct sembuf unlock[2] = {{0, 0, 0}, {0, 1, 0}};

void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		fprintf(stderr, "Couldn't close fd!\n");
		exit(EXIT_FAILURE);
	}
}

void pipectl_child(int *pipefd, int nums, int semid)
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

		sleep(1);
		semop(semid, &lock, 1);
		read(fd, &num, sizeof(num));
		printf("from file: %d\n", num);
		semop(semid, unlock, 2);
	}

	close_fd(fd);
	close_fd(pipefd[1]);
}

void pipectl_parent(int *pipefd, int nums, int semid)
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

		semop(semid, &lock, 1);
		write(fd, &num, sizeof(num));
		printf("\nfrom pipe: %d\n", num);
		semop(semid, unlock, 2);
	}

	close_fd(fd);
	close_fd(pipefd[0]);
}
