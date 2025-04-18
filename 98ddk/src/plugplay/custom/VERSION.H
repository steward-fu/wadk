/****************************************************************************
*                                                                           *
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY     *
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE       *
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR     *
* PURPOSE.                                                                  *
*                                                                           *
* Copyright (C) 1993-95  Microsoft Corporation.  All Rights Reserved.       *
*                                                                           *
****************************************************************************/

#define OFFICIAL   1 
#define FINAL      1 

/****************************************************************************
 *                                                                          *
 *      VERSION.H        -- Version information for internal builds         *
 *                                                                          *
 *      This file is only modified by the official builder to update the         *
 *      VERSION, VER_PRODUCTVERSION and VER_PRODUCTVERSION_STR values            *
 *                                                                          *
 ****************************************************************************/

#ifndef VS_FF_DEBUG 
/* ver.h defines constants needed by the VS_VERSION_INFO structure */
#include "ver.h"
#endif 

/*--------------------------------------------------------------*/
/* the following entry should be phased out in favor of         */
/* VER_PRODUCTVERSION_STR, but is used in the shell today.      */
/*--------------------------------------------------------------*/

#ifndef FROSTING
/*--------------------------------------------------------------*/
/* the following values should be modified by the official      */
/* builder for each build                                       */
/*--------------------------------------------------------------*/
#ifndef WIN32
#define VERSION                     "4.00.950"
#endif                            
#define VER_PRODUCTVERSION_STR      "4.00.950\0"
#define VER_PRODUCTVERSION          4,00,0,950
#define VER_PRODUCTVERSION_DW       (0x04000000 | 950)

#else
/*--------------------------------------------------------------*/
/* FROSTING Builds will need a higher version # than Windows 95 */
/*--------------------------------------------------------------*/
#ifndef WIN32
#define VERSION                     "4.50"
#endif
#define VER_PRODUCTVERSION_STR      "4.50\0"
#define VER_PRODUCTVERSION          4,50,0,000
#define VER_PRODUCTVERSION_DW       (0x04500000 | 000)
#endif

/*--------------------------------------------------------------*/
/* the following section defines values used in the version     */
/* data structure for all files, and which do not change.       */
/*--------------------------------------------------------------*/

/* default is nodebug */
#ifndef DEBUG
#define VER_DEBUG                   0
#else
#define VER_DEBUG                   VS_FF_DEBUG
#endif

/* default is privatebuild */
#ifndef OFFICIAL
#define VER_PRIVATEBUILD            VS_FF_PRIVATEBUILD
#else
#define VER_PRIVATEBUILD            0
#endif

/* default is prerelease */
#ifndef FINAL
#define VER_PRERELEASE              VS_FF_PRERELEASE
#else
#define VER_PRERELEASE              0
#endif

#define VER_FILEFLAGSMASK           VS_FFI_FILEFLAGSMASK
#define VER_FILEOS                  VOS_DOS_WINDOWS16
#define VER_FILEFLAGS               (VER_PRIVATEBUILD|VER_PRERELEASE|VER_DEBUG)

#define VER_COMPANYNAME_STR         "Microsoft Corporation\0"

#ifndef FROSTING
#define VER_PRODUCTNAME_STR         "Microsoft\256 Windows(TM) Operating System\0"
#else
#define VER_PRODUCTNAME_STR         "Microsoft\256  Plus!  for  Windows\256  95\0"
#endif

#define VER_LEGALTRADEMARKS_STR     \
"Microsoft\256 is a registered trademark of Microsoft Corporation. Windows(TM) is a trademark of Microsoft Corporation.\0"

