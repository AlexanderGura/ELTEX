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
	char text[5];
	struct mq_attr attributes;
	attributes.mq_maxmsg = 10;
	attributes.mq_msgsize = 256;

	mqd_t mq_id = mq_open("/queue", O_CREAT | O_RDWR, 0666, attributes);
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

	msgbuf buf;
	buf.mtype = 1;
	while (1)
	{
		if (fgets(text, 5, fd) == NULL)
		{
			mq_send(mq_id, text, 10, 255);
			break;
		}
		mq_send(mq_id, text, 10, 1);
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
