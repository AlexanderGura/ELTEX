#include <stdio.h>
#include <string.h>
#include "contact.h"

static void clear_input()
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

static int select(List *conts, char choice)
{
	switch(choice)
	{
		case '0':
			print_contacts(conts);
			return 1;
		case '1':
			add_contact(conts);
			return 1;
		case '2':
			remove_contact(conts);
			return 1;
		case '3':
			change_contact(conts);
			return 1;
		case 'Q':
		case 'q':
			printf("Goodbye, have a good day!\n");
			return 0;
		default:
			printf("Wrong action!\n");
			printf("Write your choice again: ");
			return -1;
	}
}

int menu(List *list)
{
	printf("\nEnter your choice (q - to quit):\n");
	printf("0. Print all contacts;\n");
	printf("1. Add contact;\n");
	printf("2. Remove contact;\n");
	printf("3. Change contact;\n");

	char choice, state;
	do
	{
		choice = getchar();
		clear_input();
		state = select(list, choice);
	} while (state == -1);

	return state;
}

void print_contacts(List *conts)
{
	char isEmpty = 1;
	for (int i = 0; i < conts->size; i++)
	{
		isEmpty = 0;
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
	if (isEmpty)
		printf("Base is empty!\n");
}

void add_contact(List* conts)
{
	Contact contact;
	printf("\nEnter your full name: ");
	fgets(contact.full_name, LEN, stdin);

	printf("Enter your work place: ");
	fgets(contact.work_place, LEN, stdin);

	printf("Enter your work post: ");
	fgets(contact.work_post, LEN, stdin);

	for (int j = 0; j < PHONE_NUMBER ; j++)
	{
		printf("Enter your %d number: ", j + 1);
		fgets(contact.phone_book[j], LEN, stdin);
	}

	for (int j = 0; j < EMAIL_NUMBER ; j++)
	{
		printf("Enter your %d email: ", j + 1);
		fgets(contact.email[j], LEN, stdin);
	}

	for (int j = 0; j < NETWORK_NUMBER ; j++)
	{
		printf("Enter your %d social network: ", j + 1);
		fgets(contact.social_net[j], LEN, stdin);
	}
	push(conts, contact);
}

void remove_contact(List* conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	clear_input();

	if (index < 0 || index >= conts->size)
	{
		printf("Invalid index!\n");
		return;
	}
	erase(conts, index);
}

void change_contact(List* conts)
{
	printf("\nWhat contact do you want to change?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	clear_input();
	Node *node = getAt(conts, index);

	if (index < 0 || index >= conts->size)
	{
		printf("Invalid index!\n");
		return;
	}

	printf("1(f). Full name;\n");
	printf("2(w). Work place;\n");
	printf("3(s). Work post;\n");
	printf("4(p). Phone number;\n");
	printf("5(e). Email;\n");
	printf("6(n). Social network;\n");
	printf("What field do you want to change? ");

	int num;
	char choice = getchar();
	clear_input();
	switch(choice)
	{
		case 'f':
		case '1':
			printf("Enter new full name: ");
			fgets(node->data.full_name, LEN, stdin);
			return;

		case 'w':
		case '2':
			printf("Enter new work place: ");
			fgets(node->data.work_place, LEN, stdin);
			return;

		case 's':
		case '3':
			printf("Enter new work post: ");
			fgets(node->data.work_post, LEN, stdin);
			return;

		case 'p':
		case '4':
			printf("What phone do you want do change?\n");
			printf("Enter the number of phone: ");

			scanf("%d", &num);
			clear_input();
			if (num < 1 || num > PHONE_NUMBER)
			{
				printf("Wrong number!\n");
				return;
			}

			printf("Enter new %d phone: ", num);
			fgets(node->data.phone_book[num - 1], LEN, stdin);
			return;

		case 'e':
		case '5':
			printf("What email do you want do change?\n");
			printf("Enter the number of email: ");

			scanf("%d", &num);
			clear_input();
			if (num < 1 || num > PHONE_NUMBER)
			{
				printf("Wrong number!\n");
				return;
			}

			printf("Enter new %d email: ", num);
			fgets(node->data.email[num - 1], LEN, stdin);
			return;

		case 'n':
		case '6':
			printf("What social net do you want do change?\n");
			printf("Enter the number of social net: ");

			scanf("%d", &num);
			clear_input();
			if (num < 1 || num > PHONE_NUMBER)
			{
				printf("Wrong number!\n");
				return;
			}

			printf("Enter new %d new social net: ", num);
			fgets(node->data.social_net[num - 1], LEN, stdin);
			return;

		default:
			printf("Invalid field!\n");
			return;
	}
}
