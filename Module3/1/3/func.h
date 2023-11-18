#ifndef FUNC_H_
#define FUNC_H_

#define USRBIN    10
#define INPUT_LEN 50
#define FILE_LEN  20
#define ARG_CON	  10
#define ARG_LEN   50

void clear_input();
void get_input(char *input, char *filename, char *arguments[]);
void execute(const char *pathname, char *const argv[]);

#endif
