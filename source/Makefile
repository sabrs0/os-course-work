#ifneq ($(KERNELRELEASE),)
#	obj-m := myrootkit.o
#	myrootkit-objs := ./src/myrootkit.o 
#else
#	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#	PWD := $(shell pwd)
#default:
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
#clean:
#	rm -fv *.order
#	rm -fv *.symvers
#	rm -fv *.ko
#	rm -fv *.mod*
#	rm -fv *.o
#endif

KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$$PWD modules
sign:
	/usr/src/linux-headers-$(shell uname -r)/scripts/sign-file sha256 ~/signing_key.priv     ~/signing_key.x509 $$PWD/myrootkit.ko
clean:
	rm -fv *.order
	rm -fv *.symvers
	rm -fv *.ko
	rm -fv *.mod*
	rm -fv *.o
	rm -fv ./src/*.o
