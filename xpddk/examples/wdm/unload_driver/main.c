//
// Add device
// https://steward-fu.github.io/website/index.htm
//

#include <wdm.h>
  
static PDEVICE_OBJECT pNextDevice = NULL;
  
static NTSTATUS AddDevice(PDRIVER_OBJECT pMyDriver, PDEVICE_OBJECT pPhyDevice)
{
    PDEVICE_OBJECT pMyDevice = NULL;
    UNICODE_STRING usDeviceName = { 0 };
    UNICODE_STRING usSymbolName = { 0 };
 
    RtlInitUnicodeString(&usDeviceName, L"\\Device\\MyDriver");
    IoCreateDevice(pMyDriver, 0, &usDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pMyDevice);
    DbgPrint("%s, pMyDevice = %p\n", __FUNCTION__, pMyDevice);

    RtlInitUnicodeString(&usSymbolName, L"\\DosDevices\\MyDriver");
    IoCreateSymbolicLink(&usSymbolName, &usDeviceName);

    pNextDevice = IoAttachDeviceToDeviceStack(pMyDevice, pPhyDevice);
    DbgPrint("%s, pNextDevice = %p\n", __FUNCTION__, pNextDevice);

    pMyDevice->Flags &= ~DO_DEVICE_INITIALIZING;
    pMyDevice->Flags |= DO_BUFFERED_IO;
    return STATUS_SUCCESS;
}
  
static NTSTATUS IrpDispatch(PDEVICE_OBJECT pMyDevice, PIRP pIrp)
{
    UNICODE_STRING usSymbolName = { 0 };
    PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
 
    DbgPrint("%s, Major = 0x%x\n", __FUNCTION__, pStack->MajorFunction);
    if (pStack->MinorFunction == IRP_MN_REMOVE_DEVICE) {
        DbgPrint("%s, Delete symbolic link\n", __FUNCTION__);
        RtlInitUnicodeString(&usSymbolName, L"\\DosDevices\\MyDriver");
        IoDeleteSymbolicLink(&usSymbolName);

        DbgPrint("%s, Delete device\n", __FUNCTION__);
        IoDetachDevice(pNextDevice);
        IoDeleteDevice(pMyDevice);
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);
        return STATUS_SUCCESS;
    }

    IoSkipCurrentIrpStackLocation(pIrp);
    return IoCallDriver(pNextDevice, pIrp);
}

static VOID Unload(PDRIVER_OBJECT pMyDriver)
{
    DbgPrint("%s\n", __FUNCTION__);
}
 
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    DbgPrint("%s, Set calllback\n", __FUNCTION__);
    pMyDriver->MajorFunction[IRP_MJ_PNP] = IrpDispatch;
    pMyDriver->DriverExtension->AddDevice = AddDevice;
    pMyDriver->DriverUnload = Unload;

    return STATUS_SUCCESS;
}
