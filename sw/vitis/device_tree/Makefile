include ../../../Makefile.inc

# This Makefile requires an installation of device-tree-compiler "dtc". On Ubuntu 18.04 it can
# be installed using sudo apt install device-tree-compiler

SHELL := /bin/bash
VIVADO := source /opt/Xilinx/Vivado/$(VERSION)/settings64.sh
XSCT := xsct
XSA_DIR := $(shell pwd)/../xsa
BUILD := build
DTB := $(BUILD)/system.dtb
DTS := $(BUILD)/system.dts $(BUILD)/system-top.dts

.PHONY: all
all: $(DTB) 

.PHONY: clean
clean: 
	rm -rf .Xil build 

.PHONY: device-tree
device-tree: $(DTB)

$(DTB): $(BUILD) $(DTS) 
	gcc -I my_dts -E -nostdinc -undef -D__DTS__ -x assembler-with-cpp -o $(BUILD)/system.dts $(BUILD)/system-top.dts
	dtc -I dts -O dtb -o $@ $(BUILD)/system.dts 

$(BUILD):
	$(VIVADO) && $(XSCT) -eval "\
		hsi open_hw_design ./../../xsa/design_1_wrapper.xsa; \
		hsi set_repo_path ./device-tree-xlnx; \
		hsi create_sw_design device-tree -os device_tree -proc ps7_cortexa9_0; \
		hsi generate_target -dir build; \
		exit; \
		"
	cp system-top.dts $(BUILD)/system-top.dts
	rm -rf .Xil
