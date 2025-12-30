.386p 
include vmm.inc 
include shell.inc

DECLARE_VIRTUAL_DEVICE MESSAGE,1,0, MESSAGE_Control, UNDEFINED_DEVICE_ID, UNDEFINED_INIT_ORDER

Begin_control_dispatch MESSAGE
	Control_Dispatch Create_VM, OnVMCreate
	Control_Dispatch VM_Terminate2, OnVMClose
End_control_dispatch MESSAGE

VxD_PAGEABLE_DATA_SEG
MsgTitle db "VxD MessageBox",0
VMCreated db "A VM is created",0
VMDestroyed db "A VM is destroyed",0
VxD_PAGEABLE_DATA_ENDS

VxD_PAGEABLE_CODE_SEG

BeginProc OnVMCreate
	mov ecx, OFFSET32 VMCreated
CommonCode:
	VMMCall Get_sys_vm_handle
	mov eax,MB_OK+MB_ICONEXCLAMATION
	mov edi, OFFSET32 MsgTitle
	xor esi,esi
	xor edx,edx
	VxDCall SHELL_Message
	ret
EndProc OnVMCreate

BeginProc OnVMClose
	mov ecx,OFFSET32 VMDestroyed
	jmp CommonCode
EndProc OnVMClose

VxD_PAGEABLE_CODE_ENDS

end
