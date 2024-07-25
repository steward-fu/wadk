// E100bexAdap.h: interface for the E100bexAdapter class.
//
//=============================================================================
//
// Compuware Corporation
// NuMega Lab
// 9 Townsend West
// Nashua, NH 03063  USA
//
// Copyright (c) 2004 Compuware Corporation. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States.
//
//=============================================================================
//
// Portions copied from Microsoft Windows 2000 DDK sample driver containing the
// following copyright
//
/****************************************************************************
** COPYRIGHT (C) 1994-1997 INTEL CORPORATION                               **
** DEVELOPED FOR MICROSOFT BY INTEL CORP., HILLSBORO, OREGON               **
** HTTP://WWW.INTEL.COM/                                                   **
** THIS FILE IS PART OF THE INTEL ETHEREXPRESS PRO/100B(TM) AND            **
** ETHEREXPRESS PRO/100+(TM) NDIS 5.0 MINIPORT SAMPLE DRIVER               **
****************************************************************************/


#if !defined(AFX_E100BEXADAP_H__8534F9A9_27F5_11D3_8F9E_00C04F7445B7__INCLUDED_)
#define AFX_E100BEXADAP_H__8534F9A9_27F5_11D3_8F9E_00C04F7445B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Characteristics.h"

//--------------------------------------
// Macros for flag and ref count operations
//--------------------------------------
#define MP_SET_FLAG(_F)			(m_Flags |= (_F))
#define MP_CLEAR_FLAG(_F)		(m_Flags &= ~(_F))
#define MP_CLEAR_FLAGS()		(m_Flags = 0)
#define MP_TEST_FLAG(_F)		((m_Flags & (_F)) != 0)
#define MP_TEST_FLAGS(_F)		((m_Flags & (_F)) == (_F))



#define ALIGN_16				16
//
// The driver should put the data(after Ethernet header) at 8-bytes boundary
//
#define ETH_DATA_ALIGN			8   // the data(after Ethernet header) should be 8-byte aligned
//
// Shift HW_RFD 0xA bytes to make Tcp data 8-byte aligned
// Since the ethernet header is 14 bytes long. If a packet is at 0xA bytes
// offset, its data(ethernet user data) will be at 8 byte boundary
//
#define HWRFD_SHIFT_OFFSET		0xA   // Shift HW_RFD 0xA bytes to make Tcp data 8-byte aligned
//
// The driver has to allocate more data then HW_RFD needs to allow shifting data
//
#define MORE_DATA_FOR_ALIGN		(ETH_DATA_ALIGN + HWRFD_SHIFT_OFFSET)

//--------------------------------------
// RFD (Receive Frame Descriptor)
//--------------------------------------
typedef struct _MP_RFD
{
	LIST_ENTRY				m_ListEntry;		// for KList
	KNdisPacket				NdisPacket;
	KNdisBuffer				NdisBuffer;
	KNdisSharedMemory		*pOriginalHwRfd;	// AllocVa and AllocPa
} MP_RFD, *PMP_RFD;


typedef struct _MP_FRAG_LIST
{
	ULONG NumberOfElements;
	ULONG_PTR Reserved;
	SCATTER_GATHER_ELEMENT Elements[NIC_MAX_PHYS_BUF_COUNT];
} MP_FRAG_LIST, *PMP_FRAG_LIST;


///////////////////////////////////////////////////////////////////////
// E100bexAdapter		Originally Generated by wizard
//
// This class defines member methods which are passed control on
// NDIS callbacks.
//
// The instances of the class are created automatically
// by KNDIS framework.
//
class E100bexAdapter : public KNdisMiniAdapter
{
	// NDIS handlers are called only by the 'friendly' wrapper class
	friend class KNdisWrapper<E100bexAdapter>;

	// Hardware access is delegated to 'friendly' E100bexCard class
	friend class E100bexCard;

// Construction/Destruction
public:
	SAFE_DESTRUCTORS
	E100bexAdapter();

protected:
	~E100bexAdapter();

// NDIS handlers
protected:

	// These methods MUST be implemented:
	VOID Halt(void);
	NDIS_STATUS Initialize(
		IN OUT KNdisMedium& Medium,
		IN KNdisConfig& Config
		);
	NDIS_STATUS Reset(OUT PBOOLEAN AddressingReset);

