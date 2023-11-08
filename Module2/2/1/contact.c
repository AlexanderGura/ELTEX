#include <stdio.h>
#include <string.h>
#include "contact.h"

static void clear_input()
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

static int select(Contact *conts, char choice)
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

void init_contacts(Contact *conts)
{
	for (int i = 0; i < CONTACTS_NUMBER; i++)
		conts[i].stat = Inactive;
}

int menu()
{
	Contact contacts[CONTACTS_NUMBER];

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
		state = select(contacts, choice);
	} while (state == -1);

	return state;
}

void print_contacts(const Contact *const conts)
{
	char isEmpty = 1;
	for (int i = 0; i < CONTACTS_NUMBER; i++)
	{
		if (conts[i].stat == Active)
		{
			isEmpty = 0;
			printf("\nID - %d", i);
			printf("\nFull name - %s", conts[i].full_name);
			printf("Work place - %s", conts[i].work_place);
			printf("Work post - %s", conts[i].work_post);
			for (int j = 0; j < PHONE_NUMBER; j++)
				printf("Phone number %d - %s", j, conts[i].phone_book[j]);
			for (int j = 0; j < EMAIL_NUMBER; j++)
				printf("Email %d - %s", j, conts[i].email[j]);
			for (int j = 0; j < NETWORK_NUMBER; j++)
				printf("Social network %d - %s", j, conts[i].social_net[j]);
		}
	}
	if (isEmpty)
		printf("Base is empty!\n");
}

void add_contact(Contact* conts)
{
	static int index = 0;
	if (index == 0)
	{
		init_contacts(conts);
	}
	else if (index > 5)
	{
		printf("Base is overflow!\n");
		return;
	}

	conts[index].stat = Active;
	printf("\nEnter your full name: ");
	fgets(conts[index].full_name, LEN, stdin);

	printf("Enter your work place: ");
	fgets(conts[index].work_place, LEN, stdin);

	printf("Enter your work post: ");
	fgets(conts[index].work_post, LEN, stdin);

	for (int j = 0; j < PHONE_NUMBER ; j++)
	{
		printf("Enter your %d number: ", j + 1);
		fgets(conts[index].phone_book[j], LEN, stdin);
	}

	for (int j = 0; j < EMAIL_NUMBER ; j++)
	{
		printf("Enter your %d email: ", j + 1);
		fgets(conts[index].email[j], LEN, stdin);
	}

	for (int j = 0; j < NETWORK_NUMBER ; j++)
	{
		printf("Enter your %d social network: ", j + 1);
		fgets(conts[index].social_net[j], LEN, stdin);
	}
	index++;
}

void remove_contact(Contact* conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	clear_input();

	if (index < 0 || index >= CONTACTS_NUMBER || conts[index].stat == Inactive)
	{
		printf("Invalid index!\n");
		return;
	}
	conts[index].stat = Inactive;
}

void change_contact(Contact* conts)
{
	printf("\nWhat contact do you want to change?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	clear_input();

	if (index < 0 || index >= CONTACTS_NUMBER || conts[index].stat == Inactive)
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
			fgets(conts[index].full_name, LEN, stdin);
			return;

		case 'w':
		case '2':
			printf("Enter new work place: ");
			fgets(conts[index].work_place, LEN, stdin);
			return;

		case 's':
		case '3':
			printf("Enter new work post: ");
			fgets(conts[index].work_post, LEN, stdin);
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
			fgets(conts[index].phone_book[num - 1], LEN, stdin);
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
			fgets(conts[index].email[num - 1], LEN, stdin);
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
			fgets(conts[index].social_net[num - 1], LEN, stdin);
			return;

		default:
			printf("Invalid field!\n");
			return;
	}
}
