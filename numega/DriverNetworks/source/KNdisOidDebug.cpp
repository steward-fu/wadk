// KNdisOidDebug.cpp: Misc stuff to debug OID processing
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
// This takes a lot of space (~ 30K) but works fast.
// Intended for debug builds only.
//
// NOTE: Built using LDK build 4074. This file have to be re-generated
// ===== for NDIS 6 or future NDIS update as some newly
//       introduced OIDs is not covered.
//

#include	<kndis.h>

// string arrays generated by OidGen.exe
#include "KNdisOidDebugStrings.h"

///////////////////////////////////////////////////////////////////
// Implementation
//
// Calculates a "NormalizedIndex" value for a OID based on its category.
//
// The array is built by OidGen.exe using the same normalization.
//


///////////////////////////////////////////////////////////////////////
// Get ASCII name for the OID
//
// Parameters:
// 	oid                  - NDIS_OID of interest
// Returns:
// 	ASCII string or NULL if the OID is not known
// Comments:
// 	none
const char* KNdisOidDebug::Name(const NDIS_OID oid)
{
	char* pName = sm_szUnknown;
	bool bMediumOid = true;

	unsigned MagicOffset3	= 685;
	unsigned MagicOffset9	= 170;
	unsigned MagicOffset8	= 335;

	unsigned med			= (oid>>24);
	unsigned op				= (oid>>16) & 0xFF;
	unsigned mand			= (oid>> 8) & 0xFF;
	unsigned index			= oid & 0xFF;
	unsigned NormalizedIndex= 0;

	if((med & 0x80) == 0)
	{
		op -= 1;
		mand -= 1;

		if(med == 3)
		{
			if(op <= 1)
				NormalizedIndex = index + 0x8d + (op*8) + MagicOffset3;
			else
				NormalizedIndex = index + MagicOffset3;
		}
		else if(med == 9)
		{
			NormalizedIndex = index + (mand<<5) + (op<<6) + MagicOffset9;
		}
		else if(med >= 0x8)
		{
			med &= 0x07;
			NormalizedIndex = index + (mand<<6) + (op<<7) + (med<<8) + MagicOffset8;
		}
		else
		{
			NormalizedIndex = index + (mand<<5) + (op<<6) + (med<<8);
		}
	}
	else
	{
		bMediumOid = false;
		med &= 0x07;
		med -= 3;
		if(mand == 0x10)
			mand = 1;
		NormalizedIndex = index + (mand<<5) + (op<<7) + (med<<8);
	}

	if (bMediumOid)
	{
		if (NormalizedIndex-1 < sizeof(sm_szOIDs)/sizeof(char*))
			pName = sm_szOIDs[NormalizedIndex-1];
	}
	else
	{
		if (NormalizedIndex-1 < sizeof(sm_szOIDsx)/sizeof(char*))
			pName = sm_szOIDsx[NormalizedIndex-1];
	}

	if(!pName)
		pName = sm_szUnknown;
	return pName;
}

// "unknown" string
char KNdisOidDebug::sm_szUnknown[] = "OID_???";


///////////////////////////////////////////////////////////////////////
// Check the correctness of the OID list
//
// Parameters:
// 	List[]               - pointer to the array of NDIS_OIDs
// 	nElements            - number of OIDs in the array
// Returns:
// 	TRUE if the array is sorted properly
// Comments:
// 	NDIS requires that miniport drivers return a sorted
//	in acsending order array of supported OIDs in response to
//	OID_GEN_SUPPORTED_LIST query. InOrder() checks if the array
//	(usually, statically initialized) is properly sorted.
bool KNdisOidDebug::InOrder(NDIS_OID List[], ULONG nElements)
{
	NDIS_OID prev = NDIS_OID(0);
	for (ULONG i=0; i<nElements; i++)
	{
		if (List[i] < prev)
		{
			TRACE("Wrong NDIS_OID List Order for %s\n", Name(i));
			return false;
		}
		prev = List[i];
	}
	return true;
}

ULONG KNdisOidDebug::sm_uTraceMask = (ULONG) KNDIS_OIDTRACE_ALL;
