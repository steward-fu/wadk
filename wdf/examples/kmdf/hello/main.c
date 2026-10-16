//
// Hello, world!
// https://steward-fu.github.io/website/index.htm
//

#include <ntddk.h>
#include <wdf.h>
 
NTSTATUS AddDevice(WDFDRIVER myDriver, PWDFDEVICE_INIT pMyDeviceInit)
{
    WDFDEVICE dev = { 0 };
    UNICODE_STRING name = { 0 };
    
    DbgPrint("Hello, world!");
    RtlInitUnicodeString(&name, L"\\Device\\MyDriver");
    WdfDeviceInitAssignName(pMyDeviceInit, &name);

    return WdfDeviceCreate(&pMyDeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &dev);
}
 
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    WDF_DRIVER_CONFIG cfg = { 0 };
 
    WDF_DRIVER_CONFIG_INIT(&cfg, AddDevice);

    return WdfDriverCreate(pMyDriver, pMyRegistry, WDF_NO_OBJECT_ATTRIBUTES, &cfg, WDF_NO_HANDLE);
}
