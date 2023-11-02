#include <stdio.h>
#include "contact.h"

int main()
{
	List *list = initList();
	while(menu(list) != 0);
	deleteList(&list);
}
