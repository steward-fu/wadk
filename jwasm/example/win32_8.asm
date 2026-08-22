

;--- a Windows GUI app to demonstrate -pe cmdline option.
;--- no include files and no libraries are needed.
;--- a menu and a bitmap resource are defined "manually".
;---
;--- to create the binary enter:
;---   JWasm -pe Win32_8.asm
;--- expects bitmap "Win32_8.bmp" in current directory.

    .486
    .model flat,stdcall
    option casemap:none

NULL       equ 0
LPSTR      typedef ptr sbyte
UINT_PTR   typedef ptr
LONG_PTR   typedef ptr
BOOL       typedef sdword
UINT       typedef dword

;--- resource IDs
IDR_MENU1   equ 100
IDR_BITMAP1 equ 101
IDM_EXIT    equ 1000

;--- winbase definitions
HINSTANCE  typedef ptr

;--- winuser definitions
SW_SHOWNORMAL   equ 1
SW_SHOWDEFAULT  equ 10
CS_VREDRAW      equ 0001h
CS_HREDRAW      equ 0002h
CW_USEDEFAULT   equ 80000000h
COLOR_WINDOW    equ 5
IDI_APPLICATION equ 32512
IDC_ARROW       equ 32512
WS_OVERLAPPED   equ 00000000h
WS_CAPTION      equ 00C00000h
WS_SYSMENU      equ 00080000h
WS_THICKFRAME   equ 00040000h
WS_MINIMIZEBOX  equ 00020000h
WS_MAXIMIZEBOX  equ 00010000h
WS_OVERLAPPEDWINDOW equ WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_THICKFRAME or WS_MINIMIZEBOX or WS_MAXIMIZEBOX
DT_CENTER       equ 00000001h
DT_VCENTER      equ 00000004h
DT_SINGLELINE   equ 00000020h

WM_DESTROY      equ 0002h
WM_PAINT        equ 000Fh
WM_COMMAND      equ 0111h

HWND       typedef ptr
HMENU      typedef ptr
HBRUSH     typedef ptr
HICON      typedef ptr
HCURSOR    typedef ptr
HBITMAP    typedef ptr
HDC        typedef ptr
WPARAM     typedef UINT_PTR
LPARAM     typedef LONG_PTR

proto_WNDPROC typedef proto stdcall :HWND,:dword,:WPARAM,:LPARAM
WNDPROC typedef ptr proto_WNDPROC

WNDCLASSEXA struct
cbSize        dword ?
style         dword ?
lpfnWndProc   WNDPROC ?
cbClsExtra    dword ?
cbWndExtra    dword ?
hInstance     HINSTANCE ?
hIcon         HICON ?
hCursor       HCURSOR ?
hbrBackground HBRUSH ?
lpszMenuName  LPSTR ?
lpszClassName LPSTR ?
hIconSm       HICON ?
WNDCLASSEXA ends

POINT struct
x   sdword ?
y   sdword ?
POINT ends

MSG struct 8
hwnd    HWND    ?
message dword   ?
wParam  WPARAM  ?
lParam  LPARAM  ?
time    dword   ?
pt      POINT   <>
MSG ends

RECT struct
left    sdword  ?
top     sdword  ?
right   sdword  ?
bottom  sdword  ?
RECT ends

PAINTSTRUCT struct
hdc         HDC  ?
fErase      BOOL ?
rcPaint     RECT <>
fRestore    BOOL ?
fIncUpdate  BOOL ?
rgbReserved byte 32 dup (?)
PAINTSTRUCT ends

;--- wingdi definitions

DIB_RGB_COLORS  equ 0
SRCCOPY         equ 00CC0020h

HGDIOBJ  typedef ptr

BITMAPINFOHEADER struct
biSize          dword   ?
biWidth         sdword  ?
biHeight        sdword  ?
biPlanes        word    ?
biBitCount      word    ?
biCompression   dword   ?
biSizeImage     dword   ?
biXPelsPerMeter sdword  ?
biYPelsPerMeter sdword  ?
biClrUsed       dword   ?
biClrImportant  dword   ?
BITMAPINFOHEADER ends

