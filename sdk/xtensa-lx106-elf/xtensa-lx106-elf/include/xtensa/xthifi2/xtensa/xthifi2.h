/* Copyright (c) 2008-2009 by Tensilica Inc.  ALL RIGHTS RESERVED.
/  These coded instructions, statements, and computer programs are the
/  copyrighted works and confidential proprietary information of Tensilica Inc.
/  They may not be modified, copied, reproduced, distributed, or disclosed to
/  third parties in any manner, medium, or form, in whole or in part, without
/  the prior written consent of Tensilica Inc.
/
/  The macros in this header whose names begin with "S6" are derived directly
/  from source code copyrighted by Stretch Inc., under license to Tensilica.
*/

/*  xthifi2.h	-  Xtensa HiFi2 audio board specific definitions.
 *
 *  The Tensilica XT-HiFi2 is a high performance platform for development of
 *  audio software using the HiFi2 engine. The physical platform is composed
 *  of a Stretch IP Camera base board with a modified SBIOS and a Tensilica
 *  custom daughterboard. The base board has an Xtensa LX processor with the
 *  Xtensa HiFi2 audio engine. The daughterboard provides I/O and JTAG debug.
 *
 *  The base board has a Stretch S6000 dual processor with heterogenous
 *  Xtensa LX cores sharing the same PIF memory map, and several peripherals.
 *  The first core, called the S6SCP, is a Stretch Configurable Processor 
 *  which runs the Stretch boot monitor SBIOS. The second, called the S6AUX,
 *  is a data plane processor with the Xtensa HiFi2 audio engine. The SBIOS has
 *  been modified to configure the board and start the S6AUX processor from
 *  reset. The S6SCP is concealed and only Xtensa development tools are needed.
 */

#ifndef _INC_XTHIFI2_H_
#define _INC_XTHIFI2_H_

#include <xtensa/config/core.h>
#include <xtensa/config/system.h>


/*
 *  Default assignment of XT-HiFi2 devices to external interrupts.
 *  There are many devices, and few interrupt inputs on this core.
 *  Several interrupt sources from the same device or a set of 
 *  closely related devices may share a single interrupt request.
 *  It is up to the (ideally single) device driver to disambiguate.
 *  To simplify drivers, sharing between unrelated devices is avoided.
 *  Except for the UARTs, there is only a single set of macros for
 *  each interrupt input, though it may be shared by several sources.
 */

/*  UART interrupts (both UARTS share): */
#ifdef XCHAL_EXTINT0_NUM
#define UART_INTNUM             XCHAL_EXTINT0_NUM
#define UART_INTLEVEL           XCHAL_EXTINT0_LEVEL
#define UART_INTMASK            XCHAL_EXTINT0_MASK
#else
#define UART_INTMASK            0
#endif

/*  Two Wire Interface (TWI/I2C) interrupt: */
#ifdef XCHAL_EXTINT1_NUM
#define I2C_INTNUM              XCHAL_EXTINT1_NUM
#define I2C_INTLEVEL            XCHAL_EXTINT1_LEVEL
#define I2C_INTMASK             XCHAL_EXTINT1_MASK
#else
#define I2C_INTMASK             0
#endif

/* Serial Peripheral Interface (SPI) interrupts: */
#ifdef XCHAL_EXTINT2_NUM
#define SPI_INTNUM              XCHAL_EXTINT2_NUM
#define SPI_INTLEVEL            XCHAL_EXTINT2_LEVEL
#define SPI_INTMASK             XCHAL_EXTINT2_MASK
#else
#define SPI_INTMASK             0
#endif

/*  Enhanced Generic Interface Bus (eGIB) interrupt: */
#ifdef XCHAL_EXTINT3_NUM
#define EGIB_INTNUM             XCHAL_EXTINT3_NUM
#define EGIB_INTLEVEL           XCHAL_EXTINT3_LEVEL
#define EGIB_INTMASK            XCHAL_EXTINT3_MASK
#else
#define EGIB_INTMASK            0
#endif

/* I2S (DMAC HIF ch. 2-3 terminal count and I2S error) interrupts: */
#ifdef XCHAL_EXTINT4_NUM
#define I2S_INTNUM              XCHAL_EXTINT4_NUM
#define I2S_INTLEVEL            XCHAL_EXTINT4_LEVEL
#define I2S_INTMASK             XCHAL_EXTINT4_MASK
#else
#define I2S_INTMASK             0
#endif

