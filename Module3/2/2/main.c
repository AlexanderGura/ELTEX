#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "func.h"

int main(int argc, char *argv[])
{
	srand(time(0));

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <num>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int fst_pipefd[2];
	int snd_pipefd[2];
	create_pipe(fst_pipefd);
	create_pipe(snd_pipefd);

	pid_t pid = fork();
	int num;
	switch(pid)
	{
		case -1:
		 perror("Fork error!\n");
		 exit(EXIT_FAILURE);

		case 0:
		 pipectl_child(fst_pipefd, snd_pipefd, atoi(argv[1]));
		 _exit(EXIT_SUCCESS);

		default:
		 pipectl_parent(fst_pipefd, snd_pipefd, atoi(argv[1]));
		 exit(EXIT_SUCCESS);
	}
}
