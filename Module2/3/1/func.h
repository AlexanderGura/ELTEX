#ifndef FUNC_H_
#define FUNC_H_

#define LEN_FILE   30
#define LEN_CHMOD  20
#define LEN_BITS   10
#define LEN_DIGITS  3

static void clear_input();
static int select_choice(char);
static int enter_alph_format(char *);
static int enter_dig_format(int *);

int menu();
int alph_mode_to_bin(char*);
int digit_mode_to_bin(int);
int get_stat(char *filename);
void set_stat();

void print_bin(int);
void print_alph(int);
void print_digit(int);


#endif
