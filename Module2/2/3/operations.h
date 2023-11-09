#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#define OPERATIONS_NUM 7

static void clear_input(void);
static void (*select(char choice))(void);

int menu(void);
void get_one_arg(float *);
void get_two_arg(float*, float*);
void add(void);
void sub(void);
void mult(void);
void div(void);
void power(void);
void sqroot(void);
void natlog(void);

#endif
