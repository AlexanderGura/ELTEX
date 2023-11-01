#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* initList()
{
	List *tmp = (List*) malloc(sizeof(List));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void deleteList(List **list)
{
	Node *tmp = (*list)->head;
	Node *next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	*list = NULL;
}

Node* getAt(List *list, int index)
{
	Node* tmp = list->head;
	int i = 0;

	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return tmp;
}

void pushFront(List *list, int data)
{
	Node *new_node = (Node*) malloc(sizeof(Node));
	if (new_node == NULL)
		exit(1);

	new_node->data = data;
	new_node->next = list->head;
	new_node->prev = NULL;

	if (list->head != NULL)
		list->head->prev = new_node;
	list->head = new_node;

	if (list->tail == NULL)
		list->tail = new_node;
	list->size++;
}

int popFront(List *list)
{
	Node *prev;
	int tmp;

	if (list->head == NULL)
		exit(2);

	prev = list->head;
	list->head = list->head->next;
	if (list->head != NULL)
		list->head->prev = NULL;

	if (prev == list->tail)
		list->tail = NULL;

	tmp = prev->data;
	free(prev);

	list->size--;
	return tmp;
}

void pushBack(List *list, int data)
{
	Node *new_node = (Node*) malloc(sizeof(Node));
	if (new_node == NULL)
		exit(1);

	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = list->tail;

	if (list->tail != NULL)
		list->tail->next = new_node;
	list->tail = new_node;

	if (list->head == NULL)
		list->head = new_node;
	list->size++;
}

int popBack(List *list)
{
	Node *next;
	int tmp;

	if (list->tail == NULL)
		exit(2);

	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail != NULL)
		list->tail->next = NULL;

	if (next == list->head)
		list->head = NULL;

	tmp = next->data;
	free(next);

	list->size--;
	return tmp;
}

void push(List* list, int data)
{
	if (list->head == NULL)
	{
		pushFront(list, data);
		return;
	}
	if (list->head == list->tail)
	{
		if (data > list->tail->data)
		{
			pushBack(list, data);
			return;
		}
		pushFront(list, data);
		return;
	}

	if (list->head->data > data)
	{
		pushFront(list, data);
		return;
	}

	if (list->tail->data < data)
	{
		pushBack(list, data);
		return;
	}

	Node *tmp = list->head;
	while (tmp->data < data)
	{
		tmp = tmp->next;
	}

	Node *left = tmp->prev;
	Node *right = tmp;

	Node *new_node = (Node*) malloc(sizeof(Node));
	new_node->data = data;
	new_node->prev = left;
	new_node->next = right;

	left->next = new_node;
	right->prev = new_node;
	list->size++;
	return;
}

int erase(List *list, int index)
{
	if (index < 0 || index > list->size)
		exit(1);

	Node *tmp = getAt(list, index);
	if (tmp == NULL)
		exit(1);

	if (tmp->prev == NULL)
		return popFront(list);
	if (tmp->next == NULL)
		return popBack(list);

	Node *left = tmp->prev;
	Node *right = tmp->next;

	left->next = right;
	right->prev = left;

	int data = tmp->data;
	free(tmp);
	return data;
}

void printList(List *list)
{
	Node *ptr = list->head;
	printf("Size - %d\n", list->size);
	while (ptr)
	{
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
}