/*  Ethernet (DMAC HIF ch. 0-1 terminal count, GMAC stats & err) interrupts: */
#ifdef XCHAL_EXTINT5_NUM
#define ETHERNET_INTNUM         XCHAL_EXTINT5_NUM
#define ETHERNET_INTLEVEL       XCHAL_EXTINT5_LEVEL
#define ETHERNET_INTMASK        XCHAL_EXTINT5_MASK
#else
#define ETHERNET_INTMASK        0
#endif

/*  Audio (HDMI) interrupts: */
#ifdef XCHAL_EXTINT6_NUM
#define AUDIO_INTNUM            XCHAL_EXTINT6_NUM
#define AUDIO_INTLEVEL          XCHAL_EXTINT6_LEVEL
#define AUDIO_INTMASK           XCHAL_EXTINT6_MASK
#else
#define AUDIO_INTMASK           0
#endif


/*
 * S6000 Processor Physical Memory Map (address space) from Stretch s6000.h .
 */

#define S6000_DDR_BASE            0x40000000
#define S6000_DDR_END             0xbfffffff
#define S6000_DDR_MIRROR_BASE     0x00000000
#define S6000_DDR_MIRROR_END      0x1fffffff

#define S6_EFI_BASE               0x33f00000
#define S6_MFRAM_BASE_128         0x33f00000
#define S6_MFRAM_BASE_64          0x33f10000
#define S6_MFRAM_BASE_32          0x33f20000
#define S6_MFRAM_BASE_16          0x33f30000
#define S6_MSA_STATE_BASE         0x33f40000
#define S6_MSA_CONTROL_REG_BASE   0x33f60000
#define S6_MSA_CONFIG_BASE        0x33f70000
#define S6_EFI_END                0x33ffffff
#define S6_PCIE_DATARAM1_BASE     0x34000000
#define S6_PCIE_DATARAM1_END      0x3400ffff
#define S6_PIF_DATARAM1_BASE      0x37ffc000
#define S6_PIF_DATARAM1_END       0x37ffffff
#define S6_GMAC_MEM_BASE          0x38000000
#define S6_GMAC_MEM_END           0x39ffffff
#define S6_I2S_MEM_BASE           0x3a000000
#define S6_I2S_MEM_END            0x3bffffff
#define S6_EGIB_MEM_BASE          0x3c000000
#define S6_EGIB_MEM_END           0x3dffffff
#define S6_PCIE_CFG_BASE          0x3e000000
#define S6_PCIE_DATARAM_BASE      0x3f000000
#define S6_PCIE_DATARAM_END       0x3f00ffff
#define S6_PIF_DATARAM_BASE       0x3ffe0000
#define S6_PIF_DATARAM_END        0x3ffeffff
#define S6_XLMI_DATARAM_BASE      0x3fff0000
#define S6_XLMI_DATARAM_END       0x3fffffff
#define S6_XLMI_DATARAM1_BASE     0x3fff0000
#define S6_XLMI_DATARAM1_END      0x3fff3fff
#define S6_DDR_BASE               S6000_DDR_BASE
#define S6_DDR_END                S6000_DDR_END
#define S6_DDR_MIRROR_BASE        S6000_DDR_MIRROR_BASE
#define S6_DDR_MIRROR_END         S6000_DDR_MIRROR_END
#define S6_PCIE_APER_BASE         0xc0000000
#define S6_PCIE_APER_SIZE         0x40000000    // for XT0
#define S6_PCIE_APER_END          0xffffffff    // for XT0

/* XLMI Memory Map */
#define S6_XLMI_XAD_BASE          0x37f80000
#define S6_XLMI_XAD_EVENT_BASE    0x37f81000
#define S6_XLMI_LMSDMA_BASE       0x37f84000
#define S6_XLMI_NIDMA_BASE        0x37f88000
#define S6_XLMI_NI_BASE           0x37f8c000
#define S6_XLMI_NB_BASE           0x37f90000
#define S6_XLMI_XAD_TRACE_BASE    0x37f94000

