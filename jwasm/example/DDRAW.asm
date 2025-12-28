;---------------------------------------;
;    DDRAW Plasma Demo                  ;
;                                       ;
;    Author :         X-Calibre         ;
;    ASM version :    Ewald Snel        ;
;    Copyright (C) 1999, Diamond Crew   ;
;                                       ;
;    https://here.is/diamond/            ;
;---------------------------------------;


EXCLUSIVE   equ 1

; View with TAB size 4

    TITLE WIN32ASM EXAMPLE
    .486
    .MODEL FLAT, STDCALL
    option casemap :none

;-----------------------------------------------------------;
;                WIN32ASM / DDRAW PLASMA DEMO               ;
;-----------------------------------------------------------;

    .nolist
    .nocref
WIN32_LEAN_AND_MEAN equ 1
COBJMACROS          equ 1
    INCLUDE windows.inc
    INCLUDE ddraw.inc
    .list
    .cref

    INCLUDELIB gdi32.lib
    INCLUDELIB kernel32.lib
    INCLUDELIB user32.lib
    INCLUDELIB ddraw.lib

    nextFrame   PROTO
    initPlasma  PROTO

RETURN  MACRO   arg
    IFNB <arg>
        mov     eax, arg
    ENDIF
    ret
ENDM

LRETURN MACRO   arg 
    IFNB <arg>
        mov     eax, arg
    ENDIF
    leave
    ret
ENDM

FATAL   MACRO   msg
    LOCAL @@msg
    .DATA
    @@msg   db  msg, 0
    .CODE
    INVOKE  MessageBox, hWnd, ADDR @@msg, ADDR szDisplayName, MB_OK
    INVOKE  ExitProcess, 0
ENDM


.DATA?
hWnd            HWND                ?       ; surface window
lpDD            LPDIRECTDRAW        ?       ; DDraw object
lpDDSPrimary    LPDIRECTDRAWSURFACE ?       ; DDraw primary surface
ddsd            DDSURFACEDESC       <?>; DDraw surface descriptor
ddscaps         DDSCAPS             <?>; DDraw capabilities

palette         dd                  256 dup (?)
table           dd                  512 dup (?)

.DATA

ddwidth         EQU                 800     ; display mode width
ddheight        EQU                 600     ; display mode height
ddbpp           EQU                 32      ; display mode color depth
BYTESPIXEL      equ                 4

phaseA          dd                  0
phaseB          dd                  0

factor1         EQU                 -1
factor2         EQU                 1
factor3         EQU                 1
factor4         EQU                 -1

red             REAL4               300.0
green           REAL4               320.0
blue            REAL4               340.0

scale1          REAL4               2.0
scale2          REAL4               127.5
scale3          REAL4               256.0

szClassName     db                  "DDRAW Plasma Demo", 0  ; class name
szDisplayName   EQU                 <szClassName>     ; window name

wc              WNDCLASSEX          < sizeof WNDCLASSEX, CS_HREDRAW or CS_VREDRAW, offset WndProc, 0, 0, , 0, 0, , 0, offset szClassName, 0 >

.CODE
start:

    INVOKE  GetModuleHandle, NULL
    INVOKE  WinMain, eax, NULL, NULL, SW_SHOWDEFAULT
    INVOKE  ExitProcess, eax



;-----------------------------------------------------------;
;                Calculate Next Plasma Frame                ;
;-----------------------------------------------------------;

nextFrame   PROC
    push    ebx
    push    esi
    push    edi

    mov     ecx, ddheight           ; # of scanlines
    mov     edi, [ddsd.lpSurface]   ; pixel output

@@scanline:
    push    ecx
    push    edi

    mov     esi, [phaseA]
    mov     edx, [phaseB]
    sub     esi, ecx
    and     edx, 0FFh
    and     esi, 0FFh
    mov     edx, [table][4*edx][256*4]
    mov     esi, [table][4*esi]     ; [x]  +  table0[a + y]
    sub     edx, ecx                ; [y]  +  table1[b]
    mov     ecx, ddwidth            ; [x] --> pixel counter

