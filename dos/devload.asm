;......................PROGRAM HEADER FOR PROJECT BUILDER....................


;       TITLE   DEVLOAD         to load device drivers from command line.
;       FORMAT  EXE
;       VERSION 3.12
;       CODE    80x86
;       OPTIONS /ML
;       TIME    CHECK
;       DATE    12/3/92 - 31/3/98
;       AUTHOR  David Woodhouse
;        (C) 1992, 1993 David Woodhouse.

;EXPLANATION...
;       The program first relocates itself to the top of the available memory
;       and then loads the driver below itself. If the driver loads happily, it
;       is then executed. If it asks for memory to be reserved for it, it is
;       linked into the device chains and the program TSRs keeping the required
;       amount of memory, otherwise a normal exit occurs.


;.............................ALTERATION LIST................................


;Version 1.0            12/3/92
;       Basics, not user-friendly, only supports character devices so far.
;                       13/2/92
;       Change to using EXEC (4Bh) function to load - now loads .EXE files
;       Take length to TSR from device return, not file length.
;       Don't TSR if not required.


;Version 1.1            17/3/92
;       Complete rewrite of initialisation routine.
;       Allows for more than one device per file.
;       Help message added.
;       EXEC failure now explains error codes, rather than just giving no.
;                       19/3/92
;       Print error message and exit if version < 4.
;       Loads device at PSP+6, not PSP+10h (overlay FCBs and command tail).
;       Stack moved down by 8 paras, not truncated to 80h bytes.
;                       20/3/92
;       Release environment block before TSR.


;Version 2.0            21/3/92
;       Use INT 21h, function 53h. Can now load block devices.
;       Use segment in break address, don't assume same as driver segment.
;       Ask whether to terminate if can't install any blocks.
;       Disable ctrl-break.
;                       22/3/92
;       Check sector size before installing block devices.
;       Disable break with INT 1Bh, as well as INT 23h - stops ^C appearing.
;               (taken out in v2.1) - causes problems if driver changes it.
;       Don't use INT 10h - all output via INT 21h - can be redirected.
;       Print drive letter with block header address.
;       Print LastDrive message after installing block headers, not before.
;       Change program name in arena header to device filename (for MEM.EXE).
;       Support for DOS 3 added (now works with at least DOS 3.1 onwards).
;       Print driver's load address.


;Version 2.1            24/3/92
;       Bug fix - drivers requesting memory offset FFF1 - FFFF now works OK.
;                       25/3/92
;       Now uses func 60h to expand filename before printing it.
;       Bug fix - changing INT 1B lost vector if driver altered it, so don't.
;       Display INT vectors changed by driver.
;                       26/3/92
;       Converts params to upper case before passing to driver, like DOS does.
;       Also adds space after filename if no parameters given.
;       Change data at end to ?? rather than 00 - smaller .COM file.


;Version 2.2            26/10/92
;       When no blocks installed, checks whether INT vectors changed before
;       asking whether to terminate. Still not foolproof, but better.
;       Cosmetic fix - `$' now comes after CR/LF on `None.' for INT vectors.
;       Bug fix - Check all INT vectors (200h words, not 200 words!)


;Version 3.0            11/4/93 - 20/4/93
;       Complete rewrite from scratch.
;       Only relocate if going to try EXEC - saves losing F3.
;       Use path to find driver if not in specified directory.
;       Convert to .EXE program.
;       Relocate PSP to top of memory as well as code and stack.
;       Release environment before requesting memory for driver.
;       Don't even attempt to load driver if not enough memory available.
;       Use highest memory required return.
;       Link drivers in correct order.
;       Add /Q (quiet mode) option.
;       Disperse comments ad nauseum.
;                       21/4/93
;       Add /V (verbose mode) option.
;       Move lastdrive report to end.
;       Move abort request to end.
;       Add count of character devices installed.
;       Put entry point after LASTBYTE - smaller relocated code.


;Version 3.1            18/2/95
;       Bug fix - push AX before fileerr if EXEC fails.
;       Check whether found item is directory when looking for driver file.

;Version 3.11           12/2/96
;       just add email address prior to uploading.

;..............................IMPROVEMENT IDEAS.............................


;       Load into Upper Memory Blocks (like 'DEVICEHIGH='.)
;       Work from batch files like CONFIG.SYS.
;       Change size of LASTDRIVE array by reallocating.
;       Add support for SETVER.EXE.


;.................................DEFINES....................................

STACKLEN        equ     200h
SMALLESTDRIVER  equ     100h
QuietFlag       equ     80h
VerboseFlag     equ     40h
AutoFlag        equ     20h

;.............................CODE (at last).................................

CSeg    segment public  byte    'CODE'

        org     0

        assume  cs:CSeg, ds:CSeg, es:CSeg

;.............CODE TO BE EXECUTED ONCE RELOCATED TO TOP OF MEMORY............

        ;DS:TopCSeg, ES:TopPSPSeg

        ;Get old PSP segment, store new PSP segment.

relocated:      push    es
                mov     es,PSPSeg
                pop     PSPSeg

        ;Push segment of environment.

        ;DS:TopCSeg, ES:PSPSeg

                push    es:[002Ch]

        ;Release old PSP segment.

                mov     ah,49h
                int     21h
                jnc     relPSPok

        ;Failed to release PSP - print error.

                mov     dx,offset RelPSPErrMsg
                call    PrintError
                mov     ah,9
                int     21h
                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

        ;Release environment segment.

        ;DS:TopCSeg, ES:CSeg

relPSPok:       pop     es
                mov     ah,49h
                int     21h
                jnc     relenvok

        ;Failed to release environment - print error.

                mov     dx,offset RelEnvErrMsg
                call    PrintError
                mov     ah,9
                int     21h
                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

relenvok:       push    cs
                pop     es

        ;Find out how much memory is available by asking for stupid amounts.

                mov     ah,48h
                mov     bx,0FFFFh
                int     21h

        ;In MS-DOS version 6 and below, this will always fail, but check
        ;the return status just in case it does give what we asked for.

                jnc     grablowok

        ;BX now holds the maximum amount of memory available.
        ;Don't install if less than 4K bytes available.

                cmp     bx,SMALLESTDRIVER
                ja      sizeok
                mov     bx,SMALLESTDRIVER

        ;Attempt to grab memory for driver.

