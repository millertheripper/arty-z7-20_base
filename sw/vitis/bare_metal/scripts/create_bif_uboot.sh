BOOT_BIF=$3/sw_uboot.bif
touch $BOOT_BIF

# Create boot image partition file 
echo "//arch = zynq; split = false; format = BIN">> $BOOT_BIF
echo "the_ROM_image:"                            >> $BOOT_BIF
echo "{"                                         >> $BOOT_BIF
echo "  [bootloader]$1/fsbl/Debug/fsbl.elf"      >> $BOOT_BIF
echo "  $1/$2/hw/$2.bit"                         >> $BOOT_BIF
echo "  $1/../../../u-boot-xlnx/u-boot.elf"      >> $BOOT_BIF
echo "  [load=0x0c100000]$1/app/Debug/app.elf"   >> $BOOT_BIF
echo "}"                                         >> $BOOT_BIF

# Create boot image 
bootgen -arch zynq -image $BOOT_BIF -o $3/BOOT_uboot.bin -w on