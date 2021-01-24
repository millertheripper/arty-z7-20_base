include Makefile.inc

BUILD := $(shell pwd)/build

.PHONY: all
all: fpga vitis

.PHONY: vitis
vitis:
	$(MAKE) -C sw/vitis/bare_metal
	$(MAKE) -C sw/vitis/free_rtos

.PHONY: fpga
fpga:
	$(MAKE) -C hw

.PHONY: clean
clean: clean-hw clean-sw
	rm -rf $(BUILD)
	mkdir -p $(BUILD)

.PHONY: clean-hw
clean-hw:
	$(MAKE) -C hw clean

.PHONY: clean-sw
clean-sw:
	$(MAKE) -C sw/vitis/bare_metal clean
	$(MAKE) -C sw/vitis/free_rtos clean
