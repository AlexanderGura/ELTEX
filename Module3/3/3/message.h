#ifndef MESSAGE_H_
#define MESSAGE_H_

#define MSG_EXCEPT 020000

#define MSG_NAME  "msg"
#define PROJ_ID    111
#define BUF_SIZE    30
#define CLIENTS_LEN 10
#define JOIN		 1
#define OK_JOIN 	 2
#define DISCONNECT	 3
#define MESSAGE 	 4

typedef struct msgbuf
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

#endif
