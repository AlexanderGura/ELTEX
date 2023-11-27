#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>
#include "func.h"

void close_fd(int fd)
{
	if (close(fd) == -1)
		perror("close_fd\n");
}

void pipectl_child(int *pipefd, int nums, sem_t *semid)
{
	close_fd(pipefd[0]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDONLY)) == -1)
		perror("open pipe!\n");

	int num;
	for (int i = 0; i < nums; i++)
	{
		num = rand() % 1000;
		write(pipefd[1], &num, sizeof(num));

		sleep(1);
		sem_wait(semid);
		read(fd, &num, sizeof(num));
		printf("from file: %d\n\n", num);
		sem_post(semid);
	}

	close_fd(fd);
	close_fd(pipefd[1]);
}

void pipectl_parent(int *pipefd, int nums, sem_t *semid)
{
	close_fd(pipefd[1]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDWR | O_CREAT, 0644)) == -1)
		perror("open pipe!\n");

	int num;
	for (int i = 0; i < nums; i++)
	{
		read(pipefd[0], &num, sizeof(num));

		sem_wait(semid);
		write(fd, &num, sizeof(num));
		printf("from pipe: %d\n", num);
		sem_post(semid);
	}

	close_fd(fd);
	close_fd(pipefd[0]);
}