WinMain proto :HINSTANCE,:HINSTANCE,:LPSTR,:dword

    option DLLIMPORT:<kernel32.dll>
GetModuleHandleA proto :LPSTR
GetCommandLineA  proto
ExitProcess      proto :dword

    option DLLIMPORT:<user32.dll>
BeginPaint       proto :HWND, :ptr PAINTSTRUCT
CreateWindowExA  proto :dword, :LPSTR, :LPSTR, :dword, :dword, :dword, :dword, :dword, :HWND, :HMENU, :HINSTANCE, :ptr
DefWindowProcA   proto :HWND, :dword, :WPARAM, :LPARAM
DestroyWindow    proto :HWND
DispatchMessageA proto :ptr MSG
EndPaint         proto :HWND, :ptr PAINTSTRUCT
GetClientRect    proto :HWND, :ptr RECT
GetMessageA      proto :ptr MSG, :HWND, :dword, :dword
LoadBitmapA      proto :HINSTANCE, :LPSTR
LoadCursorA      proto :HINSTANCE, :LPSTR
LoadIconA        proto :HINSTANCE, :LPSTR
PostQuitMessage  proto :dword
RegisterClassExA proto :ptr WNDCLASSEXA
ShowWindow       proto :HWND, :dword
TranslateMessage proto :ptr MSG
UpdateWindow     proto :HWND

    option DLLIMPORT:<gdi32.dll>
BitBlt             proto :HDC, :dword, :dword, :dword, :dword, :HDC, :dword, :dword, :dword
CreateCompatibleDC proto :HDC
DeleteDC           proto :HDC
GetDIBits          proto :HDC, :HBITMAP, :dword, :dword, :ptr, :ptr BITMAPINFO, :dword
SelectObject       proto :HDC, :HGDIOBJ
    option DLLIMPORT:NONE

    .data

ClassName db "SimpleWinClass",0
AppName  db "Bitmap rendering",0

    .data?

hInstance HINSTANCE ?
hBitmap   HBITMAP ?
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

    invoke LoadBitmapA, hInst, IDR_BITMAP1
    mov   hBitmap, eax

    mov   wc.cbSize, sizeof WNDCLASSEXA
    mov   wc.style, CS_HREDRAW or CS_VREDRAW
    mov   wc.lpfnWndProc, offset WndProc
    mov   wc.cbClsExtra, NULL
    mov   wc.cbWndExtra, NULL
    push  hInst
    pop   wc.hInstance
    mov   wc.hbrBackground, COLOR_WINDOW+1
    mov   wc.lpszMenuName, IDR_MENU1
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

local hdc2:HDC
local ps:PAINTSTRUCT
local rect:RECT
local bmi:BITMAPINFOHEADER

    mov eax, uMsg
    .if eax == WM_DESTROY
        invoke PostQuitMessage, NULL
        xor eax,eax
    .elseif eax == WM_COMMAND
        .if wParam == IDM_EXIT
            invoke DestroyWindow, hWnd
        .endif
        xor eax, eax
    .elseif eax == WM_PAINT
        invoke BeginPaint, hWnd, addr ps
        invoke CreateCompatibleDC, ps.hdc
        mov hdc2, eax
        invoke SelectObject, hdc2, hBitmap
        mov bmi.biSize, sizeof BITMAPINFOHEADER
        mov bmi.biBitCount, 0
        invoke GetDIBits, hdc2, hBitmap, 0, 0, 0, addr bmi, DIB_RGB_COLORS
        invoke GetClientRect, hWnd, addr rect
        mov ecx, rect.right
        sub ecx, bmi.biWidth
        jnc @F
        xor ecx, ecx
@@:
        shr ecx, 1
        mov edx, rect.bottom
        sub edx, bmi.biHeight
        jnc @F
        xor edx, edx
