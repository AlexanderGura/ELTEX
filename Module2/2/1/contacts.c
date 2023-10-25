#include <stdio.h>
#include <string.h>

#define LEN 30
#define PHONE_NUMBER 5
#define EMAIL_NUMBER 3
#define CONTACTS_NUMBER 5

typedef enum Status {Active = 1, Inactive = -1} Status;

typedef struct Contact
{
	Status stat;
	char full_name[LEN];
	char work_place[LEN];
	char work_post[LEN];
	char phone_book[LEN];
	char email[LEN];
	char social_net[LEN];
} Contact;

int menu(Contact* conts);
void print_contacts(Contact* conts);
void add_contact(Contact* conts);
void remove_contact();
void change_contact();

int main()
{
	Contact contacts[CONTACTS_NUMBER];
	contacts[0].stat = Active;
	strncpy(contacts[0].full_name, "Alex Gura", LEN);

	for (int i = 0; i < CONTACTS_NUMBER; i++)
		contacts[i].stat = Inactive;

	int active = menu(contacts);
	while (active != 0)
	{
		active = menu(contacts);
	}
	return 0;
}

int menu(Contact* conts)
{
	printf("Enter your choice (q - to quit):\n");
	printf("0. Print all contacts;\n");
	printf("1. Add contact;\n");
	printf("2. Remove contact;\n");
	printf("3. Change contact;\n");
	char choice = getchar();
	getchar();
	switch(choice)
	{
		case '0':
			print_contacts(conts);
			break;
		case '1':
			add_contact(conts);
			break;
		case '2':
			remove_contact();
			break;
		case '3':
			change_contact();
			break;
		case 'q':
			return 0;
			break;
	}
	return 1;
}

void print_contacts(Contact* conts)
{
	for (int i = 0; i < CONTACTS_NUMBER; i++)
	{
		if (conts[i].stat == Active)
		{
			printf("Full name - %s", conts[i].full_name);
			printf("Work place - %s", conts[i].work_place);
			printf("Work post - %s", conts[i].work_post);
			printf("Phone number - %s", conts[i].phone_book);
			printf("Email - %s", conts[i].email);
			printf("Social network - %s", conts[i].social_net);
		}
	}
}

void add_contact(Contact* conts)
{
	int index = 0;
	for (int i = 0; i < CONTACTS_NUMBER; i++)
		if (conts[i].stat != Active)
			index++;

	conts[index].stat = Active;
	printf("Enter your full name: ");
	fgets(conts[index].full_name, LEN, stdin);
	printf("Enter your work place: ");
	printf("Enter your work post: ");
	printf("Enter your %d numbers: ", PHONE_NUMBER);
	printf("Enter your %d emails: ", EMAIL_NUMBER);
	printf("Enter your social network: ");
}

void remove_contact() {}
void change_contact() {}
