/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    fail_driver1.c

Abstract:

    This is a sample driver that contains intentionally placed code defects 
    in order to illustrate how Static Driver Verifier works. This driver is
    not functional and not intended as a sample for real driver development
    projects.

Environment:

    Kernel mode

--*/

#include "fail_driver1.h"

#ifndef __cplusplus
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, EvtDriverDeviceAdd)
#endif

NTSTATUS 
  DriverEntry( 
    IN PDRIVER_OBJECT   DriverObject, 
    IN PUNICODE_STRING  RegistryPath
    )
{
    UNREFERENCED_PARAMETER(RegistryPath);
    UNREFERENCED_PARAMETER(DriverObject);

    /*
      This defect is injected for the "DriverCreate" rule.
    */
    SDVTest_wdf_DriverCreate();

    return STATUS_SUCCESS;
}

NTSTATUS
EvtDriverDeviceAdd(
    IN WDFDRIVER        Driver,
    IN PWDFDEVICE_INIT  DeviceInit
    )
{
    WDFDEVICE           device              = NULL;
    WDFDEVICE           controlDevice       = NULL;      
    NTSTATUS            status              = STATUS_SUCCESS;
    PWDFDEVICE_INIT     pControlDeviceInit  = NULL;
    WDF_IO_QUEUE_CONFIG     ioQueueConfig;
    WDF_OBJECT_ATTRIBUTES   queueAttributes;
    WDFQUEUE                queue;

    DECLARE_CONST_UNICODE_STRING(securityDescriptor, L"D:P");

    UNREFERENCED_PARAMETER(Driver);

    status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);

    if(!NT_SUCCESS(status)){
        return status;
    }

    /*
      This defect is injected for the "DeviceInitAPI" rule.
    */
    SDVTest_wdf_DeviceInitAPI(DeviceInit);

    pControlDeviceInit = WdfControlDeviceInitAllocate(WdfGetDriver(), &securityDescriptor);

    status = WdfDeviceCreate(&pControlDeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &controlDevice);

    if(!NT_SUCCESS(status)){
        return status;
    }

    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE (
        &ioQueueConfig,
        WdfIoQueueDispatchSequential
        );

    ioQueueConfig.EvtIoDeviceControl = EvtIoDeviceControl;
    ioQueueConfig.EvtIoRead          = EvtIoRead;
    ioQueueConfig.EvtIoInternalDeviceControl = EvtIoInternalDeviceControl;
    WDF_OBJECT_ATTRIBUTES_INIT(&queueAttributes);

    status = WdfIoQueueCreate( device,
                               &ioQueueConfig,
                               &queueAttributes,
                               &queue );    

    /*
       This defect is injected for the "CtlDeviceFinishInitDeviceAdd" rule.
    */
    return status;
}

VOID
EvtIoRead(
    IN WDFQUEUE     Queue,
    IN WDFREQUEST   Request,
    IN size_t       Length
    )
{

    UNREFERENCED_PARAMETER(Length);
    UNREFERENCED_PARAMETER(Queue);

    WdfRequestMarkCancelable(Request, EvtRequestCancel);

    /*
      This defect is injected for the "MarkCancOnCancReqLocal" rule.
    */
    SDVTest_wdf_MarkCancOnCancReqDispatch(Request);

    /*
    This defect is injected for the "StopAckWithinEvtIoStop" rule.
    */
    WdfRequestStopAcknowledge(Request,FALSE);
    
}

VOID
EvtIoDeviceControl(
    IN WDFQUEUE     Queue,
    IN WDFREQUEST   Request,
    IN size_t       OutputBufferLength,
    IN size_t       InputBufferLength,
    IN ULONG        IoControlCode
    )
{
    NTSTATUS    status;
    PMDL        pMdl;

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);
    UNREFERENCED_PARAMETER(IoControlCode);
 

    status = WdfRequestRetrieveInputWdmMdl(Request, &pMdl);

    WdfRequestComplete(Request, status);

    /*
      This defect is injected for the "MdlAfterReqCompletedIoctl" rule.
    */
    SDVTest_wdf_MdlAfterReqCompletionIoctl(Request, pMdl);
}

VOID
EvtIoInternalDeviceControl(
    IN WDFQUEUE     Queue,
    IN WDFREQUEST   Request,
    IN size_t       OutputBufferLength,
    IN size_t       InputBufferLength,
    IN ULONG        IoControlCode
    )
{
    NTSTATUS    status;
    WDFMEMORY   memory;
    PMDL        pMdl;

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);
    UNREFERENCED_PARAMETER(IoControlCode);

    status = WdfRequestRetrieveInputMemory(Request, &memory);

    status = WdfRequestRetrieveOutputWdmMdl(Request, &pMdl);

    WdfRequestComplete(Request, status);

    /*
      This defect is injected for the "MemAfterReqCompletedIntIoctlA" rule.
    */
    SDVTest_wdf_MemoryAfterReqCompletionIntIoctlAdd(memory);

    /*
      This defect is injected for the "MdlAfterReqCompletedIntIoctlA" rule.
    */
    SDVTest_wdf_MdlAfterReqCompletionIntIoctlAdd(pMdl);
}

VOID
EvtRequestCancel(
    IN WDFREQUEST  Request
    )
{
    WdfRequestComplete(Request, STATUS_CANCELLED);
}
