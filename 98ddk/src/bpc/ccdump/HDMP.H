//
// Copyright (C) 1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture DDK.
// For detailed information regarding Broadcast
// Architecture, see the DDK.
//
// hDmp.h : main header file for the HDMP application
//

#if !defined(AFX_HDMP_H__5FB09352_70C9_11D1_9301_0060B0575ABD__INCLUDED_)
#define AFX_HDMP_H__5FB09352_70C9_11D1_9301_0060B0575ABD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHDmpApp:
// See hDmp.cpp for the implementation of this class
//

class CHDmpApp : public CWinApp
{
public:
	CHDmpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDmpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHDmpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDMP_H__5FB09352_70C9_11D1_9301_0060B0575ABD__INCLUDED_)
