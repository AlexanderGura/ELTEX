#include <stdio.h>
#define LEN 30
#define PHONE_NUMBER 5
#define EMAIL_NUMBER 3
#define CONTACTS_NUMBER 5

struct Contact
{
	char full_name[LEN];
	char work_place[LEN];
	char work_post[LEN];
	char phone_book[PHONE_NUMBER][LEN];
	char email[EMAIL_NUMBER][LEN];
	char social_net[LEN];
};

int menu(struct Contact* conts);
void print_contacts(struct Contact* conts, int count);
void add_contact(struct Contact* conts, int n);
void remove_contact();
void change_contact();

int main()
{
	struct Contact contacts[CONTACTS_NUMBER];

	int active = menu(contacts);
	while (active != 0)
	{
		active = menu(contacts);
	}
	return 0;
}

int menu(struct Contact* conts)
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
			print_contacts(conts, 2);
			break;
		case '1':
			add_contact(conts, 1);
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

void print_contacts(struct Contact* conts, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("Full name: %s", (*(conts + i)).full_name);
	}
}

void add_contact(struct Contact* conts, int n)
{
	printf("Enter your full name: ");
	fgets((*(conts + n)).full_name, LEN, stdin);
	printf("Enter your work place: ");
	printf("Enter your work post: ");
	printf("Enter your %d numbers: ", PHONE_NUMBER);
	printf("Enter your %d emails: ", EMAIL_NUMBER);
	printf("Enter your social network: ");
}

void remove_contact() {}
void change_contact() {}
