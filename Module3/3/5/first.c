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

	unsigned int prio;
	char text[BUF_SIZE];
	struct mq_attr attributes;
	attributes.mq_maxmsg = 10;
	attributes.mq_msgsize = BUF_SIZE;

	mqd_t mq_id = mq_open(MQ_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0600, &attributes);
	if (mq_id == (mqd_t)-1)
	{
		fprintf(stderr, "queue open error!\n");
		exit(EXIT_FAILURE);
	}

	int is_active = 1;
	while (is_active)
	{
		printf("1. Type message\n2. Get message\nq. Quit");
		printf("\nEnter your choice: ");
		char choice = getchar();
		getchar();

		switch(choice)
		{
			case '1':
				printf("Enter your message: ");
				fgets(text, BUF_SIZE, stdin);
				mq_send(mq_id, text, BUF_SIZE, FIRST_PRIO);
				break;

			case '2':
				if (mq_receive(mq_id, text, BUF_SIZE, &prio) == -1)
					printf("\nWe don't have messages for you!\n\n");

				if (prio == SECOND_PRIO)
					printf("\nMessage: %s\n", text);
				else if (prio == SECOND_END)
				{
					mq_send(mq_id, text, BUF_SIZE, FIRST_END);
					is_active = 0;
				}
				else
					mq_send(mq_id, text, BUF_SIZE, prio);
				break;

			case 'q':
				is_active = 0;
				mq_send(mq_id, text, BUF_SIZE, FIRST_END);
				break;
		}
	}

	if (mq_close(mq_id) == -1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);
}
