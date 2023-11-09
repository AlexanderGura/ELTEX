#include <stdio.h>
#include <math.h>
#include "operations.h"

static void clear_input(void)
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

static void (*select(char choice))()
{
	switch(choice)
	{
		case '1':
		case '+':
			return add;
		case '2':
		case '-':
			return sub;
		case '3':
		case '*':
			return mult;
		case '4':
		case '/':
			return div;
		case '5':
		case '^':
			return power;
		case '6':
		case 'r':
			return sqroot;
		case '7':
		case 'l':
			return natlog;
		case '0':
		case 'q':
		case 'Q':
			printf("Good bye, have a good day!\n");
			return NULL;
		default:
			printf("Invalid choice!\n");
			return NULL;
		}
}

int menu()
{
	printf("\nEnter '0' or 'q' to end the calc!\n");
	printf("Enter the number of operation:\n");
	printf("1(+). +\n2(-). -\n3(*). *\n4(/). /\n");
	printf("5(^). power\n6(r). sqrt\n7(l). ln\n");
	printf("Your choice: ");

	char choice;
	choice = getchar();
	clear_input();

	void (*operation)(void) = select(choice);
	if (operation == NULL)
		return 0;

	operation();
	return 1;
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

void add(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("\t%.2f + %.2f = %.2f\n\n", x, y, x + y);
}
void sub(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("\t%.2f - %.2f = %.2f\n\n", x, y, x - y);
}

void mult(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("\t%.2f * %.2f = %.2f\n\n", x, y, x * y);
}

void div(void)
{
	float x, y;
	get_two_arg(&x, &y);
	if (y == 0)
		printf("ERROR: division by zero!\n\n");
	else
		printf("\t%.2f / %.2f = %.2f\n\n", x, y, x / y);
}

void power(void)
{
	float x, y;
	get_two_arg(&x, &y);
	printf("\t%.2f^%.2f = %.2f\n\n", x, y, pow(x, y));
}

void sqroot(void)
{
	float x;
	get_one_arg(&x);
	if (x < 0)
		printf("ERROR, sqrt's argument couldn't be negative!\n");
	else
		printf("\tsqrt(%.2f) = %.2f\n", x, sqrt(x));
}


void natlog(void)
{
	float x;
	get_one_arg(&x);
	if (x < 0)
		printf("ERROR, ln's argument couldn't be negative!\n\n");
	else
		printf("\tln(%.2f) = %.2f\n\n", x, log(x));
}
