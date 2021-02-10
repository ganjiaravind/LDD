obj-m := char_dev_dynamic.o char_dev_static.o char_dev_old.o char_dev_class.o
obj-m += char_buf_copy.o

.PHONY: default
default: build

build:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules

.PHONY: clean
clean:
	@$(MAKE) -C /lib/modules/$(shell uname -r)/build/ KBUILD_EXTMOD=$(shell pwd) modules clean
