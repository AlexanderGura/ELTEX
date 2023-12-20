all: object execute

object:
	gcc server.c -g -c -o server.o
	gcc client_tcp.c -g -c -o client_tcp.o
	gcc server_tcp.c -g -c -o server_tcp.o

execute:
	gcc client_tcp.o -g -o client_tcp.exe
	gcc server_tcp.o server.o -g -o server_tcp.exe

clean:
	rm $(wildcard *.o) $(wildcard *.exe)