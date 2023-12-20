msg:
	gcc client.c -g -c -o client.o
	gcc client_func.c -g -c -o client_func.o
	gcc client.o client_func.o -g -o client.exe

	gcc server.c -g -o server.exe

clean:
	rm $(wildcard *.o) $(wildcard *.exe)