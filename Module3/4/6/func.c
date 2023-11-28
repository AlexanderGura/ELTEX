#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <semaphore.h>
#include <signal.h>
#include "func.h"

void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		fprintf(stderr, "Couldn't close fd!\n");
		exit(EXIT_FAILURE);
	}
}

void pipectl_child(int *pipefd, int nums, sem_t** semid)
{
	close_fd(pipefd[0]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDONLY)) == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", PIPE_OUT);
		_exit(EXIT_FAILURE);
	}

	int num;
	int value;
	for (int i = 0; i < nums; i++)
	{
		num = rand() % 1000;
		write(pipefd[1], &num, sizeof(num));

		while (1)
		{
			sleep(1);
			sem_getvalue(semid[0], &value);
			if (value != PROC_CNT)
				break;
		}
		sem_post(semid[0]);
		read(fd, &num, sizeof(num));
		printf("from file: %d\n", num);
		sem_wait(semid[0]);
	}

	close_fd(fd);
	close_fd(pipefd[1]);
}

void pipectl_parent(int *pipefd, int nums, sem_t **semid)
{
	close_fd(pipefd[1]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDWR | O_CREAT, 0644)) == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", PIPE_OUT);
		exit(EXIT_FAILURE);
	}

	int num;
	int value;
	for (int i = 0; i < nums; i++)
	{
		read(pipefd[0], &num, sizeof(num));

		while (1)
		{
			sem_getvalue(semid[0], &value);
			if (value == 0)
				break;
			sleep(1);
		}

		sem_post(semid[1]);
		write(fd, &num, sizeof(num));
		printf("\nfrom pipe: %d\n", num);
		sem_wait(semid[1]);
	}
	sleep(1);	// delay before end;

	close_fd(fd);
	close_fd(pipefd[0]);
}
