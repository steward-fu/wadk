;// A simple Windows GUI program that creates an empty window;
option casemap:none
option frame:auto       ;//generate SEH-compatible prologues and epilogues
option win64:11         ;//reserve stack space once per procedure
option STACKBASE : RSP

.nolist
.nocref
WINVER EQU 600h

WIN32_LEAN_AND_MEAN equ 1
_WIN64    EQU 1
include windows.inc
include string.inc
include guiddef.INC
include CommCtrl.inc
include winbase.inc
include shellapi.inc
include winuser.inc
include commdlg.INC 
include Richedit.inc
include OLE2.INC
include windef.inc
include xmmtypes.inc
.list
.cref
includelib advapi32.lib
includelib user32.lib
includelib kernel32.lib
includelib gdi32.lib
includelib comctl32.lib
includelib Shell32.lib
includelib comdlg32.lib
includelib Ole32.lib
includelib uuid.lib
    

__DOALIGN32 MACRO 
    mov rax,[rsp]                 ;// save RET address in rax
    add rsp, 31                   ;// make sure wee don't delete some important data on the stack
    and rsp, 0FFFFFFFFFFFFFFE0h   ;// align it to 32 byte
    add rsp,10h                   ;// that is after call 8 and after push rbx it is 32 bit aligned
    mov [rsp],rax                 ;// put return address back for the RET
ENDM
.data
ClassName db "SimpleWinClass",0
AppName  db "Our First Window",0

.data?

hInstance HINSTANCE ?
CommandLine LPSTR ?

.code
    align 16;//================================================================================
WinMainCRTStartup proc FRAME
    __DOALIGN32    ;//this will isure 32 byte aligned locals  in next function call 
    invoke GetModuleHandleA, NULL
    mov    hInstance, rax
    invoke GetCommandLineA
    mov    CommandLine, rax    
    invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
    invoke ExitProcess, eax
    ret
WinMainCRTStartup endp
;//================================================================================
WinMain proc FRAME hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:UINT
 local wc:WNDCLASSEXA
 local msg:MSG
 local hwnd:HWND
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
;//==================================================================
WndProc proc FRAME hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
local mybuff[34]:BYTE

    .if ( uMsg == WM_DESTROY )
        invoke PostQuitMessage, NULL
        xor rax,rax
    .else
        invoke DefWindowProcA, rcx, edx, r8, r9
    .endif
    ret
WndProc endp
;//==================================================================

end WinMainCRTStartup
