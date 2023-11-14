#include <stdio.h>
#include <string.h>
#include "contact.h"

static void clear_input()
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

// 0 - equal, 1 - more, 2 - second more;
int cmp(Contact first, Contact second)
{
	if (first.id > second.id)
		return 1;
	else if (first.id < second.id)
		return 2;
	return 0;
}

static int select(Tree *conts, char choice)
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

int menu(Tree *conts)
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
		state = select(conts, choice);
	} while (state == -1);

	return state;
}

void print_contacts(Tree *conts)
{
	if (conts == NULL)
		return;

	print_contacts(conts->left);
	printf("\nID - %d", conts->data.id);
	printf("\nFull name - %s", conts->data.full_name);
	printf("Work place - %s", conts->data.work_place);
	printf("Work post - %s", conts->data.work_post);
	for (int j = 0; j < PHONE_NUMBER; j++)
		printf("Phone number %d - %s", j, conts->data.phone_book[j]);
	for (int j = 0; j < EMAIL_NUMBER; j++)
		printf("Email %d - %s", j, conts->data.email[j]);
	for (int j = 0; j < NETWORK_NUMBER; j++)
		printf("Social network %d - %s", j, conts->data.social_net[j]);
	print_contacts(conts->right);

}

void add_contact(Tree* conts)
{
	static int index = 0;

	Contact contact;
	contact.id = index++;
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
	conts = insert(conts, contact);
}

void remove_contact(Tree* conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	clear_input();

	if (index < 0)
	{
		printf("Invalid index!\n");
		return;
	}

	Tree *node = search(conts, index);
	if (node == NULL)
		printf("\nBase don't have this contact!\n");
	else
		conts = removeNode(conts, node->data);
}

void change_contact(Tree* conts)
{
	printf("\nWhat contact do you want to change?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	clear_input();

	if (index < 0)
	{
		printf("Invalid index!\n");
		return;
	}

	Tree *node = search(conts, index);
	if (node == NULL)
	{
		printf("\nBase don't have this contact!\n");
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
