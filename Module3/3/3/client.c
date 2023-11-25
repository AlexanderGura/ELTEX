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

int main(int argc, char *argv[])
{
	key_t key = ftok(MSG_NAME, PROJ_ID);
	int msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1)
	{
		fprintf(stderr, "msg open error!\n");
		exit(EXIT_FAILURE);
	}

	long own_type;
	msgbuf buf;
	join(&msgid, &buf, &own_type);

	int is_active = 1;
	while (is_active)
	{
		printf("\n1. Type message;\n2. Get message;\nq. Quit;\n");
		printf("Enter your choice: ");
		char choice = getchar();
		getchar();

		switch(choice)
		{
			case '1':
				send_message(&msgid, &buf, &own_type);
				break;

			case '2':
				recieve_message(&msgid, &buf, &own_type);
				break;

			case 'q':
				disconnect(&msgid, &buf, &own_type);
				is_active = 0;
				break;

			default:
				printf("Wrong action!\n");
				break;
		}
	}

	exit(EXIT_SUCCESS);
}
