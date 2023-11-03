#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

int main()
{
	Contact alex;
	alex.id = -1;
	strncpy(alex.full_name, "Alex", LEN);
	Tree *root = initNode(alex);
	while (menu(root) != 0);
	deleteTree(&root);
	return 0;
}
