#ifndef MESSAGE_H_
#define MESSAGE_H_

#define MSG_NAME   "msg"
#define PROJ_ID     111
#define BUF_SIZE     30
#define CLIENTS_LEN  10
#define JOIN		  1
#define OK_JOIN 	  2
#define BAD_JOIN 	  3
#define DISCONNECT	  4
#define OK_DISCONNECT 5
#define MESSAGE 	  6

typedef struct msgbuf
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

#endif
