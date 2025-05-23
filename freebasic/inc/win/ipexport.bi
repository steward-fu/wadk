'' FreeBASIC binding for mingw-w64-v4.0.4
''
'' based on the C header files:
''   DISCLAIMER
''   This file has no copyright assigned and is placed in the Public Domain.
''   This file is part of the mingw-w64 runtime package.
''
''   The mingw-w64 runtime package and its code is distributed in the hope that it 
''   will be useful but WITHOUT ANY WARRANTY.  ALL WARRANTIES, EXPRESSED OR 
''   IMPLIED ARE HEREBY DISCLAIMED.  This includes but is not limited to 
''   warranties of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
''
'' translated to FreeBASIC by:
''   FreeBASIC development team

#pragma once

#include once "in6addr.bi"
#include once "inaddr.bi"

const IP_EXPORT_INCLUDED = 1
type IPAddr as ULONG
type IPMask as ULONG
type IP_STATUS as ULONG
type IPv6Addr as IN6_ADDR

type IP_OPTION_INFORMATION
	Ttl as UCHAR
	Tos as UCHAR
	Flags as UCHAR
	OptionsSize as UCHAR
	OptionsData as PUCHAR
end type

type PIP_OPTION_INFORMATION as IP_OPTION_INFORMATION ptr

#ifdef __FB_64BIT__
	type IP_OPTION_INFORMATION32
		Ttl as UCHAR
		Tos as UCHAR
		Flags as UCHAR
		OptionsSize as UCHAR
		OptionsData as UCHAR ptr
	end type

	type PIP_OPTION_INFORMATION32 as IP_OPTION_INFORMATION32 ptr
#endif

type ICMP_ECHO_REPLY
	Address as IPAddr
	Status as ULONG
	RoundTripTime as ULONG
	DataSize as USHORT
	Reserved as USHORT
	Data as PVOID
	Options as IP_OPTION_INFORMATION
end type

type PICMP_ECHO_REPLY as ICMP_ECHO_REPLY ptr

#ifdef __FB_64BIT__
	type ICMP_ECHO_REPLY32
		Address as IPAddr
		Status as ULONG
		RoundTripTime as ULONG
		DataSize as USHORT
		Reserved as USHORT
		Data as any ptr
		Options as IP_OPTION_INFORMATION32
	end type

	type PICMP_ECHO_REPLY32 as ICMP_ECHO_REPLY32 ptr
#endif

type ARP_SEND_REPLY
	DestAddress as IPAddr
	SrcAddress as IPAddr
end type

type PARP_SEND_REPLY as ARP_SEND_REPLY ptr

type TCP_RESERVE_PORT_RANGE
	UpperRange as USHORT
	LowerRange as USHORT
end type

type PTCP_RESERVE_PORT_RANGE as TCP_RESERVE_PORT_RANGE ptr
const MAX_ADAPTER_NAME = 128

type _IP_ADAPTER_INDEX_MAP
	Index as ULONG
	Name as wstring * 128
end type

type IP_ADAPTER_INDEX_MAP as _IP_ADAPTER_INDEX_MAP
type PIP_ADAPTER_INDEX_MAP as _IP_ADAPTER_INDEX_MAP ptr

type _IP_INTERFACE_INFO
	NumAdapters as LONG
	Adapter(0 to 0) as IP_ADAPTER_INDEX_MAP
end type

type IP_INTERFACE_INFO as _IP_INTERFACE_INFO
type PIP_INTERFACE_INFO as _IP_INTERFACE_INFO ptr

type _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS
	NumAdapters as ULONG
	Address(0 to 0) as IPAddr
end type

type IP_UNIDIRECTIONAL_ADAPTER_ADDRESS as _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS
type PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS as _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS ptr

type _IP_ADAPTER_ORDER_MAP
	NumAdapters as ULONG
	AdapterOrder(0 to 0) as ULONG
end type

type IP_ADAPTER_ORDER_MAP as _IP_ADAPTER_ORDER_MAP
type PIP_ADAPTER_ORDER_MAP as _IP_ADAPTER_ORDER_MAP ptr

type _IP_MCAST_COUNTER_INFO
	InMcastOctets as ULONG64
	OutMcastOctets as ULONG64
	InMcastPkts as ULONG64
	OutMcastPkts as ULONG64
end type

type IP_MCAST_COUNTER_INFO as _IP_MCAST_COUNTER_INFO
type PIP_MCAST_COUNTER_INFO as _IP_MCAST_COUNTER_INFO ptr

type _IPV6_ADDRESS_EX
	sin6_port as USHORT
	sin6_flowinfo as ULONG
	sin6_addr(0 to 7) as USHORT
	sin6_scope_id as ULONG
end type

