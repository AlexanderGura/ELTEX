#ifndef QUEUE_H_
#define QUEUE_H_

typedef int typeData;

typedef struct Node
{
	typeData data;
	int priority;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct Queue
{
	int size;
	Node *head;
	Node *tail;
} Queue;

// Secondary functions;
static void pushFront(Queue *, int, typeData);
static void pushBack(Queue *, int, typeData);

static typeData popFront(Queue *);
static typeData popBack(Queue *);
static typeData erase(Queue *, int);

// Main queue functions;
Queue* initQueue();
Node* getAt(Queue *, int);
void push(Queue *, int, typeData);
typeData pop(Queue *);
typeData popPriority(Queue *, int);
typeData popLesserPriority(Queue *, int);
void printQueue(Queue *);
void deleteQueue(Queue **queue);

#endif
