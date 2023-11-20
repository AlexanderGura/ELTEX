#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage %s <num>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	srand(time(0));

	const char * fifoname = "/tmp/fifo1";
	unlink(fifoname);

	if (mkfifo(fifoname, O_RDWR | 0664) == -1)
	{
		fprintf(stderr, "Couldn't create %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	int fifo_fd = open(fifoname, O_WRONLY);
	if (fifo_fd == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	int num;
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		num = rand() % 10000;
		if (write(fifo_fd, &num, sizeof(num)) == -1)
			exit(EXIT_FAILURE);
	}

	if (close(fifo_fd) == -1)
	{
		fprintf(stderr, "Couldn't close %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	return 0;
}
