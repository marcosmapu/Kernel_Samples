KERNELDIR = /lib/modules/`uname -r`/build
MODULES = hello2.ko
obj-m += hello2.o

all:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	make -C $(KERNELDIR) M=$(PWD) clean
install:
	make -C $(KERNELDIR) M=$(PWD) modules_install
quickInstall:
	cp $(MODULES) /lib/modules/`uname -r`/extra