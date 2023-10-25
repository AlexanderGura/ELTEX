#include <stdio.h>
#include "operations.h"

void add(int x, int y)
{
	printf("%d + %d = %d\n", x, y, x + y);
}

void sub(int x, int y)
{
	printf("%d - %d = %d\n", x, y, x - y);
}

void mult(int x, int y)
{
	printf("%d * %d = %d\n", x, y, x * y);
}

void div(int x, int y)
{
	printf("%d / %d = %d\n", x, y, x / y);
}
