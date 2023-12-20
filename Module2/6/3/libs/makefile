all:
	gcc add.c -fPIC -c -o add.o
	gcc add.o -shared -o libadd.so

	gcc sub.c -fPIC -c -o sub.o
	gcc sub.o -shared -o libsub.so

	gcc mult.c -fPIC -c -o mult.o
	gcc mult.o -shared -o libmult.so

	gcc div.c -fPIC -c -o div.o
	gcc div.o -shared -o libdiv.so

	gcc power.c -fPIC -c -o power.o -lm
	gcc power.o -lm -shared -o libpower.so -lm

	gcc sqroot.c -fPIC -c -o sqroot.o -lm
	gcc sqroot.o -shared -o libsqroot.so -lm

	gcc natlog.c -fPIC -c -o natlog.o -lm
	gcc natlog.o -shared -o libnatlog.so -lm

clean:
	rm $(wildcard *.o)
	rm $(wildcard *.so)