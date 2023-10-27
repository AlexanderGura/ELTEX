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
			for (int j = 0; j < PHONE_NUMBER; j++)
				printf("Phone number %d - %s", j, conts[i].phone_book[j]);
			for (int j = 0; j < EMAIL_NUMBER; j++)
				printf("Email %d - %s", j, conts[i].email[j]);
			for (int j = 0; j < NETWORK_NUMBER; j++)
				printf("Social network %d - %s", j, conts[i].social_net[j]);
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
	printf("\nEnter your full name: ");
	fgets(conts[index].full_name, LEN, stdin);

	printf("Enter your work place: ");
	fgets(conts[index].work_place, LEN, stdin);

	printf("Enter your work post: ");
	fgets(conts[index].work_post, LEN, stdin);

	for (int j = 0; j < PHONE_NUMBER; j++)
	{
		printf("Enter your %d number: ", j);
		fgets(conts[index].phone_book[j], LEN, stdin);
	}

	for (int j = 0; j < EMAIL_NUMBER; j++)
	{
		printf("Enter your %d email: ", j);
		fgets(conts[index].email[j], LEN, stdin);
	}

	for (int j = 0; j < EMAIL_NUMBER; j++)
	{
		printf("Enter your %d social network: ", j);
		fgets(conts[index].social_net[j], LEN, stdin);
	}

}

void remove_contact(Contact* conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the id of contact: ");
	int index;
	scanf("%d", &index);
	getchar();

	conts[index].stat = Inactive;
	conts[index].full_name[0] = '\0';
	conts[index].work_place[0] = '\0';
	conts[index].work_post[0] = '\0';

	for (int j = 0; j < PHONE_NUMBER; j++)
		conts[index].phone_book[j][0] = '\0';
	for (int j = 0; j < PHONE_NUMBER; j++)
		conts[index].email[j][0] = '\0';
	for (int j = 0; j < PHONE_NUMBER; j++)
		conts[index].social_net[j][0] = '\0';
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

	int num;
	char choice = getchar();
	getchar();
	switch(choice)
	{
		case '1':
			printf("Enter new full name: ");
			fgets(conts[index].full_name, LEN, stdin);
			break;
		case '2':
			printf("Enter new work place: ");
			fgets(conts[index].work_place, LEN, stdin);
			break;
		case '3':
			printf("Enter new work post: ");
			fgets(conts[index].work_post, LEN, stdin);
			break;
		case '4':
			printf("What phone do you want do change?\n");
			printf("Enter the number of phone: ");
			scanf("%d", &num);
			getchar();
			printf("Enter new %d phone: ", num);
			fgets(conts[index].phone_book[num], LEN, stdin);
			break;
		case '5':
			printf("What email do you want do change?\n");
			printf("Enter the number of email: ");
			scanf("%d", &num);
			getchar();
			printf("Enter new %d email: ", num);
			fgets(conts[index].email[num], LEN, stdin);
			break;
		case '6':
			printf("What social net do you want do change?\n");
			printf("Enter the number of social net: ");
			scanf("%d", &num);
			getchar();
			printf("Enter new %d new social net: ", num);
			fgets(conts[index].social_net[num], LEN, stdin);
			break;
		default:
			break;
	}
}
