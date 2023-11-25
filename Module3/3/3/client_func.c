#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include "message.h"
#include "client_func.h"

void join(int *msgid, msgbuf *buf, long *own_type)
{
	buf->mtype = JOIN;
	msgsnd(*msgid, buf, BUF_SIZE, 0);
	if (msgrcv(*msgid, buf, BUF_SIZE, BAD_JOIN, IPC_NOWAIT) >= 0)
	{
		fprintf(stderr, "Queue don't have places!\n");
		exit(EXIT_FAILURE);
	}

	msgrcv(*msgid, buf, BUF_SIZE, OK_JOIN, 0);
	sscanf(buf->mtext, "%ld", own_type);
	printf("%s", buf->mtext);
}

void send_message(int *msgid, msgbuf *buf, long *own_type)
{
	char type[BUF_SIZE];
	sprintf(type, "%ld ", *own_type);
	buf->mtype = MESSAGE;
	printf("Enter your message: ");
	fgets(buf->mtext, BUF_SIZE, stdin);
	strcat(type, buf->mtext);
	strncpy(buf->mtext, type, BUF_SIZE);
	msgsnd(*msgid, buf, BUF_SIZE, 0);
}

void recieve_message(int *msgid, msgbuf *buf, long *own_type)
{
	if (msgrcv(*msgid, buf, BUF_SIZE, *own_type, IPC_NOWAIT) <= 0)
	{
		printf("We don't have messages!\n");
		return;
	}
	printf("%s", buf->mtext);
}

void disconnect(int *msgid, msgbuf *buf, long *own_type)
{
	char type[BUF_SIZE];
	sprintf(type, "%ln ", own_type);
	buf->mtype = DISCONNECT;
	strncpy(buf->mtext, type, BUF_SIZE);
	msgsnd(*msgid, buf, BUF_SIZE, 0);
	msgrcv(*msgid, buf, BUF_SIZE, OK_DISCONNECT, 0);
	printf("%s", buf->mtext);
}
