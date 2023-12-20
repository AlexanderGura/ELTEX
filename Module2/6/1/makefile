all:
	gcc list.c -g -c -o list.o
	ar rc liblist.a list.o
	gcc main.c -g -c -o main.o
	gcc contact.c -g -c -o contact.o
	gcc main.o contact.o -g -o list.exe -L. -llist

clean:
	rm main.o contact.o list.o list.exe liblist.a 