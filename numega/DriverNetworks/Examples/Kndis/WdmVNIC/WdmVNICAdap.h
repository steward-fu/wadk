//////////////////////////////////////////////////////////////////////
// WdmVNICAdap.h: interface for the WdmVNICAdapter class.
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
//
// Generated by DriverNetworks Wizard on	Friday, June 02, 2000
//

#if !defined(AFX_WDMVNICADAP_H__8534F9A9_27F5_11D3_8F9E_00C04F7445B7__INCLUDED_)
#define AFX_WDMVNICADAP_H__8534F9A9_27F5_11D3_8F9E_00C04F7445B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BusDeviceSim.h"

// TODO:	Include your .h files as needed

#define OID_CUSTOM_RW_ULONG			0xFF123400
#define OID_CUSTOM_RO_ULONG			0xFF123401
#define OID_CUSTOM_MAC_ADDRESS		0xFF123402
#define OID_CUSTOM_STRING			0xFF123403

// custom OIDs
KNDIS_OID_PROPERTY(OID_CUSTOM_MAC_ADDRESS, UCHAR, true)
KNDIS_OID_PROPERTY(OID_CUSTOM_STRING, UCHAR, true)

#pragma pack(1)

//-------------------------------------------------------------------------
// Ethernet Frame Sizes
//-------------------------------------------------------------------------
const USHORT	ETHERNET_ADDRESS_LENGTH         =	6;
const USHORT	ETHERNET_HEADER_SIZE			=	14;
const USHORT	MINIMUM_ETHERNET_PACKET_SIZE	=	60;
const USHORT	MAXIMUM_ETHERNET_PACKET_SIZE    =	1514;
const USHORT	RCB_BUFFER_SIZE					=	1520; // 0x5F0

//-------------------------------------------------------------------------
// Ethernet Frame Structure
//-------------------------------------------------------------------------
//- Ethernet 6-byte Address
typedef struct _ETH_ADDRESS_STRUC {
    UCHAR       EthNodeAddress[ETHERNET_ADDRESS_LENGTH];
} ETH_ADDRESS_STRUC, *PETH_ADDRESS_STRUC;


//- Ethernet 14-byte Header
typedef struct _ETH_HEADER_STRUC {
    UCHAR       Destination[ETHERNET_ADDRESS_LENGTH];
    UCHAR       Source[ETHERNET_ADDRESS_LENGTH];
    USHORT      TypeLength;
} ETH_HEADER_STRUC, *PETH_HEADER_STRUC;


typedef struct _ETH_RX_BUFFER_STRUC {
    ETH_HEADER_STRUC    RxMacHeader;
    UCHAR               RxBufferData[(RCB_BUFFER_SIZE - sizeof(ETH_HEADER_STRUC))];
} ETH_RX_BUFFER_STRUC, *PETH_RX_BUFFER_STRUC;

#pragma pack()


// Forward declaration
class WdmVNICAdapter;


///////////////////////////////////////////////////////////////////////
// NDIS_WORK_ITEM_CTX		context structure for Ndis Work Item 
//
typedef struct _NDIS_WORK_ITEM_CTX
{
	NDIS_WORK_ITEM		m_WorkItem;
	PNDIS_PACKET		m_Packet;
	WdmVNICAdapter*		m_pAdapter;

} NDIS_WORK_ITEM_CTX, *PNDIS_WORK_ITEM_CTX;



///////////////////////////////////////////////////////////////////////
// WdmVNICAdapter		Generated by wizard 
//
// This class defines member methods which are passed control on
// NDIS callbacks. 
//
// The instances of the class are created automatically
// by KNDIS framework. The class expose no public methods
// since its methods are called only from the "friendly"
// KNdisWrapper class.
//
class WdmVNICAdapter : public KNdisMiniAdapter
{
	struct _HW_RFD; // Forward

	struct IRP_CONTEXT : public KNdisHeapClient<IRP_CONTEXT> {
		WdmVNICAdapter*	Adapter;	// should be present
		union _type {					// the rest is optional
			PNDIS_PACKET	m_Packet;		// for Tx
			struct _HW_RFD*	m_pHwRfd;		// for Rx
			PVOID Something;				// Dummy pointer used in intialization
			//... Add more here if needed ...
		} type;
		inline IRP_CONTEXT(WdmVNICAdapter* a, PVOID cxt=NULL) : Adapter(a) { type.Something=cxt; }
	}; 

