/*
 * Copyright (c) 2005 by Tensilica Inc.  ALL RIGHTS RESERVED.
 * These coded instructions, statements, and computer programs are the
 * copyrighted works and confidential proprietary information of Tensilica Inc.
 * They may not be modified, copied, reproduced, distributed, or disclosed to
 * third parties in any manner, medium, or form, in whole or in part, without
 * the prior written consent of Tensilica Inc.
 */


#ifndef __DEBUGFS_INTERNAL_H__
#define __DEBUGFS_INTERNAL_H__

/* data structures used to communicate between the server and client */

/*
fields have different meanings depending on the command:

OPEN:	val0--flags as if possed to open
	val1--mode as if passed to open
	val2--unused			

CLOSE:	val0--unused
	val1--unused			
	val2--unused			
		
WRITE:	val0--bytes to write
	val1--offset into file (sometimes ignored if in append mode)
	val2--unused			

READ:	val0--bytes to read
	val1--offset into file
	val2--address of location to store read data

TRUNCATE:
	val0--length to truncate
	val1--unused
	val2--unused			

UNLINK:	val0--unused
	val1--unused
	val2--unused			

APPEND:	val0--bytes to write
	val1--align bytes to write
	val2--unused

filename always appears immediately after val2, even though it 
isn't listed in the structure
*/

typedef struct cmd_block_t 
{
  int endianess; // always set to 1 so that server can determine endianness
  int cmd;
  int val0;
  int val1;
  int val2;
} cmd_block_t;


/* The server has no way of knowing how big the uncompressed 
   command block is, so it will allocate a buffer this big to
   uncompress into.

   The client should never produce a block bigger than this after
   decompression.

   256M should be plenty big.
*/
#define LARGEST_BLOCK_SIZE (256 * 1024 * 1024)


/*  Command codes:  */
#define XT_DEBUGFS_CMD_NULL	0	/* do nothing */
#define XT_DEBUGFS_CMD_OPEN	1	/* open file */
//#define XT_DEBUGFS_CMD_CLOSE	2	/* server never sees a close command */
#define XT_DEBUGFS_CMD_WRITE	3	/* write to file */
#define XT_DEBUGFS_CMD_READ	4	/* read from file */
#define XT_DEBUGFS_CMD_LSEEK	5	/* lseek */
#define XT_DEBUGFS_CMD_TRUNCATE	6	/* truncate file */
#define XT_DEBUGFS_CMD_UNLINK	7	/* unlink file */
#define XT_DEBUGFS_CMD_APPEND	8	/* append with align */

/*  Return values:  */
#define XT_DEBUGFS_E_NODEBUG	-999	/* no debugger-based servicer present */
#define XT_DEBUGFS_E_NOTSUPP	-998	/* operation not supported */
#define XT_DEBUGFS_E_HOSTERROR	-997	/* unrecoverable error on server */

#endif
