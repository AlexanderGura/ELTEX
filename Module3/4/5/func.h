#ifndef FUNC_H_
#define FUNC_H_

#define PIPE_OUT "pipe_out.txt"

void close_fd(int);
void pipectl_child(int*, int, sem_t*);
void pipectl_parent(int*, int, sem_t*);

#endif
