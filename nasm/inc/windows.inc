[bits 32]
global _start
  
extern _Arc@36
extern _Pie@36
extern _sprintf
extern _Chord@36
extern _LineTo@12
extern _Polygon@12
extern _Ellipse@20
extern _EndPaint@8
extern _MoveToEx@16
extern _FillRect@12
extern _SetPixel@16
extern _TextOutA@20
extern _SetTimer@16
extern _KillTimer@8
extern _SetBkMode@8
extern _DrawTextA@20
extern _Rectangle@20
extern _CreatePen@12
extern _BeginPaint@8
extern _CreateFontA@56
extern _ExitProcess@4
extern _GetMessageA@16
extern _MessageBoxA@16
extern _SetTextColor@8
extern _DeleteObject@4
extern _SelectObject@8
extern _SetScrollPos@16
extern _DestroyWindow@4
extern _RegisterClassA@4
extern _DefWindowProcA@16
extern _SetScrollRange@20
extern _SetWindowTextA@8
extern _SetWindowLongA@12
extern _CallWindowProcA@20
extern _GetCommandLineA@0
extern _CreateWindowExA@48
extern _PostQuitMessage@4
extern _CreateSolidBrush@4
extern _GetModuleHandleA@4
extern _DispatchMessageA@4
  
%define ARG1 8h
%define ARG2 0ch
%define ARG3 10h
%define ARG4 14h
 
%define Arc                 _Arc@36
%define Pie                 _Pie@36
%define sprintf             _sprintf
%define Chord               _Chord@36
%define LineTo              _LineTo@12
%define TextOut             _TextOutA@20
%define Polygon             _Polygon@12
%define Ellipse             _Ellipse@20
%define EndPaint            _EndPaint@8
%define MoveToEx            _MoveToEx@16
%define FillRect            _FillRect@12
%define SetPixel            _SetPixel@16
%define SetTimer            _SetTimer@16
%define KillTimer           _KillTimer@8
%define DrawText            _DrawTextA@20
%define SetBkMode           _SetBkMode@8
%define Rectangle           _Rectangle@20
%define CreatePen           _CreatePen@12
%define BeginPaint          _BeginPaint@8
%define GetMessage          _GetMessageA@16
%define MessageBox          _MessageBoxA@16
%define CreateFont          _CreateFontA@56
%define ExitProcess         _ExitProcess@4
%define SetTextColor        _SetTextColor@8
%define DeleteObject        _DeleteObject@4
%define SelectObject        _SelectObject@8
%define SetScrollPos        _SetScrollPos@16
%define DestroyWindow       _DestroyWindow@4
%define RegisterClass       _RegisterClassA@4
%define DefWindowProc       _DefWindowProcA@16
%define SetScrollRange      _SetScrollRange@20
%define SetWindowText       _SetWindowTextA@8
%define SetWindowLong       _SetWindowLongA@12
%define CallWindowProc      _CallWindowProcA@20
%define GetCommandLine      _GetCommandLineA@0
%define CreateWindowEx      _CreateWindowExA@48
%define PostQuitMessage     _PostQuitMessage@4
%define CreateSolidBrush    _CreateSolidBrush@4
%define GetModuleHandle     _GetModuleHandleA@4
%define DispatchMessage     _DispatchMessageA@4

MB_OK                   equ 0
NULL                    equ 0      
DT_VCENTER              equ 4h
DT_CENTER               equ 1h
DT_SINGLELINE           equ 20h
TRANSPARENT             equ 1
FF_DONTCARE             equ 0
FW_BOLD                 equ 700
OUT_OUTLINE_PRECIS      equ 8
CLIP_DEFAULT_PRECIS     equ 0
CLEARTYPE_QUALITY       equ 5
DEFAULT_PITCH           equ 0
PS_SOLID                equ 0
GWL_WNDPROC             equ -4
SB_LINEUP               equ 0
SB_LINELEFT             equ 0
SB_LINEDOWN             equ 1
SB_LINERIGHT            equ 1
SB_PAGEUP               equ 2
SB_PAGELEFT             equ 2
SB_PAGEDOWN             equ 3
SB_PAGERIGHT            equ 3
SB_VERT                 equ 1
SW_SHOWNORMAL           equ 1h
WC_DIALOG               equ 8002h
WM_PAINT                equ 0fh
WM_VSCROLL              equ 115h
WM_TIMER                equ 113h
WM_MOUSEMOVE            equ 200h
WM_SYSKEYDOWN           equ 104h
WM_KEYDOWN              equ 100h
WM_DESTROY              equ 2h
WM_CLOSE                equ 10h
WS_VSCROLL              equ 200000h
WS_OVERLAPPED           equ 0h
WS_CAPTION              equ 0c00000h
WS_SYSMENU              equ 80000h
WS_THICKFRAME           equ 40000h
WS_MINIMIZEBOX          equ 20000h
WS_MAXIMIZEBOX          equ 10000h
WS_VISIBLE              equ 10000000h
WS_EX_LEFT              equ 00000000h
WS_OVERLAPPEDWINDOW     equ WS_OVERLAPPED   | \
                            WS_CAPTION      | \
                            WS_SYSMENU      | \
                            WS_THICKFRAME   | \
                            WS_MINIMIZEBOX  | \
                            WS_MAXIMIZEBOX
false                   equ 0
                    
struc RECT
    .left:   resd 1
    .top:    resd 1
    .right:  resd 1
    .bottom: resd 1
    .SIZE:
endstruc
          
struc PAINTSTRUCT
    .hdc:         resd 1
    .fErase:      resd 1
    .rcPaint:     resb RECT.SIZE
    .fRestore:    resd 1
    .fIncUpdate:  resd 1
    .rgbReserved: resb 32
    .SIZE:
endstruc
          
struc POINT
    .x: resd 1
    .y: resd 1
    .SIZE:
endstruc
                
struc MSG
    .hwnd:    resd 1
    .message: resd 1
    .wParam:  resd 1
    .lParam:  resd 1
    .time:    resd 1
    .pt:      resb POINT.SIZE
    .SIZE:
endstruc
 
struc WNDCLASS
    .style:         resd 1
    .lpfnWndProc:   resd 1
    .cbClsExtra:    resd 1
    .cbWndExtra:    resd 1
    .hInstance:     resd 1
    .hIcon:         resd 1
    .hCursor:       resd 1
    .hbrBackground: resd 1
    .lpszMenuName:  resd 1
    .lpszClassName: resd 1
    .SIZE:
endstruc 
