libadd.so:
	gcc add.c -fPIC -c -o add.o
	gcc add.o -shared -o libadd.so

libsub.so:
	gcc sub.c -fPIC -c -o sub.o
	gcc sub.o -shared -o libsub.so

libmult.so:
	gcc mult.c -fPIC -c -o mult.o -lm
	gcc mult.o -shared -o libmult.so

libdiv.so:
	gcc div.c -fPIC -c -o div.o
	gcc div.o -shared -o libdiv.so

libpower.so:
	gcc power.c -fPIC -c -o power.o -lm
	gcc power.o -lm -shared -o libpower.so -lm

libsqroot.so:
	gcc sqroot.c -fPIC -c -o sqroot.o -lm
	gcc sqroot.o -shared -o libsqroot.so -lm

libnatlog.so:
	gcc natlog.c -fPIC -c -o natlog.o -lm
	gcc natlog.o -shared -o libnatlog.so -lm

clean:
	rm libadd.so
	rm libsub.so
	rm libmult.so
	rm libdiv.so
	rm libpower.so
	rm sqroot.so
	rm natlog.so
