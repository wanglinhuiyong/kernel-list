ifneq  ($(KERNELRELEASE),)
obj-m:=list.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
CFLAGS := -g
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.symvers *.cmd *.cmd.o *mod.* modules*
endif
