#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "contact.h"

int cmp(void *first, void *second)
{
	Contact *f = (Contact *)first;
	Contact *s = (Contact *)second;
	int len_first = sizeof(f->full_name);
	int len_second = sizeof(s->full_name);
	int min_len = len_first > len_second ? len_second : len_first;
	for (int i = 0; i < min_len; i++)
		if (f->full_name[i] > s->full_name[i])
			return 1;
		else
			return 2;
}

static void clear_input()
{
	for (char c = getchar(); c != '\n' && c != EOF; c = getchar());
}

static int select_choice(List *conts, char choice)
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

void read_contacts(List *conts)
{
	if (conts == NULL)
		return;

	int fd = open(BASE_NAME, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
	{
		fprintf(stderr, "Couldn't open file!\n");
		exit(EXIT_FAILURE);
	}

	read(fd, &conts->size, sizeof(conts->size));
	Contact *tmp;
	for (int i = 0; i < conts->size; i++)
	{
		tmp = (Contact *) malloc(sizeof(Contact));
		read(fd, tmp, sizeof(Contact));
		push(conts, (void *)tmp);
	}

	if (close(fd) == -1)
	{
		fprintf(stderr, "Couldn't close file!\n");
		exit(EXIT_FAILURE);
	}
}

void write_contacts(List *conts)
{
	if (conts == NULL)
		return;

	int fd = open(BASE_NAME, O_RDWR | O_TRUNC);
	if (fd == -1)
	{
		fprintf(stderr, "Couldn't open file!\n");
		exit(EXIT_FAILURE);
	}

	write(fd, &conts->size, sizeof(conts->size));
	for (Node *tmp = conts->head; tmp != NULL; tmp = tmp->next)
		write(fd, tmp->data, sizeof(Contact));

	if (close(fd) == -1)
	{
		fprintf(stderr, "Couldn't close file!\n");
		exit(EXIT_FAILURE);
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
		state = select_choice(list, choice);
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
		Contact *cont = (Contact *) node->data;
		printf("\nID - %d", i);
		printf("\nFull name - %s", cont->full_name);
		printf("Work place - %s", cont->work_place);
		printf("Work post - %s", cont->work_post);
		for (int j = 0; j < PHONE_NUMBER; j++)
			printf("Phone number %d - %s", j, cont->phone_book[j]);
		for (int j = 0; j < EMAIL_NUMBER; j++)
			printf("Email %d - %s", j, cont->email[j]);
		for (int j = 0; j < NETWORK_NUMBER; j++)
			printf("Social network %d - %s", j, cont->social_net[j]);
	}
	if (isEmpty)
		printf("Base is empty!\n");
}

void add_contact(List* conts)
{
	Contact *contact = malloc(sizeof(Contact));
	printf("\nEnter your full name: ");
	fgets(contact->full_name, LEN, stdin);

	printf("Enter your work place: ");
	fgets(contact->work_place, LEN, stdin);

	printf("Enter your work post: ");
	fgets(contact->work_post, LEN, stdin);

	for (int j = 0; j < PHONE_NUMBER ; j++)
	{
		printf("Enter your %d number: ", j + 1);
		fgets(contact->phone_book[j], LEN, stdin);
	}

	for (int j = 0; j < EMAIL_NUMBER ; j++)
	{
		printf("Enter your %d email: ", j + 1);
		fgets(contact->email[j], LEN, stdin);
	}

	for (int j = 0; j < NETWORK_NUMBER ; j++)
	{
		printf("Enter your %d social network: ", j + 1);
		fgets(contact->social_net[j], LEN, stdin);
	}
	push(conts, (void *)contact);
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
	Contact *cont = (Contact*) node->data;
	switch(choice)
	{
		case 'f':
		case '1':
			printf("Enter new full name: ");
			fgets(cont->full_name, LEN, stdin);
			return;

		case 'w':
		case '2':
			printf("Enter new work place: ");
			fgets(cont->work_place, LEN, stdin);
			return;

		case 's':
		case '3':
			printf("Enter new work post: ");
			fgets(cont->work_post, LEN, stdin);
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
			fgets(cont->phone_book[num - 1], LEN, stdin);
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
			fgets(cont->email[num - 1], LEN, stdin);
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
			fgets(cont->social_net[num - 1], LEN, stdin);
			return;

		default:
			printf("Invalid field!\n");
			return;
	}
}
