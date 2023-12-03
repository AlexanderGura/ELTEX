#ifndef SERVER_H_
#define SERVER_H_

#define BUF_SIZE 256
#define CLIENT_NUM 5

int sub(int a, int b);
int mult(int a, int b);
int divs(int a, int b);
void print_users();
void error(const char *message);
void send_file(int sockfd);

#endif