@@:
        shr edx, 1
        invoke BitBlt, ps.hdc, ecx, edx, bmi.biWidth, bmi.biHeight, hdc2, 0, 0, SRCCOPY
        invoke DeleteDC, hdc2
        invoke EndPaint, hWnd, addr ps

        xor eax,eax
    .else
        invoke DefWindowProcA, hWnd, uMsg, wParam, lParam
    .endif
    ret
WndProc endp

if 1 ;1 for PE - define resources

RT_BITMAP equ 2
RT_MENU   equ 4

;--- menu resource flags
MF_POPUP   equ 10h
MF_END     equ 80h

IMAGE_RESOURCE_DIRECTORY struct
Characteristics      dword ?
TimeDateStamp        dword ?
MajorVersion         word  ?
MinorVersion         word  ?
NumberOfNamedEntries word  ?
NumberOfIdEntries    word  ?
IMAGE_RESOURCE_DIRECTORY ends

IMAGE_RESOURCE_DIRECTORY_ENTRY struct
union
r0      record NameIsString:1, NameOffset:31
Name_   dword   ?
Id      word    ?
ends
union
OffsetToData dword   ?
r1           record	DataIsDirectory:1, OffsetToDirectory:31
ends
IMAGE_RESOURCE_DIRECTORY_ENTRY ends

IMAGE_RESOURCE_DATA_ENTRY struct
OffsetToData dword ?
Size_        dword ?
CodePage     dword ?
Reserved     dword ?
IMAGE_RESOURCE_DATA_ENTRY ends

    option dotname

.rsrc segment dword read FLAT public 'RSRC'

;--- define menu IDR_MENU1 and bitmap IDR_BITMAP1

;--- root level: enum the resource types
      IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,2>
      IMAGE_RESOURCE_DIRECTORY_ENTRY < <RT_BITMAP>, <SECTIONREL bms   + 80000000h> >
      IMAGE_RESOURCE_DIRECTORY_ENTRY < <RT_MENU>,   <SECTIONREL menus + 80000000h> >

;--- second level: enum the IDs of resource type X
bms   IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,1>
      IMAGE_RESOURCE_DIRECTORY_ENTRY < <IDR_BITMAP1>, <SECTIONREL bm1   + 80000000h> >
menus IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,1>
      IMAGE_RESOURCE_DIRECTORY_ENTRY < <IDR_MENU1>,   <SECTIONREL menu1 + 80000000h> >

;--- third level: enum the languages of ID X
bm1   IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,1>
      IMAGE_RESOURCE_DIRECTORY_ENTRY < <409h>, <SECTIONREL bm1_l1> >
menu1 IMAGE_RESOURCE_DIRECTORY <0,0,0,0,0,1>
      IMAGE_RESOURCE_DIRECTORY_ENTRY < <409h>, <SECTIONREL m1_l1> >

;--- last level: define the resource data
;--- data for menu IDR_MENU1, language 409h
m1_l1 IMAGE_RESOURCE_DATA_ENTRY <IMAGEREL m1_l1_data, size_m1_l1, 0, 0>
m1_l1_data dw 0,0	;menu header
    dw MF_POPUP or MF_END, '&','F','i','l','e',0
    dw MF_END, IDM_EXIT,   'E','&','x','i','t',0
size_m1_l1 equ $ - m1_l1_data
    align 4

;--- data for bitmap IDR_BITMAP1
bm1_l1 IMAGE_RESOURCE_DATA_ENTRY <IMAGEREL bm1_l1_data, size_bm1_l1, 0, 0>
bm1_l1_data label word
    incbin <Win32_8.bmp>,14	;skip bitmap file header
size_bm1_l1 equ $ - ( bm1_l1_data )

.rsrc ends

;--- set /subsystem:windows
;--- the PE header is stored in section .hdr$2
    option dotname
.hdr$2 segment dword FLAT public 'HDR'
    org 5Ch ;position to IMAGE_NT_HEADER32.OptionalHeader.Subsystem
    dw 2    ;2=subsystem windows
.hdr$2 ends

endif

end start
