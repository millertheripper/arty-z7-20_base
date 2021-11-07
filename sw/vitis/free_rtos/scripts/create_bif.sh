BOOT_BIF=$3/sw.bif
touch $BOOT_BIF
FSBL_ELF=$1/$2/export/$2/sw/$2/boot/fsbl.elf

# Create boot image partition file 
echo "//arch = zynq; split = false; format = BIN">> $BOOT_BIF
echo "the_ROM_image:"                            >> $BOOT_BIF
echo "{"                                         >> $BOOT_BIF
echo "  [bootloader]$FSBL_ELF"                   >> $BOOT_BIF
echo "  $1/$2/hw/$2.bit"                         >> $BOOT_BIF
echo "  $1/app/Debug/app.elf"                    >> $BOOT_BIF
echo "}"                                         >> $BOOT_BIF

# Create boot image 
bootgen -arch zynq -image $BOOT_BIF -o $3/BOOT.bin -w on