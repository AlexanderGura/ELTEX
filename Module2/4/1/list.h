#ifndef LIST_H_
#define LIST_H_

#include "contact.h"

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

List* initList();
Node* getAt(List *, int);
void deleteList(List **list);

void pushFront(List *, typeData);
void pushBack(List *, typeData);
void push(List *, typeData);

typeData popFront(List *);
typeData popBack(List *);
typeData erase(List *, int);

void printList(List *);

#endif
