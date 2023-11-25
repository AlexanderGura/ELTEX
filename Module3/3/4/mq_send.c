#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "message.h"

int main(int argc, char *argv[])
{
	mq_unlink(MQ_NAME);

	char text[BUF_SIZE];
	struct mq_attr attributes;
	attributes.mq_maxmsg = 10;
	attributes.mq_msgsize = BUF_SIZE;

	mqd_t mq_id = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0600, &attributes);
	if (mq_id == (mqd_t)-1)
	{
		fprintf(stderr, "queue open error!\n");
		exit(EXIT_FAILURE);
	}

	FILE *fd = fopen("msg.txt", "r");
	if (fd == NULL)
	{
		fprintf(stderr, "file open error!\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		if (fgets(text, BUF_SIZE, fd) == NULL)
		{
			mq_send(mq_id, text, BUF_SIZE, MQ_END);
			break;
		}
		mq_send(mq_id, text, BUF_SIZE, MQ_PRIO);
	}

	if (mq_close(mq_id) == -1)
		exit(EXIT_FAILURE);

	if (fclose(fd) != 0)
	{
		fprintf(stderr, "file open error!\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
