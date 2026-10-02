#include <wdm.h>
  
#define DEV_NAME L"\\Device\\MyDriver"
#define SYM_NAME L"\\DosDevices\\MyDriver"
  
char szBuffer[255] = {0};
PDEVICE_OBJECT pNextDevice = NULL;
  
NTSTATUS AddDevice(PDRIVER_OBJECT pMyDriver, PDEVICE_OBJECT pPhyDevice)
{
    PDEVICE_OBJECT pMyDevice = NULL;
    UNICODE_STRING usDeviceName = { 0 };
    UNICODE_STRING usSymbolName = { 0 };
  
    RtlInitUnicodeString(&usDeviceName, DEV_NAME);
    IoCreateDevice(pMyDriver, 0, &usDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pMyDevice);
    RtlInitUnicodeString(&usSymbolName, SYM_NAME);
    IoCreateSymbolicLink(&usSymbolName, &usDeviceName);
    pNextDevice = IoAttachDeviceToDeviceStack(pMyDevice, pPhyDevice);
    pMyDevice->Flags &= ~DO_DEVICE_INITIALIZING;
    pMyDevice->Flags |= DO_BUFFERED_IO;
    return STATUS_SUCCESS;
}
  
void Unload(PDRIVER_OBJECT pMyDriver)
{
}
  
NTSTATUS IrpPnp(PDEVICE_OBJECT pMyDevice, PIRP pIrp)
{
    UNICODE_STRING usSymbolName = { 0 };
    PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
  
    if (pStack->MinorFunction == IRP_MN_REMOVE_DEVICE) {
        RtlInitUnicodeString(&usSymbolName, SYM_NAME);
        IoDeleteSymbolicLink(&usSymbolName);
        IoDetachDevice(pNextDevice);
        IoDeleteDevice(pMyDevice);
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);
        return STATUS_SUCCESS;
    }
    IoSkipCurrentIrpStackLocation(pIrp);
    return IoCallDriver(pNextDevice, pIrp);
}
  
NTSTATUS IrpFile(PDEVICE_OBJECT pMyDevice, PIRP pIrp)
{
    PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
  
    switch (pStack->MajorFunction) {
    case IRP_MJ_CREATE:
        memset(szBuffer, 0, sizeof(szBuffer));
        DbgPrint("IRP_MJ_CREATE");
        break;
    case IRP_MJ_READ:
        strcpy(pIrp->AssociatedIrp.SystemBuffer, szBuffer);
        DbgPrint("IRP_MJ_READ");
 
        pIrp->IoStatus.Status = STATUS_SUCCESS;
        pIrp->IoStatus.Information = strlen(szBuffer);
        break;
    case IRP_MJ_WRITE:
        memcpy(szBuffer, pIrp->AssociatedIrp.SystemBuffer, pStack->Parameters.Write.Length);
        DbgPrint("IRP_MJ_WRITE");
        DbgPrint("Buffer: %s, Length: %d", szBuffer, pStack->Parameters.Write.Length);
 
        pIrp->IoStatus.Status = STATUS_SUCCESS;
        pIrp->IoStatus.Information = strlen(szBuffer);
        break;
    case IRP_MJ_CLOSE:
        DbgPrint("IRP_MJ_CLOSE");
        break;
    }
    IoCompleteRequest(pIrp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}
  
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    pMyDriver->MajorFunction[IRP_MJ_PNP]    = IrpPnp;
    pMyDriver->MajorFunction[IRP_MJ_CREATE] = IrpFile;
    pMyDriver->MajorFunction[IRP_MJ_READ]   = IrpFile;
    pMyDriver->MajorFunction[IRP_MJ_WRITE]  = IrpFile;
    pMyDriver->MajorFunction[IRP_MJ_CLOSE]  = IrpFile;
    pMyDriver->DriverExtension->AddDevice   = AddDevice;
    pMyDriver->DriverUnload = Unload;
    return STATUS_SUCCESS;
}
