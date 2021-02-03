obj-m := helloworld.o
obj-m += modexport.o
obj-m += moddep.o
obj-m += moddep_header.o
obj-m += task.o

.PHONY: default
default: build

build:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules

.PHONY: clean
clean:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules clean
