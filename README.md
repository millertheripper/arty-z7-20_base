# Arty-Z7-20 Base
**Vivado Version: 2020.2**
------
Contents: 
Base project demonstrating access to LEDs and buttons from bare-metal and linux
- Vitis: Bare Metal Register/Driver access
- Vitis: FreeRTOS demonstration
- Linux: GPIO-Keys with device tree

## Hardware Requirements:
- Digilent Arty-Z7-20
- MicroUSB Cable
- SD Card

## Software Requirements
- Ubuntu 18.04 host system for compilation
- Vivado/Vitis 2020.2
- Petalinux 2020.2
- Terminal program (TeraTerm or minicom)


## Compile BSP project:
------
Compile everything: 
```bash
make
```

Create and compile Vivado project: 
```bash
make fpga
```

Create and compile Vitis bare metal project, create boot binary
```bash
make vitis
```

Create and compile petalinux project
```bash
make petalinux
```

Applying changes:
------
Vivado Block Design: From tcl shell:
```bash
write_bd_tcl [get_property DIRECTORY [current_project]]/../source/scripts/bd.tcl -include_layout -force
```

Software Design (Vitis): Put vitis source code under:
* Put all files in ./vitis/src 

BSP directory structure: 
------
```bash
├── build                       <--- Build Outputs (FPGA and Boot binaries)
├── hw                          <--- All source files related to Vivado Design 
│   ├── build                   <--- Vivado Project  
│   ├── scripts                 <--- TCL scripts to recreate project in batch mode
│   │   └── settings.tcl        <--- Set FPGA type, project name, and number of processors for compilation 
│   └── source
│       ├── constraints         <--- Constraints location. Files will be imported during creation
│       ├── hdl                 <--- Put HDL IP blocks (non block design) here
│       ├── ip                  <--- Put IP blocks (used by ip integrator) here
│       └── scripts
│           └── bd.tcl          <--- TCL script to recreate the block design.
└── sw
    ├── petalinux               <--- Petalinux project 
    ├── vitis                   <--- Project folder containing bare metal application 
    │   ├── build               <--- Boot image is located here (BOOT.bin)
    │   ├── scripts             <--- TCL scripts for batch mode
    │   ├── src                 <--- Bare metal source code files
    │   └── ws                  <--- Vitis workspace
    └── xsa                     <--- Hardware description file, exported by vivado
```