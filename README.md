# Arty-Z7-20 Base
Base project demonstrating access to LEDs and buttons from bare-metal and linux
- Vitis: Bare Metal Register/Driver access
- Linux: GPIO-Keys

## Hardware Requirements:
- Digilent Arty-Z7-20
- MicroUSB Cable
- SD Card

## Software Requirements
- Vivado/Vitis 2020.1
- Petalinux 2020.1
- Terminal program (TeraTerm or minicom)

## How to build project
- make

# Revision control
## From Vivado tcl shell: 
- write_bd_tcl [get_property DIRECTORY [current_project]]/../source/scripts/bd.tcl -include_layout -force

## Vitis source files:
- ./sw/vitis/src