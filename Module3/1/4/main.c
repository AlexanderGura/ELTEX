#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "func.h"

int main(int argc, char *argv[])
{
	int rv;
	char filename[FILE_LEN];
	char *arguments[ARG_CON];
	char input[INPUT_LEN];


	printf("Enter 'q' to quit!\n#");
	get_input(input, filename, arguments);
	while (input[0] != 'q')
	{
		pid_t pid = fork();
		switch(pid)
		{
			case -1:
			 fprintf(stderr, "Couldn't get child process!\n");
			 exit(EXIT_FAILURE);
			 break;

			case 0:
			 execute(filename, arguments);
			 exit(EXIT_SUCCESS);
			 break;

			default:
			 wait(&rv);
			 break;
		}
		printf("#");
		get_input(input, filename, arguments);
	}
	exit(EXIT_SUCCESS);
}