sizeok:         mov     ah,48h
                int     21h
                jnc     grablowok

        ;Failed to grab memory - print error and exit.

                mov     dx,offset GrabLoErrMsg
                jmp     allocerr

        ;Store segment of device.

grablowok:      mov     DvcSeg,ax
                mov     BlockSize,bx

        ;Disable Ctrl-Break.

                mov     dx,offset BreakHandler
                mov     ax,2523h
                int     21h

        ;Copy interrupt vectors for later comparison.

        ;DS:TopCSeg, ES:TopCSeg
                xor     bx,bx
                mov     ds,bx
        ;DS:0000, ES:TopCSeg
                mov     si,bx
                mov     di,offset IntVectors
                mov     cx,200h
                rep     movsw

        ;Parse parameters in same way as SYSINIT does.

                mov     ds,cs:PSPSeg

        ;DS:TopPSPSeg, ES:TopCSeg

        ;Find end of filename in DI.

                mov     di,cs:NamePtr
                add     di,cs:NameLen

        ;Find end of command line in BX.

                mov     bl,byte ptr ds:[80h]
                add     bx,81h

        ;Compare them.

                cmp     bx,di
                ja      parmsgiven

        ;If they are the same, no parameters were given, so add a space.

                mov     byte ptr [di],' '
                inc     bx

        ;Append CrLf to line.

parmsgiven:     mov     word ptr [bx],0A0Dh

        ;Print 'Filename: ' if not in Quiet Mode.

                push    cs
                pop     ds

                test    ModeFlag,QuietFlag
                jnz     noprintfname

                mov     dx,offset FNameMsg
                mov     ah,9
                int     21h

        ;Make filename ASCII$ instead of ASCIIZ for printing.

                mov     di,offset NameBuffer
                mov     dx,di
                mov     cx,80h
                xor     al,al
                repnz   scasb
                dec     di
                mov     byte ptr [di],'$'

        ;Print filename.

                int     21h

        ;Restore to ASCIIZ.

                mov     byte ptr [di],0

        ;Print CrLf after filename.

                mov     dx,offset CrLfMsg
                int     21h

        ;Load driver file into memory.

        ;DS:TopCSeg, ES:TopCSeg

noprintfname:   mov     dx,offset NameBuffer
                mov     bx,offset DvcSeg
                mov     ax,4B03h
                int     21h
                jnc     loadedok

        ;Print 'EXEC failure'.

                mov     dx,offset NotLoadMsg
                push    ax

        ;Restore error code.

fileerr:        pop     ax

        ;Print error message and number, get offset of cause in DX.

allocerr:       call    PrintError

        ;Print final message.

prexit:         mov     ah,9
                int     21h

        ;Exit program.

exit:           mov     ax,4C00h
                int     21h

;............................................................................

        ;DS:TopCSeg, ES:TopCSeg

        ;Check whether to print load address.

loadedok:       test    ModeFlag,VerboseFlag
                jz      noprintladdr

        ;Print 'Load address:'

                mov     dx,offset LoadAddrMsg
                mov     ah,9
                int     21h

        ;Print segment of driver.

                mov     ax,DvcSeg
                call    PHWord

        ;Print ':0000'

                mov     dx,offset Colon0Msg
                mov     ah,9
                int     21h

        ;DS:TopCSeg, ES:TopCSeg

        ;Get pointer to 'invar'

noprintladdr:   mov     ah,52h
                int     21h

        ;Store for later use.

                mov     InvarOfs,bx
                mov     InvarSeg,es

        ;DS:TopCSeg, ES:InvarSeg

        ;Fetch LastDrUsed and LastDrive from 'invar'

                mov     ax,es:[bx+20h]
                mov     word ptr LastDrUsed,ax

        ;Fetch max. sector size from 'invar'

                mov     ax,es:[bx+10h]
                mov     SecSize,ax

                push    es
                pop     ds

        ;Trace device chain from 'invar'.

        ;Point DS:DI to first block header.

                mov     si,bx

        ;Point to next block header.

notlast:        lds     si,[si]

        ;Point to pointer within block header to the next one.

                add     si,cs:word ptr NextBlHOfs

        ;Loop while not at the end of the chain.

                cmp     [si],0FFFFh
                jnz     notlast

        ;Point back at beginning of last block header in chain.

                sub     si,cs:word ptr NextBlHOfs

        ;Store for later use.

                mov     cs:ChainEndOfs,si
                mov     cs:ChainEndSeg,ds

        ;DS:DvcSeg, ES:InvarSeg

        ;Point ES:BX to device after NUL device.

                les     bx,es:[bx+22h]

        ;Point DS:SI to new device (DvcSeg:0000).

                mov     ds,cs:DvcSeg
                xor     si,si

        ;DS:DvcSeg, ES:OldDvcSeg

        ;Install all devices in chain.

anoth_dvc:      call    InstallDevice
                jnz     anoth_dvc

        ;Print LASTDRIVE error message if necessary.

                push    cs
                pop     ds

                cmp     [LDrErrMsg],'0'
                jz      noldrerr
                mov     dx,offset LDrErrMsg
                mov     ah,9
                int     21h

        ;Calculate size of driver to keep.

noldrerr:       mov     ax,BlHEndOfs
                add     ax,0Fh
                rcr     ax,1
                mov     cl,3
                shr     ax,cl

                add     ax,EndSeg

                sub     ax,DvcSeg

        ;Store size of driver to keep.

                push    ax

        ;Check whether anything installed, offer abortion if not.

                mov     ax,word ptr BlocksDone
                or      ax,ax
                jnz     somedone

        ;Nothing installed - check whether Auto Mode.

                test    ModeFlag,AutoFlag
                jnz     somedone

        ;If it didn't want to stay anyway, don't ask.

                pop     cx
                push    cx
                jcxz    somedone

        ;Check whether any INT vectors changed.

                xor     di,di
                mov     es,di

        ;DS:TopCSeg, ES:0000

                mov     si,offset IntVectors
                mov     cx,200h
                rep     cmpsw
                jnz     somedone

        ;Nothing installed, so give option of aborting.

                mov     dx,offset AskEndMsg
                mov     ah,9
                int     21h

        ;Get response from keyboard.

                mov     ah,8
