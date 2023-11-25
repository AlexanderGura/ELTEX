#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include "message.h"

int main(int argc, char *argv[])
{
	char text[5];
	int prio;
	struct mq_attr attr, old_attr;
	attr.mq_flags = O_NONBLOCK;

	mqd_t mq_id = mq_open("/queue", O_CREAT | O_RDWR, 0666, attr);
	if (mq_id == (mqd_t)-1)
	{
		fprintf(stderr, "queue open error!\n");
		exit(EXIT_FAILURE);
	}

	if (mq_setattr(mq_id, &attr, NULL) == -1)
	{
		fprintf(stderr, "queue setattr error!\n");
		exit(EXIT_FAILURE);
	}

	if (mq_getattr(mq_id, &old_attr) == -1)
	{
		fprintf(stderr, "queue getattr error!\n");
		exit(EXIT_FAILURE);
	}

	if ((old_attr.mq_flags & O_NONBLOCK) == 0)
		printf("NONBLOCK not set!\n");

	msgbuf buf;
	while (1)
	{
		if (mq_receive(mq_id, text, 5, &prio) == -1)
		{
			fprintf(stderr, "receive error!\n");
			exit(EXIT_FAILURE);
		}
		if (prio == 255)
			break;
		printf("%s", text);
	}

	if (mq_unlink("queue") == -1)
	{
		fprintf(stderr, "unlink error!\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
