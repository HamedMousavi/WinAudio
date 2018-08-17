// HMixer.h: interface for the CHMixer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HMIXER_H__B371238E_CCF9_452E_B968_E407C452A82A__INCLUDED_)
#define AFX_HMIXER_H__B371238E_CCF9_452E_B968_E407C452A82A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vfw.h"

class CHMixer  
{
public:
	BOOL GetComponentIDList( unsigned long *id);
	BOOL GetControlListLabel( CString *name);
	CString GetProductName();
	BOOL SetParentPointer( CWnd *pWnd);
	BOOL GetControlList( unsigned long *id );
	UINT GetControlNumber();
	UINT GetLineNumber();
	BOOL SetComponentActivity( unsigned long idComponent );
	BOOL GetComponentActiveStat(unsigned long idComponent);
	BOOL SetVolume( unsigned long idComponent,UINT newVolume );
	UINT GetVolume( unsigned long idComponent );
	CHMixer();
	virtual ~CHMixer();
	DWORD component[20];

private:
	BOOL IdentifyControls();
	BOOL FindComponent( unsigned long idComponent);
	void IdentifyCapabilities();
	BOOL GetParentPointer();
	BOOL Initialize();
	BOOL OpenMixer();

	HMIXER m_hMixer;
	BOOL m_initialized;
	BOOL mixerIsOpen;
	BOOL capsIdentified;
	CWnd* m_pWnd;
	UINT lastError;
	UINT mixerID;
	UINT m_controlNumber;
	UINT m_lineNumber;
	MIXERCAPS mixerCaps;
	MIXERCONTROLDETAILS_UNSIGNED mixerUnsigned;
	MIXERCONTROLDETAILS mixerCDetails;
	MIXERLINE mixerLine;
	MIXERCONTROL mixerControl;
	MIXERLINECONTROLS mixerLControls;
	DWORD m_controlID[20];
	CString m_label[20];
	DWORD m_component[20];
};

#endif // !defined(AFX_HMIXER_H__B371238E_CCF9_452E_B968_E407C452A82A__INCLUDED_)
