;****************************************************************************
;                                                                           *
; THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY     *
; KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE       *
; IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR     *
; PURPOSE.                                                                  *
;                                                                           *
; Copyright (C) 1993-95  Microsoft Corporation.  All Rights Reserved.       *
;                                                                           *
;****************************************************************************

;************************************************************************
; VwatchD.INC
;========================================================================

;
; This is the virtual device ID for this VxD.  It is a unique number assigned
; to this device.  For more information on VxD IDs, please see the VXDID.TXT
; file.
;
VwatchD_DEVICE_ID 	equ	7FE1h

Begin_Service_Table VwatchD

VwatchD_Service	VwatchD_Get_Version

End_Service_Table VwatchD
