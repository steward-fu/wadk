#include <wdm.h>
  
static PDEVICE_OBJECT pNextDevice = NULL;
  
static NTSTATUS AddDevice(PDRIVER_OBJECT pMyDriver, PDEVICE_OBJECT pPhyDevice)
{
    PDEVICE_OBJECT pMyDevice = NULL;
    UNICODE_STRING usDeviceName = {0};
 
    DbgPrint("Hello, world!");
    RtlInitUnicodeString(&usDeviceName, L"\\Device\\MyDriver");
    IoCreateDevice(pMyDriver, 0, &usDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pMyDevice);
    pNextDevice = IoAttachDeviceToDeviceStack(pMyDevice, pPhyDevice);
    pMyDevice->Flags &= ~DO_DEVICE_INITIALIZING;
    pMyDevice->Flags |= DO_BUFFERED_IO;
    return STATUS_SUCCESS;
}
  
static void Unload(PDRIVER_OBJECT pMyDriver)
{
}
  
static NTSTATUS IrpDispatch(PDEVICE_OBJECT pMyDevice, PIRP pIrp)
{
    PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
 
    if (pStack->MinorFunction == IRP_MN_REMOVE_DEVICE) {
        IoDetachDevice(pNextDevice);
        IoDeleteDevice(pMyDevice);
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);
        return STATUS_SUCCESS;
    }
    IoSkipCurrentIrpStackLocation(pIrp);
    return IoCallDriver(pNextDevice, pIrp);
}
  
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    pMyDriver->MajorFunction[IRP_MJ_PNP] = IrpDispatch;
    pMyDriver->DriverExtension->AddDevice = AddDevice;
    pMyDriver->DriverUnload = Unload;
    return STATUS_SUCCESS;
}
