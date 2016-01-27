/*
   xtensa-versions.h -- definitions of Xtensa version and release numbers

   This file defines most Xtensa-related product versions and releases
   that exist so far.
   It also provides a bit of information about which ones are current.
   This file changes every release, as versions/releases get added.


   $Id: //depot/rel/Boreal/Xtensa/Software/misc/xtensa-versions.h.tpp#1 $

   Copyright (c) 2006 by Tensilica Inc.  ALL RIGHTS RESERVED.
   These coded instructions, statements, and computer programs are the
   copyrighted works and confidential proprietary information of Tensilica Inc.
   They may not be modified, copied, reproduced, distributed, or disclosed to
   third parties in any manner, medium, or form, in whole or in part, without
   the prior written consent of Tensilica Inc.
*/

#ifndef XTENSA_VERSIONS_H
#define XTENSA_VERSIONS_H


/*
 *  NOTE:  A "release" is a collection of product versions
 *	made available at once (together) to customers.
 *	In the past, release and version names all matched in T####.# form,
 *	making the distinction irrelevant.
 *	Starting with the RA-2004.1 release, this is no longer the case.
 */


/* Hardware (Xtensa/Diamond processor) versions:  */
#define XTENSA_HWVERSION_T1020_0	102000	/* versions T1020.0 */
#define  XTENSA_HWCIDSCHEME_T1020_0	 10
#define  XTENSA_HWCIDVERS_T1020_0	 2
#define XTENSA_HWVERSION_T1020_1	102001	/* versions T1020.1 */
#define  XTENSA_HWCIDSCHEME_T1020_1	 10
#define  XTENSA_HWCIDVERS_T1020_1	 3
#define XTENSA_HWVERSION_T1020_2B	102002	/* versions T1020.2b */
#define  XTENSA_HWCIDSCHEME_T1020_2B	 10
#define  XTENSA_HWCIDVERS_T1020_2B	 5
#define XTENSA_HWVERSION_T1020_2	102002	/* versions T1020.2 */
#define  XTENSA_HWCIDSCHEME_T1020_2	 10
#define  XTENSA_HWCIDVERS_T1020_2	 4
#define XTENSA_HWVERSION_T1020_3	102003	/* versions T1020.3 */
#define  XTENSA_HWCIDSCHEME_T1020_3	 10
#define  XTENSA_HWCIDVERS_T1020_3	 6
#define XTENSA_HWVERSION_T1020_4	102004	/* versions T1020.4 */
#define  XTENSA_HWCIDSCHEME_T1020_4	 10
#define  XTENSA_HWCIDVERS_T1020_4	 7
#define XTENSA_HWVERSION_T1030_0	103000	/* versions T1030.0 */
#define  XTENSA_HWCIDSCHEME_T1030_0	 10
#define  XTENSA_HWCIDVERS_T1030_0	 9
#define XTENSA_HWVERSION_T1030_1	103001	/* versions T1030.1 */
#define  XTENSA_HWCIDSCHEME_T1030_1	 10
#define  XTENSA_HWCIDVERS_T1030_1	 10
#define XTENSA_HWVERSION_T1030_2	103002	/* versions T1030.2 */
#define  XTENSA_HWCIDSCHEME_T1030_2	 10
#define  XTENSA_HWCIDVERS_T1030_2	 11
#define XTENSA_HWVERSION_T1030_3	103003	/* versions T1030.3 */
#define  XTENSA_HWCIDSCHEME_T1030_3	 10
#define  XTENSA_HWCIDVERS_T1030_3	 12
#define XTENSA_HWVERSION_T1040_0	104000	/* versions T1040.0 */
#define  XTENSA_HWCIDSCHEME_T1040_0	 10
#define  XTENSA_HWCIDVERS_T1040_0	 15
#define XTENSA_HWVERSION_T1040_1	104001	/* versions T1040.1 */
#define  XTENSA_HWCIDSCHEME_T1040_1	 01
#define  XTENSA_HWCIDVERS_T1040_1	 32
#define XTENSA_HWVERSION_T1040_1P	104001	/* versions T1040.1-prehotfix */
#define  XTENSA_HWCIDSCHEME_T1040_1P	 10
#define  XTENSA_HWCIDVERS_T1040_1P	 16
#define XTENSA_HWVERSION_T1040_2	104002	/* versions T1040.2 */
#define  XTENSA_HWCIDSCHEME_T1040_2	 01
#define  XTENSA_HWCIDVERS_T1040_2	 33
#define XTENSA_HWVERSION_T1040_3	104003	/* versions T1040.3 */
#define  XTENSA_HWCIDSCHEME_T1040_3	 01
#define  XTENSA_HWCIDVERS_T1040_3	 34
#define XTENSA_HWVERSION_T1050_0	105000	/* versions T1050.0 */
#define  XTENSA_HWCIDSCHEME_T1050_0	 1100
#define  XTENSA_HWCIDVERS_T1050_0	 1
#define XTENSA_HWVERSION_T1050_1	105001	/* versions T1050.1 */
#define  XTENSA_HWCIDSCHEME_T1050_1	 1100
#define  XTENSA_HWCIDVERS_T1050_1	 2
#define XTENSA_HWVERSION_T1050_2	105002	/* versions T1050.2 */
#define  XTENSA_HWCIDSCHEME_T1050_2	 1100
#define  XTENSA_HWCIDVERS_T1050_2	 4
#define XTENSA_HWVERSION_T1050_3	105003	/* versions T1050.3 */
#define  XTENSA_HWCIDSCHEME_T1050_3	 1100
#define  XTENSA_HWCIDVERS_T1050_3	 6
#define XTENSA_HWVERSION_T1050_4	105004	/* versions T1050.4 */
#define  XTENSA_HWCIDSCHEME_T1050_4	 1100
#define  XTENSA_HWCIDVERS_T1050_4	 7
#define XTENSA_HWVERSION_T1050_5	105005	/* versions T1050.5 */
#define  XTENSA_HWCIDSCHEME_T1050_5	 1100
#define  XTENSA_HWCIDVERS_T1050_5	 8
#define XTENSA_HWVERSION_RA_2004_1	210000	/* versions LX1.0.0 */
#define  XTENSA_HWCIDSCHEME_RA_2004_1	 1100
#define  XTENSA_HWCIDVERS_RA_2004_1	 3
#define XTENSA_HWVERSION_RA_2005_1	210001	/* versions LX1.0.1 */
#define  XTENSA_HWCIDSCHEME_RA_2005_1	 1100
#define  XTENSA_HWCIDVERS_RA_2005_1	 20
#define XTENSA_HWVERSION_RA_2005_2	210002	/* versions LX1.0.2 */
#define  XTENSA_HWCIDSCHEME_RA_2005_2	 1100
#define  XTENSA_HWCIDVERS_RA_2005_2	 21
#define XTENSA_HWVERSION_RA_2005_3	210003	/* versions LX1.0.3, X6.0.3 */
#define  XTENSA_HWCIDSCHEME_RA_2005_3	 1100
#define  XTENSA_HWCIDVERS_RA_2005_3	 22
#define XTENSA_HWVERSION_RA_2006_4	210004	/* versions LX1.0.4, X6.0.4 */
#define  XTENSA_HWCIDSCHEME_RA_2006_4	 1100
#define  XTENSA_HWCIDVERS_RA_2006_4	 23
#define XTENSA_HWVERSION_RA_2006_5	210005	/* versions LX1.0.5, X6.0.5 */
#define  XTENSA_HWCIDSCHEME_RA_2006_5	 1100
#define  XTENSA_HWCIDVERS_RA_2006_5	 24
#define XTENSA_HWVERSION_RA_2006_6	210006	/* versions LX1.0.6, X6.0.6 */
#define  XTENSA_HWCIDSCHEME_RA_2006_6	 1100
#define  XTENSA_HWCIDVERS_RA_2006_6	 25
#define XTENSA_HWVERSION_RA_2007_7	210007	/* versions LX1.0.7, X6.0.7 */
#define  XTENSA_HWCIDSCHEME_RA_2007_7	 1100
#define  XTENSA_HWCIDVERS_RA_2007_7	 26
#define XTENSA_HWVERSION_RA_2008_8	210008	/* versions LX1.0.8, X6.0.8 */
#define  XTENSA_HWCIDSCHEME_RA_2008_8	 1100
#define  XTENSA_HWCIDVERS_RA_2008_8	 27
#define XTENSA_HWVERSION_RB_2006_0	220000	/* versions LX2.0.0, X7.0.0 */
#define  XTENSA_HWCIDSCHEME_RB_2006_0	 1100
#define  XTENSA_HWCIDVERS_RB_2006_0	 48
#define XTENSA_HWVERSION_RB_2007_1	220001	/* versions LX2.0.1, X7.0.1 */
#define  XTENSA_HWCIDSCHEME_RB_2007_1	 1100
#define  XTENSA_HWCIDVERS_RB_2007_1	 49
#define XTENSA_HWVERSION_RB_2007_2	221000	/* versions LX2.1.0, X7.1.0 */
#define  XTENSA_HWCIDSCHEME_RB_2007_2	 1100
#define  XTENSA_HWCIDVERS_RB_2007_2	 52
#define XTENSA_HWVERSION_RB_2008_3	221001	/* versions LX2.1.1, X7.1.1 */
#define  XTENSA_HWCIDSCHEME_RB_2008_3	 1100
#define  XTENSA_HWCIDVERS_RB_2008_3	 53
#define XTENSA_HWVERSION_RB_2008_4	221002	/* versions LX2.1.2, X7.1.2 */
#define  XTENSA_HWCIDSCHEME_RB_2008_4	 1100
#define  XTENSA_HWCIDVERS_RB_2008_4	 54
#define XTENSA_HWVERSION_RB_2009_5	221003	/* versions LX2.1.3, X7.1.3 */
#define  XTENSA_HWCIDSCHEME_RB_2009_5	 1100
#define  XTENSA_HWCIDVERS_RB_2009_5	 55
#define XTENSA_HWVERSION_RB_2007_2_MP	221100	/* versions LX2.1.8-MP, X7.1.8-MP */
#define  XTENSA_HWCIDSCHEME_RB_2007_2_MP	 1100
#define  XTENSA_HWCIDVERS_RB_2007_2_MP	 64
#define XTENSA_HWVERSION_RC_2009_0	230000	/* versions LX3.0.0, X8.0.0, MX1.0.0 */
#define  XTENSA_HWCIDSCHEME_RC_2009_0	 1100
#define  XTENSA_HWCIDVERS_RC_2009_0	 65
#define XTENSA_HWVERSION_RC_2010_1	230001	/* versions LX3.0.1, X8.0.1, MX1.0.1 */
#define  XTENSA_HWCIDSCHEME_RC_2010_1	 1100
#define  XTENSA_HWCIDVERS_RC_2010_1	 66

