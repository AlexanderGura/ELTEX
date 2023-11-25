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
	char text[BUF_SIZE];
	unsigned int prio;

	mqd_t mq_id = mq_open(MQ_NAME, O_RDWR);
	if (mq_id == (mqd_t)-1)
	{
		fprintf(stderr, "queue open error!\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		mq_receive(mq_id, text, BUF_SIZE, &prio);
		if (prio == MQ_END)
			break;
		printf("%s", text);
	}

	if (mq_close(mq_id) == -1)
	{
		fprintf(stderr, "close error!\n");
		exit(EXIT_FAILURE);
	}

	if (mq_unlink(MQ_NAME) == -1)
	{
		fprintf(stderr, "unlink error!\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
