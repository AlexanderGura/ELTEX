#include <stdio.h>
#include <stdlib.h>
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
	while (1)
	{
		msgrcv(msgid, &buf, BUF_SIZE, 0, 0);
		if (buf.mtype == SND_END)
		{
			buf.mtype = RCV_END;
			msgsnd(msgid, &buf, BUF_SIZE, 0);
			break;
		}
		printf("%s", buf.mtext);
	}
	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);

	return 0;
}
