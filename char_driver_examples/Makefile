obj-m := char_dev_dynamic.o char_dev_static.o

.PHONY: default
default: build

build:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules

.PHONY: clean
clean:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules clean
