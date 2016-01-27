/*******************************************************************************

Copyright (c) 2008 Tensilica Inc.  ALL RIGHTS RESERVED.
These coded instructions, statements, and computer programs are the
copyrighted works and confidential proprietary information of Tensilica Inc.
They may not be modified, copied, reproduced, distributed, or disclosed to
third parties in any manner, medium, or form, in whole or in part, without
the prior written consent of Tensilica Inc.
--------------------------------------------------------------------------------

uart-16550-board.h  Board-specific UART info on the XT-HiFi2 board.

Interface between board-independent driver and board-specific header.

This is used by a board-independent 16550 UART driver to obtain board-specific
information about 1 instance of the 16550 UART on the board, such as the device
register base address and spacing (a function of how the address lines are 
connected on the board) and the frequency of the UART clock. The driver does
not refer directly to the board-specific header, which therefore is not 
constrained to use macro names consistent with other boards.

!! Must not contain any board-specific macro names (only UART specific). !!

Included at compile-time via an include path specific to the board.

The XT-HiFi2 board contains two 16550 UARTs and uses a dedicated UART clock.

*******************************************************************************/

#ifndef _UART_16550_BOARD_H
#define _UART_16550_BOARD_H

#include <xtensa/xtbsp.h>               /* BSP API */
#include <xtensa/xthifi2.h>             /* Board info */


/* Base address of UART's registers. UART1 is connected to DB9 on debug card. */
#define UART_16550_REGBASE S6_APB_UART1_BASE

/* 
The UART's registers are connected at word addresses on the XT-HiFi2.
Each byte-wide register appears as the least-significant-byte (LSB) of the 
word regardless of the endianness of the processor.
*/
#define UART_16550_REGSPACING 4
typedef unsigned uart16550_reg_t;

/* UART Clock Frequency in Hz */
#define UART_16550_XTAL_FREQ 1843200    /* 1.8432 MHz */

/* UART Clock Frequency Precision in Hz. Optional.
   For rounding measured processor clock frequency if UART is used for that.
   If this is not defined for a board, no rounding is done. */
#define UART_16550_XTAL_PRECISION 200   /* 200 Hz */

/* UART Interrupt Number */
#ifdef UART_INTNUM
#define UART_16550_INTNUM UART_INTNUM
#endif


/* Include generic information shared by all boards that use this device. */
#include    <xtensa/uart-16550.h>

#endif /* _UART_16550_BOARD_H */

