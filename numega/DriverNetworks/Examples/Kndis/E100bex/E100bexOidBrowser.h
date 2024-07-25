// E100bexOidBrowser.h
//
//=============================================================================
//
// Compuware Corporation
// NuMega Lab
// 9 Townsend West
// Nashua, NH 03060  USA
//
// Copyright (c) 2001 Compuware Corporation. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States.
//
//=============================================================================
// Contains Signatures of OID handler members of E100bexAdapter class.
//
// This file is generated only for convenience and is NOT #included
// in any of the .cpp files of the Skeleton project.
//
// This file is included in the "OID Handlers" sub-project found
// in the MSDev IDE Workspace of your driver project. It allows to
// easily navigate to the OID handlers using the IDE Class Viewer.
//
// *** DO NOT EDIT THIS FILE ***
//
#ifdef __COMMENT_ONLY__
class E100bexAdapter 
{
protected:
NDIS_HARDWARE_STATUS getOID_GEN_HARDWARE_STATUS(void);
ULONG  getOID_802_3_XMIT_ONE_COLLISION(void);
ULONG  getOID_802_3_XMIT_MORE_COLLISIONS(void);
ULONG  getOID_802_3_RCV_ERROR_ALIGNMENT(void);
NDIS_STATUS  getOID_802_3_MULTICAST_LIST
(ETHERNET_ADDRESS *, IN OUT PULONG ByteCount, OUT PULONG BytesNeeded);
ULONG  getOID_802_3_MAXIMUM_LIST_SIZE(void);
ETHERNET_ADDRESS   getOID_802_3_CURRENT_ADDRESS(void);
ETHERNET_ADDRESS   getOID_802_3_PERMANENT_ADDRESS(void);
ULONG  getOID_GEN_RCV_NO_BUFFER(void);
ULONG  getOID_GEN_RCV_ERROR(void);
ULONG  getOID_GEN_RCV_OK(void);
ULONG  getOID_GEN_XMIT_ERROR(void);
ULONG  getOID_GEN_XMIT_OK(void);
ULONG  getOID_GEN_MAXIMUM_SEND_PACKETS(void);
NDIS_MEDIA_STATE  getOID_GEN_MEDIA_CONNECT_STATUS(void);
ULONG  getOID_GEN_MAC_OPTIONS(void);
ULONG  getOID_GEN_MAXIMUM_TOTAL_SIZE(void);
USHORT getOID_GEN_DRIVER_VERSION(void);
ULONG  getOID_GEN_CURRENT_LOOKAHEAD(void);
ULONG  getOID_GEN_CURRENT_PACKET_FILTER(void);
NDIS_STATUS  getOID_GEN_VENDOR_DESCRIPTION
(char* pDesc, IN OUT PULONG ByteCount, OUT PULONG BytesNeeded);
ULONG  getOID_GEN_VENDOR_ID(void);
ULONG getOID_GEN_VENDOR_DRIVER_VERSION();
ULONG  getOID_GEN_RECEIVE_BLOCK_SIZE(void);
ULONG  getOID_GEN_TRANSMIT_BLOCK_SIZE(void);
ULONG  getOID_GEN_RECEIVE_BUFFER_SPACE(void);
ULONG  getOID_GEN_TRANSMIT_BUFFER_SPACE(void);
ULONG  getOID_GEN_LINK_SPEED(void);
ULONG  getOID_GEN_MAXIMUM_FRAME_SIZE(void);
ULONG  getOID_GEN_MAXIMUM_LOOKAHEAD(void);
NDIS_STATUS  getOID_GEN_MEDIA_SUPPORTED
(NDIS_MEDIUM* pMedium, PULONG ByteCount, OUT PULONG BytesNeeded) ;
NDIS_STATUS  getOID_GEN_MEDIA_IN_USE
(NDIS_MEDIUM* pMedium, PULONG ByteCount, OUT PULONG BytesNeeded) ;
NDIS_STATUS  setOID_802_3_MULTICAST_LIST
(ETHERNET_ADDRESS *, PULONG ByteCount, OUT PULONG BytesNeeded) ;
NDIS_STATUS  setOID_GEN_PROTOCOL_OPTIONS(PULONG Param);
NDIS_STATUS  setOID_GEN_CURRENT_PACKET_FILTER(PULONG Param);
NDIS_STATUS  setOID_GEN_CURRENT_LOOKAHEAD(PULONG pLookahead);

NDIS_STATUS getOID_PNP_QUERY_POWER(PNDIS_DEVICE_POWER_STATE DesiredState);
NDIS_STATUS setOID_PNP_SET_POWER(PNDIS_DEVICE_POWER_STATE DesiredState);
};
#endif // __COMMENT_ONLY__

