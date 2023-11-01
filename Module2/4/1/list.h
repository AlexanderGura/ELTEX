#ifndef LIST_H_
#define LIST_H_

typedef struct Node
{
	int data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct List
{
	int size;
	Node *head;
	Node *tail;
} List;

List* initList();
Node* getAt(List *, int);
void deleteList(List **list);

void pushFront(List *, int);
void pushBack(List *, int);
void push(List *, int);

int popFront(List *);
int popBack(List *);
int erase(List *, int);

void printList(List *);

#endif
