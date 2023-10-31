#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
	List* list = initList();
	list = pushFront(list, 10);
	list = pushFront(list, 13);
	list = pushFront(list, 22);
	list = pushFront(list, 22);
	list = pushBack(list, 44);
	printList(list);
	deleteList(list);

	return 0;
}
