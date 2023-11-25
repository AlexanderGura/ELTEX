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
	int num_client = 0;
	int tmp_int;
	char tmp_str[10];
	while (is_active)
	{
		msgrcv(msgid, &buf, BUF_SIZE, 0, 0);

		switch(buf.mtype)
		{
			case JOIN:
				printf("Join. We have %d clients!\n", ++num_client);
				buf.mtype = num_client * 10;
				clients[num_client] = buf.mtype;
				sprintf(buf.mtext, "%ld ", buf.mtype);
				strncpy(tmp_str, "Accessful connection!\n", BUF_SIZE);
				strcat(buf.mtext, tmp_str);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			case DISCONNECT:
				buf.mtype = atoi(buf.mtext);
				clients[buf.mtype / 10] = 0;
				printf("Disconnect. We have %d clients!\n", --num_client);
				strncpy(buf.mtext, "Accessful disconnection!\n", BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			case MESSAGE:
				sprintf(tmp_str, " (%ld)", buf.mtype);
				strcat(buf.mtext, tmp_str);
				tmp_int = buf.mtype;
				msgsnd(msgid, &buf, BUF_SIZE, MSG_EXCEPT);
				break;
		}

		if (num_client == -1)
		{
			printf("No clients!\n");
			break;
		}
	}
	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);


	exit(EXIT_SUCCESS);
}
