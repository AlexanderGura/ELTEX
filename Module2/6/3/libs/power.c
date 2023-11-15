#include <stdio.h>
#include "operations.h"

void power(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("\t%.2f^%.2f = %.2f\n\n", x, y, pow(x, y));
}
