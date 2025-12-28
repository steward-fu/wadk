

;--- a simple Windows GUI program, no includes.
;---
;--- to create the binary enter:
;---   jwasm -coff Win32_3.asm
;---   link Win32_3.obj /subsystem:windows

    .486
    .model flat,stdcall
    option casemap:none

    includelib <kernel32.lib>
    includelib <user32.lib>

HINSTANCE typedef ptr
HWND      typedef ptr
HMENU     typedef ptr
HICON     typedef ptr
HBRUSH    typedef ptr
HCURSOR   typedef ptr
WPARAM    typedef dword
LPARAM    typedef dword
LPSTR     typedef ptr
LPVOID    typedef ptr
UINT      typedef dword

proto_WNDPROC typedef proto :HWND,:dword,:WPARAM,:LPARAM
WNDPROC typedef ptr proto_WNDPROC

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

POINT struct
x   sdword ?
y   sdword ?
POINT ends

MSG struct
hwnd    HWND ?
message dword ?
wParam  WPARAM ?
lParam  LPARAM ?
time    dword ?
pt      POINT <>
MSG ends

WNDCLASSEXA struct 
cbSize          dword ?
style           dword ?
lpfnWndProc     WNDPROC ?
cbClsExtra      dword ?
cbWndExtra      dword ?
hInstance       HINSTANCE ?
hIcon           HICON ?
hCursor         HCURSOR ?
hbrBackground   HBRUSH ?
lpszMenuName    LPSTR ?
lpszClassName   LPSTR ?
hIconSm         HICON ?
WNDCLASSEXA ends

WinMain          proto :HINSTANCE,:HINSTANCE,:LPSTR,:dword
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

    .data

ClassName db "SimpleWinClass",0
AppName  db "Our First Window",0
hellomsg db "Hello world"

    .data?

hInstance HINSTANCE ?
CommandLine LPSTR ?

    .code

start:
    invoke GetModuleHandleA, NULL
    mov    hInstance, eax
    invoke GetCommandLineA
    mov    CommandLine, eax
    invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
    invoke ExitProcess, eax

WinMain proc hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:dword
    local wc:WNDCLASSEXA
    local msg:MSG
    local hwnd:HWND

    mov   wc.cbSize, sizeof WNDCLASSEXA
    mov   wc.style, CS_HREDRAW or CS_VREDRAW
    mov   wc.lpfnWndProc, offset WndProc
    mov   wc.cbClsExtra, 0
    mov   wc.cbWndExtra, 0
    push  hInstance
    pop   wc.hInstance
    mov   wc.hbrBackground, COLOR_WINDOW+1
    mov   wc.lpszMenuName, NULL
    mov   wc.lpszClassName, offset ClassName
    invoke LoadIconA, NULL, IDI_APPLICATION
    mov   wc.hIcon, eax
    mov   wc.hIconSm, eax
    invoke LoadCursorA, NULL, IDC_ARROW
    mov   wc.hCursor, eax
    invoke RegisterClassExA, addr wc
    invoke CreateWindowExA, NULL, ADDR ClassName, ADDR AppName,
           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
           CW_USEDEFAULT, NULL, NULL, hInst, NULL
    mov   hwnd, eax
    invoke ShowWindow, hwnd, SW_SHOWNORMAL
    invoke UpdateWindow, hwnd
    .while (1)
        invoke GetMessageA, ADDR msg, NULL, 0, 0
        .break .if (!eax)
        invoke TranslateMessage, ADDR msg
        invoke DispatchMessageA, ADDR msg
    .endw
    mov   eax, msg.wParam
    ret
WinMain endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov eax, uMsg
    .if (eax == WM_DESTROY)
        invoke PostQuitMessage, NULL
        xor eax,eax
    .else
        invoke DefWindowProcA, hWnd, uMsg, wParam, lParam
    .endif
    ret
WndProc endp

end start
