#if !defined(AFX_HSLIDER_H__DBFCB9AF_9A1B_4F0A_A4A2_B50276EC533E__INCLUDED_)
#define AFX_HSLIDER_H__DBFCB9AF_9A1B_4F0A_A4A2_B50276EC533E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HSlider.h : header file
//
#define WM_MOVED WM_USER+9526
/////////////////////////////////////////////////////////////////////////////
// CHSlider window

class CHSlider : public CSliderCtrl
{
// Construction
public:
	CHSlider();
	CHSlider(unsigned long cID,unsigned long newID,CString label);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	unsigned long GetComponentID();
	unsigned long GetID();
	void SetID(unsigned long newID);
	virtual ~CHSlider();

	// Generated message map functions
protected:
	unsigned long	m_ID,m_controlID;
	CString m_label;
	//{{AFX_MSG(CHSlider)
	afx_msg void OnReleasedcapture(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HSLIDER_H__DBFCB9AF_9A1B_4F0A_A4A2_B50276EC533E__INCLUDED_)
