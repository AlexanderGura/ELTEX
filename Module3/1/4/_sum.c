#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int result = 0;
	int temp;
	for (int i = 0; i < argc; i++)
	{
		temp = atoi(argv[i]);
		if (temp != 0)
			result += temp;
	}
	printf("Sum is %d\n", result);
	return 0;
}
