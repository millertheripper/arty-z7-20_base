VERSION ?= 2020.2
PETALINUX := source /opt/Xilinx/petalinux/$(VERSION)/settings.sh &&
DISTDIR := $(shell pwd)/../../build/petalinux

.PHONY: all
all: update-fpga BOOT_BIN dist

.PHONY: BOOT_BIN
BOOT_BIN: petalinux 	
	$(PETALINUX) petalinux-package --boot --fpga --u-boot --force
	$(PETALINUX) petalinux-package --wic --extra-bootfiles "image.ub system.dtb"

.PHONY: petalinux
petalinux:
	$(PETALINUX) petalinux-config --silentconfig
	$(PETALINUX) petalinux-build

.PHONY: clean
clean:
	$(PETALINUX) petalinux-build -x mrproper -f

.PHONY: update-fpga
update-fpga:
	$(PETALINUX) petalinux-config --silentconfig --get-hw-description ../xsa/

.PHONY: dist
dist:
	rm -rf ${DISTDIR} && mkdir -p ${DISTDIR}
	cp $(shell pwd)/images/linux/{boot.scr,BOOT.BIN,image.ub,system.dtb,uImage,rootfs.tar.gz} ${DISTDIR}
	tar -czvf ${DISTDIR}/sdimage-wic.tar.gz $(shell pwd)/images/linux/petalinux-sdimage.wic
	



