#include <stdio.h>
#include <fcntl.h>
#include "contact.h"

int main()
{
	List *list = initList();
//	read_contacts(list);

	while(menu(list) != 0);

	write_contacts(list);
	deleteList(&list);
	return 0;
}
