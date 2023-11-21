#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
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


	pid_t pid = fork();
	int num;
	if (signal(SIGUSR1, handler_usr1) == SIG_ERR)
		exit(EXIT_FAILURE);

	if (signal(SIGUSR2, handler_usr2) == SIG_ERR)
		exit(EXIT_FAILURE);

	switch(pid)
	{
		case -1:
		 perror("Fork error!\n");
		 exit(EXIT_FAILURE);

		case 0:
			pipectl_child(pipefd, atoi(argv[1]));
			_exit(EXIT_SUCCESS);

		default:
			pipectl_parent(pipefd, atoi(argv[1]));
			exit(EXIT_SUCCESS);
	}
}
