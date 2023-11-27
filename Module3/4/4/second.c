#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	const int sem_count = 3;
	char *semph[] = {
		"mutex",
		"empty",
		"full"
	};
	sem_t *semid[sem_count];
	for (int i = 0; i < sem_count; i++)
	{
		semid[i] = sem_open(semph[i], O_RDWR);
		if (semid[i] == SEM_FAILED)
			perror(NULL);
	}

	const char *fifoname = "/tmp/fifo1";
	int fifo_fd = open(fifoname, O_RDONLY | O_NONBLOCK);
	if (fifo_fd == -1)
		perror(NULL);

	int num;
	unsigned int value;
	sleep(1);
	while (1)
	{
		sem_getvalue(semid[2], &value);
		if (value == 0)
			break;

		sem_wait(semid[0]);
		if (read(fifo_fd, &num, sizeof(num)) < 0)
			perror(NULL);
		printf("FIFO: %d\n", num);
		sem_post(semid[1]);
		sem_wait(semid[2]);
 		sem_post(semid[0]);
	}

	if (close(fifo_fd) == -1)
		perror(NULL);

	for (int i = 0; i < sem_count; i++)
	{
		if (sem_close(semid[i]) == -1)
			perror(NULL);
		if (sem_unlink(semph[i]) == -1)
			perror(NULL);
	}

	return 0;
}
