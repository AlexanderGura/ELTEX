#ifndef CONTACT_H_
#define CONTACT_H_

#define LEN 30
#define PHONE_NUMBER 3
#define EMAIL_NUMBER 3
#define NETWORK_NUMBER 3
#define CONTACTS_NUMBER 5

typedef enum Status {Active = 1, Inactive = -1} Status;

typedef struct Contact
{
	Status stat;
	char full_name[LEN];
	char work_place[LEN];
	char work_post[LEN];
	char phone_book[PHONE_NUMBER][LEN];
	char email[EMAIL_NUMBER][LEN];
	char social_net[NETWORK_NUMBER][LEN];
} Contact;

int menu(Contact* conts);
void print_contacts(Contact* conts);
void add_contact(Contact* conts);
void remove_contact(Contact* conts);
void change_contact(Contact* conts);

#endif
