.386
.model flat,stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

DlgProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
.data
Failure db "Cannot load VxDInt.VXD",0
AppName db "MS-DOS Beep",0
VxDName db "\\.\vxdint.vxd",0

.data?
hInstance HINSTANCE ?
hVxD dd ?

.const
IDD_VXDRUN    equ 101
IDC_LOAD      equ 1000

.code
start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	invoke DialogBoxParam, hInstance, IDD_VXDRUN ,NULL,addr DlgProc,NULL
	invoke ExitProcess,eax

DlgProc proc hDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	.IF uMsg==WM_INITDIALOG
		invoke CreateFile,addr VxDName,0,0,0,0,FILE_FLAG_DELETE_ON_CLOSE,0
		.if eax==INVALID_HANDLE_VALUE
			invoke MessageBox,hDlg,addr Failure,addr AppName,MB_OK+MB_ICONERROR
			mov hVxD,0
			invoke EndDialog,hDlg,NULL
		.else
			mov hVxD,eax
		.endif
	.elseif uMsg==WM_CLOSE
		.if hVxD!=0
			invoke CloseHandle,hVxD
		.endif
		invoke EndDialog,hDlg,0
	.ELSEIF uMsg==WM_COMMAND
		mov eax,wParam
		mov edx,wParam
		shr edx,16
		.if dx==BN_CLICKED
			.IF ax==IDC_LOAD
					invoke DeviceIoControl,hVxD,1,NULL,0,NULL,NULL,NULL,NULL
			.endif
		.endif
	.ELSE
		mov eax,FALSE
		ret
	.ENDIF
	mov eax,TRUE
	ret
DlgProc endp
end start
