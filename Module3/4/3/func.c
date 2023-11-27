#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>
#include "func.h"

static struct sembuf join[2] = {{1, 0, 0}, {0, 1, 0}};
static struct sembuf disconnect = {0, -1, 0};
static struct sembuf start_write[2] = {{0, 0, 0}, {0, 1, 0}};
static struct sembuf end_write = {0, -1, 0};

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
	union semun arg;
	for (int i = 0; i < nums; i++)
	{
		num = rand() % 1000;
		write(pipefd[1], &num, sizeof(num));

		while (1)
		{
			sleep(1);
			semctl(semid, 0, GETVAL, arg);
			if (arg.val != PROC_CNT)
				break;
		}
		semop(semid, join, 2);
		read(fd, &num, sizeof(num));
		printf("from file: %d\n", num);
		semop(semid, &disconnect, 1);
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

		semop(semid, start_write, 2);
		write(fd, &num, sizeof(num));
		printf("\nfrom pipe: %d\n", num);
		semop(semid, &end_write, 1);
	}
	sleep(3);	// delay before end;

	close_fd(fd);
	close_fd(pipefd[0]);
}
