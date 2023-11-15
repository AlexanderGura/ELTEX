#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#define ADD_SYM 14

static void clear_input(void);
static char* prepare_path(const char *);
static void clear_path(char *);
static void get_function(const char *);
static int select_choice(char choice);

int menu(void);

#endif
