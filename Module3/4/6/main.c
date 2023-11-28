#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "func.h"


int main(int argc, char *argv[])
{
	srand(time(0));

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <num>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("Couldn't create pipe!\n");
		exit(EXIT_FAILURE);
	}

	sem_t *semid[SEM_CNT];
	char *sem[] = { "readers", "writers" };
	for (int i = 0; i < SEM_CNT; i++)
	{
		semid[i] = sem_open(sem[i], O_CREAT, 0600, 0);
		if (semid[i] == SEM_FAILED)
			perror("sem_open\n");
	}

	pid_t pid = fork();
	int fd;
	switch(pid)
	{
		case -1:
		 perror("Fork error!\n");
		 exit(EXIT_FAILURE);

		case 0:
			pipectl_child(pipefd, atoi(argv[1]), semid);
			_exit(EXIT_SUCCESS);

		default:
			pipectl_parent(pipefd, atoi(argv[1]), semid);
			exit(EXIT_SUCCESS);
	}

	for (int i = 0; i < SEM_CNT; i++)
	{
		if (sem_close(semid[i]) == -1)
			perror(NULL);
		if (sem_unlink(sem[i]) == -1)
			perror(NULL);
	}
}
