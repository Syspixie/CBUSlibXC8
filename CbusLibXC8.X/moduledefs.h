/**
 * @file CbusLibXC8 moduledefs.h
 * @copyright (C) 2022 Konrad Orlowski     <syspixie@gmail.com>
 * 
 *  CbusLibXC8 is licensed under the:
 *      Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 *      International License.
 *  To view a copy of this license, visit:
 *      http://creativecommons.org/licenses/by-nc-sa/4.0/
 *  Postal address: Creative Commons, PO Box 1866, Mountain View, CA 94042, USA
 * 
 * License summary:
 * 
 *  You are free to:
 *      Share, copy and redistribute the material in any medium or format;
 *      Adapt, remix, transform, and build upon the material.
 *  The licensor cannot revoke these freedoms as long as you follow the license
 *  terms.
 *
 *  Attribution: You must give appropriate credit, provide a link to the
 *  license, and indicate if changes were made. You may do so in any reasonable
 *  manner, but not in any way that suggests the licensor endorses you or your
 *  use.
 * 
 *  NonCommercial: You may not use the material for commercial purposes. **(see
 *  note below)
 *
 *  ShareAlike: If you remix, transform, or build upon the material, you must
 *  distribute your contributions under the same license as the original.
 *
 *  No additional restrictions: You may not apply legal terms or technological
 *  measures that legally restrict others from doing anything the license
 *  permits.
 * 
 * ** For commercial use, please contact the original copyright holder(s) to
 * agree licensing terms.
 * 
 *  This software is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.
 * 
 *******************************************************************************
 * 
 * CbusLibXC8 and CbusLibBootXC8 is code that can form the basis of the firmware
 * required to build a Model Electronic Railway Group (MERG) CBUS compatible
 * module.  It was developed using the Microchip XC8 compiler and MPLAB X IDE,
 * and targets PIC18F MCUs with built-in CAN bus peripherals.
 * 
 * The software was created to meet the CBUS specification as detailed in the
 * "Developer's Guide for CBUS" version 6c.
 * 
 * Credit to Mike Bolton and Gil Fuchs for the development of CBUS, and to
 * Pete Brownlow, Ian Hogg, and many other MERG members, for the development
 * and testing of CBUS modules, hardware and firmware, over the past 15 years.
 * 
 * MERG CBUS: https://www.merg.org.uk/resources/cbus
 */

/**
 * @author Konrad Orlowski
 * @date September 2022
 * 
 * Primary location for application and hardware specific settings.
 */

#ifndef MODULEDEFS_H
#define	MODULEDEFS_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "cbusdefs.h"
#include "hardware.h"


// Uncomment if 'test mode' is supported - i.e. pressing the program button for
// more than 8 seconds invokes a test mode; requires application support for
// state handling (see interact.c)
//#define INCLUDE_INTERACT_TEST_MODE

// Uncomment if CAN bus statistics (IO and errors counts) are collected;
// only useful if there is application support for reporting the data
//#define INCLUDE_CBUS_CAN_STATS


#define MAJOR_VERSION 1
#define MINOR_VERSION 'a'
#define BETA_VERSION 0                  // 0: production

#define CURRENT_EEPROM_VERSION 1
#define CURRENT_FLASH_VERSION 1

// Parameter block values
#define MODULE_MANUFACTURER MANU_MERG   // FlimConfig accepts limited values
#define MODULE_ID 99                    // MERG module ID
#define MODULE_TYPE_NAME "THING  "      // MERG module name (7 characters)
#define MODULE_FLAGS PF_COMBI           // Producer & consumer
#define CPU_MANUFACTURER CPUM_MICROCHIP
#define CBUS_BUS PB_CAN

// Node variables and events
#define NUM_NODE_VARS 20                // Max: 255
#define MAX_NUM_EVENTS 32               // Max: 255
#define EVENT_NUM_VARS 20               // Max: 255
#define EVENT_HASH_SIZE 32

// Timed response
#define TIMEDRESPONSE_QUEUE_LENGTH 8    // Must be power of 2
#define TIMEDRESPONSE_DELAY_MILLIS 10   // Time between successive messages

// CAN bus buffers
#define RX_FIFO_LENGTH 8    // Must be power of 2
#define TX_FIFO_LENGTH 8    // Must be power of 2


//******************************************************************************

// The following definitions should NOT be edited - the values are fixed, or are
// calculated from the definitions above


#define EVENT_SIZE (6 + EVENT_NUM_VARS)

// Bottom up...
#define APPLICATION_BASE_ADDRESS 0x000800
#define PARAMETER_BLOCK_ADDRESS (APPLICATION_BASE_ADDRESS + 0x20)
#define MODULE_TYPE_NAME_ADDRESS (PARAMETER_BLOCK_ADDRESS + sizeof(parameterBlock_t))

// Top down...
// Put flashVersion on the first word boundary below top
#define FLASH_VERSION_ADDRESS (FLASH_TOP & ~1)
// Next is nodeVariables, on a word boundary
#define NODE_VAR_ADDRESS ((FLASH_VERSION_ADDRESS - NUM_NODE_VARS) & ~1)
// Finally eventTable, on a block boundary
#define EVENTS_FLASH_ADDRESS ((NODE_VAR_ADDRESS - (MAX_NUM_EVENTS * EVENT_SIZE)) & ~(FLASH_BLOCK_SIZE - 1))

// Interrupt vector table, at the top of bootloader region
// Note: can't use calculation to derive address: __interrupt can't handle it!
#if defined(CPU_FAMILY_PIC18_K83)
#define IVT_BASE_ADDRESS 0x000760   // 80 vectors; 0x000800 - (2 * 80)
#endif
#if defined(CPU_FAMILY_PIC18_Q83)
#define IVT_BASE_ADDRESS 0x0006E0   // 144 vectors; 0x000800 - (2 * 144)
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* MODULEDEFS_H */
