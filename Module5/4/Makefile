obj-m += kernel_sp.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc user_sp.c -o user.exe

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm user.exe