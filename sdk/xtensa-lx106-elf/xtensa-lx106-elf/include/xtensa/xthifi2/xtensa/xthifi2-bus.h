/*******************************************************************************

Copyright (c) 2008 by Tensilica Inc.  ALL RIGHTS RESERVED.
These coded instructions, statements, and computer programs are the
copyrighted works and confidential proprietary information of Tensilica Inc.
They may not be modified, copied, reproduced, distributed, or disclosed to
third parties in any manner, medium, or form, in whole or in part, without
the prior written consent of Tensilica Inc.
--------------------------------------------------------------------------------

xthifi2-bus.h       Bus Address Translation for XT-HiFi2 board.

Support for virtual to S6000 bus address mapping in XT-HiFi2,
for use in setting up DMA transfers. Note the bus address is 
not the Xtensa physical addresses, but is outside the processor.

*******************************************************************************/

#ifndef _XTHIFI2_BUS_H_
#define _XTHIFI2_BUS_H_

#include <xtensa/xthifi2-sx-types.h>

SX_EXTERN_BEGIN

SX_EXTERN sx_uint32 sx_virt_to_bus(void *vaddr);

SX_EXTERN_END

#endif /* _XTHIFI2_BUS_H_ */


