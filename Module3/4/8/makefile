memory:
	gcc main.c -g -c -o main.o
	gcc func.c -g -c -o func.o
	gcc main.o func.o -g -o memory.exe

clean:
	rm $(wildcard *.o) $(wildcard *.exe)