#include <stdio.h>
#include "list.h"

int main()
{
	List *list = initList();
	push(list, 11);
	push(list, 22);
	push(list, 52);
	push(list, -43);
	push(list, 12);
	printList(list);

	popFront(list);
	popBack(list);
	erase(list, 1);
	printList(list);

	deleteList(&list);
	return 0;
}

