#ifndef FUNC_H_
#define FUNC_H_

#define PIPE_OUT "pipe_out.txt"
#define PROC_CNT 5

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct sem_info *__buf;
};

void close_fd(int);
void pipectl_child(int*, int, int);
void pipectl_parent(int*, int, int);

#endif
