#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <time.h>
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
	const char * fifoname = "/tmp/fifo1";
	key_t key = ftok(fifoname, 1313);
	int semid = semget(key, 3, 0600); // 0 - mutex, 1 - empty, 2 - full
	printf("%d\n", semid);

	struct sembuf lock = {0, -1, 0};
	struct sembuf pop[2] = { {2, 1, IPC_NOWAIT}, {1, 1, IPC_NOWAIT}};
	struct sembuf unlock = {0, 1, 0};

	int fifo_fd = open(fifoname, O_RDONLY | O_NONBLOCK);
	if (fifo_fd == -1)
	{
		fprintf(stderr, "Couldn't open %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	int num;
	while (1)
	{
		semop(semid, &lock, 1);
 		semop(semid, pop, 2);
		if (read(fifo_fd, &num, sizeof(num)) < 0)
			exit(EXIT_FAILURE);
		printf("FIFO: %d\n", num);
 		semop(semid, &unlock, 1);
	}

	if (close(fifo_fd) == -1)
	{
		fprintf(stderr, "Couldn't close %s!\n", fifoname);
		exit(EXIT_FAILURE);
	}

	semctl(semid, 0, IPC_RMID);

	return 0;
}
