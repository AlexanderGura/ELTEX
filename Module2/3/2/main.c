#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IP_DIGITS 4

int ip_to_array(char*);

int main(int args, char* argv[])
{
	srand(time(0));
	int range = 0xffffffff;
	int count_own = 0;
	int count_other = 0;

	int ip_sluice;
	int mask;
	ip_sluice = ip_to_array(argv[1]);
	mask = ip_to_array(argv[2]);

	int pack_num = atoi(argv[3]);
	int ip_dst = 0x0;
	for (int i = 0; i < pack_num; i++)
	{
		int ip_dst = rand();
		int result = (ip_sluice & mask) ^ (ip_dst & mask);
		(result == 0) ? count_own++ : count_other++;
	}
	double perc_own = (count_own * 100 / pack_num);
	double perc_other = (count_other * 100 / pack_num);
	printf("Count own - %d\n", count_own);
	printf("Percent own packs - %lf\n", perc_own);
	printf("Count other - %d\n", count_other);
	printf("Percent other packs - %lf\n", perc_other);
}

int ip_to_array(char* ip)
{
	int tokens[IP_DIGITS];
	char* token = strtok(ip, ".");
	for (int i = 0; i < IP_DIGITS && token != NULL; i++)
	{
		tokens[IP_DIGITS - i - 1] = atoi(token);
		token = strtok(NULL, ".");
	}

	int result = 0;
	int index = 0;
	for (int i = 0; i < IP_DIGITS; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			result |= ((tokens[i] % 2) << index++);
			tokens[i] /= 2;
		}
	}
	return result;
}
