#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "func.h"

void clear_input()
{
	for (char c = getchar(); c != '\n'; c = getchar());
}

void get_filename(char *fn)
{
	printf("Enter the filename: ");
	fgets(fn, FILE_LEN, stdin);
	sscanf(fn, "%s", fn);
}

void get_args(char args_str[], char *args_tok[])
{
	printf("Enter arguments: ");
	fgets(args_str, ARG_LEN, stdin);

	args_tok[0] = strtok(args_str, " ");
	for (int i = 1; i < ARG_CON; i ++)
		args_tok[i] = strtok(NULL, " ");

}

void execute(const char *pathname, char *const argv[])
{
	if (execv(pathname, argv) == -1)
	{
		fprintf(stderr, "Exec couldn't replace binary image!\n");
		exit(EXIT_FAILURE);
	}
}
