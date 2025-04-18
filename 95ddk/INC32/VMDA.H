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

/******************************************************************************
 *
 *   Title:	VMDA.H - Include file for VMDOSAPP/GRABBER SHELL interaction
 *
 *   Version:	1.00
 *
 *****************************************************************************/

/*
 * EQUATES for VMDOSAPP device calls
 */
#define	SHELL_Call_Dev_VDD	0x0000A	/* Actually GRABBER services */

/*
 * SHELL VMDA interface services.  All services not listed here are reserved
 * for internal use.
 */
#define	SHELL_Debug_Out 	   8

/*
 * THIS IS THE MAXIMUM SIZE IN BYTES OF THE INFO RETURNED ON
 *	VDD CALLS OTHER THAN GET CONTOLLER STATE MADE BY THE GRABBER
 *
 * This is the size of an area reserved for use on grabber calls
 */
#define	VDD_MOD_MAX		256

/*
 * THIS IS THE MAXIMUM SIZE IN BYTES OF THE INFO RETURNED ON
 *	THE GET CONTOLLER STATE VDD CALL MADE BY THE GRABBER
 *
 * This is the size of an area reserved for use on this grabber call
 */
#define	VDD_CTRL_STATE_MAX	128

/*
 * Stuff specific to VMDA events
 */

#define	WMX_USER		  0x0400

/* ASM
INCLUDE VDDGRB.INC
*/
/* ASM
.ERRE VDA_Type_Chng	EQ	((WMX_USER+20)+2) ; Defined in VDDGRB.INC!!
.ERRE VDA_Display_Event EQ	((WMX_USER+20)+6) ; Defined in VDDGRB.INC!!
*/

/* All other VDA_* values are reserved for internal use */

/*
 * lParam is ALWAYS the "Event ID". This is used on the VMDOSAPP call backs
 *  to the shell to identify the event which is being processed.
 */

/*
 * On VDA_Display_Message event, wParam == 0 if normal message
 *				       != 0 if ASAP or SYSMODAL message
 *   VMDOSAPP instance which gets the message is messaging VM
 */

/*
 * On VDA_Type_Chng event, wParam is not used
 *   VMDOSAPP instance which gets the message has had its type changed by
 *   protected mode code
 */
