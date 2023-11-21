#ifndef FUNC_H_
#define FUNC_H_

#define PIPE_OUT "pipe_out.txt"

void close_fd(int);
void handler_usr(int);
void pipectl_child(int*, int);
void pipectl_parent(int*, int);

#endif
