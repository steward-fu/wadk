.386p 
include vmm.inc 
include vwin32.inc
include shell.inc

DECLARE_VIRTUAL_DEVICE SHELLMSG,1,0, SHELLMSG_Control,\
     UNDEFINED_DEVICE_ID, UNDEFINED_INIT_ORDER 

Begin_control_dispatch SHELLMSG
	Control_Dispatch w32_DeviceIoControl, OnDeviceIoControl
End_control_dispatch SHELLMSG

VxD_PAGEABLE_DATA_SEG
pTitle dd ?
pMessage dd ?
VxD_PAGEABLE_DATA_ENDS

VxD_PAGEABLE_CODE_SEG
BeginProc OnDeviceIoControl 
	assume esi:ptr DIOCParams
	.if [esi].dwIoControlCode==DIOC_Open
		xor eax,eax
	.elseif [esi].dwIoControlCode==1
		mov edi,[esi].lpvInBuffer
		;-----------------------------------
		; copy the message title to buffer
		;-----------------------------------
		VMMCall _lstrlen, <[edi]>
		inc eax
		push eax
		VMMCall _HeapAllocate,<eax,HEAPZEROINIT>
		mov pTitle,eax
		pop eax
		VMMCall _lstrcpyn,<pTitle,[edi],eax>
		;-----------------------------------
		; copy the message text to buffer
		;-----------------------------------
		VMMCall _lstrlen, <[edi+4]>
		inc eax
		push eax
		VMMCall _HeapAllocate,<eax,HEAPZEROINIT>
		mov pMessage,eax
		pop eax
		VMMCall _lstrcpyn,<pMessage,[edi+4],eax>		
		mov edi,pTitle
		mov ecx,pMessage
		mov eax,MB_OK
		VMMCall Get_Sys_VM_Handle
		VxDCall SHELL_sysmodal_Message
		VMMCall _HeapFree,pTitle,0
		VMMCall _HeapFree,pMessage,0
		xor eax,eax
	.endif
	ret
EndProc OnDeviceIoControl
VxD_PAGEABLE_CODE_ENDS

end