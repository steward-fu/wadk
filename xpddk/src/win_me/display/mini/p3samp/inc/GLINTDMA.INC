;--------------------------------------------------------------------------
; GLINTDMA.INC
;
; Copyright (c) 1995-2001 Microsoft Corporation.  All rights reserved.
;--------------------------------------------------------------------------

GlintDMABuffers struc
dwNBuffers      dd      ?
dwBuffSize      dd      ?
dwBuffPhys      dd      ?               ; repeats as required
dwBuffVirt      dd      ?
GlintDMABuffers ends

GlintDMARequest struc
dwContext       dd      ?               ; context of request
dwSize          dd      ?               ; size of request
dwPhys          dd      ?               ; physical address
GlintDMARequest ends
