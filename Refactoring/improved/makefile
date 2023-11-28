prog.exe : prog.o list.o contact.o
	gcc prog.o list.o contact.o -g -o prog.exe

prog.o : prog.c
	gcc prog.c -g -c -o prog.o

list.o : list.c
	gcc list.c -g -c -o list.o

contact.o : contact.c
	gcc contact.c -g -c -o contact.o

