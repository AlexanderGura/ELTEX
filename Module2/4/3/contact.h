#ifndef CONTACT_H_
#define CONTACT_H_

#define LEN 30
#define PHONE_NUMBER 1
#define EMAIL_NUMBER 1
#define NETWORK_NUMBER 1

typedef struct Contact
{
	int id;
	char full_name[LEN];
	char work_place[LEN];
	char work_post[LEN];
	char phone_book[PHONE_NUMBER][LEN];
	char email[EMAIL_NUMBER][LEN];
	char social_net[NETWORK_NUMBER][LEN];
} Contact;

typedef Contact typeData;

typedef struct Tree
{
	typeData data;
	int height;
	struct Tree *left;
	struct Tree *right;
} Tree;

//Secondary tree fucntions;
static int getHeight(Tree *);
static int diffHeight(Tree *);
static void updateHeight(Tree *);
static Tree* rotateRight(Tree *);
static Tree* rotateLeft(Tree *);
static Tree* balance(Tree *);
static Tree* findMin(Tree *);
static Tree* removeMin(Tree *);

// Main tree functions;
Tree* initNode(typeData);
Tree* insert(Tree *, typeData);
Tree* search(Tree *, int);
Tree* removeNode(Tree *, typeData);
void printTree(Tree *);
void deleteTree(Tree **);

// Contact functios;
int menu(Tree* conts);
int comparison(Contact, Contact);
void print_contacts(Tree* conts);
void add_contact(Tree* conts);
void remove_contact(Tree* conts);
void change_contact(Tree* conts);

#endif
