/* Copyright (c) 2002 by Tensilica Inc.  ALL RIGHTS RESERVED.
/  These coded instructions, statements, and computer programs are the
/  copyrighted works and confidential proprietary information of Tensilica Inc.
/  They may not be modified, copied, reproduced, distributed, or disclosed to
/  third parties in any manner, medium, or form, in whole or in part, without
/  the prior written consent of Tensilica Inc.
*/

/*  xt1000.h  -  Xtensa XT1000 Evaluation Board specific definitions  */

#ifndef _INC_XT1000_H_
#define _INC_XT1000_H_

#include <xtensa/config/core.h>
#include <xtensa/config/system.h>


/*
 *  Default assignment of XT1000 devices to external interrupts.
 *  On the SiChip2 boards, if you change the jumpers for these
 *  interrupts, you must change these definitions accordingly.
 */

/*  Ethernet interrupt:  */
#ifdef XCHAL_EXTINT3_NUM
#define SONIC83934_INTNUM	XCHAL_EXTINT3_NUM
#define SONIC83934_INTLEVEL	XCHAL_EXTINT3_LEVEL
#define SONIC83934_INTMASK	XCHAL_EXTINT3_MASK
#else
#define SONIC83934_INTMASK	0
#endif

/*  DUART channel 1 interrupt (P1 - console):  */
#ifdef XCHAL_EXTINT4_NUM
#define DUART16552_1_INTNUM	XCHAL_EXTINT4_NUM
#define DUART16552_1_INTLEVEL	XCHAL_EXTINT4_LEVEL
#define DUART16552_1_INTMASK	XCHAL_EXTINT4_MASK
#else
#define DUART16552_1_INTMASK	0
#endif

/*  DUART channel 2 interrupt (P2 - 2nd serial port):  */
#ifdef XCHAL_EXTINT5_NUM
#define DUART16552_2_INTNUM	XCHAL_EXTINT5_NUM
#define DUART16552_2_INTLEVEL	XCHAL_EXTINT5_LEVEL
#define DUART16552_2_INTMASK	XCHAL_EXTINT5_MASK
#else
#define DUART16552_2_INTMASK	0
#endif



/*
 *  Device addresses.
 *
 *  Note:  for endianness-independence, use 32-bit loads and stores for all
 *  register accesses to Ethernet, DUART and LED devices.  Undefined bits
 *  may need to be masked out if needed when reading if the actual register
 *  size is smaller than 32 bits.
 *
 *  Note:  XT1000 bus byte lanes are defined in terms of msbyte and lsbyte
 *  relative to the processor.  So 32-bit registers are accessed consistently
 *  from both big and little endian processors.  However, this means byte
 *  sequences are not consistent between big and little endian processors.
 *  This is fine for RAM, and for ROM if ROM is created for a specific
 *  processor (and thus has correct byte sequences).  However this may be
 *  unexpected for Flash, which might contain a file-system that one wants
 *  to use for multiple processor configurations (eg. the Flash might contain
 *  the Ethernet card's address, endianness-independent application data, etc).
 *  That is, byte sequences written in Flash by a core of a given endianness
 *  will be byte-swapped when seen by a core of the other endianness.
 *  Someone implementing an endianness-independent Flash file system will
 *  likely handle this byte-swapping issue in the Flash driver software.
 */

#define DUART16552_XTAL_FREQ	18432000	/* crystal frequency in Hz */
#define XTBOARD_FLASH_SIZE	0x400000	/* 4 MB */
#define XTBOARD_EPROM_SIZE	0x040000	/* 256 kB (max; but 256kB always used) */
#define XTBOARD_ASRAM_SIZE	0x100000	/* 1 MB */

#ifdef XSHAL_IOBLOCK_BYPASS_PADDR
/*  AMD Am29LV008B x 4 Flash devices:  */
# define XTBOARD_FLASH_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0x8000000)
/*  SONIC SN83934 Ethernet controller/transceiver:  */
# define SONIC83934_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xC000000)
/*  Bus Interface registers:  */
# define XTBOARD_BUSINT_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xD010000)
/*  16-segment LED display:  */
# define XT1000_LED_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xD040000)
/*  National-Semi PC16552D DUART:  */
# define DUART16552_1_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xD050020)	/* channel 1 (P1 - console) */
# define DUART16552_2_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xD050000)	/* channel 2 (P2) */
/*  Asynchronous Static RAM:  */
# define XTBOARD_ASRAM_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xD400000)
/*  2 x 16-bit EPROMs:  */
# define XTBOARD_EPROM_PADDR	(XSHAL_IOBLOCK_BYPASS_PADDR+0xD800000)
#endif /* XSHAL_IOBLOCK_BYPASS_PADDR */

/*  These devices might be accessed cached:  */
#ifdef XSHAL_IOBLOCK_CACHED_PADDR
# define XTBOARD_FLASH_CACHED_PADDR	(XSHAL_IOBLOCK_CACHED_PADDR+0x8000000)
# define XTBOARD_ASRAM_CACHED_PADDR	(XSHAL_IOBLOCK_CACHED_PADDR+0xD400000)
# define XTBOARD_EPROM_CACHED_PADDR	(XSHAL_IOBLOCK_CACHED_PADDR+0xD800000)
#endif /* XSHAL_IOBLOCK_CACHED_PADDR */

/*  Same thing over again, this time with virtual addresses:  */