@@pixel:
    and     esi, 0FFh
    and     edx, 0FFh
    mov     eax, [table][4*esi]
    mov     ebx, [table][4*edx][256*4]
    add     eax, ebx
    add     esi, factor3
    shr     eax, 1
    add     edx, factor4
    and     eax, 0FFh
    add     edi, BYTESPIXEL
    mov     eax, [palette][4*eax]
    dec     ecx
    mov     [edi][-BYTESPIXEL], eax
    jnz     @@pixel

    pop     edi
    pop     ecx
    add     edi, [ddsd.lPitch]      ; inc. display position
    dec     ecx
    jnz     @@scanline

    add     [phaseA], factor1
    add     [phaseB], factor2

    pop     edi
    pop     esi
    pop     ebx

    ret
nextFrame   ENDP


;-----------------------------------------------------------;
;                Initalize Plasma Tables                    ;
;-----------------------------------------------------------;

initPlasma  PROC

    LOCAL @@i :DWORD
    LOCAL @@r :DWORD
    LOCAL @@g :DWORD
    LOCAL @@b :DWORD
    LOCAL temp :DWORD

    mov     [@@i], 0

    .WHILE @@i < 256

        mov     edx, [@@i]

; Calculate table0 value

        fldpi
        fimul   [@@i]
        fmul    [scale1]
        fdiv    [scale3]
        fsin
        fmul    [scale2]
        fadd    [scale2]
        fistp   [table][4*edx]

; Calculate table1 value

        fldpi
        fimul   [@@i]
        fmul    [scale1]
        fdiv    [scale3]
        fcos
        fmul    [scale2]
        fadd    [scale2]
        fldpi
        fmulp   st(1), st
        fmul    [scale1]
        fdiv    [scale3]
        fsin
        fmul    [scale2]
        fadd    [scale2]
        fistp   [table][4*edx][4*256]

; Calculate palette value

        xor     eax, eax

        FOR comp, <red, green, blue>
            fldpi
            fimul   [@@i]
            fmul    [scale1]
            fdiv    [comp]
            fcos
            fmul    [scale2]
            fadd    [scale2]
            fistp   [temp]
            shl     eax, 8
            or      eax, [temp]
        ENDM

        mov     [palette][4*edx] , eax
        inc     [@@i]

    .ENDW

    ret
initPlasma  ENDP



;-----------------------------------------------------------;
;                WinMain  ( entry point )                   ;
;-----------------------------------------------------------;

WinMain     PROC    hInst     :HINSTANCE,
                    hPrevInst :HINSTANCE,
                    CmdLine   :LPSTR,
                    CmdShow   :DWORD

    LOCAL msg  :MSG

; Fill WNDCLASSEX structure with required variables

    mov     eax, [hInst]
    mov     [wc.hInstance], eax
    INVOKE  GetStockObject, BLACK_BRUSH
    mov     [wc.hbrBackground], eax

    INVOKE  RegisterClassEx, ADDR wc

; Create window at following size

if EXCLUSIVE
    INVOKE  CreateWindowEx, 0, ADDR szClassName, ADDR szDisplayName, WS_POPUP, 0, 0, ddwidth, ddheight, NULL, NULL, hInst, NULL
else
    INVOKE  CreateWindowEx, 0, ADDR szClassName, ADDR szDisplayName, WS_POPUP, 100, 100, ddwidth, ddheight, NULL, NULL, hInst, NULL
endif
    mov     [hWnd], eax

    INVOKE  SetFocus, hWnd

if EXCLUSIVE
    INVOKE  ShowCursor, 0
endif

; Initialize display

    INVOKE  DirectDrawCreate, NULL, ADDR lpDD, NULL
    .IF eax != DD_OK
        FATAL "Couldn't init DirectDraw"
    .ENDIF

if EXCLUSIVE
    INVOKE  IDirectDraw_SetCooperativeLevel(lpDD, hWnd, DDSCL_EXCLUSIVE or DDSCL_FULLSCREEN)
