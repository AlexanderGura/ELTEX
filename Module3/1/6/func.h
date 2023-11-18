#ifndef FUNC_H_
#define FUNC_H_

#include <dirent.h>

#define DIR_LEN 20

void get_dirname(char *);
void check_dir(const char*, int);
void check_type(struct dirent *, int);

#endif

