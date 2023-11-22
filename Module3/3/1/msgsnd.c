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
	printf("%d\n", key);
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

	buffer buf;
	buf.mtype = 1;
	while (fgets(buf.mtext, BUF_SIZE, fd) != NULL)
	{
		msgsnd(msgid, &buf, sizeof(buf), 0);
	}
	buf.mtype = 255;
	buf.mtext[0] = '\0';
	msgsnd(msgid, &buf, sizeof(buf), 0);

	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);

	if (fclose(fd) == -1)
	{
		fprintf(stderr, "file close error!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);

	return 0;
}
