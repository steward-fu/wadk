ARC_RECEIVE_BUFFERS equ 64
ARC_BUFFER_LIST STRUC
	Buffer		PVOID ?
	_Size		UINT ?
	BytesLeft	UINT ?
	Next		PVOID ?
ARC_BUFFER_LIST ENDS
PARC_BUFFER_LIST TYPEDEF PTR ARC_BUFFER_LIST
ARCNET_ADDRESS_LEN	equ 1
ARC_PROTOCOL_HEADER STRUC
	SourceId	UCHAR ARCNET_ADDRESS_LEN dup(?)	; Source Address
	DestId		UCHAR ARCNET_ADDRESS_LEN dup(?)	; Destination Address
	ProtId		UCHAR ?							; Protocol ID
ARC_PROTOCOL_HEADER ENDS
PARC_PROTOCOL_HEADER TYPEDEF PTR ARC_PROTOCOL_HEADER
ARC_PACKET_HEADER STRUC
	ProtHeader	ARC_PROTOCOL_HEADER<>	;		 	// Protocol header
	USHORT					FrameSequence;		// Frame sequence Number
	UCHAR					SplitFlag;			// Split flag
	UCHAR					LastSplitFlag;		// Split Flag for the last frame
	UCHAR					FramesReceived;		// Frames in This Packet
ARC_PACKET_HEADER ENDS
PARC_PACKET_HEADER TYPEDEF PTR ARC_PACKET_HEADER

typedef struct _ARC_PACKET
{
	ARC_PACKET_HEADER		Header;				// Information about the packet
	struct _ARC_PACKET *	Next;				// Next packet in use by filter
	ULONG					TotalLength;
	BOOLEAN					LastFrame;
	PARC_BUFFER_LIST		FirstBuffer;
	PARC_BUFFER_LIST		LastBuffer;
	NDIS_PACKET				TmpNdisPacket;
} ARC_PACKET, * PARC_PACKET;


#define ARC_PROTOCOL_HEADER_SIZE		(sizeof(ARC_PROTOCOL_HEADER))
#define ARC_MAX_FRAME_SIZE				504
#define ARC_MAX_ADDRESS_IDS				256
#define ARC_MAX_FRAME_HEADER_SIZE		6
#define ARC_MAX_PACKET_SIZE				576


//
// Check whether an address is broadcast.
//

#define ARC_IS_BROADCAST(Address) \
	(BOOLEAN)(!(Address))


//
// An action routine type.	The routines are called
// when a filter type is set for the first time or
// no more bindings require a particular type of filter.
//
// NOTE: THIS ROUTINE SHOULD ASSUME THAT THE LOCK IS ACQUIRED.
//
typedef
NDIS_STATUS
(*ARC_FILTER_CHANGE)(
	IN	UINT					OldFilterClasses,
	IN	UINT					NewFilterClasses,
	IN	NDIS_HANDLE				MacBindingHandle,
	IN	PNDIS_REQUEST			NdisRequest,
	IN	BOOLEAN					Set
	);


//
// This action routine is called when the mac requests a close for
// a particular binding *WHILE THE BINDING IS BEING INDICATED TO
// THE PROTOCOL*.  The filtering package can't get rid of the open
// right away.  So this routine will be called as soon as the
// NdisIndicateReceive returns.
//
// NOTE: THIS ROUTINE SHOULD ASSUME THAT THE LOCK IS ACQUIRED.
//
typedef
VOID
(*ARC_DEFERRED_CLOSE)(
	IN	NDIS_HANDLE				MacBindingHandle
	);

typedef ULONG MASK,*PMASK;

//
// Maximum number of opens the filter package will support.  This is
// the max so that bit masks can be used instead of a spaghetti of
// pointers.
//
#define ARC_FILTER_MAX_OPENS (sizeof(ULONG) * 8)


//
// The binding info is threaded on two lists.  When
// the binding is free it is on a single freelist.
//
// When the binding is being used it is on an index list.
//
typedef struct _ARC_BINDING_INFO
{
	NDIS_HANDLE					MacBindingHandle;
	NDIS_HANDLE					NdisBindingContext;
	UINT						PacketFilters;
	ULONG						References;
	struct _ARC_BINDING_INFO *	NextOpen;
	BOOLEAN						ReceivedAPacket;
	// UCHAR					FilterIndex;
	UINT						OldPacketFilters;
} ARC_BINDING_INFO,*PARC_BINDING_INFO;

//
// An opaque type that contains a filter database.
// The MAC need not know how it is structured.
//
typedef struct _ARC_FILTER
{
	//
	// For accessing the mini-port.
	//
	struct _NDIS_MINIPORT_BLOCK *Miniport;

	//
	// Spin lock used to protect the filter from multiple accesses.
	//
	PNDIS_SPIN_LOCK Lock;

	//
	// Combination of all the filters of all the open bindings.
	//
	UINT CombinedPacketFilter;

	//
	// Pointer for traversing the open list.
	//
	PARC_BINDING_INFO OpenList;

	//
	// Action routines to be invoked on notable changes in the filter.
	//

	ARC_FILTER_CHANGE FilterChangeAction;
	ARC_DEFERRED_CLOSE CloseAction;

	NDIS_HANDLE ReceiveBufferPool;

	PARC_BUFFER_LIST FreeBufferList;
	PARC_PACKET FreePackets;

	PARC_PACKET OutstandingPackets;

	//
	// Address of the adapter.
	//
	UCHAR	AdapterAddress;

	UINT	OldCombinedPacketFilter;

} ARC_FILTER,*PARC_FILTER;



