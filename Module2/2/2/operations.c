#include <stdio.h>
#include "operations.h"

static void clear_input()
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

void add(int x, int y)
{
	printf("%d + %d = %d\n\n", x, y, x + y);
}

void sub(int x, int y)
{
	printf("%d - %d = %d\n\n", x, y, x - y);
}

void mult(int x, int y)
{
	printf("%d * %d = %d\n\n", x, y, x * y);
}

void div(int x, int y)
{
	if (y == 0)
		printf("ERROR: division by zero!\n\n");
	else
		printf("%d / %d = %d\n\n", x, y, x / y);
}

int select(char choice, int *f, int *s)
{
	switch(choice)
	{
		case '+':
			add(*f, *s);
			return 1;

		case '-':
			sub(*f, *s);
			return 1;

		case '*':
			mult(*f, *s);
			return 1;

		case '/':
			div(*f, *s);
			return 1;

		case 'Q':
		case 'q':
			printf("Good bye, have a good day!\n");
			return 0;

		default:
			printf("\nInvalid choice!\nEnter again: ");
			return -1;
	}
}

int menu()
{
	int first, second;

	printf("Enter 'q' to end calc.\n");
	printf("Enter the firts number: ");
	scanf("%d", &first);
	clear_input();

	printf("Enter the second number: ");
	scanf("%d", &second);
	clear_input();

	printf("Enter the operation(+ - * /): ");
	char choice, state;
	do
	{
		choice = getchar();
		clear_input();
		state = select(choice, &first, &second);
	} while (state == -1);
}

