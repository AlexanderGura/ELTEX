#ifndef FUNC_H_
#define FUNC_H_

#define OPC_COUNT 4

#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct sem_info *__buf;
};

void hand_sigint(int);
int min(int*, int);
int max(int*, int);
int sum(int*, int);
int avr(int*, int);
void child(int semid, int *array, int array_len, int nop);

#endif
