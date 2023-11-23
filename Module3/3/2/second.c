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

	FILE *fd = fopen("second_msg.txt", "r");
	if (fd == NULL)
	{
		fprintf(stderr, "file open error!\n");
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
				printf("%s", buf.mtext);
				buf.mtype = SECOND_TYPE;
				if (fgets(buf.mtext, BUF_SIZE,fd) == NULL)
					is_active = 0;
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;
			case SND_END:
				buf.mtype = RCV_END;
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				is_active = 0;
				break;
			default:
				break;
		}
	}
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