type IPV6_ADDRESS_EX as _IPV6_ADDRESS_EX
type PIPV6_ADDRESS_EX as _IPV6_ADDRESS_EX ptr
const IP_STATUS_BASE = 11000
const IP_SUCCESS = 0
const IP_BUF_TOO_SMALL = IP_STATUS_BASE + 1
const IP_DEST_NET_UNREACHABLE = IP_STATUS_BASE + 2
const IP_DEST_HOST_UNREACHABLE = IP_STATUS_BASE + 3
const IP_DEST_PROT_UNREACHABLE = IP_STATUS_BASE + 4
const IP_DEST_PORT_UNREACHABLE = IP_STATUS_BASE + 5
const IP_NO_RESOURCES = IP_STATUS_BASE + 6
const IP_BAD_OPTION = IP_STATUS_BASE + 7
const IP_HW_ERROR = IP_STATUS_BASE + 8
const IP_PACKET_TOO_BIG = IP_STATUS_BASE + 9
const IP_REQ_TIMED_OUT = IP_STATUS_BASE + 10
const IP_BAD_REQ = IP_STATUS_BASE + 11
const IP_BAD_ROUTE = IP_STATUS_BASE + 12
const IP_TTL_EXPIRED_TRANSIT = IP_STATUS_BASE + 13
const IP_TTL_EXPIRED_REASSEM = IP_STATUS_BASE + 14
const IP_PARAM_PROBLEM = IP_STATUS_BASE + 15
const IP_SOURCE_QUENCH = IP_STATUS_BASE + 16
const IP_OPTION_TOO_BIG = IP_STATUS_BASE + 17
const IP_BAD_DESTINATION = IP_STATUS_BASE + 18
const IP_DEST_NO_ROUTE = IP_STATUS_BASE + 2
const IP_DEST_ADDR_UNREACHABLE = IP_STATUS_BASE + 3
const IP_DEST_PROHIBITED = IP_STATUS_BASE + 4
const IP_DEST_PORT_UNREACHABLE = IP_STATUS_BASE + 5
const IP_HOP_LIMIT_EXCEEDED = IP_STATUS_BASE + 13
const IP_REASSEMBLY_TIME_EXCEEDED = IP_STATUS_BASE + 14
const IP_PARAMETER_PROBLEM = IP_STATUS_BASE + 15
const IP_DEST_UNREACHABLE = IP_STATUS_BASE + 40
const IP_TIME_EXCEEDED = IP_STATUS_BASE + 41
const IP_BAD_HEADER = IP_STATUS_BASE + 42
const IP_UNRECOGNIZED_NEXT_HEADER = IP_STATUS_BASE + 43
const IP_ICMP_ERROR = IP_STATUS_BASE + 44
const IP_DEST_SCOPE_MISMATCH = IP_STATUS_BASE + 45
const IP_ADDR_DELETED = IP_STATUS_BASE + 19
const IP_SPEC_MTU_CHANGE = IP_STATUS_BASE + 20
const IP_MTU_CHANGE = IP_STATUS_BASE + 21
const IP_UNLOAD = IP_STATUS_BASE + 22
const IP_ADDR_ADDED = IP_STATUS_BASE + 23
const IP_MEDIA_CONNECT = IP_STATUS_BASE + 24
const IP_MEDIA_DISCONNECT = IP_STATUS_BASE + 25
const IP_BIND_ADAPTER = IP_STATUS_BASE + 26
const IP_UNBIND_ADAPTER = IP_STATUS_BASE + 27
const IP_DEVICE_DOES_NOT_EXIST = IP_STATUS_BASE + 28
const IP_DUPLICATE_ADDRESS = IP_STATUS_BASE + 29
const IP_INTERFACE_METRIC_CHANGE = IP_STATUS_BASE + 30
const IP_RECONFIG_SECFLTR = IP_STATUS_BASE + 31
const IP_NEGOTIATING_IPSEC = IP_STATUS_BASE + 32
const IP_INTERFACE_WOL_CAPABILITY_CHANGE = IP_STATUS_BASE + 33
const IP_DUPLICATE_IPADD = IP_STATUS_BASE + 34
const IP_NO_FURTHER_SENDS = IP_STATUS_BASE + 35
const IP_GENERAL_FAILURE = IP_STATUS_BASE + 50
const MAX_IP_STATUS = IP_GENERAL_FAILURE
const IP_PENDING = IP_STATUS_BASE + 255
const IP_FLAG_DF = &h2
const IP_OPT_EOL = 0
const IP_OPT_NOP = 1
const IP_OPT_SECURITY = &h82
const IP_OPT_LSRR = &h83
const IP_OPT_SSRR = &h89
const IP_OPT_RR = &h7
const IP_OPT_TS = &h44
const IP_OPT_SID = &h88
const IP_OPT_ROUTER_ALERT = &h94
const MAX_OPT_SIZE = 40
