#ifndef FUNC_H_
#define FUNC_H_

#define FILE_LEN 50
#define ARG_CON	 10
#define ARG_LEN  50

void clear_input();
void get_filename(char *fn);
void get_args(char args_str[], char *args_tok[]);
void execute(const char *pathname, char *const argv[]);

#endif
