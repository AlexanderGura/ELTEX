calc.exe : calc.o operations.o
	gcc calc.o operations.o -rdynamic -g -o operations.exe -ldl
calc.o : calc.c
	gcc calc.c -c -g -o calc.o

operations.o : operations.c
	gcc operations.c -c -g -o operations.o
