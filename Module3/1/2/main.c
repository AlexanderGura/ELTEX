#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	int tmp;
	switch(pid)
	{
		case -1:
			printf("Error\n");
			exit(EXIT_FAILURE);
		case 0:
			printf("\nI'm a child(%d)!\n", getpid());
			for (int i = argc / 2 + 1; i < argc; i++)
			{
				tmp = atoi(argv[i]);
				printf("%d: %d\n", i, tmp * tmp);
			}
			exit(EXIT_SUCCESS);
		default:
			printf("\nI'm a parent(%d)!\n", getpid());
			for (int i = 1; i <= argc / 2; i++)
			{
				tmp = atoi(argv[i]);
				printf("%d: %d\n", i, tmp * tmp);
			}
			exit(EXIT_SUCCESS);
	}
}
