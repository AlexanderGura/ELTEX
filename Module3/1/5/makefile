# Create execute file;
contact.exe : main.o contact.o
	gcc main.o contact.o -g -o contact.exe -L. -llist

main.o : main.c
	gcc main.c -g -c -o main.o

contact.o : contact.c
	gcc contact.c -g -c -o contact.o -L. -llist

# Create library;
liblist.so : list.o
	gcc list.o -shared -g -o liblist.so

list.o : list.c
	gcc list.c -fPIC -g -c -o list.o
