#include <ntddk.h>
#include <tdi.h>
#include <tdikrnl.h>

static HANDLE hAddr = NULL;
static HANDLE hConn = NULL;
static PFILE_OBJECT pAddrObj = NULL;
static PFILE_OBJECT pConnObj = NULL;

static NTSTATUS TdiCompletion(PDEVICE_OBJECT DevObj, PIRP Irp, PVOID Context)
{
    KeSetEvent((PKEVENT)Context, IO_NO_INCREMENT, FALSE);

    return STATUS_MORE_PROCESSING_REQUIRED;
}

static NTSTATUS TdiCreateAddress(void)
{
    ULONG eaSize = 0;
    NTSTATUS status = 0;
    HANDLE handle = NULL;
    IO_STATUS_BLOCK iosb = { 0 };
    UNICODE_STRING devName = { 0 };
    OBJECT_ATTRIBUTES objAttr = { 0 };
    PFILE_OBJECT fileObj = NULL;
    PTDI_ADDRESS_IP ipAddr = NULL;
    PFILE_FULL_EA_INFORMATION ea = NULL;
    PTRANSPORT_ADDRESS tranAddr = NULL;

    eaSize = FIELD_OFFSET(FILE_FULL_EA_INFORMATION, EaName) +
        TDI_TRANSPORT_ADDRESS_LENGTH +
        1 +
        sizeof(TRANSPORT_ADDRESS) + sizeof(TDI_ADDRESS_IP);

    ea = (PFILE_FULL_EA_INFORMATION)ExAllocatePool(NonPagedPool, eaSize);

    RtlZeroMemory(ea, eaSize);
    ea->EaNameLength = TDI_TRANSPORT_ADDRESS_LENGTH;
    ea->EaValueLength = sizeof(TRANSPORT_ADDRESS) + sizeof(TDI_ADDRESS_IP);
    RtlCopyMemory(ea->EaName, TdiTransportAddress, TDI_TRANSPORT_ADDRESS_LENGTH);
    tranAddr = (PTRANSPORT_ADDRESS)(ea->EaName + ea->EaNameLength + 1);
    tranAddr->TAAddressCount = 1;
    tranAddr->Address[0].AddressLength = sizeof(TDI_ADDRESS_IP);
    tranAddr->Address[0].AddressType = TDI_ADDRESS_TYPE_IP;
    ipAddr = (PTDI_ADDRESS_IP)tranAddr->Address[0].Address;
    ipAddr->in_addr = 0;
    ipAddr->sin_port = 0;
    RtlZeroMemory(ipAddr->sin_zero, sizeof(ipAddr->sin_zero));
    RtlInitUnicodeString(&devName, L"\\Device\\Tcp");
    InitializeObjectAttributes(&objAttr,
        &devName,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL
    );

    status = ZwCreateFile(&handle,
        GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
        &objAttr,
        &iosb,
        NULL,
        0,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_OPEN_IF,
        0,
        ea,
        eaSize
    );
    ExFreePool(ea);

    status = ObReferenceObjectByHandle(handle,
        FILE_ANY_ACCESS,
        *IoFileObjectType, KernelMode,
        (PVOID *)&fileObj,
        NULL);

    hAddr = handle;
    pAddrObj = fileObj;

    return STATUS_SUCCESS;
}

static NTSTATUS TdiCreateConnection(void)
{
    NTSTATUS status = 0;
    UNICODE_STRING devName = { 0 };
    OBJECT_ATTRIBUTES objAttr = { 0 };
    IO_STATUS_BLOCK iosb = { 0 };
    PFILE_FULL_EA_INFORMATION ea = { 0 };
    ULONG eaSize = 0;
    HANDLE handle = NULL;
    PFILE_OBJECT fileObj = NULL;
    CONNECTION_CONTEXT connContext = { 0 };

    eaSize = FIELD_OFFSET(FILE_FULL_EA_INFORMATION, EaName) +
        TDI_CONNECTION_CONTEXT_LENGTH +
        1 +
        sizeof(CONNECTION_CONTEXT);

    ea = (PFILE_FULL_EA_INFORMATION)ExAllocatePool(NonPagedPool, eaSize);
    RtlZeroMemory(ea, eaSize);
    ea->EaNameLength = TDI_CONNECTION_CONTEXT_LENGTH;
    ea->EaValueLength = sizeof(CONNECTION_CONTEXT);
    RtlCopyMemory(ea->EaName,
        TdiConnectionContext,
        TDI_CONNECTION_CONTEXT_LENGTH
    );

    connContext = NULL;
    RtlCopyMemory(ea->EaName + ea->EaNameLength + 1,
        &connContext,
        sizeof(connContext)
    );

    RtlInitUnicodeString(&devName, L"\\Device\\Tcp");
    InitializeObjectAttributes(&objAttr,
        &devName,
        OBJ_CASE_INSENSITIVE,
        NULL,
        NULL
    );

    status = ZwCreateFile(&handle,
        GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
        &objAttr,
        &iosb,
        NULL,
        0,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_OPEN_IF,
        0,
        ea,
        eaSize
    );

    ExFreePool(ea);
    status = ObReferenceObjectByHandle(handle,
        FILE_ANY_ACCESS,
        *IoFileObjectType,
        KernelMode,
        (PVOID *)&fileObj,
        NULL
    );

    hConn = handle;
    pConnObj = fileObj;

    return STATUS_SUCCESS;
}