	// sending packets
	VOID SendPackets(
		IN	PPNDIS_PACKET			PacketArray,
		IN	UINT					NumberOfPackets
		);

	// checking for bad things
	BOOLEAN CheckForHang(void);

	// dealing with INTs
	VOID DisableInterrupt(void);
	VOID EnableInterrupt(void);
	VOID HandleInterrupt(void);
	VOID Isr(
		OUT PBOOLEAN				InterruptRecognized,
		OUT PBOOLEAN				QueueMiniportHandleInterrupt
		);

	// reclaiming packets
	VOID ReturnPacket(IN PNDIS_PACKET Packet);

	// processing shutdown, also a NDIS 5.1 handler
	VOID Shutdown(void);

	// asynchronous allocation complete
	VOID AllocateComplete(
		PVOID						VirtualAddress,
		PNDIS_PHYSICAL_ADDRESS		PhysicalAddress,
		ULONG						Length,
		PVOID						Context
		);

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
			IN NDIS_DEVICE_PNP_EVENT PnPEvent,
			IN PVOID				InformationBuffer,
			IN ULONG				InformationBufferLength
			);

	VOID CancelSendPackets(
			IN PVOID				CancelId
			);
#endif // NDIS51_MINIPORT

	// Standard OID handlers. This should be included in every adapter class declaration.
	#include	<KNdisOidDefs.h>

	// A list of supported OIDs. Inserted by the wizard
	static NDIS_OID sm_OID_GEN_SUPPORTED_LIST[];

// Helper methods
public:
	// These methods are callbacks required by KNdisSharedReceiveArea to initialize h/w RFD's
	VOID DescriptorInitialize(PHW_RFD pHwRfd, PNDIS_PHYSICAL_ADDRESS pPhysAddr);
	VOID DescriptorInvalidate(PHW_RFD pHwRfd);
	VOID DescriptorComplete(PHW_RFD pHwRfd, PNDIS_PHYSICAL_ADDRESS pPhysAddr);
	VOID DescriptorReclaim(PHW_RFD pHwRfd, PNDIS_PHYSICAL_ADDRESS pPhysAddr);

	PUCHAR AlignSharedMemory(PULONG pLowPhysAddr, ULONG Alignment, KNdisSharedMemory& ShMem);

protected:
	// Helper for our AllocateComplete
	VOID DescriptorInitializeStart(void);
	VOID DescriptorInitializeComplete(void);

	// Timer binding and callback function used in reset
	KNDIS_DECLARE_TIMERCALLBACK(E100bexAdapter, AsyncResetTimerCallback);
	VOID		AsyncResetTimerCallback(void);

	NDIS_STATUS ParseRegistryParameters(KNdisConfig& Config, ADAPTER_INFO& Ai);
	NDIS_STATUS EnableCard(void);
	VOID		DisableCard(void);
	NDIS_STATUS NICAllocAdapterMemory(void);
	VOID		DeleteSharedAdapterMemory(void);

	VOID		NICInitSend(void);
	NDIS_STATUS NICInitRecv(void);
	NDIS_STATUS NICSendPacket(
					IN  PD100SwTcb		pMpTcb,
					IN  PMP_FRAG_LIST	pFragList
		);
	NDIS_STATUS NICStartSend(IN  PD100SwTcb pMpTcb);
	BOOLEAN		StartReceiveUnit(void);

	BOOLEAN		ProcessRXInterrupt(void);
	NDIS_STATUS	ProcessTXInterrupt(void);
	BOOLEAN		FreeSendPacket(IN  PD100SwTcb pMpTcb);

	NDIS_STATUS MpSendPacket(KNdisPacket& Packet, BOOLEAN bFromQueue);
	ULONG		CopyPacketToBuffer(
					KNdisBuffer CurrentBuffer,
					PCOALESCE   pMpTxBuf
					);
	VOID		DumpHwRfd(PHW_RFD pHwRfd);

