obj-m := mutex_example.o spin_example.o completion_example.o

.PHONY: default
default: build

build:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules

.PHONY: clean
clean:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules clean