#ifdef XSHAL_IOBLOCK_BYPASS_VADDR
/*  AMD Am29LV008B x 4 Flash devices:  */
# define XTBOARD_FLASH_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0x8000000)
/*  SONIC SN83934 Ethernet controller/transceiver:  */
# define SONIC83934_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xC000000)
/*  Bus Interface registers:  */
# define XTBOARD_BUSINT_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xD010000)
/*  16-segment LED display:  */
# define XT1000_LED_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xD040000)
/*  National-Semi PC16552D DUART:  */
# define DUART16552_1_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xD050020)	/* channel 1 (P1 - console) */
# define DUART16552_2_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xD050000)	/* channel 2 (P2) */
/*  Asynchronous Static RAM:  */
# define XTBOARD_ASRAM_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xD400000)
/*  2 x 16-bit EPROMs:  */
# define XTBOARD_EPROM_VADDR	(XSHAL_IOBLOCK_BYPASS_VADDR+0xD800000)
#endif /* XSHAL_IOBLOCK_BYPASS_VADDR */

/*  These devices might be accessed cached:  */
#ifdef XSHAL_IOBLOCK_CACHED_VADDR
# define XTBOARD_FLASH_CACHED_VADDR	(XSHAL_IOBLOCK_CACHED_VADDR+0x8000000)
# define XTBOARD_ASRAM_CACHED_VADDR	(XSHAL_IOBLOCK_CACHED_VADDR+0xD400000)
# define XTBOARD_EPROM_CACHED_VADDR	(XSHAL_IOBLOCK_CACHED_VADDR+0xD800000)
#endif /* XSHAL_IOBLOCK_CACHED_VADDR */


/*  System ROM:  */
#define XTBOARD_ROM_SIZE		XSHAL_ROM_SIZE
#ifdef XSHAL_ROM_VADDR
#define XTBOARD_ROM_VADDR	XSHAL_ROM_VADDR
#endif
#ifdef XSHAL_ROM_PADDR
#define XTBOARD_ROM_PADDR	XSHAL_ROM_PADDR
#endif

/*  System RAM:  */
#define XTBOARD_RAM_SIZE		XSHAL_RAM_SIZE
#ifdef XSHAL_RAM_VADDR
#define XTBOARD_RAM_VADDR	XSHAL_RAM_VADDR
#endif
#ifdef XSHAL_RAM_PADDR
#define XTBOARD_RAM_PADDR	XSHAL_RAM_PADDR
#endif
#define XTBOARD_RAM_BYPASS_VADDR	XSHAL_RAM_BYPASS_VADDR
#define XTBOARD_RAM_BYPASS_PADDR	XSHAL_RAM_BYPASS_PADDR


#if 0

/*  SONIC SN83934 Ethernet controller/transceiver:  */
#ifdef XSHAL_ETHER_VADDR
#define SONIC83934_VADDR	XSHAL_ETHER_VADDR
#endif

/*  National-Semi PC16552D DUART:  */
#define DUART16552_XTAL_FREQ	18432000	/* crystal frequency in Hz */
#ifdef XSHAL_UART_VADDR
#define DUART16552_1_VADDR	(XSHAL_UART_VADDR+0x20)	/* channel 1 (console) */
#define DUART16552_2_VADDR	XSHAL_UART_VADDR	/* channel 2 (2nd serial port) */
#endif

/*  16-segment LED display:  */
#ifdef XSHAL_LED_VADDR
#define XT1000_LED_VADDR	XSHAL_LED_VADDR
#endif

/*  AMD Am29LV008B x 4 Flash devices:  */
#ifdef XSHAL_FLASH_VADDR
#define XTBOARD_FLASH_VADDR	XSHAL_FLASH_VADDR
#define XTBOARD_FLASH_SIZE	XSHAL_FLASH_SIZE
#endif

/*  System ROM:  */
#ifdef XSHAL_ROM_VADDR
#define XTBOARD_ROM_VADDR	XSHAL_ROM_VADDR
#define XTBOARD_ROM_SIZE		XSHAL_ROM_SIZE
#endif

/*  System RAM:  */
#ifdef XSHAL_RAM_VADDR
#define XTBOARD_RAM_VADDR	XSHAL_RAM_VADDR
#define XTBOARD_RAM_SIZE		XSHAL_RAM_SIZE
#define XTBOARD_RAM_BYPASS_VADDR	XSHAL_RAM_BYPASS_VADDR
#endif

#endif /*0*/


/*
 *  Things that depend on device addresses.
 */

#define XTBOARD_CACHEATTR_WRITEBACK	XSHAL_XT1000_CACHEATTR_WRITEBACK
#define XTBOARD_CACHEATTR_WRITEALLOC	XSHAL_XT1000_CACHEATTR_WRITEALLOC
#define XTBOARD_CACHEATTR_WRITETHRU	XSHAL_XT1000_CACHEATTR_WRITETHRU
#define XTBOARD_CACHEATTR_BYPASS	XSHAL_XT1000_CACHEATTR_BYPASS
#define XTBOARD_CACHEATTR_DEFAULT	XSHAL_XT1000_CACHEATTR_DEFAULT

#define XTBOARD_BUSINT_PIPE_REGIONS	XSHAL_XT1000_PIPE_REGIONS
#define XTBOARD_BUSINT_SDRAM_REGIONS	0


#endif /*_INC_XT1000_H_*/

