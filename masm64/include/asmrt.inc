RegClass PROTO ClassName:LPSTR,MenuName:LPSTR,WndProc:WNDPROC,hbrBackground:HBRUSH
RegClassEx PROTO ClassName:LPSTR,MenuName:LPSTR,WndProc:WNDPROC,hbrBackground:HBRUSH,hIcon:HICON
StdWndProc PROTO hWnd:HWND,uMsg:QWORD,wParam:WPARAM,lParam:LPARAM
InitRegData PROTO
SetStdClass PROTO wcex:PWNDCLASSEX
FreeRegData PROTO
OpenFileDialog PROTO hWndOwner:HWND,FileName:LPSTR,Filter:LPSTR,TemplateName:LPSTR,lpfnHook:PVOID
SaveFileDialog PROTO hWndOwner:HWND,FileName:LPSTR,Filter:LPSTR,TemplateName:LPSTR,lpfnHook:PVOID
IFDEF asmrt
	externdef RegSection:CRITICAL_SECTION
	externdef DlgSection:CRITICAL_SECTION
	externdef StdClass:WNDCLASSEX
	externdef OFileName:OPENFILENAME
	externdef DefaultFilePath:BYTE
ELSE
	extern __imp_RegSection:LPCRITICAL_SECTION
	RegSection equ <__imp_RegSection>
	extern __imp_DlgSection:LPCRITICAL_SECTION
	DlgSection equ <__imp_DlgSection>
	extern __imp_StdClass:PWNDCLASSEX
	StdClass equ <__imp_StdClass>
	extern __imp_OFileName:LPOPENFILENAME
	OFileName equ <__imp_OFileName>
	extern __imp_DefaultFilePath:LPOPENFILENAME
	DefaultFilePath equ <__imp_DefaultFilePath>
ENDIF
;STD_CLIENT_STYLE	equ (CS_DROPSHADOW or CS_GLOBALCLASS or CS_HREDRAW or CS_VREDRAW or CS_PARENTDC)
STD_CLIENT_STYLE	equ (CS_HREDRAW or CS_VREDRAW or CS_GLOBALCLASS)