else
    INVOKE  IDirectDraw_SetCooperativeLevel(lpDD, hWnd, DDSCL_NORMAL)
endif
    .IF eax != DD_OK
        FATAL "Couldn't set DirectDraw cooperative level"
    .ENDIF

if EXCLUSIVE
    INVOKE  IDirectDraw_SetDisplayMode(lpDD, ddwidth, ddheight, ddbpp)
    .IF eax != DD_OK
        FATAL "Couldn't set display mode"
    .ENDIF
endif

    mov     [ddsd.dwSize], sizeof DDSURFACEDESC
    mov     [ddsd.dwFlags], DDSD_CAPS
    mov     [ddsd.ddsCaps.dwCaps], DDSCAPS_PRIMARYSURFACE
    INVOKE  IDirectDraw_CreateSurface(lpDD, ADDR ddsd, ADDR lpDDSPrimary, NULL)
    .IF eax != DD_OK
        FATAL "Couldn't create primary surface"
    .ENDIF

    INVOKE  ShowWindow, hWnd, CmdShow

    call    initPlasma

; Loop until PostQuitMessage is sent

    .WHILE 1

        INVOKE  PeekMessage, ADDR msg, NULL, 0, 0, PM_REMOVE

        .IF eax != 0
            .IF msg.message == WM_QUIT
                INVOKE  PostQuitMessage, msg.wParam
                .BREAK
            .ELSE
                INVOKE  TranslateMessage, ADDR msg
                INVOKE  DispatchMessage, ADDR msg
            .ENDIF
        .ELSE
            INVOKE  GetFocus

            .IF eax == hWnd

                mov     [ddsd.dwSize], sizeof DDSURFACEDESC
                mov     [ddsd.dwFlags], DDSD_PITCH

                .WHILE 1
                    INVOKE  IDirectDrawSurface_Lock(lpDDSPrimary, NULL, ADDR ddsd, DDLOCK_WAIT, NULL)

                    .BREAK .IF eax == DD_OK

                    .IF (eax == DDERR_SURFACELOST)
                        INVOKE  IDirectDrawSurface_Restore(lpDDSPrimary)
                    .ELSE
                        FATAL "Couldn't lock surface"
                    .ENDIF
                .ENDW

                INVOKE  IDirectDraw_WaitForVerticalBlank(lpDD, DDWAITVB_BLOCKBEGIN, NULL)

                call    nextFrame

                INVOKE  IDirectDrawSurface_Unlock(lpDDSPrimary, ddsd.lpSurface)

            .ENDIF
        .ENDIF
    .ENDW

if EXCLUSIVE
    INVOKE IDirectDraw_RestoreDisplayMode(lpDD)
    .IF eax != DD_OK
        FATAL "Couldn't restore displaymode"
    .ENDIF
endif

    INVOKE DestroyWindow, hWnd
    .IF eax == NULL
        FATAL "Couldn't destroy window"
    .ENDIF

    .IF lpDD != NULL
        .IF lpDDSPrimary != NULL
            INVOKE  IDirectDrawSurface_Release(lpDDSPrimary)
            mov     [lpDDSPrimary], NULL
        .ENDIF

        INVOKE  IDirectDraw_Release(lpDD)
        mov     [lpDD], NULL

    .ENDIF

    ret
WinMain     ENDP


;-----------------------------------------------------------;
;             Window Proc  ( handle events )                ;
;-----------------------------------------------------------;

WndProc     PROC    hWin   :DWORD,
                    uMsg   :DWORD,
                    wParam :DWORD,
                    lParam :DWORD

    .IF uMsg == WM_KEYDOWN
        .IF wParam == VK_ESCAPE
            INVOKE  PostQuitMessage, NULL
            RETURN  0 
        .ENDIF
    .ELSEIF uMsg == WM_DESTROY
        INVOKE  PostQuitMessage, NULL
        RETURN  0 
    .ENDIF

    INVOKE  DefWindowProc, hWin, uMsg, wParam, lParam

    ret
WndProc     ENDP

END start
