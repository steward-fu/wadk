SetRichHilite PROTO REHandle:HWND,phFont:PVOID
RegisterXstatic PROTO hInst:HINSTANCE
UnregisterXstatic PROTO
curr_id=WM_USER+10
enum WM_GETBGCOLOUR,WM_GETTEXTCOLOUR,WM_SETBGCOLOUR,WM_SETTEXTCOLOUR,WM_GETLOGFONT,WM_SETLOGFONT
xclr macro bgClr,ttClr
	EXITM<((bgClr shl 32) or ttClr)>
endm
xstat struc
	hFont	HFONT ?
	hBrush	HBRUSH ?
	TextClr	COLORREF ?
	BgClr	COLORREF ?
	lf		LOGFONT<>
xstat ends
curr_id=WM_USER+10
enum WM_SETBASE