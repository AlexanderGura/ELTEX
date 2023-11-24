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

	msgbuf buf;
	int is_active = 1;
	while (is_active)
	{
		msgrcv(msgid, &buf, BUF_SIZE, 0, 0);

		switch(buf.mtype)
		{
			case FIRST_TYPE:
				printf("Message from first: %s", buf.mtext);
				buf.mtype = SECOND_TYPE;

				printf("Enter your message: ");
				fgets(buf.mtext, BUF_SIZE, stdin);
				if (strcmp(buf.mtext, "q\n") == 0)
				{
					is_active = 0;
					strncpy(buf.mtext, "bye", BUF_SIZE);
					buf.mtype = SND_END;
				}
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				if (buf.mtype == SND_END)
					msgrcv(msgid, &buf, BUF_SIZE, FST_END, 0);
				break;

			case FST_END:
				buf.mtype = SND_END;
				strncpy(buf.mtext, "bye", BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				is_active = 0;
				break;
		}
	}

	if (buf.mtype == SND_END)
	{
		if (msgctl(msgid, IPC_RMID, NULL) == -1)
			exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

	return 0;
}
