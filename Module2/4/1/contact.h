#ifndef CONTACT_H_
#define CONTACT_H_

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

typedef Contact typeData;

typedef struct Node
{
	typeData data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct List
{
	int size;
	Node *head;
	Node *tail;
} List;

// List functions;
List* initList();
Node* initNode(typeData);
Node* getAt( List *, int);
void deleteList(List **list);

void pushFront(List *, typeData);
void pushBack(List *, typeData);
void push(List *, typeData);

typeData popFront(List *);
typeData popBack(List *);
typeData erase(List *, int);

void printList(List *);

// Contact functios;
int menu(List *);
int comp(Contact, Contact);
void print_contacts( List* );
void add_contact(List*);
void remove_contact(List*);
void change_contact(List*);

#endif
