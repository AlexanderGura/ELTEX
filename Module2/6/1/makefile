# Create library;
ar rc liblist.a list.o:
	gcc list.c -g -c -o list.o

# Create execute file;
list.exe : main.o contact.o
	gcc main.o contact.o -g -o list.exe -L. -llist

main.o : main.c
	gcc main.c -g -c -o main.o

contact.o : contact.c
	gcc contact.c -g -c -o contact.o
