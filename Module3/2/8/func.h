#ifndef FUNC_H_
#define FUNC_H_

#define PIPE_OUT "pipe_out.txt"

void handler_usr1(int);
void handler_usr2(int);
void pipectl_child(int*, int);
void pipectl_parent(int*, int);

#endif
