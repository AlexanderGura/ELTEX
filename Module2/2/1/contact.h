#ifndef CONTACT_H_
#define CONTACT_H_

#define LEN 30
#define PHONE_NUMBER 1
#define EMAIL_NUMBER 1
#define NETWORK_NUMBER 1
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

static void clear_input();
static int select(Contact*, char);

void init_contacts(Contact*);
int menu();
void print_contacts(const Contact *const);
void add_contact(Contact*);
void remove_contact(Contact*);
void change_contact(Contact*);

#endif
