#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "func.h"

int (*operations[])(int *, int) = {min, max, sum, avr};
int is_active = 1;
struct sembuf lock = {0, -1, 0};
struct sembuf unlock[2] = { {0, 0, 0}, {0, 1, 0} };

void hand_sigint(int sig)
{
	is_active = 0;
}

int max(int *array, int count)
{
	int tmp = array[0];
	for (int i = 1; i < count; i++)
	{
		if (array[i] > tmp)
			tmp = array[i];
	}
	return tmp;
}

int min(int *array, int count)
{
	int tmp = array[0];
	for (int i = 1; i < count; i++)
	{
		if (array[i] < tmp)
			tmp = array[i];
	}
	return tmp;
}

int sum(int *array, int count)
{
	int tmp = array[0];
	for (int i = 1; i < count; i++)
		tmp += array[i];
	return tmp;
}

int avr(int *array, int count)
{
	int tmp = array[0];
	for (int i = 1; i < count; i++)
		tmp += array[i];
	return tmp / count;
}

void child(sem_t *semid, int *array, int array_len, int nop)
{
	while (is_active)
	{	sleep(1);
		sem_wait(semid);

		array[array_len + nop] = operations[nop](array, array_len);

		sem_post(semid);
	}
	if (munmap(semid, (array_len + OPC_COUNT) * sizeof(int)) == -1)
		perror("munmap\n");
	_exit(EXIT_SUCCESS);
}
