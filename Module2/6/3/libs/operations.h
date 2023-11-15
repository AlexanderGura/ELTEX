#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <stdio.h>
#include <math.h>

void clear_input(void)
{
	for (char c = getchar(); c != '\n'; c = getchar());
}

void get_one_arg(float* num)
{
	printf("Enter the number: ");
	scanf("%f", num);
	clear_input();
}

void get_two_arg(float* first, float* second)
{
	printf("Enter the first number: ");
	scanf("%f", first);
	clear_input();

	printf("Enter the second number: ");
	scanf("%f", second);
	clear_input();
}

#endif
