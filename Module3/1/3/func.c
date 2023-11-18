#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "func.h"

void clear_input()
{
	for (char c = getchar(); c != '\n'; c = getchar());
}

void get_input(char *input, char *filename, char *arguments[])
{
	fgets(input, INPUT_LEN, stdin);
	sscanf(input, "%s", filename);
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	arguments[0]  = strtok(input, " ");
	for (int i = 1; i < ARG_CON; i ++)
		arguments[i] = strtok(NULL, " ");
}

void execute(const char *pathname, char *const argv[])
{
	if (execv(pathname, argv) == -1)
	{
		fprintf(stderr, "Exec couldn't replace binary image!\n");
		exit(EXIT_FAILURE);
	}
}
