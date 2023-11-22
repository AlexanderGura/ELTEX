#ifndef MESSAGE_H_
#define MESSAGE_H_

#define MSG_NAME "message01"
#define PROJ_ID 111
#define BUF_SIZE 10


typedef struct msgbuf
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

#endif
