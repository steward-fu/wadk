// isession.cpp
// Implementation of ReadWriteSession class
//
// Generated by DriverWizard version DriverStudio 2.7.0 (Build 554)
// Requires Compuware's DriverWorks classes
//

#include <vdw.h>

#include "servdev.h"
#include "server.h"

/////////////////////////////////////////////////////////////////////
//  ReadWriteSession::OnConnect
//
//	Routine Description:
//		OnConnect event handler
//
//	Parameters:
//		[in] AddressLength
//			address length
//
//		[in] pTA
//			address structure
//
//		[in] OptionsLength
//			options length
//
//		[in] Options
//			options
//
//	Return Value:
//		TRUE, if connection accepted.
//
//	Comments:
//		None
//
BOOLEAN ReadWriteSession::OnConnect(uint AddressLength, PTRANSPORT_ADDRESS pTA, uint OptionsLength, PVOID Options)
{
	char szIPaddr[20];

	inet_ntoa(PTDI_ADDRESS_IP(pTA->Address[0].Address)->in_addr, szIPaddr, sizeof(szIPaddr));

    t << "ReadWriteSession::OnConnect " << szIPaddr << EOL;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
//  ReadWriteSession::OnDisconnect
//
//	Routine Description:
//		disconnect event handler
//
//	Parameters:
//		[in] OptionsLength
//			options length
//
//		[in] Options
//			options
//
//		[in] bAbort
//			TRUE, if connection aborted
//
//	Return Value:
//		None.
//
//	Comments:
//		None
//
void ReadWriteSession::OnDisconnect(uint OptionsLength, PVOID Options, BOOLEAN bAbort)
{
    t << "ReadWriteSession::OnDisconnect\n";
}


////////////////////////////////////////////////////////////////////////
//  ReadWriteSession::OnReceive
//
//	Routine Description:
//		receive data handler
//
//	Parameters:
//		[in] Indicated 
//			number of bytes indicated
//
//		[in] Data
//			received data
//
//		[in] Available
//			number of bytes available
//
//		[out] RcvBuffer 
//			buffer for the rest of data
//
//		[out] RcvBufferLen 
//			size of rcv buffer
//
//	Return Value:
//		None
//
//	Comments:
//		None
//
uint ReadWriteSession::OnReceive(uint Indicated, uchar* Data, uint Available, uchar** RcvBuffer, uint* RcvBufferLen)
{
    t << "ReadWriteSession::OnReceive\n";

	if( Data )
	{
		ReadWriteSocket* pSocket = static_cast<ReadWriteSocket*>(m_pSocket);
		pSocket->m_pDevice->OnReceive(this, Data, Indicated);
	}

	return Indicated;
	UNREFERENCED_PARAMETERS3(Available, RcvBuffer, RcvBufferLen); 
}

////////////////////////////////////////////////////////////////////////
//  ReadWriteSession::OnSendComplete
//
//	Routine Description:
//		send complete handler
//
//	Parameters:
//		[in] pCxt
//			pointer to our context
//
//		[in] Status 
//			status of send
//
//		[in] ByteCount
//			number of bytes send
//
//	Return Value:
//		None
//
//	Comments:
//		None
//
void ReadWriteSession::OnSendComplete(PVOID buf, TDI_STATUS status, uint bytecnt)
{
    t << "ReadWriteSession::OnSendComplete\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//  BroadcastSocket::OnReceive
//
//	Routine Description:
//		receive data handler
//
//	Parameters:
//		[in] Indicated 
//			number of bytes indicated
//
//		[in] Data
//			received data
//
//		[in] Available
//			number of bytes available
//
//		[out] RcvBuffer 
//			buffer for the rest of data
//
//		[out] RcvBufferLen 
//			size of rcv buffer
//
//	Return Value:
//		None
//
//	Comments:
//		None
//
uint BroadcastSocket::OnReceive(
	uint AddressLength, 
	PTRANSPORT_ADDRESS pTA, 
	uint OptionsLength, 
	PVOID Options, 
	uint Indicated, 
	uchar* Data, 
	uint Available, 
	uchar** RcvBuffer, 
	uint* RcvBufferLen)
{
	char szIPaddr[20];

	inet_ntoa(PTDI_ADDRESS_IP(pTA->Address[0].Address)->in_addr, szIPaddr, sizeof(szIPaddr));

    t << "BroadcastSocket::OnReceive " << szIPaddr << EOL;

	CTDI_CONNECTION_INFORMATION resp(*PTDI_ADDRESS_IP(pTA->Address[0].Address));

	PUCHAR p = new UCHAR[4];

	TDI_STATUS Status = sendto(resp, p, 4, p);

	return Indicated;
}

////////////////////////////////////////////////////////////////////////
//  BroadcastSocket::On_sendtoComplete
//
//	Routine Description:
//		send complete handler
//
//	Parameters:
//		[in] pCxt
//			pointer to our context
//
//		[in] Status 
//			status of send
//
//		[in] ByteCount
//			number of bytes send
//
//	Return Value:
//		None
//
//	Comments:
//		None
//
void BroadcastSocket::On_sendtoComplete(PVOID pCxt, TDI_STATUS Status, uint ByteCount)
{
	PUCHAR p = (PUCHAR)pCxt;

	delete[] p;
}
