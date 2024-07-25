;; novxdsvc.asm - library stub for VxDs that do not supply VxD services
;=============================================================================
;
; Compuware Corporation
; NuMega Lab
; 9 Townsend West
; Nashua, NH 03060  USA
;
; Copyright (c) 1998 Compuware Corporation. All Rights Reserved.
; Unpublished - rights reserved under the Copyright laws of the
; United States.
;
; U.S. GOVERNMENT RIGHTS-Use, duplication, or disclosure by the
; U.S. Government is subject to restrictions as set forth in 
; Compuware Corporation license agreement and as provided in 
; DFARS 227.7202-1(a) and 227.7202-3(a) (1995), 
; DFARS 252.227-7013(c)(1)(ii)(OCT 1988), FAR 12.212(a) (1995), 
; FAR 52.227-19, or FAR 52.227-14 (ALT III), as applicable.  
; Compuware Corporation.
; 
; This product contains confidential information and trade secrets 
; of Compuware Corporation. Use, disclosure, or reproduction is 
; prohibited without the prior express written permission of Compuware 
; Corporation.
;
;=============================================================================
;;
	.386P

	.xlist
	NO_SEGMENTS=1
	include VMM.INC
	include VSEGMENT.INC
	include CDEFNS.INC

VxD_IDATA_SEG

	PUBLIC _VXD_SERVICE_TABLE
	PUBLIC _VXD_SERVICE_TABLE_SIZE

_VXD_SERVICE_TABLE	dd 0
_VXD_SERVICE_TABLE_SIZE	dd 0


VxD_IDATA_ENDS

	END
