unit main;
 
interface
uses
    DDDK;
     
const
    DEV_NAME = '\Device\MyDriver';
    SYM_NAME = '\DosDevices\MyDriver';

    IOCTL_START = (FILE_DEVICE_UNKNOWN shl 16) or (FILE_ANY_ACCESS shl 14) or ($800 shl 2) or (METHOD_BUFFERED);
    IOCTL_STOP = (FILE_DEVICE_UNKNOWN shl 16) or (FILE_ANY_ACCESS shl 14) or ($801 shl 2) or (METHOD_BUFFERED);

function __DriverEntry(pMyDriver : PDRIVER_OBJECT; pMyRegistry : PUNICODE_STRING) : NTSTATUS; stdcall;
 
implementation
var
    cnt : ULONG;
    dpc : TKDpc;
    obj : KTIMER;
    pDevice : PDEVICE_OBJECT;
 
procedure OnTimer(Dpc : KDPC; DeferredContext : Pointer; SystemArgument1 : Pointer; SystemArgument2 : Pointer); stdcall;
begin
    cnt := cnt + 1;
    DbgPrint('DpcTimer: %d', [cnt]);
end;
 
procedure IrpFileCreate(myDevice : WDFDEVICE; myRequest : WDFREQUEST; myFileObject : WDFFILEOBJECT); stdcall;
begin
    DbgPrint('IRP_MJ_CREATE', []);
    WdfRequestComplete(myRequest, STATUS_SUCCESS);
end;
 
procedure IrpFileClose(myFileObject : WDFFILEOBJECT); stdcall;
begin
    DbgPrint('IRP_MJ_CLOSE', []);
end;
 
procedure IrpIOCTL(myQueue : WDFQUEUE; myRequest : WDFREQUEST; myOutLen : ULONG; myInLen : ULONG; myCode : ULONG); stdcall;
var
    tt : LARGE_INTEGER;

begin
    if myCode = IOCTL_START then begin
        DbgPrint('IOCTL_START', []);
        cnt := 0;
        tt.HighPart := tt.HighPart or -1;
        tt.LowPart := ULONG(-10000000);
        KeSetTimerEx(@obj, tt.LowPart, tt.HighPart, 1000, @dpc);
    end else if myCode = IOCTL_STOP then begin
        DbgPrint('IOCTL_STOP', []);
        KeCancelTimer(@obj);
    end;
    WdfRequestComplete(myRequest, STATUS_SUCCESS);
end;
 
function AddDevice(pMyDriver : WDFDRIVER; pMyDeviceInit : PWDFDEVICE_INIT) : NTSTATUS; stdcall;
var
    device : WDFDEVICE;
    io_cfg : WDF_IO_QUEUE_CONFIG;
    file_cfg : WDF_FILEOBJECT_CONFIG;
    szDevName : UNICODE_STRING;
    szSymName : UNICODE_STRING;
 
begin
    WdfDeviceInitSetIoType(pMyDeviceInit, WdfDeviceIoBuffered);
    WDF_FILEOBJECT_CONFIG_INIT(@file_cfg, @IrpFileCreate, @IrpFileClose, Nil);
    WdfDeviceInitSetFileObjectConfig(pMyDeviceInit, @file_cfg, WDF_NO_OBJECT_ATTRIBUTES);
     
    RtlInitUnicodeString(@szDevName, DEV_NAME);
    RtlInitUnicodeString(@szSymName, SYM_NAME);
    WdfDeviceInitAssignName(pMyDeviceInit, @szDevName);
    WdfDeviceCreate(@pMyDeviceInit, WDF_NO_OBJECT_ATTRIBUTES, @device);
    WdfDeviceCreateSymbolicLink(device, @szSymName);
     
    pDevice := WdfDeviceWdmGetDeviceObject(device);
    KeInitializeTimer(@obj);
    KeInitializeDpc(@dpc, OnTimer, pDevice);
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(@io_cfg, WdfIoQueueDispatchSequential);
    io_cfg.EvtIoDeviceControl := @IrpIOCTL;
    Result := WdfIoQueueCreate(device, @io_cfg, WDF_NO_OBJECT_ATTRIBUTES, WDF_NO_HANDLE);
end;
 
function __DriverEntry(pMyDriver : PDRIVER_OBJECT; pMyRegistry : PUNICODE_STRING) : NTSTATUS; stdcall;
var
    config : WDF_DRIVER_CONFIG;
     
begin
    WDF_DRIVER_CONFIG_INIT(@config, AddDevice);
    WdfDriverCreate(pMyDriver, pMyRegistry, WDF_NO_OBJECT_ATTRIBUTES, @config, WDF_NO_HANDLE);
    Result := STATUS_SUCCESS;
end;
end.
