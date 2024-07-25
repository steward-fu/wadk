// file generated by the wizard

#ifndef __CHARACTERISTICS_H__
#define __CHARACTERISTICS_H__

// Optional NDIS MINIPORT handlers this driver supports
KNDIS_MINIPORT_HANDLER(NmIntAdapter, Send)
KNDIS_MINIPORT_HANDLER(NmIntAdapter, ReturnPacket)
KNDIS_MINIPORT_HANDLER(NmIntAdapter, TransferData)

// Optional NDIS PROTOCOL handlers this driver supports
KNDIS_PROTOCOL_HANDLER(NmIntBinding, SendComplete)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, TransferDataComplete)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, Receive)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, ReceiveComplete)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, ReceivePacket)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, Status)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, StatusComplete)
KNDIS_PROTOCOL_HANDLER(NmIntBinding, PnpEvent)

// Ethernet Frame Sizes
const USHORT	ETHERNET_ADDRESS_LENGTH         =	6;
const USHORT	ETHERNET_HEADER_SIZE			=	14;
const USHORT	MINIMUM_ETHERNET_PACKET_SIZE	=	60;
const USHORT	MAXIMUM_ETHERNET_PACKET_SIZE    =	1514;

const USHORT	MAX_MULTICAST_ADDRESSES	= 32;
const UCHAR		MAX_ARRAY_SEND_PACKETS	= 8;
const ULONG		NMINT_VERSION_MAJOR		= 1;
const ULONG		NMINT_VERSION_MINOR		= 0;

// Uncomment this if desired for the following behavior:
// generates a unique MAC address for virtual adapters and
// puts the underlying NIC into promiscuous mode and performs
// packet decoding in the receive path
#define GENERATE_MAC_ADDRESS


#endif // __CHARACTERISTICS_H__
 