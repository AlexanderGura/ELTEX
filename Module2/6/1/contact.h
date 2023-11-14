#ifndef CONTACT_H_
#define CONTACT_H_

#include "list.h"

#define LEN 	       30
#define PHONE_NUMBER	1
#define EMAIL_NUMBER 	1
#define NETWORK_NUMBER 	1

typedef struct Contact
{
	char full_name[LEN];
	char work_place[LEN];
	char work_post[LEN];
	char phone_book[PHONE_NUMBER][LEN];
	char email[EMAIL_NUMBER][LEN];
	char social_net[NETWORK_NUMBER][LEN];
} Contact;

// Contact functios;
static void clear_input();
static int select_choice(List *, char);
int menu(List *);
int comp(Contact, Contact);
void print_contacts( List* );
void add_contact(List*);
void remove_contact(List*);
void change_contact(List*);

#endif
