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
void add_contact(struct Contact* conts);
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
	printf("1. Add contact;\n");
	printf("2. Remove contact;\n");
	printf("3. Change contact;\n");
	char choice = getchar();
	getchar();
	switch(choice)
	{
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

void add_contact(struct Contact* conts)
{

}

void remove_contact() {}
void change_contact() {}
