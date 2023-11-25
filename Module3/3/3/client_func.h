#ifndef CLIENT_FUNC_H
#define CLIENT_FUNC_H

void join(int *, msgbuf *, long *);
void send_message(int *,msgbuf *, long *);
void recieve_message(int *, msgbuf *, long *);
void disconnect(int *, msgbuf *, long *);

#endif
