#include <stdio.h>
#include "operations.h"

int menu();

int main()
{
	int is_active = 1;
	while (is_active != 0)
		is_active = menu();

	return 0;
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
