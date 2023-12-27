ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m   += hello1.o
obj-m   += hello2.o

ccflags-y := -g -I$(src)/inc			# add debugging info

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello1.ko hello1.ko.unstripped
	$(CROSS_COMPILE)strip -g hello1.ko  # strip only debugging info

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

%.s %.i: %.c 							# just use make hello.s instead of objdump
	$(MAKE) -C $(KDIR) M=$$PWD $@

endif