// waitq.h - include file for event wait queue
//=============================================================================
//
// Compuware Corporation
// NuMega Lab
// 9 Townsend West
// Nashua, NH 03060  USA
//
// Copyright (c) 1998 Compuware Corporation. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States.
//
//=============================================================================

class SerialDevice;

class SerialWaitQueue : public KDriverManagedQueueEx
{
	SAFE_DESTRUCTORS
public:
	VOID CompleteCurrent(NTSTATUS status);
	VOID SetDevice(SerialDevice* Dev) {m_Device=Dev;}

protected:
	// called from the base class
	virtual VOID StartIo(KIrp I);
	virtual VOID Cancel(KIrp I);

	SerialDevice* m_Device;
};
