#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

int main()
{
	Contact alex;
	alex.id = -1;
	strncpy(alex.full_name, "Alex\n", LEN);
	strncpy(alex.work_place, "ELTEX\n", LEN);
	strncpy(alex.work_post, "Programmer\n", LEN);
	strncpy(alex.phone_book[0], "89139999999\n", LEN);
	strncpy(alex.email[0], "alex@eltex.ru\n", LEN);
	strncpy(alex.social_net[0], "vk.com\n", LEN);


	Tree *root = initNode(alex);
	while (menu(root) != 0);
	deleteTree(&root);
	return 0;
}
