include Makefile.inc

BUILD := $(shell pwd)/build

.PHONY: all
all: git-init fpga u-boot vitis petalinux

.PHONY: petalinux
petalinux:
	$(MAKE) -C sw/petalinux

.PHONY: u-boot
u-boot:
	$(MAKE) -C sw/u-boot-xlnx xilinx_zynq_virt_defconfig
	$(MAKE) -C sw/u-boot-xlnx -j

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
	$(MAKE) -C sw/petalinux clean
	$(MAKE) -C sw/u-boot distclean
	rm -rf $(BUILD)/vitis/*
	rm -rf $(BUILD)/petalinux/*

.PHONY: git-init
git-init:
	git submodule init --update --remote

