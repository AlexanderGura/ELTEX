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

	mqd_t mq_id = mq_open(MQ_NAME, O_RDWR | O_NONBLOCK);
	if (mq_id == (mqd_t)-1)
	{
		fprintf(stderr, "queue open error!\n");
		exit(EXIT_FAILURE);
	}

	int is_active = 1;
	while (is_active)
	{
		printf("1. Type message;\n2. Get message;\nq. Quit;");
		printf("\nEnter your choice: ");
		char choice = getchar();
		getchar();

		switch(choice)
		{
			case '1':
				printf("Enter your message: ");
				fgets(text, BUF_SIZE, stdin);
				mq_send(mq_id, text, BUF_SIZE, SECOND_PRIO);
				break;

			case '2':
				if (mq_receive(mq_id, text, BUF_SIZE, &prio) == -1)
				{
					printf("\nWe don't have messages for you!\n\n");
					break;
				}

				if (prio == FIRST_PRIO)
					printf("\nMessage: %s\n", text);
				else if (prio == FIRST_END)
				{
					mq_send(mq_id, text, BUF_SIZE, SECOND_END);
					is_active = 0;
				}
				else
					mq_send(mq_id, text, BUF_SIZE, prio);
				break;

			case 'q':
				mq_send(mq_id, text, BUF_SIZE, SECOND_END);
				is_active = 0;
				break;
		}
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
