#ifndef FUNC_H_
#define FUNC_H_

#define PIPE_OUT "pipe_out.txt"

void create_pipe(int *);
void close_fd(int);
void pipectl_child(int*, int*, int);
void pipectl_parent(int*, int*, int);

#endif
