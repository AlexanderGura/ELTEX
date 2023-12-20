ip.exe : main.o func.o
	gcc main.o func.o -g -o ip.exe

main.o : main.c
	gcc main.c -g -c -o main.o

func.o : func.c
	gcc func.c -g -c -o func.o

clean:
	rm main.o func.o ip.exe