/*++

Copyright (c) 1994-1999  Microsoft Corporation

Module Name:

    ntddpcm.h

Abstract:

    This is the include file that defines all constants and types for
    accessing the PCMCIA Adapters.

--*/

#ifndef _NTDDPCMH_
#define _NTDDPCMH_

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Device Name - this string is the name of the device.  It is the name
// that should be passed to NtOpenFile when accessing the device.
//
// Note:  For devices that support multiple units, it should be suffixed
//        with the Ascii representation of the unit number.
//
// Note: The IOCTL interface to pcmcia host controllers is turned off by
//       default. These IOCTLs are provided for testing purposes only. To
//       turn on this interface, add the following registry value:
// HKLM\SYSTEM\CurrentControlSet\Services\Pcmcia\Parameters\IoctlInterface : REG_DWORD : 1
//

#define IOCTL_PCMCIA_BASE                 FILE_DEVICE_CONTROLLER

#define DD_PCMCIA_DEVICE_NAME "\\\\.\\Pcmcia"

//
// IoControlCode values for this device.
//

#define IOCTL_GET_TUPLE_DATA         CTL_CODE(IOCTL_PCMCIA_BASE, 3000, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SOCKET_INFORMATION     CTL_CODE(IOCTL_PCMCIA_BASE, 3004, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PCMCIA_HIDE_DEVICE     CTL_CODE(IOCTL_PCMCIA_BASE, 3010, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_PCMCIA_REVEAL_DEVICE   CTL_CODE(IOCTL_PCMCIA_BASE, 3011, METHOD_BUFFERED, FILE_WRITE_ACCESS)

//
// Tuple request parameters.
//

typedef struct _PCMCIA_SOCKET_REQUEST {
   USHORT  Socket;
} PCMCIA_SOCKET_REQUEST, *PPCMCIA_SOCKET_REQUEST;

typedef struct _TUPLE_REQUEST {
   USHORT  Socket;
} TUPLE_REQUEST, *PTUPLE_REQUEST;

#define MANUFACTURER_NAME_LENGTH 64
#define DEVICE_IDENTIFIER_LENGTH 64
#define DRIVER_NAME_LENGTH       32

#define PcmciaInvalidControllerType 0xffffffff

//
// Controller classes returned in socket information structure.
//

typedef enum _PCMCIA_CONTROLLER_CLASS {
   PcmciaInvalidControllerClass = -1,
   PcmciaIntelCompatible,
   PcmciaCardBusCompatible,
   PcmciaElcController,
   PcmciaDatabook,
   PcmciaPciPcmciaBridge,
   PcmciaCirrusLogic,
   PcmciaTI,
   PcmciaTopic,
   PcmciaRicoh,
   PcmciaDatabookCB,
   PcmciaOpti,
   PcmciaTrid,
   PcmciaO2Micro,
   PcmciaNEC,
   PcmciaNEC_98
} PCMCIA_CONTROLLER_CLASS, *PPCMCIA_CONTROLLER_CLASS;


typedef struct _PCMCIA_SOCKET_INFORMATION {
   USHORT  Socket;
   USHORT  TupleCrc;
   UCHAR   Manufacturer[MANUFACTURER_NAME_LENGTH];
   UCHAR   Identifier[DEVICE_IDENTIFIER_LENGTH];
   UCHAR   DriverName[DRIVER_NAME_LENGTH];
   UCHAR   DeviceFunctionId;
   UCHAR   Reserved;
   UCHAR   CardInSocket;
   UCHAR   CardEnabled;
   ULONG   ControllerType;
} PCMCIA_SOCKET_INFORMATION, *PPCMCIA_SOCKET_INFORMATION;

//
// macros to crack the ControllerId field of the socket info structure
//
#define PcmciaClassFromControllerType(type) ((PCMCIA_CONTROLLER_CLASS)((type) & 0xff))
#define PcmciaModelFromControllerType(type) (((type) >> 8) & 0x3ffff)
#define PcmciaRevisionFromControllerType(type) ((type) >> 26)

//
// Begin pcmcia exported interfaces to other drivers
//

#ifdef _NTDDK_

DEFINE_GUID( GUID_PCMCIA_INTERFACE_STANDARD,     0xbed5dadfL, 0x38fb, 0x11d1, 0x94, 0x62, 0x00, 0xc0, 0x4f, 0xb9, 0x60, 0xee);

#define  PCMCIA_MEMORY_8BIT_ACCESS     0
#define  PCMCIA_MEMORY_16BIT_ACCESS    1

