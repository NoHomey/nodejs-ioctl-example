#Makefile
__name__ = ioctl_example
__device__ = /dev/$(__name__)_dev
__mode__ = 666
__major__ = $(shell grep -o "[0-9]\+ $(__name__)" /proc/devices | grep -o -m 1 "[0-9]\+")
__minor__ = 0
__npm_bin__ = ./node_modules/.bin
make_module_action = make -C /lib/modules/$(shell uname -r)/build M=$(PWD)
ccflags-y := -O3
obj-m := $(__name__).o

all: clean
	$(make_module_action) modules
	g++ -std=c++11 ioctl_export.cc
	./a.out
	$(__npm_bin__)/tsc

clean:
	$(make_module_action) clean
	rm -f ./a.out *.js IOCTL_EXAMPLE.*

load:
	dmesg -c
	clear
	insmod $(__name__).ko

device:
	mknod $(__device__) c $(__major__) $(__minor__)
	chmod $(__mode__) $(__device__)

unload:
	rmmod -f $(__name__)
	rm -f $(__device__)*

reset: clean
	 rm -fR typings node_modules