	//-------------------------------------------------------------------------
	// Hardware Receive Frame Descriptor (RFD)
	//-------------------------------------------------------------------------
	// This struct is declared as a public nested type so that 
	// KNdisSharedReceiveArea<A> can reference A::HW_RFD
	typedef struct _HW_RFD {
		PIRP				m_pIrp;				// Pointer to IRP associated with this HW_RFD
		IRP_CONTEXT			m_IrpContext;		// Context Structure for IRP
		LIST_ENTRY			m_ListEntry;		// List entry for m_RxIrpList
#if KNDIS_W9X_COMPATIBLE
		LIST_ENTRY			m_LE;				// List entry for m_RxIndicateQueue
#endif // KNDIS_W9X_COMPATIBLE
		ULONG				m_RfdActualCount;	// Number Of Bytes Received
		ULONG				m_RfdSize;			// Number Of Bytes In RFD
		ETH_RX_BUFFER_STRUC m_RfdBuffer;		// Data buffer for NDIS buffer
		static ULONG GetBufferLength()			// Required by KNdisReceiveArea
			{ return MAXIMUM_ETHERNET_PACKET_SIZE; }
		static ULONG GetBufferOffset()			// Required by KNdisReceiveArea
			{ return FIELD_OFFSET(HW_RFD, m_RfdBuffer); }
	} HW_RFD, *PHW_RFD;

	SAFE_DESTRUCTORS
public:
	WdmVNICAdapter();

protected:
	~WdmVNICAdapter();

	// These methods MUST be implemented:
	NDIS_STATUS Initialize
				(IN OUT KNdisMedium& Medium, IN KNdisConfig& Config);
    VOID Halt(VOID);
    NDIS_STATUS Reset(OUT PBOOLEAN AddressingReset);

	// Optional handlers in accord with the content of Characteristics.h file.
	// The handlers are called from the following "friendly" class:
	friend class KNdisWrapper<WdmVNICAdapter>;

	// sending packets
    NDIS_STATUS Send(IN	PNDIS_PACKET Packet, IN	UINT Flags);
	NDIS_STATUS TxPacket(IN PNDIS_PACKET Packet);
	NTSTATUS CompletionTxRoutine(PIRP pIrp, IRP_CONTEXT* Context);

	// checking for bad things
    BOOLEAN CheckForHang();
		
	// recliaming packets
	VOID ReturnPacket(IN PNDIS_PACKET Packet);
	NTSTATUS CompletionRxRoutine(PIRP pIrp, IRP_CONTEXT* Context);
	VOID CompleteHwRfd(PHW_RFD pRfd);
	static VOID OnReturnPacketX(PNDIS_WORK_ITEM pWorkItem, PVOID pContext)
	{
		PNDIS_WORK_ITEM_CTX pCtx = (PNDIS_WORK_ITEM_CTX) pContext;
		ASSERT(pCtx);
		pCtx->m_pAdapter->OnReturnPacket(pCtx);			
	}

	VOID OnReturnPacket(PNDIS_WORK_ITEM_CTX pCtx);	


#if KNDIS_W9X_COMPATIBLE
	VOID IndicateCallback(void);
	KNDIS_DECLARE_TIMERCALLBACK(WdmVNICAdapter, IndicateCallback);
#endif // KNDIS_W9X_COMPATIBLE

	VOID StartReceiveUnit(void);

	// processing shutdown
	VOID Shutdown(VOID);

	// OID processing (via OID_MAP)
	NDIS_STATUS QueryInformation(
			IN	NDIS_OID				Oid,
			IN	PVOID					InformationBuffer,
			IN	ULONG					InformationBufferLength,
			OUT PULONG					BytesWritten,
			OUT PULONG					BytesNeeded
			);
	NDIS_STATUS SetInformation(
			IN	NDIS_OID				Oid,
			IN	PVOID					InformationBuffer,
			IN	ULONG					InformationBufferLength,
			OUT PULONG					BytesRead,
			OUT PULONG					BytesNeeded
			);

	// NDIS 5.1 Handlers
#if defined(NDIS51_MINIPORT)
	VOID PnPEventNotify(
			IN NDIS_DEVICE_PNP_EVENT  PnPEvent,
			IN PVOID  InformationBuffer,
			IN ULONG  InformationBufferLength
		    );

	VOID CancelSendPackets(		
			IN PVOID	CancelId
			);

#endif // NDIS51_MINIPORT

	// Standard OID hanlders. This should be included in every adapter class declaration.
	#include	<KNdisOidDefs.h>

	DECLARE_OID_HANDLERS(OID_CUSTOM_RW_ULONG)
	DECLARE_OID_HANDLERS(OID_CUSTOM_RO_ULONG)
	DECLARE_OID_HANDLERS(OID_CUSTOM_MAC_ADDRESS)
	DECLARE_OID_HANDLERS(OID_CUSTOM_STRING)

