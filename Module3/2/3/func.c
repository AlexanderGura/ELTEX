#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "func.h"

void clear_input()
{
	for (char c = getchar(); c != '\n'; c = getchar());
}

void create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Couldn't create pipe!\n");
		exit(EXIT_FAILURE);
	}
}

void close_fd(int file_d)
{
	if (close(file_d) == -1)
	{
		perror("Couln't close pipefd!\n");
		exit(EXIT_FAILURE);
	}
}

void get_input(char *input, char *filename[], char **arguments[])
{
	fgets(input, INPUT_LEN, stdin);
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	char *tmp[10];
	int j = 0;
	tmp[0] = strtok(input, "|");
	while (tmp[j] != NULL)
		tmp[++j] = strtok(NULL, "|");

	int index = 0;
	while (tmp[index] != NULL)
	{
		sscanf(tmp[index], "%s", filename[index]);

		arguments[index] = (char **) malloc(ARG_CON * ARG_LEN);
		arguments[index][0]  = strtok(tmp[index], " ");
		arguments[index][1] = strtok(NULL, " ");
		index++;
	}

}

void get_syspath(char *sp, const char *fp)
{
	strncpy(sp, "/usr/bin/", USRBIN);
	strncat(sp, fp, FILE_LEN - USRBIN);
}

void execute(const char **pathname, char **const argv[])
{
	//execv(pathname, argv);
	char syspath[FILE_LEN];
	if (argv[1] == NULL)
	{
		get_syspath(syspath, pathname[0]);
		if (execv(syspath, argv[0]) == -1)
		{
			fprintf(stderr, "Exec couldn't replace binary image!\n");
			exit(EXIT_FAILURE);
		}
	}
	int i = 0;
	int fst_pipefd[2];
	create_pipe(fst_pipefd);
	close_fd(fst_pipefd[0]);

	while (argv[i++] != NULL)
	{
		int pipefd[2];
		create_pipe(pipefd);
		dup2(pipefd[1], 1);
		dup2(pipefd[0], 0);

		get_syspath(syspath, pathname[i]);

		if (execv(syspath, argv[i]) == -1)
		{
			fprintf(stderr, "Exec couldn't replace binary image!\n");
			exit(EXIT_FAILURE);
		}
	}
}
