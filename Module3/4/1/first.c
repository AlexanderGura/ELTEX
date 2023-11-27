#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct sem_info *__buf;
};

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage %s <num>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char * fifoname = "/tmp/fifo1";
	key_t key = ftok(fifoname, 1313);
	int semid = semget(key, 3, 0666 | IPC_CREAT); // 0 - mutex, 1 - empty, 2 - full
	printf("%d\n", semid);

	union semun arg;
	unsigned short args[3] = {1, atoi(argv[1]), 0};
	arg.array = args;
	semctl(semid, 0, SETALL, arg);

	struct sembuf lock = {0, -1, 0};
	struct sembuf push[2] = { {2, 1, IPC_NOWAIT}, {1, -1, IPC_NOWAIT} };
	struct sembuf unlock = {0, 1, 0};

	unlink(fifoname);
	if (mkfifo(fifoname, O_CREAT | O_RDWR | 0664) == -1)
	{
		fprintf(stderr, "Couldn't create %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	int fifo_fd = open(fifoname, O_WRONLY,  O_NONBLOCK);
	if (fifo_fd == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	int num;
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		semop(semid, &lock, 1);
		num = rand() % 10000;
		if (write(fifo_fd, &num, sizeof(num)) == -1)
			exit(EXIT_FAILURE);
		semop(semid, push, 2);
		semop(semid, &unlock, 1);
	}

	if (close(fifo_fd) == -1)
	{
		fprintf(stderr, "Couldn't close %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	return 0;
}
