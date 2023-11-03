#include <stdio.h>
#include <string.h>
#include "contact.h"

// 0 - equal, 1 - more, 2 - second more;
int comparison(Contact first, Contact second)
{
	int len_first = sizeof(first.full_name);
	int len_second = sizeof(second.full_name);
	int min_len = len_first > len_second ? len_second : len_first;
	for (int i = 0; i < min_len; i++)
		if (first.full_name[i] > second.full_name[i])
			return 1;
		else
			return 2;
	return 0;
}

int menu(Tree *conts)
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

void print_contacts(Tree *conts)
{
	if (conts != NULL)
	{
		print_contacts(conts->left);
		printf("ID - %d\n", conts->data.id);
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
}

void add_contact(Tree *conts)
{
	static int count = 0;
	Contact contact;
	contact.id = count++;
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
	conts = insert(conts, contact);

}

void remove_contact(Tree *conts)
{
	printf("\nWhat contact do you want to remove?\n");
	printf("Enter the ID of contact: ");
	int id = 0;
	scanf("%d", &id);
	getchar();
	Tree *node = search(conts, id);
	if (node == NULL)
		printf("Base don't have this contact!\n");
	else
		conts = removeNode(conts, node->data);
}

void change_contact(Tree *conts)
{
	printf("\nWhat contact do you want to change?\n");
	printf("Enter the ID of contact: ");
	int id = 0;
	scanf("%d", &id);
	getchar();
	Tree *node = search(conts, id);

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
