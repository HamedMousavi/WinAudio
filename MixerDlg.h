#if !defined(AFX_MIXERDLG_H__FC04E16E_E531_4ED6_A011_80CF67938F2D__INCLUDED_)
#define AFX_MIXERDLG_H__FC04E16E_E531_4ED6_A011_80CF67938F2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MixerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMixerDlg dialog
#include "hslider.h"
#include "hmixer.h"

#define WM_MOVED WM_USER+9526

class CMixerDlg : public CDialog
{
// Construction
public:
	void SetPos(int x, int y);
	CMixerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMixerDlg)
	enum { IDD = IDD_MIXER_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMixerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMixerDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnMixerBarMoved(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	int	m_posX,m_posY;
	CSliderCtrl *bar[20];
	unsigned long *id;
	unsigned long *controlId;
	CString *m_str;
	CHMixer mixer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXERDLG_H__FC04E16E_E531_4ED6_A011_80CF67938F2D__INCLUDED_)
