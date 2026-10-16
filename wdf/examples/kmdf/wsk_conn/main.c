//
// Winsock Kernel (WSK) - connect
// Remove error check for better readability
// https://steward-fu.github.io/website/index.htm
//

#include <ntddk.h>
#include <wsk.h>

#define SERVER_IP L"10.0.2.2" 
#define SERVER_PORT 9999

static PVOID pThread = NULL;
static WSK_PROVIDER_NPI npi = { 0 };
static WSK_REGISTRATION wsk_reg = { 0 };
static const WSK_CLIENT_DISPATCH client_disp = {
    MAKE_WSK_VERSION(1, 0),
    0,
    NULL
};
 
static NTSTATUS CompleteRoutine(PDEVICE_OBJECT DevObj, PIRP Irp, PKEVENT Event)
{
    KeSetEvent(Event, IO_NO_INCREMENT, FALSE);
 
    return STATUS_MORE_PROCESSING_REQUIRED;
}
 
static void MyThread(PVOID Context)
{
    PIRP irp = NULL;
    KEVENT event = { 0 };
    NTSTATUS status = 0;
    WSK_CLIENT_NPI client = { 0 };
    SOCKADDR_IN local = { 0 };
    PCWSTR term = NULL;
    SOCKADDR_IN remote = { 0 };
    PWSK_SOCKET socket = NULL;
    PWSK_PROVIDER_CONNECTION_DISPATCH sock_dispatch = NULL;
 
    client.ClientContext = NULL;
    client.Dispatch = &client_disp;
    status = WskRegister(&client, &wsk_reg);
    status = WskCaptureProviderNPI(&wsk_reg, WSK_INFINITE_WAIT, &npi);
    KeInitializeEvent(&event, SynchronizationEvent, FALSE);

    irp = IoAllocateIrp(1, FALSE);
    IoSetCompletionRoutine(irp, CompleteRoutine, &event, TRUE, TRUE, TRUE);

    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = 0;

    remote.sin_family = AF_INET;
    remote.sin_port = RtlUshortByteSwap(SERVER_PORT);
    status = RtlIpv4StringToAddressW(SERVER_IP, TRUE, &term, &remote.sin_addr);
    status = npi.Dispatch->WskSocketConnect(
        npi.Client,
        SOCK_STREAM,
        IPPROTO_TCP,
        (PSOCKADDR)&local,
        (PSOCKADDR)&remote,
        WSK_FLAG_CONNECTION_SOCKET,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        irp
    );

    if (status == STATUS_PENDING){
        KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        status = irp->IoStatus.Status;
        socket = (PWSK_SOCKET)irp->IoStatus.Information;
        sock_dispatch = (PWSK_PROVIDER_CONNECTION_DISPATCH)socket->Dispatch;
    }
    DbgPrint("Connect to server");

    KeResetEvent(&event);
    IoReuseIrp(irp, STATUS_UNSUCCESSFUL);
    IoSetCompletionRoutine(irp, CompleteRoutine, &event, TRUE, TRUE, TRUE);

    status = sock_dispatch->WskCloseSocket(socket, irp);
    if (status == STATUS_PENDING) {
        KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
        status = irp->IoStatus.Status;
    }
    DbgPrint("Disconnect from server");
     
    IoFreeIrp(irp);
    WskReleaseProviderNPI(&wsk_reg);
    WskDeregister(&wsk_reg);
    PsTerminateSystemThread(STATUS_SUCCESS);
}
 
void Unload(PDRIVER_OBJECT pMyDriver)
{
    KeWaitForSingleObject(pThread, Executive, KernelMode, FALSE, NULL);
    ObDereferenceObject(pThread);
}
   
NTSTATUS DriverEntry(PDRIVER_OBJECT pMyDriver, PUNICODE_STRING pMyRegistry)
{
    HANDLE hThread = 0;
    NTSTATUS status = 0;
 
    status = PsCreateSystemThread(&hThread,
        THREAD_ALL_ACCESS,
        NULL,
        NULL,
        NULL,
        MyThread,
        NULL
    );
 
    status = ObReferenceObjectByHandle(hThread, THREAD_ALL_ACCESS, NULL, KernelMode, &pThread, NULL);
    ZwClose(hThread);
    pMyDriver->DriverUnload = Unload;
     
    return STATUS_SUCCESS;
}
