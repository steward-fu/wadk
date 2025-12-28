

;--- A simple Windows GUI program that creates an empty window;
;--- Similar to Win64_3, but unlike that variant this version 
;--- uses hll directives, so it cannot be assembled
;--- with Masm64. Also, OPTION FRAME:AUTO is used.
;---
;--- assemble:
;---   JWasm -win64 Win64_3e.asm
;--- link:
;---   MS Link: link Win64_3e.obj libpath:\wininc\lib64
;---   JWlink:  jwlink format win pe f Win64_3e.obj libpath \wininc\lib64

    option casemap:none
    option frame:auto    ;generate SEH-compatible prologues and epilogues
    option win64:2       ;reserve stack space once per procedure

    includelib kernel32.lib
    includelib user32.lib

HINSTANCE typedef qword
HWND      typedef qword
HMENU     typedef qword
HICON     typedef qword
HBRUSH    typedef qword
HCURSOR   typedef qword
WPARAM    typedef qword
LPARAM    typedef qword
LPSTR     typedef qword
LPVOID    typedef qword
UINT      typedef dword

NULL           equ 0
WS_OVERLAPPEDWINDOW equ 0CF0000h
CW_USEDEFAULT  equ 80000000h
SW_SHOWDEFAULT equ 10
SW_SHOWNORMAL  equ 1
IDC_ARROW      equ 32512
IDI_APPLICATION equ 32512
WM_DESTROY     equ 2
CS_VREDRAW     equ 1
CS_HREDRAW     equ 2
COLOR_WINDOW   equ 5

proto_WNDPROC typedef proto :HWND,:qword,:WPARAM,:LPARAM
WNDPROC typedef ptr proto_WNDPROC

WNDCLASSEXA struct 8
cbSize          dword   ?
style           dword   ?
lpfnWndProc     WNDPROC ?
cbClsExtra      dword   ?
cbWndExtra      dword   ?
hInstance       HINSTANCE ?
hIcon           HICON   ?
hCursor         HCURSOR ?
hbrBackground   HBRUSH  ?
lpszMenuName    LPSTR   ?
lpszClassName   LPSTR   ?
hIconSm         HICON   ?
WNDCLASSEXA ends

POINT   struct
x   sdword  ?
y   sdword  ?
POINT   ends

MSG struct 8
hwnd    HWND    ?
message dword   ?
wParam  WPARAM  ?
lParam  LPARAM  ?
time    dword   ?
pt      POINT   <>
MSG ends

GetModuleHandleA proto :LPSTR
GetCommandLineA  proto
ExitProcess      proto :UINT
LoadIconA        proto :HINSTANCE, :LPSTR
LoadCursorA      proto :HINSTANCE, :LPSTR
RegisterClassExA proto :ptr WNDCLASSEXA
CreateWindowExA  proto :dword, :LPSTR, :LPSTR, :dword, :sdword, :sdword, :sdword, :sdword, :HWND, :HMENU, :HINSTANCE, :LPVOID
ShowWindow       proto :HWND, :sdword
UpdateWindow     proto :HWND
GetMessageA      proto :ptr MSG, :HWND, :sdword, :sdword
TranslateMessage proto :ptr MSG
DispatchMessageA proto :ptr MSG
PostQuitMessage  proto :sdword
DefWindowProcA   proto :HWND, :UINT, :WPARAM, :LPARAM

WinMain proto :HINSTANCE, :HINSTANCE, :LPSTR, :UINT

    .data

ClassName db "SimpleWinClass",0
AppName  db "Our First Window",0

    .data?

hInstance HINSTANCE ?
CommandLine LPSTR ?

    .code

WinMainCRTStartup proc FRAME

    invoke GetModuleHandleA, NULL
    mov    hInstance, rax
    invoke GetCommandLineA
    mov    CommandLine, rax
    invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
    invoke ExitProcess, eax

WinMainCRTStartup endp

WinMain proc FRAME hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:UINT

    local wc:WNDCLASSEXA
    local msg:MSG
    local hwnd:HWND

;--- init the "shadow variable". Alternatively, one may set bit 0 
;--- of OPTION WIN64, then this is done automatically.
    mov   hInst, rcx

    mov   wc.cbSize, sizeof WNDCLASSEXA
    mov   wc.style, CS_HREDRAW or CS_VREDRAW
    lea   rax, [WndProc]
    mov   wc.lpfnWndProc, rax
    mov   wc.cbClsExtra, 0
    mov   wc.cbWndExtra, 0
    mov   wc.hInstance, rcx
    mov   wc.hbrBackground, COLOR_WINDOW+1
    mov   wc.lpszMenuName, NULL
    lea   rax, [ClassName]
    mov   wc.lpszClassName, rax
    invoke LoadIconA, NULL, IDI_APPLICATION
    mov   wc.hIcon, rax
    mov   wc.hIconSm, rax
    invoke LoadCursorA, NULL, IDC_ARROW
    mov   wc.hCursor,rax
    invoke RegisterClassExA, addr wc
    invoke CreateWindowExA, NULL, ADDR ClassName, ADDR AppName,\
           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,\
           CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL,\
           hInst, NULL
    mov   hwnd,rax
    invoke ShowWindow, hwnd, SW_SHOWNORMAL
    invoke UpdateWindow, hwnd
    .while (1)
        invoke GetMessageA, ADDR msg, NULL, 0, 0
        .break .if (!eax)
        invoke TranslateMessage, ADDR msg
        invoke DispatchMessageA, ADDR msg
    .endw
    mov   rax, msg.wParam
    ret
WinMain endp

WndProc proc FRAME hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if ( edx == WM_DESTROY )
        invoke PostQuitMessage, NULL
        xor rax,rax
    .else
        invoke DefWindowProcA, rcx, edx, r8, r9
    .endif
    ret
WndProc endp

end WinMainCRTStartup