badkey:         int     21h

        ;If it's an extended character code, get the second byte and try again.

                or      al,al
                jnz     realchar
                int     21h
                jmp     badkey

        ;If it's valid, act upon it, else loop for another.

realchar:       cmp     al,'N'
                jz      nokill
                cmp     al,'n'
                jz      nokill
                cmp     al,'Y'
                jz      kill
                cmp     al,'y'
                jnz     badkey

        ;Response was yes, so set length required to zero.

kill:           pop     bx
                xor     bx,bx
                push    bx

                ;mov     bx,DvcSeg
                ;mov     EndSeg,bx
                ;xor     bx,bx
                ;mov     BlHEndOfs,bx


        ;Print the key pressed.

nokill:         mov     ah,02h
                mov     dl,al
                int     21h

        ;Print CrLf afterwards.

                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

        ;Print Lastdrive and LastDrUsed if blocks done and Verbose Mode.

somedone:       push    cs
                pop     ds

                test    BlocksDone,0FFh
                jz      noprintldrmsg

                test    ModeFlag,VerboseFlag
                jz      noprintldrmsg

                mov     ax,word ptr LastDrUsed

                mov     LDMsgA,'A'-1
                mov     LDMsgB,'A'-1

                add     byte ptr LDMsgA,al
                add     byte ptr LDMsgB,ah

                mov     dx,offset LastDrMsg
                mov     ah,9
                int     21h

        ;If not Quiet Mode, print number of devices installed.

noprintldrmsg:  test    ModeFlag,QuietFlag
                jnz     noprintnuminst

        ;Get driver keep size into CX, don't print installed message if zero.

                pop     cx
                push    cx
                jcxz    noprintnuminst

        ;Print number of blocks installed, if any.

                mov     bl,BlocksDone
                or      bl,bl
                jz      noblocks

                add     NumBlInstMsg,bl
                mov     dx,offset NumBlInstMsg
                mov     ah,9
                int     21h

                mov     dx,offset NumInstMsgA
                cmp     bl,1
                jnz     blnoplural
                inc     dx
blnoplural:     int     21h

        ;Print number of character devices installed, if any.

noblocks:       mov     bl,CharsDone
                or      bl,bl
                jz      noprintnuminst

                add     NumChInstMsg,bl
                mov     dx,offset NumChInstMsg
                mov     ah,9
                int     21h

                mov     dx,offset NumInstMsgA
                cmp     bl,1
                jnz     chnoplural
                inc     dx
chnoplural:     int     21h

        ;Insert new LastDrUsed into 'invar'.

noprintnuminst: les     bx,Invar

                mov     al,LastDrUsed
                mov     byte ptr es:[bx+20h],al

        ;Restore driver size in paragraphs.

                pop     bx

        ;Test whether to print driver size.

                test    ModeFlag,VerboseFlag
                jz      noprintsize

        ;Print 'Size of driver in paras:'.

                mov     dx,offset SizeMsg
                mov     ah,9
                int     21h

                mov     ax,bx
                call    PHWord

                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

noprintsize:    or      bx,bx
                jnz     lengthnotzero

        ;Length of driver is zero, so exit now.

                jmp     exit

        ;Check whether it fits in the allocated block.

lengthnotzero:  cmp     ax,BlockSize
                jna     drvrfits
                mov     dx,offset TooBigMsg
                mov     ah,9
                int     21h

        ;Change memory allocation on lowest block in memory.

drvrfits:       mov     es,DvcSeg
                mov     ah,4Ah
                int     21h
                jnc     allocok

        ;Print 'allocation error'.

                mov     dx,offset Reduce2ErrMsg
                call    PrintError
                mov     ah,9
                int     21h
                mov     dx,offset Reduce2ErrMsga
                mov     ah,9
                int     21h

        ;Check whether to print INT vectors changed.

allocok:        test    ModeFlag,VerboseFlag
                jz      noprintints

        ;Print 'Interrupt vectors changed:'

                mov     dx,offset IntChangeMsg
                mov     ah,9
                int     21h

        ;Print all INTs changed.

                xor     bx,bx
                mov     es,bx
                mov     di,bx
                mov     si,offset IntVectors
                mov     cx,200h

        ;Print no comma before the first INT number.

                mov     dx,offset CommaMsg-1

        ;Compare INT vectors with copy taken earlier.

loopints:       rep     cmpsw

        ;If we stopped at the end, leave the loop.

                jcxz    lastdiff

        ;Flag that at least one was changed.

                or      bl,1

        ;Print 'h, ' between INT numbers.

                mov     ah,9
                int     21h

        ;Check whether it was offset or segment that was different.

                mov     ax,di
                dec     ax
                test    ax,2
                jnz     notofs

        ;If was the offset, so don't bother checking the segment.

                add     di,2
                add     si,2
                dec     cx

        ;Print interrupt number.

notofs:         shr     ax,1
                shr     ax,1
                call    PHByte

        ;After the first one, print 'h, ' before the rest.

                mov     dx,offset CommaMsg
                jmp     loopints

        ;Print either full stop or 'None.'

lastdiff:       mov     dx,offset FullStopMsg

        ;Test flag to see whether any were changed.

                or      bl,bl
                jnz     notnochanges

        ;None were changed, so print 'None.' instead of a full stop.

                mov     dx,offset NoneMsg

notnochanges:   mov     ah,9
                int     21h

        ;DS:TopCSeg, ES:0000

        ;Link from NUL device.

