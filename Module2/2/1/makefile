contact.exe : main.o contact.o
	gcc main.o contact.o -g -o contact.exe

main.o : main.c
	gcc main.c -c -g -o main.o

contact.o : contact.c
	gcc contact.c -c -g -o contact.o

clean:
	rm contact.o main.o contact.exe