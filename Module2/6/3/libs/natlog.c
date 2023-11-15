#include <stdio.h>
#include "operations.h"

void natlog(void)
{
	float x;
	get_one_arg(&x);
	if (x < 0)
		printf("ERROR, ln's argument couldn't be negative!\n\n");
	else
		printf("\tln(%.2f) = %.2f\n\n", x, log(x));
}
