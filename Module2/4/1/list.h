#ifndef LIST_H_
#define LIST_H_

typedef struct Node
{
	double data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct List
{
	Node* head;
	Node* tail;
} List;

Node* initNode(double);

List* initList();
List* pushFront(List*, double);
List* pushBack(List*, double);
void printList(List*);
void deleteList(List*);

#endif
