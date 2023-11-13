#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int cmp(Contact first, Contact second)
{
	int len_first = sizeof(first.full_name);
	int len_second = sizeof(second.full_name);
	int min_len = len_first > len_second ? len_second : len_first;
	for (int i = 0; i < min_len; i++)
		if (first.full_name[i] > second.full_name[i])
			return 1;
		else
			return 2;
}

List* initList()
{
	List *tmp = (List*) malloc(sizeof(List));
	if (tmp == NULL)
		exit(EXIT_FAILURE);

	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}

Node* initNode(typeData data)
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);

	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void deleteList(List **list)
{
	for (Node *tmp = (*list)->head; tmp != NULL; tmp = (*list)->head)
	{
		(*list)->head = (*list)->head->next;
		free(tmp);
	}
	free(*list);
}

Node* getAt(List *list, int index)
{
	if (index < 0 || index >= list->size)
		exit(EXIT_FAILURE);

	Node* tmp = list->head;
	for(int i = 0; tmp && i < index; i++)
		tmp = tmp->next;
	return tmp;
}

void pushFront(List *list, typeData data)
{
	Node *new_node = initNode(data);
	new_node->next = list->head;

	if (list->head != NULL)
		list->head->prev = new_node;
	list->head = new_node;

	if (list->tail == NULL)
		list->tail = new_node;
	list->size++;
}


void pushBack(List *list, typeData data)
{
	Node *new_node = initNode(data);
	new_node->prev = list->tail;

	if (list->tail != NULL)
		list->tail->next = new_node;
	list->tail = new_node;

	if (list->head == NULL)
		list->head = new_node;
	list->size++;
}

void push(List* list, typeData data)
{
	if (list->head == NULL || cmp(list->head->data, data) == 1)
	{
		pushFront(list, data);
		return;
	}

	if (cmp(list->tail->data,  data) == 2)
	{
		pushBack(list, data);
		return;
	}

	Node *tmp = list->head;
	while (cmp(tmp->data, data) == 2)
		tmp = tmp->next;

	Node *left = tmp->prev;
	Node *right = tmp;

	Node *new_node = initNode(data);
	new_node->prev = left;
	new_node->next = right;

	left->next = new_node;
	right->prev = new_node;
	list->size++;
	return;
}

typeData popFront(List *list)
{
	if (list->head == NULL)
		exit(EXIT_FAILURE);

	Node *prev = list->head;
	list->head = list->head->next;
	if (list->head != NULL)
		list->head->prev = NULL;

	if (prev == list->tail)
		list->tail = NULL;

	typeData tmp = prev->data;
	free(prev);

	list->size--;
	return tmp;
}

typeData popBack(List *list)
{
	if (list->tail == NULL)
		exit(EXIT_FAILURE);

	Node *next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail != NULL)
		list->tail->next = NULL;

	if (next == list->head)
		list->head = NULL;

	typeData tmp = next->data;
	free(next);

	list->size--;
	return tmp;
}

typeData erase(List *list, int index)
{
	Node *tmp = getAt(list, index);
	if (tmp == NULL)
		exit(EXIT_FAILURE);

	if (tmp->prev == NULL)
		return popFront(list);
	if (tmp->next == NULL)
		return popBack(list);

	Node *left = tmp->prev;
	Node *right = tmp->next;

	left->next = right;
	right->prev = left;

	typeData data = tmp->data;
	free(tmp);
	list->size--;
	return data;
}

void printList(List *list)
{
	printf("Size - %d\n", list->size);
	for (Node *ptr = list->head; ptr != NULL; ptr = ptr->next)
		printf("%s ", ptr->data.full_name);
	printf("\n");
}
