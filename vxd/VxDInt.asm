.386p
include \masm\include\vmm.inc
include \masm\include\vwin32.inc
include \masm\include\v86mmgr.inc

VxDName TEXTEQU <VXDINT>
ControlName TEXTEQU <VXDINT_Control>
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

VXD_LOCKED_CODE_ENDS

VXD_PAGEABLE_CODE_SEG
BeginProc OnDeviceIoControl
	assume esi:ptr DIOCParams
	.if [esi].dwIoControlCode==1
		Push_Client_State
		VMMCall Begin_Nest_V86_Exec
		assume ebp:ptr Client_Byte_Reg_Struc
		mov [ebp].Client_dl,7
		mov [ebp].Client_ah,2
		mov eax,21h
		VMMCall Exec_Int
		VMMCall End_Nest_Exec
		Pop_Client_State
EndI:
	.endif
	xor eax,eax
	ret
EndProc OnDeviceIoControl
VXD_PAGEABLE_CODE_ENDS

end
