all:
	# Create library;
	gcc list.c -fPIC -g -c -o list.o
	gcc list.o -shared -g -o liblist.so

	# Create app;
	gcc main.c -g -c -o main.o
	gcc contact.c -g -c -o contact.o -L. -llist
	gcc main.o contact.o -g -o contact.exe -L. -llist

clean:
	rm $(wildcard *.o) $(wildcard *.exe) $(wildcard *.so)