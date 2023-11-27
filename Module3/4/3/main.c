#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include "func.h"

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct sem_info *__buf;
};

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

	int semid = semget(IPC_PRIVATE, 2, 0666 | IPC_CREAT);
	if (semid == -1)
		perror("Create sem!\n");

	union semun arg;
	arg.val = 0;
	semctl(semid, 0, SETVAL, arg);	// count of readers;
	semctl(semid, 1, SETVAL, arg);	// count of writers;

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
}