/* Software (Xtensa Tools) versions:  */
#define XTENSA_SWVERSION_T1020_0	102000	/* versions T1020.0 */
#define XTENSA_SWVERSION_T1020_1	102001	/* versions T1020.1 */
#define XTENSA_SWVERSION_T1020_2B	102002	/* versions T1020.2b */
#define XTENSA_SWVERSION_T1020_2	102002	/* versions T1020.2 */
#define XTENSA_SWVERSION_T1020_3	102003	/* versions T1020.3 */
#define XTENSA_SWVERSION_T1020_4	102004	/* versions T1020.4 */
#define XTENSA_SWVERSION_T1030_0	103000	/* versions T1030.0 */
#define XTENSA_SWVERSION_T1030_1	103001	/* versions T1030.1 */
#define XTENSA_SWVERSION_T1030_2	103002	/* versions T1030.2 */
#define XTENSA_SWVERSION_T1030_3	103003	/* versions T1030.3 */
#define XTENSA_SWVERSION_T1040_0	104000	/* versions T1040.0 */
#define XTENSA_SWVERSION_T1040_1	104001	/* versions T1040.1 */
#define XTENSA_SWVERSION_T1040_1P	104001	/* versions T1040.1-prehotfix */
#define XTENSA_SWVERSION_T1040_2	104002	/* versions T1040.2 */
#define XTENSA_SWVERSION_T1040_3	104003	/* versions T1040.3 */
#define XTENSA_SWVERSION_T1050_0	105000	/* versions T1050.0 */
#define XTENSA_SWVERSION_T1050_1	105001	/* versions T1050.1 */
#define XTENSA_SWVERSION_T1050_2	105002	/* versions T1050.2 */
#define XTENSA_SWVERSION_T1050_3	105003	/* versions T1050.3 */
#define XTENSA_SWVERSION_T1050_4	105004	/* versions T1050.4 */
#define XTENSA_SWVERSION_T1050_5	105005	/* versions T1050.5 */
#define XTENSA_SWVERSION_RA_2004_1	600000	/* versions 6.0.0 */
#define XTENSA_SWVERSION_RA_2005_1	600001	/* versions 6.0.1 */
#define XTENSA_SWVERSION_RA_2005_2	600002	/* versions 6.0.2 */
#define XTENSA_SWVERSION_RA_2005_3	600003	/* versions 6.0.3 */
#define XTENSA_SWVERSION_RA_2006_4	600004	/* versions 6.0.4 */
#define XTENSA_SWVERSION_RA_2006_5	600005	/* versions 6.0.5 */
#define XTENSA_SWVERSION_RA_2006_6	600006	/* versions 6.0.6 */
#define XTENSA_SWVERSION_RA_2007_7	600007	/* versions 6.0.7 */
#define XTENSA_SWVERSION_RA_2008_8	600008	/* versions 6.0.8 */
#define XTENSA_SWVERSION_RB_2006_0	700000	/* versions 7.0.0 */
#define XTENSA_SWVERSION_RB_2007_1	700001	/* versions 7.0.1 */
#define XTENSA_SWVERSION_RB_2007_2	701000	/* versions 7.1.0 */
#define XTENSA_SWVERSION_RB_2008_3	701001	/* versions 7.1.1 */
#define XTENSA_SWVERSION_RB_2008_4	701002	/* versions 7.1.2 */
#define XTENSA_SWVERSION_RB_2009_5	701003	/* versions 7.1.3 */
#define XTENSA_SWVERSION_RB_2007_2_MP	701100	/* versions 7.1.8-MP */
#define XTENSA_SWVERSION_RC_2009_0	800000	/* versions 8.0.0 */
#define XTENSA_SWVERSION_RC_2010_1	800001	/* versions 8.0.1 */
#define XTENSA_SWVERSION_T1040_1_PREHOTFIX	XTENSA_SWVERSION_T1040_1P	/* T1040.1-prehotfix */
#define XTENSA_SWVERSION_6_0_0	XTENSA_SWVERSION_RA_2004_1	/* 6.0.0 */
#define XTENSA_SWVERSION_6_0_1	XTENSA_SWVERSION_RA_2005_1	/* 6.0.1 */
#define XTENSA_SWVERSION_6_0_2	XTENSA_SWVERSION_RA_2005_2	/* 6.0.2 */
#define XTENSA_SWVERSION_6_0_3	XTENSA_SWVERSION_RA_2005_3	/* 6.0.3 */
#define XTENSA_SWVERSION_6_0_4	XTENSA_SWVERSION_RA_2006_4	/* 6.0.4 */
#define XTENSA_SWVERSION_6_0_5	XTENSA_SWVERSION_RA_2006_5	/* 6.0.5 */
#define XTENSA_SWVERSION_6_0_6	XTENSA_SWVERSION_RA_2006_6	/* 6.0.6 */
#define XTENSA_SWVERSION_6_0_7	XTENSA_SWVERSION_RA_2007_7	/* 6.0.7 */
#define XTENSA_SWVERSION_6_0_8	XTENSA_SWVERSION_RA_2008_8	/* 6.0.8 */
#define XTENSA_SWVERSION_7_0_0	XTENSA_SWVERSION_RB_2006_0	/* 7.0.0 */
#define XTENSA_SWVERSION_7_0_1	XTENSA_SWVERSION_RB_2007_1	/* 7.0.1 */
#define XTENSA_SWVERSION_7_1_0	XTENSA_SWVERSION_RB_2007_2	/* 7.1.0 */
#define XTENSA_SWVERSION_7_1_1	XTENSA_SWVERSION_RB_2008_3	/* 7.1.1 */
#define XTENSA_SWVERSION_7_1_2	XTENSA_SWVERSION_RB_2008_4	/* 7.1.2 */
#define XTENSA_SWVERSION_7_1_3	XTENSA_SWVERSION_RB_2009_5	/* 7.1.3 */
#define XTENSA_SWVERSION_7_1_8_MP	XTENSA_SWVERSION_RB_2007_2_MP	/* 7.1.8-MP */
#define XTENSA_SWVERSION_8_0_0	XTENSA_SWVERSION_RC_2009_0	/* 8.0.0 */
#define XTENSA_SWVERSION_8_0_1	XTENSA_SWVERSION_RC_2010_1	/* 8.0.1 */


/*  The current release:  */
#define XTENSA_RELEASE_NAME		"RC-2010.1"
#define XTENSA_RELEASE_CANONICAL_NAME	"RC-2010.1"

/*  The product versions within the current release:  */
#define XTENSA_SWVERSION		XTENSA_SWVERSION_RC_2010_1
#define XTENSA_SWVERSION_NAME		"8.0.1"
#define XTENSA_SWVERSION_CANONICAL_NAME	"8.0.1"
/*  Note:  there may be multiple hardware products in one release,
    and software can target older hardware, so the notion of
    "current" hardware versions is partially configuration dependent.
    For now, "current" hardware product version info is left out
    to avoid confusion.  */

#endif /*XTENSA_VERSIONS_H*/

