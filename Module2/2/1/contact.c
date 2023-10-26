#include <stdio.h>
#include <string.h>
#include "contact.h"

int menu(Contact* conts)
{
	printf("\nEnter your choice (q - to quit):\n");
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
			remove_contact(conts);
			break;
		case '3':
			change_contact(conts);
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
			printf("\nID - %d", i);
			printf("\nFull name - %s", conts[i].full_name);
			printf("Work place - %s", conts[i].work_place);
			printf("Work post - %s", conts[i].work_post);
			printf("Phone number - %s", conts[i].phone_book);
			printf("Email - %s", conts[i].email);
			printf("Social network - %s\n", conts[i].social_net);
		}
	}
}

void add_contact(Contact* conts)
{
	int index = 0;
	for (int i = 0; i < CONTACTS_NUMBER; i++)
		if (conts[i].stat == Inactive)
		{
			index = i;
			break;
		}

	conts[index].stat = Active;
	printf("Enter your full name: ");
	fgets(conts[index].full_name, LEN, stdin);

	printf("Enter your work place: ");
	fgets(conts[index].work_place, LEN, stdin);

	printf("Enter your work post: ");
	fgets(conts[index].work_post, LEN, stdin);

	printf("Enter your number: ");
	fgets(conts[index].phone_book, LEN, stdin);

	printf("Enter your email: ");
	fgets(conts[index].email, LEN, stdin);

	printf("Enter your social network: ");
	fgets(conts[index].social_net, LEN, stdin);

}

void remove_contact(Contact* conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	getchar();

	conts[index].stat = Inactive;
	conts[index].full_name[0] = '\0';;
	conts[index].work_place[0] = '\0';;
	conts[index].work_post[0] = '\0';;
	conts[index].phone_book[0] = '\0';;
	conts[index].email[0] = '\0';;
	conts[index].social_net[0] = '\0';
}

void change_contact(Contact* conts)
{
	printf("\nWhat contact do you want to change?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	getchar();

	printf("1. Full name;\n");
	printf("2. Work place;\n");
	printf("3. Work post;\n");
	printf("4. Phone number;\n");
	printf("5. Email;\n");
	printf("6. Social network;\n");
	printf("What field do you want to change? ");

	char choice = getchar();
	getchar();
	switch(choice)
	{
		case '1':
			fgets(conts[index].full_name, LEN, stdin);
			break;
		case '2':
			fgets(conts[index].work_place, LEN, stdin);
			break;
		case '3':
			fgets(conts[index].work_post, LEN, stdin);
			break;
		case '4':
			fgets(conts[index].phone_book, LEN, stdin);
			break;
		case '5':
			fgets(conts[index].email, LEN, stdin);
			break;
		case '6':
			fgets(conts[index].social_net, LEN, stdin);
			break;
		default:
			break;
	}
}
