//
// File operation
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
  
static VOID Unload(PDRIVER_OBJECT pMyDriver)
{
    DbgPrint("%s, pMyDriver = %p\n", __FUNCTION__, pMyDriver);
}
  
static NTSTATUS IrpPnp(PDEVICE_OBJECT pMyDevice, PIRP pIrp)
{
    UNICODE_STRING usSymbolName = { 0 };
    PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);

    DbgPrint("%s, Major = 0x%x\n", __FUNCTION__, pStack->MajorFunction);
    if (pStack->MinorFunction == IRP_MN_REMOVE_DEVICE) {
        RtlInitUnicodeString(&usSymbolName, L"\\DosDevices\\MyDriver");
        IoDeleteSymbolicLink(&usSymbolName);
        DbgPrint("%s, Delete symbolic link\n", __FUNCTION__);

        IoDetachDevice(pNextDevice);
        DbgPrint("%s, Delete device\n", __FUNCTION__);

        IoDeleteDevice(pMyDevice);
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);
        return STATUS_SUCCESS;
    }

    IoSkipCurrentIrpStackLocation(pIrp);
    return IoCallDriver(pNextDevice, pIrp);
}
  
static NTSTATUS IrpFile(PDEVICE_OBJECT pMyDevice, PIRP pIrp)
{
    PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
 
    switch (pStack->MajorFunction) {
    case IRP_MJ_CREATE:
        DbgPrint("%s, Handle IRP_MJ_CREATE\n", __FUNCTION__);
        break;
    case IRP_MJ_READ:
        DbgPrint("%s, Handle IRP_MJ_READ\n", __FUNCTION__);
        break;
    case IRP_MJ_WRITE:
        DbgPrint("%s, Handle IRP_MJ_WRITE\n", __FUNCTION__);
        break;
    case IRP_MJ_CLOSE:
        DbgPrint("%s, Handle IRP_MJ_CLOSE\n", __FUNCTION__);
        break;
    }

    IoCompleteRequest(pIrp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}
  
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    DbgPrint("%s, pMyDriver = %p\n", __FUNCTION__, pMyDriver);
    pMyDriver->MajorFunction[IRP_MJ_PNP]    = IrpPnp;
    pMyDriver->MajorFunction[IRP_MJ_CREATE] = IrpFile;
    pMyDriver->MajorFunction[IRP_MJ_READ]   = IrpFile;
    pMyDriver->MajorFunction[IRP_MJ_WRITE]  = IrpFile;
    pMyDriver->MajorFunction[IRP_MJ_CLOSE]  = IrpFile;
    pMyDriver->DriverExtension->AddDevice   = AddDevice;
    pMyDriver->DriverUnload = Unload;

    return STATUS_SUCCESS;
}
