// USBNICDrv.h 
//
// Generated by DriverNetworks Wizard 
//====================================================================
//
// Compuware Corporation
// NuMega Lab
// 9 Townsend West
// Nashua, NH 03060  USA
//
// Copyright (c) 2002 Compuware Corporation. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States.
//
//====================================================================

#ifndef _USBNICDrv_h	
#define _USBNICDrv_h

#include	<kndis.h>

//////////////////////////////////////////////////////////////////////
// USBNICDriver	Declaration
class USBNICDriver : public KNdisMiniDriver
{
protected:
	// must implement the entry point
	NTSTATUS DriverEntry(IN PVOID RegistryPath);

};

#endif 