#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int ip_to_int(char* ip)
{
	int tokens[IP_DIGITS];
	int tmp;
	char* token = strtok(ip, ".");
	for (int i = 0; i < IP_DIGITS && token != NULL; i++)
	{
		tmp = atoi(token);
		tokens[IP_DIGITS - i - 1] = tmp;
		if (tmp > 256 && tmp < 0)
		{
			printf("Invalid ip!\n");
			return -1;
		}
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
