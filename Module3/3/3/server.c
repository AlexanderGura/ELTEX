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
	int clients[CLIENTS_LEN];
	int num_client = 1;
	int tmp;
	while (is_active)
	{
		msgrcv(msgid, &buf, BUF_SIZE, 0, 0);

		switch(buf.mtype)
		{
			case JOIN:
				clients[num_client] = num_client * 10;
				buf.mtype = clients[num_client++];
				strncpy(buf.mtext, "Accessful connection!\n", BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			case DISCONNECT:
				buf.mtype = atoi(buf.mtext);
				clients[buf.mtype / 10] = 0;
				strncpy(buf.mtext, "Accessful disconnection!\n", BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			default:
				for (int i = 1; i < CLIENTS_LEN; i++)
				{
					if (clients[i] == 0 && clients[i] != buf.mtype / 10)
						continue;
					buf.mtype = clients[i];
					msgsnd(msgid, &buf, BUF_SIZE, 0);
				}
				break;
		}
	}

	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);

	exit(EXIT_SUCCESS);

	return 0;
}