noprintints:    les     bx,Invar
                add     bx,0022h
                mov     ax,NewDrvOfs
                mov     es:[bx],ax
                mov     ax,NewDrvSeg
                mov     es:[bx+2],ax

                push    cs
                pop     es

        ;DS:TopCSeg, ES:TopCSeg

        ;Find last backslash in filename.

                mov     di,offset NameBuffer+80h
                mov     al,'\'
                std
                mov     cx,0080h

                repnz   scasb
                cld
                add     di,2

        ;Point to arena header of driver segment.

                mov     ax,DvcSeg
                dec     ax
                mov     es,ax

        ;Set driver segment to self-ownership.

                inc     ax
                mov     word ptr es:[1],ax

        ;DS:TopCSeg, ES:DvcSeg-1

        ;Move name into arena header.

                mov     si,di
                mov     di,8
                mov     cx,8
movname:        lodsb
                cmp     al,2eh
                jz      fill0s
                cmp     al,0
                jz      fill0s
                stosb
                loop    movname
                jmp     stayexit

fill0s:         xor     al,al
                rep     stosb

stayexit:       mov     dx,offset StayingMsg
                jmp     prexit




;......................break handler......................................

BreakHandler:   iret                    ;well, that didn't take long!

;.....................PHWord...........................

;       IN:     AX      word to be printed
;       OUT:    nothing
;       LOST:   nothing


PHWord:         push    ax
                xchg    al,ah
                call    PHByte
                mov     al,ah
                call    PHByte
                pop     ax
                ret

;................PHByte...........

;       IN      AL      byte to printed
;       OUT:    nothing
;       LOST:   nothing

PHByte:         push    ax
                mov     ah,al
                shr     al,1
                shr     al,1
                shr     al,1
                shr     al,1
                call    PHNibble
                mov     al,ah
                call    PHNibble
                pop     ax
                ret

;..............PHNibble................

;       IN:     AL      nibble to be printed
;       OUT:    nothing
;       LOST:   nothing

PHNibble:       push    dx
                push    ax
                and     al,0Fh
                add     al,'0'
                cmp     al,'9'
                jna     ph1
                add     al,'A'-'9'-1
ph1:            mov     ah,02h
                mov     dl,al
                int     21h
                pop     ax
                pop     dx
                ret


;........................PrintError..........................................

;       IN:     AX      Error message to explain.
;               DX      Offset of error message.
;               DS      CSeg
;       OUT:    DX      Offset of error cause message.
;       LOST:   AX
;               BX

        ;Print first message.

PrintError:     push    ax
                mov     ah,9
                int     21h
                pop     ax

        ;Print error number.

                call    PHWord

        ;If over 0Bh, zero it - (unknown).

                cmp     ax,000Bh
                jb      notoverB
                xor     ax,ax

        ;Look up offset of error message.

notoverB:       mov     bx,offset ErrTable
                shl     ax,1
                add     bx,ax
                mov     dx,[bx]
                ret


;.............................InstallDevice..................................

;       IN:     DS:SI   address of new driver header
;               ES:BX   address of old driver header

;       OUT:    DS:SI   address of next driver header
;               ES:BX   address of new driver header
;               ZERO    set if last driver in file


        ;Store device addresses.

