all:
	gcc calc.c -c -g -o calc.o
	gcc operations.c -c -g -o operations.o
	gcc calc.o operations.o -rdynamic -g -o operations.exe -ldl

clean:
	rm operations.o calc.o operations.exe