/* SCB Memory Map */
#define S6_SCB_APB_BASE           0x20000000
#define S6_SCB_NB_BASE            0x20010000
#define S6_SCB_LMSDMA_BASE        0x20020000
#define S6_SCB_NI_BASE            0x20030000
#define S6_SCB_NIDMA_BASE         0x20040000
#define S6_SCB_NS_BASE            0x20050000
#define S6_SCB_DDR_BASE           0x20060000
#define S6_SCB_GBLREG_BASE        0x20070000
#define S6_SCB_DP_BASE            0x20080000
#define S6_SCB_DP_END             0x2008ffff
#define S6_SCB_DPDMA_BASE         0x20090000
#define S6_SCB_EGIB_BASE          0x200a0000
#define S6_SCB_PCIE_BASE          0x200b0000
#define S6_SCB_I2S_BASE           0x200c0000
#define S6_SCB_GMAC_BASE          0x200d0000
#define S6_SCB_HIFDMA_BASE        0x200e0000
#define S6_SCB_GBLREG2_BASE       0x200f0000
#define S6_SCB_TRACEMEM_BASE      0x20100000

/* APB Memory Map */
#define S6_APB_UART0_BASE         0x20000000
#define S6_APB_UART1_BASE         0x20001000
#define S6_APB_INTCTRL_BASE       0x20002000
#define S6_APB_SPI_BASE           0x20003000
#define S6_APB_I2C_BASE           0x20004000
#define S6_APB_GPIO_BASE          0x20008000

/* Auxiliary (HiFi2) processor virtual memory map (address space) */
#define S6_AUX_MEM_BASE           0xf0000000
#define S6_AUX_MEM_MAX_SIZE       0x10000000
#define S6_AUX_MEM_END            0xffffffff
#define S6_AUX_VECTOR_BASE        0xffff0000
#define S6_AUX_VECTOR_SIZE        0x00010000

/*  System ROM:	 */
#define XTBOARD_ROM_SIZE		XSHAL_ROM_SIZE
#ifdef XSHAL_ROM_VADDR
#define XTBOARD_ROM_VADDR		XSHAL_ROM_VADDR
#endif
#ifdef XSHAL_ROM_PADDR
#define XTBOARD_ROM_PADDR		XSHAL_ROM_PADDR
#endif

/*  System RAM:	 */
#define XTBOARD_RAM_SIZE		XSHAL_RAM_SIZE
#ifdef XSHAL_RAM_VADDR
#define XTBOARD_RAM_VADDR		XSHAL_RAM_VADDR
#endif
#ifdef XSHAL_RAM_PADDR
#define XTBOARD_RAM_PADDR		XSHAL_RAM_PADDR
#endif
#define XTBOARD_RAM_BYPASS_VADDR	XSHAL_RAM_BYPASS_VADDR
#define XTBOARD_RAM_BYPASS_PADDR	XSHAL_RAM_BYPASS_PADDR

/* 
 * The miniboot loader sets up the NorthBridge on the board to map a portion
 * of DDR (as much as possible) at the top of the physical DDR address space
 * into the SysRAM and SysROM address spaces of the S6AUX processor. The
 * XSHAL_ macros referenced above represent the S6AUX virtual address space.
 * The physical addresses (outside the S6000's NorthBridge) are required for
 * DMA, so are defined here (note: the PADDR macros above refer to the Xtensa
 * processor and are in the S6000 *virtual* space inside the NorthBridge).
 */
#define XTHIFI2_DDR_TOTAL           0x08000000     // total size of DDR 128 MB
#define XTHIFI2_DDR_TOP             (S6_DDR_BASE + XTHIFI2_DDR_TOTAL)
#if defined(XSHAL_RAM_SIZE) && defined (XSHAL_ROM_SIZE)
#define XTHIFI2_DDR_SIZE            (XSHAL_RAM_SIZE + XSHAL_ROM_SIZE)
#else
#define XTHIFI2_DDR_SIZE            0
#endif
#define XTHIFI2_DDR_BASE            (XTHIFI2_DDR_TOP - XTHIFI2_DDR_SIZE)


/*
 *  Things that depend on device addresses.
 *
 *  For the following, a 512MB region is used if it contains any system RAM,
 *  system ROM, local memory, XLMI, or other board device or memory.
 *  Regions containing devices are forced to cache-BYPASS mode regardless
 *  of whether the macro is _WRITEBACK vs. _BYPASS etc.
 */

#define XTBOARD_CACHEATTR_WRITEBACK	0x4FF2222F
#define XTBOARD_CACHEATTR_WRITEALLOC	0x4FF2222F
#define XTBOARD_CACHEATTR_WRITETHRU	0x1FF2222F
#define XTBOARD_CACHEATTR_BYPASS	0x2FF2222F
#define XTBOARD_CACHEATTR_DEFAULT	XTBOARD_CACHEATTR_WRITEBACK

#endif /*_INC_XTHIFI2_H_*/