InstallDevice:  mov     cs:NewDrvOfs,si
                mov     cs:NewDrvSeg,ds
                mov     cs:OldDrvOfs,bx
                mov     cs:OldDrvSeg,es

                push    cs
                pop     ds

        ;Print CrLf to keep display tidy.

        ;DS:TopCSeg, ES:OldDvcSeg

                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

        ;Set up request header.

        ;Insert next block device number.

                mov     al,LastDrUsed
                mov     byte ptr [RqHdr+16h],al

        ;Insert command number zero - INIT.

                mov     byte ptr [RqHdr+2],0

        ;Insert default end of driver address = start of driver.

                mov     ax,DvcSeg
                mov     word ptr [RqHdr+10h],ax
                mov     word ptr [RqHdr+0Eh],0

        ;Insert default no blocks in driver.
                
                mov     byte ptr [RqHdr+0Dh],0

        ;Insert pointer to copy of command line.

                mov     ax,PSPSeg
                mov     word ptr [RqHdr+14h],ax
                mov     ax,NamePtr
                mov     word ptr [RqHdr+12h],ax

                push    cs
                pop     es

        ;DS:TopCSeg, ES:TopCSeg

        ;Store registers (don't count on driver to keep them).

                push    si

        ;Set ES:BX to point to RqHdr (for DvcStrat call.)

                mov     bx,offset RqHdr

        ;Set up return addresses on stack.

                mov     ds,cs:NewDrvSeg

        ;DS:NewDrvSeg, ES:TopCSeg
                
        ;Push far address of DEVLOAD.

                push    cs
                mov     ax,offset after_int
                push    ax

        ;Push far address of dvc_int.

                push    ds
                push    word ptr ds:[si+8]

        ;Push far address of dvc_strat

                push    ds
                push    word ptr ds:[si+6]

        ;Pass control to dvc_strat, which RETFs to dvc_int, which
        ;in turn RETFs to after_int.

BREAKPOINT2:    retf

        ;Restore registers.

after_int:      pop     si

        ;Increase count of character devices if it is one.

                test    byte ptr ds:[si+5],80h
                push    cs
                pop     ds
                jz      notchardev
                inc     CharsDone

        ;Print CrLf after driver.

notchardev:     mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

        ;Get offset of end of driver.

                mov     ax,word ptr ds:[RqHdr+0Eh]

        ;Convert to paragraphs (rounded up.)

                add     ax,0Fh
                rcr     ax,1
                mov     cl,3
                shr     ax,cl

        ;Add segment of end of driver.

                add     ax,word ptr ds:[RqHdr+10h]

        ;Compare with previous value of EndSeg

                cmp     ax,EndSeg
                jb      endset

        ;EndSeg has increased - this is only a problem if blocks are
        ;already installed.

                test    BlocksDone,0FFh
                jz      oktogrow

        ;Some block headers are already at EndSeg - can't change it now.
        
                mov     dx,offset BadIncMsg
                mov     ah,9
                int     21h
                jmp     endset

        ;No block headers done yet - change EndSeg.
                
oktogrow:       mov     EndSeg,ax

        ;DS:TopCSeg

        ;Check number of units in driver. Skip if none.

endset:         mov     ch,[RqHdr+0Dh]
                or      ch,ch
                jnz     yesunits

        ;No units in this device, so skip the next section.

                jmp     nounits

        ;Zero count of block number in this device.

yesunits:       xor     cl,cl

        ;Point ES:BP to new block header location.

                les     bp,BlHEnd

        ;Point DS:BX to BPB pointer array from driver.

                lds     bx,dword ptr [RqHdr+12h]

        ;Point DS:SI to next BPB and increase pointer.

nextblk:        mov     si,[bx]
                inc     bx
                inc     bx

        ;Check sector size.

                mov     ax,[si]
                cmp     ax,cs:[SecSize]
                jna     secsizeok
                jmp     secsizeerr

secsizeok:      mov     al,cs:LastDrUsed
                mov     cs:[BlHdrMsgA],'A'
                add     cs:[BlHdrMsgA],al
        
        ;Check lastdrive.

                cmp     al,cs:LastDrive
                jnz     ldrok
                jmp     ldrerr

        ;Increase LastDrUsed.

ldrok:          inc     cs:LastDrUsed

        ;Store absolute block no. and block no. in device.

                mov     ah,cl
                inc     cl
                mov     es:[bp],ax

        ;Store pointer to BPB ptr array.

                push    ds
                push    bx

        ;Point DS:BX to last block header in chain.

                lds     bx,cs:ChainEnd

        ;Make it point to the new one.

                add     bx,cs:word ptr NextBlHOfs
                mov     [bx],bp
                mov     [bx+2],es
                sub     bx,cs:word ptr NextBlHOfs

                push    cs
                pop     ds

        ;Store new pointer to end of block header chain.

                mov     ChainEndOfs,bp
                mov     ChainEndSeg,es
                
        ;Print address of new block header if Verbose Mode.

                test    ModeFlag,VerboseFlag
                jz      noprintblhmsg

                mov     dx,offset BlHdrMsg
                mov     ah,9
                int     21h
                
                mov     ax,es
                call    PHWord
                mov     ah,02h
                mov     dl,3ah
                int     21h
                mov     ax,bp
                call    PHWord

                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

        ;Get pointer to LASTDRIVE array.

noprintblhmsg:  lds     bx,Invar
                lds     bx,[bx+16h]

        ;Calculate offset in array of entry for this drive.

                mov     al,cs:LastDrUsed
                dec     al
                mov     ah,cs:LDrSize
                mul     ah
                add     bx,ax

        ;Insert 'valid' flag.

                mov     byte ptr [bx+44h],40h

        ;Insert pointer to block header for this drive.

                mov     word ptr [bx+45h],bp
                mov     word ptr [bx+47h],es

        ;Restore pointer to BPB pointer array.

                pop     bx
                pop     ds

        ;Insert pointer to device into block header.

                mov     ax,cs:NewDrvOfs
                add     bp,cs:word ptr NextBlHOfs
                mov     es:[bp-6],ax
                mov     ax,cs:NewDrvSeg
                mov     es:[bp-4],ax

        ;Insert 'BPB needs rebuilding' flag into block header.

                mov     byte ptr es:[bp-1],0FFh
                
        ;Insert 'End of chain' into block header.

                mov     es:[bp],0FFFFh
                sub     bp,cs:word ptr NextBlHOfs

        ;Expand BPB into block header.

                mov     ah,53h                 ;hello woody y doesnt this work
                int     21h

        ;Point ES:BP to location of next block header.

                add     bp,cs:BlHSize

        ;Store location of next block header.

                mov     cs:BlHEndOfs,bp

        ;Increase count of blocks installed.

                inc     cs:BlocksDone

        ;Loop if more blocks in this device to install.

nxtblkchk:      cmp     cl,ch
                jz      nounits
                jmp     nextblk

        ;Sector size too big - print error and fail to install this block.

secsizeerr:     push    cs
                pop     ds
                mov     dx,offset SSizeErrMsg
                mov     ah,9
                int     21h
                inc     cl
                jmp     nxtblkchk

        ;Lastdrive too small - signal error and don't install any more.

ldrerr:         push    cs
                pop     ds
                sub     ch,cl
                add     [LDrErrMsg],ch

        ;Finished installing units, or was none to install.

nounits:        push    cs
                pop     ds

        ;Print init return status if not Verbose Mode.

                test    ModeFlag,VerboseFlag
                jz      noprintinitret

                mov     dx,offset InitRetMsg
                mov     ah,9
                int     21h
                mov     ax,word ptr [RqHdr+3]
                call    PHWord

                mov     dx,offset CrLfMsg
                mov     ah,9
                int     21h

        ;DS:TopCSeg

        ;Set up pointers.

noprintinitret: les     bx,OldDrv
                lds     si,NewDrv

        ;DS:NewDvcSeg, ES:OldDvcSeg

        ;Find location of next driver in file.

                mov     ax,ds:[si+2]
                push    ax

                mov     ax,ds:[si]
                push    ax

        ;Link NewDrv to OldDrv.

                mov     ds:[si],bx
                mov     ds:[si+2],es

        ;Restore next driver in file address to AX:SI

                pop     si
                pop     ax

        ;Point ES:BX to just installed driver.

                les     bx,cs:NewDrv

        ;Check whether to change segment or use same seg for next driver.

                cmp     ax,0FFFFh
                jz      nosegchange

        ;Segment is different - add value onto old segment and put into DS.

                mov     cx,ds
                add     cx,ax
                mov     ds,cx

        ;Set zero flag on whether this is the last driver in the file.

nosegchange:    cmp     si,0FFFFh
                ret

;.............................TEXT MESSAGES..................................

StayingMsg      db 'Driver staying resident.',13,10,24h
FNameMsg        db 'Filename     : $'
LoadAddrMsg     db 'Load address : $'
InitRetMsg      db 'Init function return status : $'
SizeMsg         db 'Size of driver (paragraphs) : $'
IntChangeMsg    db 'Interrupt vectors changed   : $'
NoneMsg         db 'None.',13,10,24h
CommaMsg        db 'h, $'
FullStopMsg     db 'h.',13,10,24h
Colon0Msg       db ':'
NotStayMsg      db '0000'
CrLfMsg         db 13,10,24h
LastDrMsg       db 13,10,'Last drive in use : '
LDMsgA          db 'A:',13,10,'Last drive avail. : '
LDMsgB          db 'A:',13,10,24h
BlHdrMsg        db 'Block header for drive '
BlHdrMsgA       db 'A: at $'
NumBlInstMsg    db '0 block$'
NumChInstMsg    db '0 character device$'
NumInstMsgA     db 's installed.',13,10,24h
LDrErrMsg       db '0 block(s) not installed - '
                db 'LASTDRIVE= parameter in CONFIG.SYS too small.',13,10,24h
AskEndMsg       db 13,10,'No blocks or INTs installed - terminate (Y/N) ? $'
SSizeErrMsg     db 'Block not installed - sector size too large.',13,10,24h

        ;Error messages.

ReduceErrMsg    db "Error: Can't reduce memory allocation ($"
RelEnvErrMsg    db "Error: Can't release environment ($"
RelPSPErrMsg    db "Error: Can't release original segment ($"
GrabHiErrMsg    db "Error: Can't grab enough memory to relocate ($"
GrabLoErrMsg    db "Error: Can't grab memory to load driver ($"
Reduce2ErrMsg   db 13,10,"Error: Can't change final memory allocation ($"
Reduce2ErrMsga  db " Have installed driver; continuing anyway.",13,10
                db " Rebooting your system is recommended.",13,10,10,24h
BadIncMsg       db 'Error: End of driver address returned has increased after'
                db 13,10,'       block header(s) installed.',13,10
                db '       Increased request will be ignored.',13,10,24h
NotLoadMsg      db 13,10,'Error: EXEC failed ($'
TooBigMsg       db 13,10,'Error: Driver requested more memory than is '
                db 'available.',13,10,24h

        ;Error cause messages.

Err2            db 'h - File not found)',13,10,24h
Err3            db "h - Directory doesn't exist)",13,10,24h
Err5            db 'h - Access denied)',13,10,24h
Err7            db 'h - Arena header corrupted)',13,10,24h
Err8            db 'h - Out of memory)',13,10,24h
Err9            db 'h - Wrong segment passed!)',13,10
                db ' PLEASE INFORM THE AUTHOR!',13,10,24h
ErrB            db 'h - Format invalid)',13,10,24h
ErrUnknown      db 'h'
BadSwitchMsg2   db ')',13,10,24h


ErrTable        dw      ErrUnknown
                dw      ErrUnknown
                dw      Err2
                dw      Err3
                dw      ErrUnknown
                dw      Err5
                dw      ErrUnknown
                dw      Err7
                dw      Err8
                dw      Err9
                dw      ErrUnknown
                dw      ErrB

;.............................PROGRAM DATA...................................

LDrSize         db      58h,0   ;size of block in LastDrive array.
BlHSize         dw      0021h   ;size in paras of parameter block.
NextBlHOfs      db      19h,0   ;offset in parameter block of ptr to next one.

BlocksDone      db      00              ;no. of blocks installed.
CharsDone       db      00              ;no. of character devices installed.

DvcSeg          dw      ?               ;parameter block for EXEC function.
                dw      0000            ;i.e. segment, relocation factor.

ModeFlag        db      00

BlHEnd          label   dword
BlHEndOfs       dw      0000
EndSeg          dw      ?               ;segment, end of required memory.

PSPSeg          dw      ?

PathPtr         dd      0

NameBuffer      db      80h dup(?)
                  
LastDrUsed      db      ?
LastDrive       db      ?

OldAllocStrat   dw      ?
BlockSize       dw      ?

NamePtr         dw      ?               ;pointer to start of name.
NameLen         dw      ?

Invar           label   dword
InvarOfs        dw      ?
InvarSeg        dw      ?

ChainEnd        label   dword
ChainEndOfs     dw      ?               ;last device parameter block in chain.
ChainEndSeg     dw      ?

SecSize         dw      ?

NewDrv          label   dword
NewDrvOfs       dw      ?               ;storage for InstallDevice routine.
NewDrvSeg       dw      ?

OldDrv          label   dword
OldDrvOfs       dw      ?
OldDrvSeg       dw      ?

RqHdr           db      20h dup (?)

IntVectors      dw      200h dup (?)    ;storage for interrupt vectors,
                                        ;for checking whether they've changed.

        ;Marker to signal last byte that needs relocation.

LASTBYTE        equ     $

;.................DATA WHICH ISN'T NEEDED AFTER RELOCATION...................

SignOnMsg       db 'DEVLOAD.EXE v3.11 (C) 1992 - 1996 David Woodhouse.'
                db '  <Dave@imladris.demon.co.uk>',13,10
                db ' Loads device drivers from the command line.',13,10,10,24h

HelpMsg1        db 'Usage: DEVLOAD [<switches>] <filename> [<params>]',13,10
                db 'Emulates device=<filename> [<params>] in CONFIG.SYS',13,10
                db 10,'Switches:',13,10
                db '      /A - automatic mode (no abortion).',13,10
                db '   /? /H - display this help message.',13,10
                db '      /Q - quiet mode.',13,10
                db '      /V - verbose mode.',13,10
                db 10,'Not supported by DR-DOS or MS-DOS before 3.00',13,10,10
                db 'Breakpoints for debugging drivers -',13,10
                db 'Relocation RETF : $'
HelpMsg2        db 13,10,'Execution  RETF : $'


BadSwitchMsg    db 'Error: Bad switch ($'
NoFileMsg       db 'Error: No filename given. Use DEVLOAD /? for instructions.'
                db 13,10,24h
FileNoExistMsg  db "Error: Can't open file ($"
BadVerMsg       db 'Error: This program uses version-specific information, and'
                db 13,10,'       only supports MS-DOS versions 3 to 6.'
                db 13,10,24h


;.........MAIN PROGRAM ENTRY POINT - SITUATE ABOVE LASTBYTE BECAUSE..........
;......IT DOESN'T NEED TO BE KEPT WHEN RELOCATING TO THE TOP OF MEMORY.......

        ;Set up segment registers.

Main:           push    cs
                pop     ds
                push    cs
                pop     es
                cld

        ;Get PSP segment.

                mov     ah,62h
                int     21h
                mov     cs:PSPSeg,bx

        ;Print sign on message.

                mov     dx,offset SignOnMsg
                mov     ah,9
                int     21h

        ;Check DOS version.

                mov     ax,3000h
                int     21h
                cmp     al,3
                ja      okver
                jz      ver3

        ;Version before 3.0, so print error and exit.

                mov     dx,offset BadVerMsg
                jmp     prexit

        ;Version 3.x, so change variables to correct values.

ver3:           mov     LDrSize,51h
                mov     byte ptr BlHSize,20h
                mov     NextBlHOfs,18h

        ;Check command line.

okver:          mov     ds,PSPSeg
                xor     bh,bh
                mov     bl,byte ptr ds:[80h]
                or      bx,bx
                jnz     cmdlineexists

        ;No parameters given - print error and exit.

nofilename:     mov     dx,offset NoFileMsg
                push    cs
                pop     ds
                jmp     prexit

        ;Command line exists - convert to all upper case.

cmdlineexists:  mov     si,0081h
                mov     cx,bx
toupperloop:    lodsb
                cmp     al,'a'
                jb      notlower
                cmp     al,'z'
                ja      notlower
                xor     al,20h
                mov     [si-1],al
notlower:       loop    toupperloop

        ;Check whether filename present.

                mov     si,0081h
                add     bx,si

        ;DS:SI--> Start of command line.
        ;DS:BX--> End of command line.

getloop1:       lodsb

        ;If passed end of command line, exit loop.

                cmp     si,bx
                ja      nofilename

        ;Loop while whitespace.

                cmp     al,' '
                jz      getloop1
                cmp     al,9
                jz      getloop1

        ;Found non-whitespace, point back at it.

                dec     si

        ;DS:SI --> first non-whitespace char on command line.

        ;Get current switch char (usually '/').

                mov     ax,3700h
                int     21h

        ;Check whether first char on command line is a switch.

                cmp     [si],dl
                jz      isswitch
                jmp     noswitch

        ;Load switch and check it.

isswitch:       lodsw
                cmp     ah,'?'
                jz      help
                cmp     ah,'H'
                jz      help
                cmp     ah,'Q'
                jz      quiet
                cmp     ah,'A'
                jz      auto
                cmp     ah,'V'
                jz      verbose

        ;Unrecognised switch - print error and exit.

unknownswitch:  push    ax

                push    cs
                pop     ds

                mov     dx,offset BadSwitchMsg
                mov     ah,9
                int     21h

                pop     dx
                mov     ah,2
                int     21h
                mov     dl,dh
                int     21h

                mov     dx,offset BadSwitchMsg2
                jmp     prexit

        ;Print help message.

help:           push    cs
                pop     ds

                mov     dx,offset HelpMsg1
                mov     ah,9
                int     21h
                mov     ax,offset BREAKPOINT1
                call    PHWord
                mov     dx,offset HelpMsg2
                mov     ah,9
                int     21h
                mov     ax,offset BREAKPOINT2
                call    PHWord
                mov     dx,offset CrLfMsg
                jmp     prexit

        ;Set verbose mode flag.

verbose:        or      cs:ModeFlag,VerboseFlag
                and     cs:ModeFlag,not QuietFlag
                jmp     switchloop

        ;Set automatic mode flag.

auto:           or      cs:ModeFlag,AutoFlag
                jmp     switchloop

        ;Set quiet mode flag.

quiet:          or      cs:ModeFlag,QuietFlag
                and     cs:ModeFlag,not VerboseFlag

        ;Skip to next space.

switchloop:     lodsb
                cmp     si,bx
                jna     switchloop1
                jmp     nofilename

switchloop1:    cmp     al,9
                jz      outswitchloop
                cmp     al,' '
                jnz     switchloop

        ;Point back at first space and go back to getloop1 to skip
        ;to either next switch or to filename.

outswitchloop:  dec     si
                jmp     getloop1

        ;Store pointer to start of pathname.

noswitch:       push    si
                mov     bp,si

        ;Find pointer to actual 8-char filename and end of pathname.

getloop2:       lodsb
                cmp     al,'\'
                jz      backsl
                cmp     al,'/'
                jnz     nobacksl

        ;Move pointer to after backslash into BP.

backsl:         mov     bp,si

        ;Break out of loop if space, tab, CR or LF found.

nobacksl:       cmp     al,' '
                jz      outloop2
                cmp     al,9
                jz      outloop2
                cmp     al,13
                jz      outloop2
                cmp     al,10
                jz      outloop2

        ;Check whether end of command line reached. Loop if not.

                cmp     si,bx
                jna     getloop2

        ;DS:SI-2 --> last char of pathname.
        ;DS:BP --> first char in filename.

        ;Calculate length of filename.

outloop2:       mov     es:NamePtr,bp
                dec     si
                mov     cx,si
                sub     si,bp
                mov     es:NameLen,si

        ;Restore pointer to start of pathname.

                pop     si

        ;Check whether file specified contains path.

                cmp     si,bp
                jz      notpathname

        ;Set PathPtr to point to zero - simulate no PATHs left.

                mov     word ptr es:PathPtr,offset DvcSeg+2
                mov     word ptr es:PathPtr+2,cs

        ;Start with default directory.

notpathname:    sub     cx,si
                mov     di,offset NameBuffer

        ;Use default directory or one specified first time, not PATH.

                jmp     entrypoint

;............................................................................

        ;Filename doesn't exist as specified - try using PATH.

        ;Check whether we've already got a pointer to PATH.

allpathloop:    lds     si,PathPtr
                or      si,si
                jnz     pathfound

        ;Not yet, so find PATH segment.

                mov     ds,cs:PSPSeg
                mov     bx,word ptr ds:[002Ch]

        ;Check whether it exists.

                or      bx,bx
                jnz     envsegexists

        ;No more PATH items or no PATH segment, so print error and exit.

filenoexist:    push    cs
                pop     ds
                mov     dx,offset FileNoExistMsg
                jmp     fileerr

        ;Store PATH segment in local pointer.

envsegexists:   mov     ds,bx
                mov     word ptr cs:PathPtr+2,bx

        ;Scan environment for 'PATH='
                                     
envloop1:       lodsb
                cmp     al,0
                jz      filenoexist
                cmp     al,'P'
                jnz     nextenvvar1
                lodsb
                cmp     al,'A'
                jnz     nextenvvar1
                lodsb
                cmp     al,'T'
                jnz     nextenvvar1
                lodsb
                cmp     al,'H'
                jnz     nextenvvar1
                lodsb
                cmp     al,'='
                jnz     nextenvvar1
                jmp     pathfound

        ;Not 'PATH=', so skip to next environment variable.

nextenvvar:     lodsb
nextenvvar1:    or      al,al
                jnz     nextenvvar
                jmp     envloop1

        ;Store file error message.

pathfound:      push    ax

        ;Skip spaces at start of this PATH item.

pathfoundloop:  lodsb
                cmp     al,' '
                jz      pathfoundloop
                cmp     al,9
                jz      pathfoundloop

        ;DS:SI-1 --> first non-whitespace in PATH item.

        ;If we've reached the end of the PATH statement, error and exit.

                cmp     al,0
                jz      filenoexist

        ;Forget file error message - we'll try again.

                add     sp,2

        ;Store start of this PATH item + 1.

                push    si

        ;Find end of this PATH item.

pathloop1:      lodsb
                cmp     al,0
                jz      endpath
                cmp     al,';'
                jnz     pathloop1

        ;Store start of next PATH item.

endpath:        mov     word ptr cs:PathPtr,si

        ;If last one, point back at the terminating NULL.

                or      al,al
                jnz     ismorepaths
                dec     word ptr cs:PathPtr

        ;Calculate length of this PATH item.

ismorepaths:    mov     cx,si
                pop     si
                sub     cx,si
                dec     si

        ;Copy PATH item to NameBuffer.

                mov     di,offset NameBuffer
                rep     movsb

        ;Add backslash if necessary.

                push    cs
                pop     ds

                cmp     byte ptr [di-1],'\'
                jz      alreadybacksl
                mov     al,'\'
                stosb

        ;Copy filename after PATH item.

alreadybacksl:  mov     si,NamePtr
                mov     cx,NameLen

                mov     ds,PSPSeg

entrypoint:     rep     movsb

        ;Store terminating NULL.

                xor     al,al
                stosb

        ;Check whether file exists by attempting to get attributes.

                push    cs
                pop     ds

                mov     dx,offset NameBuffer
                mov     ax,4300h
                int     21h
                jnc     foundfilename
                jmp     allpathloop

        ;Found file entry, but is it a directory?

foundfilename:  test    cl,10h
                jz      okfilename

        ;If it is, make the error code into `file not found'
        
                mov     ax,2
                jmp     allpathloop

        ;File exists - expand filename using function 60h.

okfilename:     mov     si,offset NameBuffer
                mov     di,si
                mov     ah,60h
                int     21h

        ;Get old allocation strategy.

                mov     ax,5800h
                int     21h
                mov     OldAllocStrat,ax

        ;Reduce main allocation.

        ;DS:CSeg, ES:CSeg

                mov     bx,offset LASTBYTE+10Fh
                add     bx,offset STACKLEN
                mov     cl,4
                shr     bx,cl
                mov     cx,bx
                mov     es,PSPSeg
                mov     ah,4ah
                int     21h
                jnc     reduceok

        ;Failed to reduce memory allocation, so print error and exit.

                mov     dx,offset ReduceErrMsg
                jmp     allocerr

        ;Set allocation strategy to highest fit.

reduceok:       mov     ax,5801h
                mov     bx,2
                int     21h

        ;Request enough at top of mem for PSP + DEVLOAD + STACK.

                mov     bx,cx
                mov     ah,48h
                int     21h
                pushf
                mov     es,ax

        ;Reset allocation strategy to old value.

        ;DS:CSeg, ES:TopPSPSeg

                mov     ax,5801h
                mov     bx,OldAllocStrat
                int     21h

        ;Check whether grabbed memory OK.

                popf
                jnc     nograbhierr

        ;Failed to grab memory, so print error and exit.

                mov     dx,offset GrabHiErrMsg
                jmp     allocerr

        ;Make new PSP at top of memory.

        ;DS:CSeg, ES:TopPSPSeg

nograbhierr:    mov     ds,PSPSeg
                mov     si,word ptr [2]
                mov     dx,es
                mov     ah,55h
                int     21h

        ;Fix parent PSP record in new PSP.

                mov     ax,ds:[16h]
                mov     es:[16h],ax

        ;Move program to top of memory.

                mov     cx,offset LASTBYTE+8Fh
                and     cx,0FFF0h
                shr     cx,1
                mov     di,80h
                mov     si,di
                rep     movsw

        ;Make segment at top of memory self-owned.

                push    cs
                pop     ds

                mov     ax,es
                dec     ax
                mov     ds,ax
                mov     word ptr ds:[1],es

                push    cs
                pop     ds

        ;Calculate location of stack at top of memory.

                mov     bx,offset LASTBYTE+10Fh
                mov     cl,4
                shr     bx,cl
                mov     ax,es
                add     ax,bx

        ;Change to stack at top of memory.

                mov     ss,ax

        ;Make PSP at top of memory current.

                mov     bx,es
                mov     ah,50h
                int     21h

        ;Transfer control to top of memory via RETF.

                mov     ax,es
                add     ax,10h
                mov     ds,ax
                push    ax
                mov     ax,offset relocated
                push    ax
BREAKPOINT1:    retf





CSeg            ends

SSeg    segment stack   para    'STACK'

        org     0

        db      STACKLEN dup (?)


SSeg            ends

        end     Main