typedef
__drv_functionClass(PCMCIA_MODIFY_MEMORY_WINDOW)
BOOLEAN
PCMCIA_MODIFY_MEMORY_WINDOW(
    __in_opt PVOID Context,
    __in ULONGLONG HostBase,
    __in ULONGLONG CardBase,
    __in BOOLEAN Enable,
    __in_opt ULONG WindowSize,
    __in_opt UCHAR AccessSpeed,
    __in_opt UCHAR BusWidth,
    __in_opt BOOLEAN IsAttributeMemory
    );
typedef PCMCIA_MODIFY_MEMORY_WINDOW *PPCMCIA_MODIFY_MEMORY_WINDOW;

#define     PCMCIA_VPP_0V     0
#define     PCMCIA_VPP_12V    1
#define     PCMCIA_VPP_IS_VCC 2

typedef
__drv_functionClass(PCMCIA_SET_VPP)
BOOLEAN
PCMCIA_SET_VPP(
    __in_opt PVOID Context,
    __in UCHAR VppLevel
    );
typedef PCMCIA_SET_VPP *PPCMCIA_SET_VPP;

typedef
__drv_functionClass(PCMCIA_IS_WRITE_PROTECTED)
BOOLEAN
PCMCIA_IS_WRITE_PROTECTED(
    __in_opt PVOID Context
    );
typedef PCMCIA_IS_WRITE_PROTECTED *PPCMCIA_IS_WRITE_PROTECTED;

//
// These are interfaces for manipulating memory windows, setting Vpp etc.,
// primarily used by flash memory card drivers
//
typedef struct _PCMCIA_INTERFACE_STANDARD {
   USHORT Size;
   USHORT Version;
   PINTERFACE_REFERENCE InterfaceReference;
   PINTERFACE_DEREFERENCE InterfaceDereference;
   PVOID Context;
   PPCMCIA_MODIFY_MEMORY_WINDOW ModifyMemoryWindow;
   PPCMCIA_SET_VPP SetVpp;
   PPCMCIA_IS_WRITE_PROTECTED IsWriteProtected;
} PCMCIA_INTERFACE_STANDARD, *PPCMCIA_INTERFACE_STANDARD;

//
// Definitions for PCMCIA_BUS_INTERFACE_STANDARD.
// This interface is obtained using GUID_PCMCIA_BUS_INTERFACE_STANDARD
// and is used for reading/writing to PCMCIA config. space
//

typedef
__drv_functionClass(PCMCIA_READ_CONFIG)
ULONG
PCMCIA_READ_CONFIG(
    __in_opt PVOID Context,
    __in ULONG WhichSpace,
    __out_bcount_full(Length) PUCHAR Buffer,
    __in ULONG Offset,
    __in ULONG Length
    );
typedef PCMCIA_READ_CONFIG *PPCMCIA_READ_CONFIG;

typedef
__drv_functionClass(PCMCIA_WRITE_CONFIG)
ULONG
PCMCIA_WRITE_CONFIG(
    __in_opt PVOID Context,
    __in ULONG WhichSpace,
    __in_bcount(Length) PUCHAR Buffer,
    __in ULONG Offset,
    __in ULONG Length
    );
typedef PCMCIA_WRITE_CONFIG *PPCMCIA_WRITE_CONFIG;

//
// WhichSpace for IRP_MN_READ_CONFIG/WRITE_CONFIG
// and PCMCIA_BUS_INTERFACE_STANDARD
//
typedef ULONG MEMORY_SPACE;

#define    PCCARD_PCI_CONFIGURATION_SPACE    0  // for cardbus cards
#define    PCCARD_ATTRIBUTE_MEMORY           1
#define    PCCARD_COMMON_MEMORY              2
#define    PCCARD_ATTRIBUTE_MEMORY_INDIRECT  3
#define    PCCARD_COMMON_MEMORY_INDIRECT     4

// Legacy support
//
#define    PCMCIA_CONFIG_SPACE               PCCARD_ATTRIBUTE_MEMORY

typedef struct _PCMCIA_BUS_INTERFACE_STANDARD {
   //
   // generic interface header
   //
   USHORT Size;
   USHORT Version;
   PVOID Context;
   PINTERFACE_REFERENCE InterfaceReference;
   PINTERFACE_DEREFERENCE InterfaceDereference;
   //
   // standard PCMCIA bus interfaces
   //
   PPCMCIA_READ_CONFIG ReadConfig;
   PPCMCIA_WRITE_CONFIG WriteConfig;
} PCMCIA_BUS_INTERFACE_STANDARD, *PPCMCIA_BUS_INTERFACE_STANDARD;

#endif

#ifdef __cplusplus
}
#endif
#endif

