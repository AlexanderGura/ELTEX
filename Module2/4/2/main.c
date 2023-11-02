#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
	Queue *queue = initQueue();
	int priority, data;

	for (int i = 0; i < 100; i++)
	{
		priority = rand() % 256;
		data = rand() % 1000;
		push(queue, priority, data);
	}
	printQueue(queue);

	while (popLesserPriority(queue, 20) != -1);
	printQueue(queue);
	deleteQueue(&queue);
}
