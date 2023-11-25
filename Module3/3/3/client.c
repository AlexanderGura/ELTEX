#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include "message.h"

int main(int argc, char *argv[])
{
	key_t key = ftok(MSG_NAME, PROJ_ID);
	int msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1)
	{
		fprintf(stderr, "msg open error!\n");
		exit(EXIT_FAILURE);
	}

	int own_type;
	msgbuf buf;

	buf.mtype = JOIN;
	msgsnd(msgid, &buf, BUF_SIZE, 0);
	msgrcv(msgid, &buf, BUF_SIZE, OK_JOIN, 0);
	sscanf(buf.mtext, "%d", &own_type);
	printf("%s", buf.mtext);

	int is_active = 1;
	char type[BUF_SIZE];
	sprintf(type, "%d ", own_type);
	while (is_active)
	{
		printf("\n1. Type message;\n2. Get message;\nq. Quit;\n");
		printf("Enter your choice: ");
		char choice = getchar();
		getchar();

		switch(choice)
		{
			case '1':
				buf.mtype = MESSAGE;
				printf("Enter your message: ");
				fgets(buf.mtext, BUF_SIZE, stdin);
				strcat(type, buf.mtext);
				strncpy(buf.mtext, type, BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			case '2':
				if (msgrcv(msgid, &buf, BUF_SIZE, own_type, IPC_NOWAIT) <= 0)
				{
					printf("We don't have messages!\n");
					break;
				}
				printf("%s", buf.mtext);
				break;

			case 'q':
				buf.mtype = DISCONNECT;
				strncpy(buf.mtext, type, BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				is_active = 0;
				break;

			default:
				printf("Wrong action!\n");
				break;
		}
	}

	exit(EXIT_SUCCESS);
}
