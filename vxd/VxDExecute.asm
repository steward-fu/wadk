.386p
include \masm\include\vmm.inc
include \masm\include\vwin32.inc
include \masm\include\shell.inc

VxDName TEXTEQU <VXDEXEC>
ControlName TEXTEQU <VXDEXEC_Control>
VxDMajorVersion TEXTEQU <1>
VxDMinorVersion TEXTEQU <0>

VxD_STATIC_DATA_SEG
VxD_STATIC_DATA_ENDS

VXD_LOCKED_CODE_SEG
;----------------------------------------------------------------------------
; Remember: The name of the vxd MUST be uppercase else it won't work/unload
;----------------------------------------------------------------------------
DECLARE_VIRTUAL_DEVICE %VxDName,%VxDMajorVersion,%VxDMinorVersion, %ControlName,UNDEFINED_DEVICE_ID,UNDEFINED_INIT_ORDER

Begin_control_dispatch %VxDName
        Control_Dispatch W32_DEVICEIOCONTROL, OnDeviceIoControl
End_control_dispatch %VxDName


BeginProc OnDeviceIoControl
	assume esi:ptr DIOCParams
	.if [esi].dwIoControlCode==1
		VxDCall _SHELL_CallAtAppyTime,<<OFFSET32 OnAppyTime>,0,0,0>
	.endif
	xor eax,eax
	ret
EndProc OnDeviceIoControl
VXD_LOCKED_CODE_ENDS

VXD_PAGEABLE_CODE_SEG
BeginProc OnAppyTime, CCALL
	ArgVar RefData,DWORD
	ArgVar TheFlag,DWORD
	EnterProc
	mov File.shex_dwTotalSize,sizeof SHEXPACKET
	add File.shex_dwTotalSize,sizeof EXEName
	mov File.shex_dwSize,sizeof SHEXPACKET
	mov File.shex_ibOp,0
	mov File.shex_ibFile,sizeof SHEXPACKET
	mov File.shex_ibParams,0
	mov File.shex_ibDir,0
	mov File.shex_dwReserved,0
	mov File.shex_nCmdShow,1
	VxDCall _SHELL_ShellExecute, <OFFSET32 File>
	LeaveProc
	Return
EndProc OnAppyTime
VXD_PAGEABLE_CODE_ENDS

VXD_PAGEABLE_DATA_SEG
	File SHEXPACKET <>
	EXEName db "calc.exe",0
VXD_PAGEABLE_DATA_ENDS

end
