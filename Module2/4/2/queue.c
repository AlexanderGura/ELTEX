#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Secondary functions;
static void pushFront(Queue *queue, int priority, typeData data)
{
	Node *new_node = initNode(priority, data);
	new_node->next = queue->head;

	if (queue->head != NULL)
		queue->head->prev = new_node;
	queue->head = new_node;

	if (queue->tail == NULL)
		queue->tail = new_node;
	queue->size++;
}


static void pushBack(Queue *queue, int priority, typeData data)
{
	Node *new_node = initNode(priority, data);
	new_node->prev = queue->tail;

	if (queue->tail != NULL)
		queue->tail->next = new_node;
	queue->tail = new_node;

	if (queue->head == NULL)
		queue->head = new_node;
	queue->size++;
}

static typeData popFront(Queue *queue)
{
	if (queue->head == NULL)
		exit(EXIT_FAILURE);

	Node *prev = queue->head;
	queue->head = queue->head->next;
	if (queue->head != NULL)
		queue->head->prev = NULL;

	if (prev == queue->tail)
		queue->tail = NULL;

	typeData tmp = prev->data;
	free(prev);

	queue->size--;
	return tmp;
}

static typeData popBack(Queue *queue)
{
	if (queue->tail == NULL)
		exit(EXIT_FAILURE);

	Node *next = queue->tail;
	queue->tail = queue->tail->prev;
	if (queue->tail != NULL)
		queue->tail->next = NULL;

	if (next == queue->head)
		queue->head = NULL;

	typeData tmp = next->data;
	free(next);

	queue->size--;
	return tmp;
}

static typeData erase(Queue *queue, int index)
{
	Node *tmp = getAt(queue, index);
	if (tmp == NULL)
		exit(EXIT_FAILURE);

	if (tmp->prev == NULL)
		return popFront(queue);
	if (tmp->next == NULL)
		return popBack(queue);

	Node *left = tmp->prev;
	Node *right = tmp->next;

	left->next = right;
	right->prev = left;

	typeData data = tmp->data;
	free(tmp);
	queue->size--;
	return data;
}

// Main queue functions;
Queue* initQueue()
{
	Queue *tmp = (Queue*) malloc(sizeof(Queue));
	if (tmp == NULL)
		exit(EXIT_FAILURE);

	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}

Node* initNode(int priority, typeData data)
{
	Node *new_node = malloc(sizeof(Node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);

	new_node->priority = priority;
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

Node* getAt(Queue *queue, int index)
{
	if (index < 0 || index >= queue->size)
		exit(EXIT_FAILURE);

	Node* tmp = queue->head;
	for(int i = 0; tmp && i < index; i++)
		tmp = tmp->next;
	return tmp;
}

void push(Queue* queue, int priority, typeData data)
{
	if (queue->head == NULL || queue->head->priority > priority)
	{
		pushFront(queue, priority, data);
		return;
	}

	if (queue->tail->priority < priority)
	{
		pushBack(queue, priority, data);
		return;
	}

	Node *tmp = queue->head;
	while (tmp->priority < priority)
		tmp = tmp->next;

	Node *left = tmp->prev;
	Node *right = tmp;

	Node *new_node = initNode(priority, data);
	new_node->prev = left;
	new_node->next = right;

	left->next = new_node;
	right->prev = new_node;
	queue->size++;
	return;
}

typeData pop(Queue *queue)
{
	return popFront(queue);
}

typeData popPriority(Queue *queue, int priority)
{
	for (int i = 0; i < queue->size; i++)
	{
		if (getAt(queue, i)->priority == priority)
			return erase(queue, i);
	}
	printf("\nQueue don't have item with %d priority.\n", priority);
	printf("Function return '-1'!\n");
	return -1;
}

typeData popLesserPriority(Queue *queue, int priority)
{
	for (int i = 0; i < queue->size; i++)
	{
		if (getAt(queue, i)->priority > priority)
			return erase(queue, i);
	}
	printf("\nQueue don't have item with lesser priority.\n");
	printf("Function return '-1'!\n");
	return -1;
}

void printQueue(Queue *queue)
{
	printf("Size - %d\n", queue->size);
	int i = 0;
	for (Node *ptr = queue->head; ptr != NULL; ptr = ptr->next)
	{
		if (i++ % 5 == 0)
			printf("\n");
		printf("%d(%d) ", ptr->data, ptr->priority);
	}
	printf("\n");
}

void deleteQueue(Queue **queue)
{
	for (Node *tmp = (*queue)->head; tmp != NULL; tmp = (*queue)->head)
	{
		(*queue)->head = (*queue)->head->next;
		free(tmp);
	}
	free(*queue);
}
