#include <stdio.h>
#include <string.h>
#include "contact.h"

int main()
{
	Contact contacts[CONTACTS_NUMBER];

	for (int i = 0; i < CONTACTS_NUMBER; i++)
		contacts[i].stat = Inactive;

	while (menu(contacts) != 0);
	return 0;
}
