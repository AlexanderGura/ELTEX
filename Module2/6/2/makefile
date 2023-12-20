all:
	gcc list.c -fPIC -g -c -o list.o
	gcc list.o -shared -g -o liblist.so
	gcc main.c -g -c -o main.o
	gcc contact.c -g -c -o contact.o -L. -llist
	gcc main.o contact.o -g -o list.exe -L. -llist

clean:
	rm list.o liblist.so main.o contact.o list.exe