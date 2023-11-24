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
	int own_type = FIRST_TYPE;
	buf.mtype = JOIN;
	msgsnd(msgid, &buf, BUF_SIZE, 0);
	msgrcv(msgid, &buf, BUF_SIZE, own_type, 0);
	printf("%s", buf.mtext);

	while (1)
	{
		buf.mtype = FIRST_TYPE;
		printf("Enter your message: ");
		fgets(buf.mtext, BUF_SIZE, stdin);
		msgsnd(msgid, &buf, BUF_SIZE, 0);
		msgrcv(msgid, &buf, BUF_SIZE, own_type, 0);
		printf("%s", buf.mtext);


		printf("Enter your message: ");
		fgets(buf.mtext, BUF_SIZE, stdin);
		if (strcmp(buf.mtext, "q\n") == 0)
		{
			buf.mtype = DISCONNECT;
			strncpy(buf.mtext, "10", BUF_SIZE);
			msgsnd(msgid, &buf, BUF_SIZE, 0);
			break;
		}
	}

	exit(EXIT_SUCCESS);

	return 0;
}