	// A list of supported OIDs. 
	static NDIS_OID sm_OID_GEN_SUPPORTED_LIST[];

	// A list of custom GUID OIDs (WMI)
	static const NDIS_GUID sm_OID_GEN_SUPPORTED_GUIDS[];

// Helper methods
public:
	// These methods are callbacks required by KNdisSharedReceiveArea to initialize h/w RFD's
	VOID DescriptorInitialize(PHW_RFD pHwDesc, PNDIS_PHYSICAL_ADDRESS pPhysAddr);
	VOID DescriptorInvalidate(PHW_RFD pHwDesc);
	VOID DescriptorComplete(PHW_RFD pHwDesc, PNDIS_PHYSICAL_ADDRESS pPhysAddr);
	VOID DescriptorReclaim(PHW_RFD pHwDesc, PNDIS_PHYSICAL_ADDRESS pPhysAddr);
	VOID DumpHwRfd(PHW_RFD p);

private:
	// Your custom data member go in here
	PDEVICE_OBJECT		m_PhysicalDeviceObject;
	PDEVICE_OBJECT		m_TopOfStackDeviceObject;

	BOOLEAN				m_HaltFlag;
	KNdisEvent			m_RxIdleEvent;
	KNdisCounter		m_RxIrpsOutstanding;

	CBusDeviceSim		m_BusDevice;

	ETHERNET_ADDRESS	m_CurrentAddress;
	ETHERNET_ADDRESS	m_PermanentAddress;

	// NDIS_PACKET_TYPE_xxx bit set 
	ULONG				m_uPacketFilter;

	// NDIS_MAC_OPTION_xxx bit set
	ULONG				m_uMacOptions;
		
	// Queue of "pending" Tx packets. Serialized miniports might use
	// this queue to keep track of "pending" packets. Deserialized miniports 
	// have to maintain  an internal queue to cope with low resource situations
	// since NDIS doesn't take care of that in this case.
	KNdisInterlockedPacketList	m_TxQueue;

#if KNDIS_W9X_COMPATIBLE
	// NDIS Timer used for indicating receive packets (see below)
	KNdisTimer m_Timer;

	// Queue of HW_RFDs containing Rx packets waiting to be indicated. This is necessary for
	// NDIS_WDM drivers on 9x platforms, since it is only safe to call NDIS on an NDIS thread.
	// This means that we cannot indicate the packet in the context of the Rx completion
	// routine, since it is not an NDIS thread.  Instead we will queue the packet and indicate
	// it using an NDIS timer callback.
	KNdisInterlockedList<HW_RFD>		m_RxIndicateQueue;
#endif // KNDIS_W9X_COMPATIBLE

	// IRP pool that will be used to cycle IRPs to our lower device for send 
	// NOTE: Use KNDIS_WDM_STRICT=1 to turn on KIrpPool which is NdisTest compliant
	KIrpPool<KGenericIrpBuilder, KNdisSpinLock>			m_TxIrpPool;

	// Usually, need a context block associated with a submitted irp.
	// We use a fast heap (lookaside list-based) for allocating those blocks.
	// TODO: add new fields to address your device specifics

	// Fast Context storage (lookaside list-based)
	KNdisHeap<IRP_CONTEXT>				m_ContextHeap;

	// Receive Area for incomming network packets
	KNdisSystemReceiveArea< WdmVNICAdapter, HW_RFD >*	m_pRxArea;

	// List of HW_RFDs each containing a receive IRP.  Used in StartRecieveUnit() to get all
	// of the IRPs started on the device and for cleanup in Halt() to wait until all of the IRPs
	// are completed
	KNdisList <HW_RFD>					m_RxIrpList;

	// Statistics. Included are the statistics defined by NDIS statistics OIDs

	KNdisStatsGen						m_GenStats;		// Mandatory GENeral stats
	// KNdisStatsGenEx					m_GenStats;		// Optional GENeral stats
	KNdisStatsEx<WDMVNIC_MEDIUM_TYPE>	m_MediumStats;	// Medium-specific stats

	// Power Management State
#if KNDIS_PNP_AWARE
	KNdisPnpMode<WdmVNICAdapter>		m_Power;
#endif

	KNdisBufferPool						m_RxBufPool;

	// custom OID variables
	ULONG								m_nCustomSet;
};



#endif // !defined(AFX_WDMVNICADAP_H__8534F9A9_27F5_11D3_8F9E_00C04F7445B7__INCLUDED_)
 