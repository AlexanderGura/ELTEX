#include <stdio.h>
#include <string.h>
#include "func.h"

int main(int argc, char *argv[])
{
	char dirname[20];

	while (1)
	{
		printf("\nEnter 'q' to quit!\n");
		get_dirname(dirname);
		if (strcmp(dirname, "q") == 0)
		{
			printf("Good bye!\n");
			break;
		}

		check_dir(dirname, 0);
	}
	return 0;
}
