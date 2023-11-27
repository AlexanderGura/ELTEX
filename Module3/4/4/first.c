#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage %s <num>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const int sem_count = 3;
	char *semph[] = {
		"mutex",
		"empty",
		"full"
	};
	sem_t *semid[sem_count];
	semid[0] = sem_open(semph[0], O_CREAT, 0600, 1);
	semid[1] = sem_open(semph[1], O_CREAT, 0600, atoi(argv[1]));
	semid[2] = sem_open(semph[2], O_CREAT, 0600, 0);
	for (int i = 0; i < sem_count; i++)
	{
		if (semid[i] == SEM_FAILED)
			perror(NULL);
	}

	const char *fifoname = "/tmp/fifo1";
	unlink(fifoname);
	if (mkfifo(fifoname, O_CREAT | O_RDWR | 0664) == -1)
	{
		fprintf(stderr, "Couldn't create %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	int fifo_fd = open(fifoname, O_WRONLY,  O_NONBLOCK);
	if (fifo_fd == -1)
		perror(NULL);

	int num;
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		sem_wait(semid[0]);
		num = rand() % 10000;
		if (write(fifo_fd, &num, sizeof(num)) == -1)
			perror(NULL);
		sem_wait(semid[1]);
		sem_post(semid[2]);
		sem_post(semid[0]);
	}

	if (close(fifo_fd) == -1)
		perror(NULL);

	for (int i = 0; i < sem_count; i++)
	{
		if (sem_close(semid[i]) == -1)
			perror(NULL);
	}

	return 0;
}
