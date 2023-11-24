#ifndef MESSAGE_H_
#define MESSAGE_H_

#define MSG_NAME  "msg"
#define PROJ_ID    111
#define BUF_SIZE    30
#define CLIENTS_LEN 10
#define JOIN		 1
#define DISCONNECT	 2
#define FIRST_TYPE 	10
#define SECOND_TYPE 20

typedef struct msgbuf
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

#endif
