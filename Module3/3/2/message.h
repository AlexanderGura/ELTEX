#ifndef MESSAGE_H_
#define MESSAGE_H_

#define MSG_NAME "msg"
#define PROJ_ID   111
#define BUF_SIZE    5
#define FIRST_TYPE  1
#define SECOND_TYPE 2
#define FST_END   255
#define SND_END   256

typedef struct msgbuf
{
	long mtype;
	char mtext[BUF_SIZE];
} msgbuf;

#endif
