#include <stdio.h>
#include "operations.h"

void div(void)
{
	float x, y;
	get_two_arg(&x, &y);
	if (y == 0)
		printf("ERROR: division by zero!\n\n");
	else
		printf("\t%.2f / %.2f = %.2f\n\n", x, y, x / y);
}
