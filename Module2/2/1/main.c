#include <stdio.h>
#include <string.h>
#include "contact.h"

int main()
{
	Contact contacts[CONTACTS_NUMBER];

	for (int i = 0; i < CONTACTS_NUMBER; i++)
		contacts[i].stat = Inactive;

	contacts[0].stat = Active;
	strncpy(contacts[0].full_name, "Alex Gura", LEN);



	int active = menu(contacts);
	while (active != 0)
	{
		active = menu(contacts);
	}
	return 0;
}
