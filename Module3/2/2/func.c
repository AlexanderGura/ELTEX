#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "func.h"

void create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Couldn't create pipe!\n");
		exit(EXIT_FAILURE);
	}
}

void close_fd(int file_d)
{
	if (close(file_d) == -1)
	{
		perror("Couln't close pipefd!\n");
		exit(EXIT_FAILURE);
	}
}

void pipectl_child(int *fst_pipefd, int *snd_pipefd, int nums)
{
	close_fd(fst_pipefd[0]);
	close_fd(snd_pipefd[1]);

	int num;
	for (int i = 0; i < nums; i++)
	{
		num = rand() % 1000;
		write(fst_pipefd[1], &num, sizeof(num));
		read(snd_pipefd[0], &num, sizeof(num));
		printf("child - %d\n\n", num);
	}

	close_fd(fst_pipefd[1]);
	close_fd(snd_pipefd[0]);
}

void pipectl_parent(int *fst_pipefd, int *snd_pipefd, int nums)
{

	close_fd(fst_pipefd[1]);
	close_fd(snd_pipefd[0]);

	int fd;
	if ((fd = open(PIPE_OUT, O_RDWR | O_CREAT, 0644)) == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", PIPE_OUT);
		exit(EXIT_FAILURE);
	}

	int num, numx2;
	for (int i = 0; i < nums; i++)
	{
		read(fst_pipefd[0], &num, sizeof(num));
		numx2 = num * 2;
		write(fd, &num, sizeof(num));
		printf("parent - %d\n", num);
		write(snd_pipefd[1], &numx2, sizeof(num));
	}

	close_fd(fd);
	close_fd(fst_pipefd[0]);
	close_fd(snd_pipefd[1]);
}
