#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
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

void child(int semid, int *array, int array_len, int nop)
{
	while (is_active)
	{	sleep(1);
		semop(semid, &lock, 1);

		array[array_len + nop] = operations[nop](array, array_len);

		semop(semid, unlock, 2);
	}
	if (shmdt(array) == -1)
		perror("shmdt\n");
	_exit(EXIT_SUCCESS);
}
