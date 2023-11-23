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
		if (fgets(buf.mtext, BUF_SIZE, fd) == NULL)
			break;
		msgsnd(msgid, &buf, BUF_SIZE, 0);
	}

	buf.mtype = SND_END;
	buf.mtext[0] = '\0';
	msgsnd(msgid, &buf, BUF_SIZE, 0);
	msgrcv(msgid, &buf, BUF_SIZE, RCV_END, 0);

	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);

	if (fclose(fd) != 0)
	{
		fprintf(stderr, "file open error!\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

	return 0;
}
