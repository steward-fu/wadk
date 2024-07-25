// Ping.h
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
// Generated by DriverWizard version DriverStudio 2.0.0 (Build 552)
// Requires Compuware's DriverWorks classes
//

#ifndef __Ping_h__
#define __Ping_h__

#define EOL "\n"

// Global driver trace object
extern	KTrace	t;

class Ping : public KDriver
{
	SAFE_DESTRUCTORS
public:
	virtual NTSTATUS DriverEntry(PUNICODE_STRING RegistryPath);
	virtual NTSTATUS AddDevice(PDEVICE_OBJECT Pdo);

			void	 LoadRegistryParameters(KRegistryKey &Params);

	int	m_Unit;

	// The following data members are loaded from the registry during DriverEntry
	ULONG m_bBreakOnEntry;

#ifdef TDI_WINDOWS_NT
	TdiPnpCallbacks		m_TdiCallbacks;
	PUNICODE_STRING		m_pRegistryPath;
#endif

};

#endif			// __Ping_h__
