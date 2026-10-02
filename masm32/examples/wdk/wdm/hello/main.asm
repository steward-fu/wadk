.386p
.model flat, stdcall
option casemap:none
     
include c:\masm32\include\w2k\ntddk.inc
include c:\masm32\include\w2k\ntstatus.inc
include c:\masm32\include\w2k\ntoskrnl.inc
include c:\masm32\include\w2k\ntddkbd.inc
include c:\masm32\Macros\Strings.mac
    
public DriverEntry
 
.data
pNextDevice PDEVICE_OBJECT 0
      
.code
AddDevice proc pMyDriver : PDRIVER_OBJECT, pPhyDevice : PDEVICE_OBJECT
    local pMyDevice : PDEVICE_OBJECT
    local szDevName : UNICODE_STRING
 
    invoke DbgPrint, $CTA0("Hello, world\:")
    invoke RtlInitUnicodeString, addr szDevName, $CTW0("\\Device\\MyDriver")
    invoke IoCreateDevice, pMyDriver, 0, addr szDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, addr pMyDevice
    invoke IoAttachDeviceToDeviceStack, pMyDevice, pPhyDevice
    mov pNextDevice, eax
 
    mov eax, pMyDevice
    or (DEVICE_OBJECT ptr [eax]).Flags, DO_BUFFERED_IO
    and (DEVICE_OBJECT ptr [eax]).Flags, not DO_DEVICE_INITIALIZING
    mov eax, STATUS_SUCCESS
    ret
AddDevice endp
     
Unload proc pMyDriver : PDRIVER_OBJECT
    ret
Unload endp
     
IrpPnp proc pMyDevice : PDEVICE_OBJECT, pIrp : PIRP
    IoGetCurrentIrpStackLocation pIrp
    movzx eax, (IO_STACK_LOCATION ptr [eax]).MinorFunction
    
    .if eax == IRP_MN_REMOVE_DEVICE
        invoke IoDetachDevice, pNextDevice
        invoke IoDeleteDevice, pMyDevice
        fastcall IofCompleteRequest, pIrp, IO_NO_INCREMENT
        ret
    .endif
    
    IoSkipCurrentIrpStackLocation pIrp
    invoke IoCallDriver, pNextDevice, pIrp
    ret
IrpPnp endp
     
DriverEntry proc pMyDriver : PDRIVER_OBJECT, pMyRegistry : PUNICODE_STRING
    mov eax, pMyDriver
    mov (DRIVER_OBJECT ptr [eax]).MajorFunction[IRP_MJ_PNP * (sizeof PVOID)], offset IrpPnp
    mov (DRIVER_OBJECT ptr [eax]).DriverUnload, offset Unload
    mov eax, (DRIVER_OBJECT ptr [eax]).DriverExtension
    mov (DRIVER_EXTENSION ptr [eax]).AddDevice, AddDevice
    mov eax, STATUS_SUCCESS
    ret
DriverEntry endp
end
