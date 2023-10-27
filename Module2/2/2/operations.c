#include <stdio.h>
#include "operations.h"

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

int menu()
{
	int first, second;

	printf("Enter 'q' to end calc.\n");
	printf("Enter the firts number: ");
	scanf("%d", &first);

	printf("Enter the second number: ");
	scanf("%d", &second);

	printf("Enter the operation(+ - * /): ");
	getchar();
	char choice = getchar();
	getchar();

	switch(choice)
	{
		case '+':
			add(first, second); return 1;
		case '-':
			sub(first, second); return 1;
		case '*':
			mult(first, second); return 1;
		case '/':
			div(first, second); return 1;
		default:
			return 0;
	}
}

