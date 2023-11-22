#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include "message.h"

typedef struct buffer
{
	long mtype;
	char mtext[10];
} buffer;

int main(int argc, char *argv[])
{
	key_t key = ftok("message01.txt", 111);
	int msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1)
	{
		fprintf(stderr, "msg open error!\n");
		exit(EXIT_FAILURE);
	}

	buffer buf;
	buf.mtype = 1;
	int is_rcv = 1;
	while(is_rcv);
	{
		msgrcv(msgid, &buf, sizeof(buf), 1, 0);
		if (buf.mtype == 255)
			is_rcv = 0;
		printf("%s\n", buf.mtext);
	}

	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);

	return 0;
}
