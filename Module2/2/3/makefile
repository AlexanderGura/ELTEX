calc.exe : calc.o operations.o
	gcc calc.o operations.o -g -o operations.exe -lm

calc.o : calc.c
	gcc calc.c -c -g -o calc.o

operations.o : operations.c
	gcc operations.c -c -g -o operations.o

clean:
	rm calc.o operations.o operations.exe