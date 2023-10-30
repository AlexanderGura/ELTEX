#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int args, char* argv[])
{
	srand(time(0));
	int range = 0xffffffff;

	char* IP_sluice = argv[1];
	char* mask = argv[2];
	int pack_num = atoi(argv[3]);
	for (int i = 0; i < pack_num; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%d.", rand() % 256);
		printf("\n");
	}
}