static NTSTATUS TdiAssociateAddress(void)
{
    PIRP irp = NULL;
    NTSTATUS status = 0;
    KEVENT event = { 0 };
    PDEVICE_OBJECT devObj = NULL;

    devObj = pConnObj->DeviceObject;
    KeInitializeEvent(&event, NotificationEvent, FALSE);
    irp = IoAllocateIrp(devObj->StackSize, FALSE);
    TdiBuildAssociateAddress(irp, devObj, pConnObj, TdiCompletion, &event, hAddr);
    status = IoCallDriver(devObj, irp);
    if (status == STATUS_PENDING) {
        KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        status = irp->IoStatus.Status;
    }
    IoFreeIrp(irp);

    return status;
}

static NTSTATUS TdiConnect(void)
{
    NTSTATUS status = 0;
    PIRP irp = NULL;
    PDEVICE_OBJECT devObj = NULL;
    KEVENT event = { 0 };
    PTRANSPORT_ADDRESS remote = NULL;
    PTDI_ADDRESS_IP ipAddr = NULL;
    TDI_CONNECTION_INFORMATION connInfo = { 0 };
    ULONG addrSize = 0;

    addrSize = FIELD_OFFSET(TRANSPORT_ADDRESS, Address[0].Address) +
        sizeof(TDI_ADDRESS_IP);

    remote = (PTRANSPORT_ADDRESS)ExAllocatePool(NonPagedPool, addrSize);
    RtlZeroMemory(remote, addrSize);
    remote->TAAddressCount = 1;
    remote->Address[0].AddressLength = sizeof(TDI_ADDRESS_IP);
    remote->Address[0].AddressType = TDI_ADDRESS_TYPE_IP;
    ipAddr = (PTDI_ADDRESS_IP)remote->Address[0].Address;

    // 10.0.2.2:9999
    ipAddr->in_addr = 0x0202000A;
    ipAddr->sin_port = 0x0F27;

    RtlZeroMemory(ipAddr->sin_zero, sizeof(ipAddr->sin_zero));
    RtlZeroMemory(&connInfo, sizeof(connInfo));
    connInfo.RemoteAddressLength = (LONG)addrSize;
    connInfo.RemoteAddress = remote;
    connInfo.UserDataLength = 0;
    connInfo.UserData = NULL;
    connInfo.OptionsLength = 0;
    connInfo.Options = NULL;
    devObj = pConnObj->DeviceObject;
    KeInitializeEvent(&event, NotificationEvent, FALSE);
    irp = IoAllocateIrp(devObj->StackSize, FALSE);
    TdiBuildConnect(irp,
        devObj,
        pConnObj,
        TdiCompletion,
        &event,
        NULL,
        &connInfo,
        NULL
    );

    status = IoCallDriver(devObj, irp);
    if (status == STATUS_PENDING) {
        KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        status = irp->IoStatus.Status;
    }
    IoFreeIrp(irp);
    ExFreePool(remote);

    return status;
}

static void TdiCleanup(void)
{
    ObDereferenceObject(pConnObj);
    ZwClose(hConn);
    ObDereferenceObject(pAddrObj);
    ZwClose(hAddr);
}

static NTSTATUS TdiSend(const char *buf, ULONG len)
{
    PIRP irp = NULL;
    PMDL mdl = NULL;
    PVOID buffer = NULL;
    KEVENT event = { 0 };
    NTSTATUS status = STATUS_SUCCESS;
    PDEVICE_OBJECT devObj = NULL;

    buffer = ExAllocatePool(NonPagedPool, len);
    RtlCopyMemory(buffer, buf, len);
    mdl = IoAllocateMdl(buffer, len, FALSE, FALSE, NULL);
    MmBuildMdlForNonPagedPool(mdl);
    devObj = pConnObj->DeviceObject;
    KeInitializeEvent(&event, NotificationEvent, FALSE);
    irp = IoAllocateIrp(devObj->StackSize, FALSE);
    TdiBuildSend(irp, devObj, pConnObj, TdiCompletion, &event, mdl, 0, len);
    status = IoCallDriver(devObj, irp);
    if (status == STATUS_PENDING) {
        KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        status = irp->IoStatus.Status;
    }
    else {
        status = irp->IoStatus.Status;
    }
    DbgPrint("Send %lubytes\n", (ULONG)irp->IoStatus.Information);
    IoFreeIrp(irp);
    IoFreeMdl(mdl);
    ExFreePool(buffer);

    return status;
}

static void DriverUnload(PDRIVER_OBJECT DriverObj)
{
    TdiCleanup();
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObj, PUNICODE_STRING RegistryPath)
{
    NTSTATUS status = 0;
    const char *p = "Hello, world!";

    status = TdiCreateAddress();
    status = TdiCreateConnection();
    status = TdiAssociateAddress();
    status = TdiConnect();
    DbgPrint("Connection result: 0x%x\n", status);
    TdiSend(p, strlen(p));

    DriverObj->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
