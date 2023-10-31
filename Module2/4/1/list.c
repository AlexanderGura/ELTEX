#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* initNode(double data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

List* initList()
{
	List* lst = malloc(sizeof(List));
	lst->head = NULL;
	lst->tail = NULL;
	return lst;
}

List* pushFront(List* lst, double data)
{
	Node* new_node = initNode(data);

	if (lst->head == NULL)
	{
		lst->head = new_node;
		lst->tail = new_node;
		return lst;
	}
	new_node->next = lst->head;
	lst->head->prev = new_node;
	lst->head = new_node;
	return lst;
}

List* pushBack(List* lst, double data)
{
	Node* new_node = initNode(data);

	if (lst->tail == NULL)
	{
		lst->tail = new_node;
		lst->head = new_node;
		return lst;
	}
	new_node->prev = lst->tail;
	lst->tail->next = new_node;
	lst->tail = new_node;
	return lst;
}


void printList(List* lst)
{
	for(Node* ptr = lst->head; ptr != NULL; ptr = ptr->next)
		printf("%f ", ptr->data);
	printf("\n");
}

void deleteList(List* lst)
{
	for(Node* ptr = lst->head; ptr != NULL; ptr = lst->head)
	{
		lst->head = lst->head->next;
		free(ptr);
	}
}

