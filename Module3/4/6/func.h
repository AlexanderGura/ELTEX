#ifndef FUNC_H_
#define FUNC_H_

#include <semaphore.h>

#define PIPE_OUT "pipe_out.txt"
#define PROC_CNT 5
#define SEM_CNT  2

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct sem_info *__buf;
};

void close_fd(int);
void pipectl_child(int*, int, sem_t**);
void pipectl_parent(int*, int, sem_t**);

#endif
