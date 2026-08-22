.386p
include \masm\include\vmm.inc
include \masm\include\vwin32.inc
include \masm\include\v86mmgr.inc

VxDName TEXTEQU <VXDLABEL>
ControlName TEXTEQU <VXDLABEL_Control>
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
		VMMCall Get_Sys_VM_Handle
		mov Handle,ebx
		assume ebx:ptr cb_s
		mov ebp,[ebx+CB_Client_Pointer]
		mov ecx,sizeof MID
		stc
		push esi
		mov esi,OFFSET32 MediaID
		push ds
		pop fs
		VxDCall V86MMGR_Allocate_Buffer
		pop esi
		jc EndI
		mov AllocSize,ecx
		Push_Client_State
		VMMCall Begin_Nest_V86_Exec
		assume ebp:ptr Client_Byte_Reg_Struc
		mov [ebp].Client_ch,8
		mov [ebp].Client_cl,66h
		assume ebp:ptr Client_word_reg_struc
		mov edx,edi
		mov [ebp].Client_bx,3	; drive C
		mov [ebp].Client_ax,440dh
		mov [ebp].Client_dx,dx
		shr edx,16
		mov [ebp].Client_ds,dx
		mov eax,21h
		VMMCall Exec_Int
		VMMCall End_Nest_Exec
		Pop_Client_State
		;-------------------------------
		; retrieve the data
		;-------------------------------
		mov ecx,AllocSize
		stc
		mov ebx,Handle
		push esi
		mov esi,OFFSET32 MediaID
		push ds
		pop fs
		VxDCall V86MMGR_Free_Buffer
		pop esi
		mov edx,esi
		assume edx:ptr DIOCParams
		mov edi,[edx].lpvOutBuffer
		mov esi,OFFSET32 MediaID.midVolLabel
		mov ecx,11
		rep movsb
		mov byte ptr [edi],0
		mov ecx,[edx].lpcbBytesReturned
		mov dword ptr [edx],11
EndI:
	.endif
	xor eax,eax
	ret
EndProc OnDeviceIoControl
VXD_PAGEABLE_CODE_ENDS

VXD_PAGEABLE_DATA_SEG
	MID struct
		midInfoLevel dw 0
		midSerialNum dd ?
		midVolLabel db 11 dup(?)
		midFileSysType db 8 dup(?)
	MID ends
	MediaID MID <>
	Handle dd ?
	AllocSize dd ?
VXD_PAGEABLE_DATA_ENDS

end
