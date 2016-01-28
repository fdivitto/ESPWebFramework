/* Copyright (c) 2006-2007 by Tensilica Inc.  ALL RIGHTS RESERVED.
/  These coded instructions, statements, and computer programs are the
/  copyrighted works and confidential proprietary information of Tensilica Inc.
/  They may not be modified, copied, reproduced, distributed, or disclosed to
/  third parties in any manner, medium, or form, in whole or in part, without
/  the prior written consent of Tensilica Inc.
*/

/*  xtav60.h    -  Xtensa Avnet LX60 (XT-AV60) board specific definitions  */

#ifndef _INC_XTAV60_H_

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

This is a wrapper to the xtav60-specific header lives in the
xtav60-specific include area. The recommended way to find the header is to
add the board-specific location to your -I include path for compilation.
Alternatively "#include <xtensa/xtav60/xtensa/xtav60.h>" like below.

This wrapper explicitly includes it for convenience in builds (without
an explicit board package) that use board support internal to an Xtensa
core package, and where an explicit -I is not used. It is provided
because xt-xcc currently has no concept of board and does not search the
board-specific include area.  In the future this wrapper might disappear.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include    <xtensa/xtav60/xtensa/xtav60.h>

#endif /*_INC_XTAV60_H_*/

