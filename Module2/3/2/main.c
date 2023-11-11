#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Program needs 4 params!\n");
		exit(EXIT_FAILURE);
	}

	srand(time(0));
	int range = 0xffffffff;
	int count_own = 0;
	int count_other = 0;

	int ip_sluice = ip_to_int(argv[1]);
	if (ip_sluice == -1)
		exit(EXIT_FAILURE);

	int mask = ip_to_int(argv[2]);
	if (ip_sluice == -1)
		exit(EXIT_FAILURE);

	int pack_num = atoi(argv[3]);
	int ip_dst = 0x0;
	for (int i = 0; i < pack_num; i++)
	{
		int ip_dst = rand();
		int result = (ip_sluice & mask) ^ (ip_dst & mask);
		(result == 0) ? count_own++ : count_other++;
	}

	float perc_own = (count_own * 100.00) / pack_num;
	float perc_other = (count_other * 100.00) / pack_num;
	printf("Count own - %d%%\n", count_own);
	printf("Percent own packs - %lf%%\n", perc_own);
	printf("Count other - %d\n", count_other);
	printf("Percent other packs - %lf%%\n", perc_other);

	exit(EXIT_SUCCESS);
}
