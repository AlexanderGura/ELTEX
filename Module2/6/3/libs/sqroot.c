#include <stdio.h>
#include "operations.h"

void sqroot(void)
{
	float x;
	get_one_arg(&x);
	if (x < 0)
		printf("ERROR, sqrt's argument couldn't be negative!\n");
	else
		printf("\tsqrt(%.2f) = %.2f\n", x, sqrt(x));
}
