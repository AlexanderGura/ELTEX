all:
	gcc main.c -g -c -o main.o
	gcc func.c -g -c -o func.o
	gcc main.o func.o -g -o exec.exe
	gcc _str.c -g -o _str.exe
	gcc _sum.c -g -o _sum.exe

clean:
	rm $(wildcard *.exe) $(wildcard *.o)