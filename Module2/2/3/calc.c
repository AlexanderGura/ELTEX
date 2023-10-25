#include <stdio.h>
#include "operations.h"

#define OPERATIONS_NUM 7

int menu();

int main()
{
	while (menu() != 0);

	return 0;
}

int menu()
{
	printf("\nEnter the number of operation:\n");
	printf("Enter '0' to end the calc!\n");
	printf("1. +\n2. -\n3. *\n4. /\n5. power\n6. sqrt\n7. ln\n");

	int choice;
	scanf("%d", &choice);
	getchar();
	if (choice == 0)
		return 0;

	void (*operations[OPERATIONS_NUM]) (void) = {
		add, sub, mult, div, power, sqroot, natlog};
	operations[choice - 1]();
	return 1;
}
