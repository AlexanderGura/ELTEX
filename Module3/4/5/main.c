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
		perror(NULL);

	sem_t *semid = sem_open("sem", O_CREAT, 0666, 1);
	if (semid == SEM_FAILED)
		perror("Create sem!\n");

	pid_t pid = fork();
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

	if (sem_close(semid) == -1)
		perror("sem_close\n");
	if (sem_unlink("sem") == -1)
		perror("sem_unlink\n");
}

