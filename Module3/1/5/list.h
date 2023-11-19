#ifndef LIST_H_
#define LIST_H_

typedef struct Node
{
	void* data;
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
Node* initNode(void*);
Node* getAt(List *, int);
void deleteList(List **list);

void pushFront(List *, void*);
void pushBack(List *, void*);
void push(List *, void*);

void popFront(List *);
void popBack(List *);
void erase(List *, int);

void printList(List *);

#endif
