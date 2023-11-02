#include <stdio.h>
#include <string.h>
#include "contact.h"

int menu(List *conts)
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

void print_contacts(List *conts)
{
	for (int i = 0; i < conts->size; i++)
	{
		Node *node = getAt(conts, i);
		printf("\nID - %d", i);
		printf("\nFull name - %s", node->data.full_name);
		printf("Work place - %s", node->data.work_place);
		printf("Work post - %s", node->data.work_post);
		for (int j = 0; j < PHONE_NUMBER; j++)
			printf("Phone number %d - %s", j, node->data.phone_book[j]);
		for (int j = 0; j < EMAIL_NUMBER; j++)
			printf("Email %d - %s", j, node->data.email[j]);
		for (int j = 0; j < NETWORK_NUMBER; j++)
			printf("Social network %d - %s", j, node->data.social_net[j]);
	}
}

void add_contact(List *conts)
{
	Contact contact;
	printf("\nEnter your full name: ");
	fgets(contact.full_name, LEN, stdin);

	printf("Enter your work place: ");
	fgets(contact.work_place, LEN, stdin);

	printf("Enter your work post: ");
	fgets(contact.work_post, LEN, stdin);

	for (int j = 0; j < PHONE_NUMBER; j++)
	{
		printf("Enter your %d number: ", j);
		fgets(contact.phone_book[j], LEN, stdin);
	}

	for (int j = 0; j < EMAIL_NUMBER; j++)
	{
		printf("Enter your %d email: ", j);
		fgets(contact.email[j], LEN, stdin);
	}

	for (int j = 0; j < NETWORK_NUMBER; j++)
	{
		printf("Enter your %d social network: ", j);
		fgets(contact.social_net[j], LEN, stdin);
	}
	push(conts, contact);

}

void remove_contact(List *conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	getchar();

	Node *node = getAt(conts, index);
	erase(conts, index);
}

void change_contact(List *conts)
{
	printf("\nWhat contact do you want to change?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	getchar();
	Node *node = getAt(conts, index);

	printf("1. Full name;\n");
	printf("2. Work place;\n");
	printf("3. Work post;\n");
	printf("4. Phone number;\n");
	printf("5. Email;\n");
	printf("6. Social network;\n");
	printf("What field do you want to change? ");

	int num;
	char choice = getchar();
	getchar();
	switch(choice)
	{
		case '1':
			printf("Enter new full name: ");
			fgets(node->data.full_name, LEN, stdin);
			break;
		case '2':
			printf("Enter new work place: ");
			fgets(node->data.work_place, LEN, stdin);
			break;
		case '3':
			printf("Enter new work post: ");
			fgets(node->data.work_post, LEN, stdin);
			break;
		case '4':
			printf("What phone do you want do change?\n");
			printf("Enter the number of phone: ");
			scanf("%d", &num);
			getchar();
			printf("Enter new %d phone: ", num);
			fgets(node->data.phone_book[num], LEN, stdin);
			break;
		case '5':
			printf("What email do you want do change?\n");
			printf("Enter the number of email: ");
			scanf("%d", &num);
			getchar();
			printf("Enter new %d email: ", num);
			fgets(node->data.email[num], LEN, stdin);
			break;
		case '6':
			printf("What social net do you want do change?\n");
			printf("Enter the number of social net: ");
			scanf("%d", &num);
			getchar();
			printf("Enter new %d new social net: ", num);
			fgets(node->data.social_net[num], LEN, stdin);
			break;
		default:
			break;
	}
}
