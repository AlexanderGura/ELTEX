memory:
	gcc main.c -g -c -o main.o -lrt
	gcc func.c -g -c -o func.o -lrt
	gcc main.o func.o -g -o memory.exe -lrt

clean:
	rm $(wildcard *.o) $(wildcard *.exe)