.386
.model flat,stdcall
include windows.inc
include kernel32.inc
includelib kernel32.lib
include user32.inc
includelib user32.lib
.data
AppName db "DeviceIoControl",0
VxDName db "\\.\shellmsg.vxd",0
Success db "The VxD is successfully loaded!",0
Failure db "The VxD is not loaded!",0
Unload db "The VxD is now unloaded!",0
MsgTitle db "DeviceIoControl Example",0
MsgText db "I'm called from a VxD!",0
InBuffer dd offset MsgTitle
         dd offset MsgText
.data?
hVxD dd ?
.code
start:
	invoke CreateFile,addr VxDName,0,0,0,0,FILE_FLAG_DELETE_ON_CLOSE,0
	.if eax!=INVALID_HANDLE_VALUE
		mov hVxD,eax
		invoke MessageBox,NULL,addr Success,addr AppName,MB_OK+MB_ICONINFORMATION
		invoke DeviceIoControl,hVxD,1,addr InBuffer,8,NULL,NULL,NULL,NULL
		invoke CloseHandle,hVxD
		invoke MessageBox,NULL,addr Unload,addr AppName,MB_OK+MB_ICONINFORMATION
	.else
		invoke MessageBox,NULL,addr Failure,NULL,MB_OK+MB_ICONERROR
	.endif
	invoke ExitProcess,NULL
end start
