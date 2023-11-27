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
	mq_unlink(SERVER_MQ);

	unsigned int prio;
	char text[BUF_SIZE];
	struct mq_attr attributes;
	attributes.mq_maxmsg = 10;
	attributes.mq_msgsize = BUF_SIZE;

	mqd_t mq_id = mq_open(SERVER_MQ, O_CREAT | O_RDWR | O_NONBLOCK, 0600, &attributes);

	if (mq_id == (mqd_t)-1)
	{
		fprintf(stderr, "queue open error!\n");
		exit(EXIT_FAILURE);
	}

	mqd_t client_id[CLIENT_LEN];
	mqd_t tmp;
	int client_count = 0;
	char client_count_str[3];
	char client_name[10];

	int is_active = 1;
	while (is_active)
	{
		mq_receive(mq_id, text, BUF_SIZE, &prio);

		switch(prio)
		{
			case CONNECT:
				strncpy(client_name, CLIENT_MQ, 10);
				sprintf(client_count_str, "%d", ++client_count);
				strcat(client_name, client_count_str);
				printf("%s\n", client_name);
				if (client_id[client_count] = mq_open(client_name,
				  O_CREAT | O_RDWR | O_NONBLOCK, 0600, &attributes) == -1);
					exit(EXIT_FAILURE);

				sprintf(text, "%d", client_id[client_count]);
				mq_send(mq_id, text, BUF_SIZE, client_id[client_count]);
				break;

			case DISCONNECT:
				sscanf(text, "%d", &tmp);
				if (mq_close(tmp) == -1)
					exit(EXIT_FAILURE);
				if (mq_unlink(tmp) == -1)
					exit(EXIT_FAILURE);
				break;

			default:
				for (int i = 0; i < CLIENT_LEN; i++)
				{
					if (prio == client_id[i])
						continue;
					mq_send(client_id[i], text, BUF_SIZE, client_id[i]);
				}
				break;
		}
	}

	if (mq_close(mq_id) == -1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}
