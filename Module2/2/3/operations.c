#include <stdio.h>
#include <math.h>
#include "operations.h"

void get_one_arg(float* num)
{
	printf("Enter the number: ");
	scanf("%f", num);
	getchar();
}

void get_two_arg(float* first, float* second)
{
	printf("Enter the first number: ");
	scanf("%f", first);
	getchar();

	printf("Enter the second number: ");
	scanf("%f", second);
	getchar();
}

void add(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("%.2f + %.2f = %.2f\n", x, y, x + y);
}
void sub(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("%.2f - %.2f = %.2f\n", x, y, x - y);
}

void mult(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("%.2f * %.2f = %.2f\n", x, y, x * y);
}

void div(void)
{
	float x, y;
	get_two_arg(&x, &y);
	if (y == 0)
		printf("ERROR: division by zero!\n");
	else
		printf("%.2f / %.2f = %.2f\n", x, y, x / y);
}

void power(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("%.2f^%.2f = %.2f\n", x, y, pow(x, y));
}

void sqroot(void)
{
	float x;
	get_one_arg(&x);
	if (x < 0)
		printf("ERROR, sqrt's argument couldn't be negative!\n");
	else
		printf("sqrt(%.2f) = %.2f\n", x, sqrt(x));
}


void natlog(void)
{
	float x;
	get_one_arg(&x);
	if (x < 0)
		printf("ERROR, ln's argument couldn't be negative!\n");
	else
		printf("ln(%.2f) = %.2f\n", x, log(x));
}
