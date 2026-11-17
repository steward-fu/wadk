
;--- GDI+ sample
;--- based on a small sample from qWord found at the MASM32 forum

	.386
	.model flat, stdcall
	option casemap:none

	.nolist
	.nocref
	include \wininc\include\windows.inc
	include \wininc\include\gdiplus.inc
	.list
	.cref

	includelib kernel32.lib
	includelib user32.lib
	includelib gdi32.lib
	includelib gdiplus.lib

CStr macro x:vararg
local xxx
	.const
xxx db x,0
	.code
	exitm <offset xxx>
endm

ifdef __JWASM__
FP4 macro x
	exitm <x>	;jwasm is able to push float constants directly
endm
else
FP4 macro x
local xxx
	.const
xxx real4 x
	.code
	exitm <xxx>
endm
endif

WND_DATA struct
hdc     HDC ?
ptPos   POINT <>
WND_DATA ends

	.code

WndProc proto :HWND, :UINT, :WPARAM, :LPARAM

main proc 

LOCAL wcex:WNDCLASSEX
LOCAL msg:MSG
LOCAL gsi:GdiplusStartupInput
LOCAL gtkn:PULONG

	mov gsi.GdiplusVersion, 1
	mov gsi.DebugEventCallback, NULL
	mov gsi.SuppressBackgroundThread, 0
	mov gsi.SuppressExternalCodecs, 0
	invoke GdiplusStartup, ADDR gtkn, ADDR gsi, 0

	; create window class and window
	invoke GetModuleHandle, NULL
	mov wcex.hInstance, eax
	mov wcex.cbSize, SIZEOF WNDCLASSEX
	mov wcex.style, CS_HREDRAW or CS_VREDRAW
	mov wcex.lpfnWndProc, OFFSET WndProc
	mov wcex.cbClsExtra, NULL
	mov wcex.cbWndExtra, SIZEOF WND_DATA
	mov wcex.hbrBackground, NULL
	mov wcex.lpszMenuName, NULL
	mov wcex.lpszClassName, CStr("Win32GDI+")
	invoke LoadIcon,NULL, IDI_APPLICATION
	mov wcex.hIcon, eax
	mov wcex.hIconSm,eax
	invoke LoadCursor, NULL, IDC_ARROW
	mov wcex.hCursor, eax
	invoke RegisterClassEx, ADDR wcex
	invoke CreateWindowEx, 0, wcex.lpszClassName, CStr("win32,GDI+"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, wcex.hInstance, NULL
	mov esi,eax

	invoke ShowWindow, esi, SW_SHOWNORMAL

	.while 1
		invoke GetMessage, ADDR msg, NULL, 0, 0
		.break .if !eax || eax == -1
		invoke DispatchMessage, ADDR msg
	.endw

	invoke GdiplusShutdown, gtkn
	mov eax, msg.wParam
	ret
	align 4

main endp

;--- fill bitmap with 2 rectangles

SetBitmap proc hWnd:HWND

LOCAL graphics:PVOID	; object pointers
LOCAL pen:PVOID			;
LOCAL brush:PVOID		;
LOCAL x:REAL4
LOCAL y:REAL4

	; get our DC
	invoke GetWindowLong, hWnd, WND_DATA.hdc
	mov ebx, eax

	; create Graphics object from HDC
	invoke GdipCreateFromHDC, ebx, ADDR graphics

	; set world unit to millimeter (screen) - the default is pixels
	invoke GdipSetPageUnit, graphics, UnitMillimeter

	; set drawings quality
	invoke GdipSetSmoothingMode, graphics, SmoothingModeHighQuality

	; clear DC/Graphics
	invoke GdipGraphicsClear, graphics, ColorsCornflowerBlue

	; create pen. Take care for parameters type! -> msdn
	; UnitWorld -> the parameter <width> uses Graphics current Unit = millimeter.
	invoke GdipCreatePen1, ColorsBlack, FP4(1.0), UnitWorld, ADDR pen

	; create brush
	invoke GdipCreateSolidFill, ColorsAquamarine, ADDR brush

	; calculate x-pos 
	invoke GetWindowLong, hWnd, WND_DATA.ptPos.x
	push eax
	fild SDWORD ptr [esp]
	fstp x
	add esp, 4

	; calculate y-pos 
	invoke GetWindowLong, hWnd, WND_DATA.ptPos.y
	push eax
	fild SDWORD ptr [esp]
	fstp y
	add esp, 4

	; do some drawing - for many function there are two forms: one for floating point values
	; and one for one for integer parameters. e.g.: GdipFillRectangle <-> GdipFillRectangleI
	invoke GdipFillRectangle, graphics, brush, x, y, FP4(20.0), FP4(20.0)
	invoke GdipDrawRectangle, graphics, pen, x, y, FP4(20.0), FP4(20.0)

	; draw a rectangle using alpha-value
	invoke GdipSetSolidFillColor, brush, (ColorsBeige XOR 0ff000000h) OR (128 SHL 24)
	invoke GdipFillRectangleI, graphics, brush, 20, 15, 30, 30
	invoke GdipSetPenColor, pen, (ColorsBlack XOR 0ff000000h) OR (128 SHL 24)
	invoke GdipDrawRectangleI, graphics, pen, 20, 15, 30, 30

	; delete the Graphics-object. The DC is still valid
	invoke GdipDeleteGraphics, graphics

	; delete brush and pen
	invoke GdipDeletePen, pen
	invoke GdipDeleteBrush, brush
	ret
	align 4

SetBitmap endp

;--- change position of smaller rectangle

SetPos proc uses ebx esi edi hWnd:HWND, xdiff:DWORD, ydiff:DWORD

	.if xdiff
		invoke GetWindowLong, hWnd, WND_DATA.ptPos.x
		add eax, xdiff
		.if ( sdword ptr eax < 0 )
			ret
		.endif
		invoke SetWindowLong, hWnd, WND_DATA.ptPos.x, eax
	.else
		invoke GetWindowLong, hWnd, WND_DATA.ptPos.y
		add eax, ydiff
		.if ( sdword ptr eax < 0 )
			ret
		.endif
		invoke SetWindowLong, hWnd, WND_DATA.ptPos.y, eax
	.endif
	; update bitmap
	invoke SetBitmap, hWnd
	; force redraw
	invoke InvalidateRect, hWnd, 0, 0
	; synchronize
	invoke UpdateWindow, hWnd
	ret
	align 4

SetPos endp

WndProc proc uses ebx esi edi hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

LOCAL ps:PAINTSTRUCT

	.if uMsg == WM_CREATE

		; create a compatible bitmap - used for drawing
		invoke GetDC, hWnd
		mov esi, eax
		invoke CreateCompatibleDC, esi
		mov ebx, eax
		invoke GetSystemMetrics, SM_CXSCREEN
		mov edi, eax
		invoke GetSystemMetrics, SM_CYSCREEN
		invoke CreateCompatibleBitmap, esi, edi, eax
		; select compatible bitmap into compatible DC
		invoke SelectObject, ebx, eax
		; and delete the old bitmap ( a 1x1 dummy bitmap ) 
		invoke DeleteObject, eax
		invoke ReleaseDC, hWnd, esi

		invoke SetWindowLong, hWnd, WND_DATA.hdc, ebx
		invoke SetWindowLong, hWnd, WND_DATA.ptPos.x, 10
		invoke SetWindowLong, hWnd, WND_DATA.ptPos.y, 5

		invoke SetBitmap, hWnd

	.elseif uMsg == WM_DESTROY

		invoke GetWindowLong, hWnd, WND_DATA.hdc
		invoke DeleteObject, eax
		invoke PostQuitMessage, NULL

	.elseif uMsg == WM_KEYDOWN

		.if ( wParam == VK_UP )
			invoke SetPos, hWnd, 0, -1
		.elseif ( wParam == VK_DOWN )
			invoke SetPos, hWnd, 0, 1
		.elseif ( wParam == VK_LEFT )
			invoke SetPos, hWnd, -1, 0
		.elseif ( wParam == VK_RIGHT )
			invoke SetPos, hWnd, 1, 0
		.endif

	.elseif uMsg == WM_PAINT

		invoke BeginPaint, hWnd, ADDR ps
		invoke GetWindowLong, hWnd, WND_DATA.hdc
		mov ebx, eax
		mov edx, ps.rcPaint.right
		sub edx, ps.rcPaint.left
		mov ecx, ps.rcPaint.bottom
		sub ecx, ps.rcPaint.top
		invoke BitBlt, ps.hdc, ps.rcPaint.left, ps.rcPaint.top, edx, ecx, ebx, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY
		invoke EndPaint, hWnd, ADDR ps

	.else

		invoke DefWindowProc, hWnd, uMsg, wParam, lParam
		ret

	.endif

	xor eax,eax
	ret
WndProc endp

start:
	invoke main
	invoke ExitProcess, eax

end start
