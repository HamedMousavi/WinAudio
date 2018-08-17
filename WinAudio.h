// WinAudio.h : main header file for the WINAUDIO application
//

#if !defined(AFX_WINAUDIO_H__7DD8A241_456D_4CD7_8F76_7A1600E63A4C__INCLUDED_)
#define AFX_WINAUDIO_H__7DD8A241_456D_4CD7_8F76_7A1600E63A4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinAudioApp:
// See WinAudio.cpp for the implementation of this class
//

class CWinAudioApp : public CWinApp
{
public:
	CWinAudioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinAudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinAudioApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINAUDIO_H__7DD8A241_456D_4CD7_8F76_7A1600E63A4C__INCLUDED_)
