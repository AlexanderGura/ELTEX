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
	int server_requests[3] = {JOIN, DISCONNECT, MESSAGE};
	int num_client = 0;
	long tmp_int;
	char tmp_str[10];
	while (is_active)
	{
		int j = 0;
		while(msgrcv(msgid, &buf, BUF_SIZE, server_requests[j % 3], IPC_NOWAIT) <= 0)
			j++;

		switch(buf.mtype)
		{
			case JOIN:
				if (num_client == CLIENTS_LEN)
				{
					buf.mtype = BAD_JOIN;
					msgsnd(msgid, &buf, BUF_SIZE, 0);
					break;
				}

				printf("Join. We have %d clients!\n", ++num_client);
				clients[num_client] = num_client * 10;
				buf.mtype = OK_JOIN;
				sprintf(buf.mtext, "%d ", clients[num_client]);
				strncpy(tmp_str, "Accessful connection!\n", BUF_SIZE);
				strcat(buf.mtext, tmp_str);
				printf("%s", buf.mtext);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			case DISCONNECT:
				buf.mtype = OK_DISCONNECT;
				clients[buf.mtype / 10] = 0;
				printf("Disconnect. We have %d clients!\n", --num_client);
				strncpy(buf.mtext, "Accessful disconnection!\n", BUF_SIZE);
				msgsnd(msgid, &buf, BUF_SIZE, 0);
				break;

			case MESSAGE:
				printf("%s", buf.mtext);
				sscanf(buf.mtext, "%ld", &tmp_int);
				for (int i = 1; i < CLIENTS_LEN; i++)
				{
					if (clients[i] == 0 || clients[i] == tmp_int)
						continue;
					buf.mtype = clients[i];
					msgsnd(msgid, &buf, BUF_SIZE, 0);
				}
				break;
		}

		if (num_client == 0)
		{
			printf("No clients!\n");
			break;
		}
	}
	if (msgctl(msgid, IPC_RMID, NULL) == -1)
		exit(EXIT_FAILURE);


	exit(EXIT_SUCCESS);
}