// Data members
private:

	// Card object which we use to manipulate the hardware
	E100bexCard	*		m_pCard;

	// Holds the interrupt object for this adapter.
	KNdisInterrupt		m_Interrupt;

	// CSR range accessors
	KNdisIoRange		m_CSRIoRange;
	KNdisMemoryRange	m_CSRMemoryRange;

	// Holds the timer structure used for Async Resets
	KNdisTimer			m_Timer;

	// Encapsulates shared memory for receive structure
	KNdisSharedMemory*	m_pRxShMem;

	// Encapsulates receive frame descriptors, buffer and packet pools for Rx
	typedef KNdisSharedReceiveArea< E100bexAdapter, HW_RFD > E100bexReceiveArea;
	// By changing the 2nd template parameter of KNdisSharedReceiveArea<> to
	// KNdisRxAreaNoAsync, asynchronous shared memory allocation support is removed.
	E100bexReceiveArea*	m_pRxArea;

	// Spin Lock
	KNdisSpinLock		m_Lock;
	KNdisSpinLock		m_SendLock;
	KNdisSpinLock		m_RcvLock;

	USHORT				m_AiThreshold;    // 'Threshold', Transmit Threshold

	NDIS_MEDIA_STATE	m_LinkIsActive;

	ETHERNET_ADDRESS	m_AiNodeAddress;

	// Fields for various D100 specific parameters
	UINT				m_NumBuffers;     // 'NumCoalese'
	UINT				m_NumRfd;         // 'NumRfd'
	UINT				m_CurrNumRfd;     // OID_GEN_RECEIVE_BUFFER_SPACE need to report this
	UINT				m_RfdShrinkCount;
	UINT				m_MaxNumRfd;
	UINT				m_NumTbdPerTcb;   // 'NumTbdPerTcb'
	UINT				m_NumTbd;         // Total number of TBDs
	UINT				m_RegNumTcb;      // number of transmit control blocks the registry says
	UINT				m_NumTcb;         // 'NumTcb' (number of tcb we are actually using (usually RegNumTcb+1))

	// command unit status flags
	BOOLEAN				m_TransmitIdle;
	BOOLEAN				m_ResumeWait;
	ULONG				m_Flags;

	// Transmit memory structures.
	KNdisBufferPool		m_SendBufferPool;
	PUCHAR				m_pMpTcbMem;
	UINT				m_MpTcbMemSize;
	PUCHAR				m_MpTxBufMem;
	KNdisSharedMemory*	m_pHwSendMem;
	// Memory for 82557/82558 Control Structures. (note: VOLATILE memory area)
	KNdisSharedMemory*	m_pHwMiscMem;

	// Map into a local array to avoid overflow in the Tcb if the virtual
	// buffer is made of too many physical buffers. This is a temporary
	// scratch area.
	NDIS_PHYSICAL_ADDRESS_UNIT m_pUnits[NIC_MAX_PHYS_BUF_COUNT];

	// Keep a list of free transmit descriptors.
	KList<D100SwTcb>	m_TxCBList;
	// To send a packet, dequeue one from m_TxCBList and add into m_ActiveChainList
	// When it's done, move descriptor back to m_TxCBList
	KList<D100SwTcb>	m_ActiveChainList;

	// Keep a coalesce buffer list around for those times when there are too many
	// physical mappings.
	KList<COALESCE>		m_SendBufList;

	// Queue of "pending" Tx packets
	LONG				m_nCancelSend;
	KNdisPacketList		m_SendWaitQueue;

	// Needed for multicast address changes during resets
	UCHAR				m_MCList[NIC_MAX_MCAST_LIST][ETH_LENGTH_OF_ADDRESS];
	UINT				m_MCAddressCount;

	// place to hold the revision id of the d100 chip (read from PCI config)
	UCHAR				m_AiRevID;
	USHORT				m_AiSubVendor;
	USHORT				m_AiSubDevice;

	// NDIS_MAC_OPTION_xxx bit set
	ULONG				m_uMacOptions;

	// Statistics. Based on wizard's input only a basic or specific or
	// custom stats can be inserted
	KNdisStats<ERR_COUNT_STRUC>		m_Stats;

	// Power Management State
#if KNDIS_PNP_AWARE
	KNdisPnpMode<E100bexAdapter>	m_Power;
#endif

#if DBG
	USHORT				m_txsent;
	USHORT				m_txind;
	UINT				m_sdebugindex;
#endif

	HW_RFD* m_pPrevHwDesc;
};


#endif // !defined(AFX_E100BEXADAP_H__8534F9A9_27F5_11D3_8F9E_00C04F7445B7__INCLUDED_)
 