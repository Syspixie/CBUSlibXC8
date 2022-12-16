# CbusLibXC8
**MERG CBUS library for PIC18F MCUs - XC8 compiler.**

Written in C, with a smattering of assembler where necessary, these projects provide the basis
for creating the firmware for Microchip PIC18F based CBUS modules.

#### [CbusLibXC8](https://github.com/Syspixie/CbusLibXC8/tree/main/CbusLibXC8.X)

Code to provide basic CBUS functionality for PIC18F K80, K83, Q83 and Q84 processors.

#### [CbusLibBootXC8](https://github.com/Syspixie/CbusLibXC8/tree/main/CbusLibBootXC8.X)

Code to provide bootloader functionality for a CbusLibXC8 application.

**********

# Revision History

### Version 2b
Moved Interrupt Vector Table to be compatible with bootloader.

### Version 2a
Added support for Q83/84 family processors.  Implemented Interrupt Vector Table for K83 and Q83/84 processors.

### Version 1a
Initial version, supporting K80 and K83 family processors.

**********

# Notes

## Developed using:
- MPLAB X IDE (v6.00)
- XC8 (v2.40)
- MPLAB Snap In-Circuit Debugger/Programmer
- MERG CANUSB CAN bus USB interface
- MERG CANGIZMO CBUS module bench tester
- MERG FLiM Configuration Utility (v1.4.7.54)

## Project properties
Hidden in each project's configuration files are some important settings which are vital
in the building of the code.

#### CbusLibBootXC8

The bootloader must be built first.

    Project properties -> Conf: [...]
       XC8 Compiler -> Optimisations -> Optimisation level 2  
       XC8 Linker -> Memory model -> ROM ranges -> 0-7FF

*Optimisation level is optional*  
*ROM ranges* 0-7FF *limits the bootloader to the lowest 2K of memory*

#### CbusLibXC8

The application can then be built.

    Project properties -> Conf: [...]
       Loading -> Add loadable file -> {select the .hex file of the appropriate bootloader}
       XC8 Compiler -> Optimisations -> Optimisation level 2
       XC8 Linker -> Additional options -> Codeoffset -> 0x0800

*Optimisation level is optional*  
*Codeoffset* 0x0800 *places the application above the bootloader in memory*  

The required output is a *.unified.hex* file, which contains the bootloader and the application.
