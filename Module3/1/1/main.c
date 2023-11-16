#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void goodbye(void)
{
	printf("See you later! Bye...\n");
}

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	int state = atexit(goodbye);
	if (state != 0)
	{
		fprintf(stderr, "cannot set exit function!\n");
		exit(EXIT_FAILURE);
	}

	switch(pid)
	{
		case -1:
			printf("Error\n");
			exit(EXIT_FAILURE);
		case 0:
			printf("\nI'm a child(%d)!\n", getpid());
			for (int i = 1; i < argc; i++)
				printf("%d: %s\n", i, argv[i]);
			exit(EXIT_SUCCESS);
		default:
			printf("\nI'm a parent(%d)!\n", getpid());
			for (int i = 1; i < argc; i++)
				printf("%d: %s\n", i, argv[i]);
			exit(EXIT_SUCCESS);
	}
}
