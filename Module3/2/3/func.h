#ifndef FUNC_H_
#define FUNC_H_

#define USRBIN    10
#define INPUT_LEN 50
#define FILE_LEN  20
#define ARG_CON	   2
#define ARG_LEN   50

void create_pipe(int *);
void close_fd(int);
void clear_input();
void get_input(char *input, char *filename[], char **arguments[]);
void get_syspath(char *sp, const char *fp);
void execute(const char **pathname, char **const argv[]);

#endif
