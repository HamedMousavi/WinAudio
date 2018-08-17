#if !defined(AFX_ABOUTDLG_H__5FE893A0_4568_4EB7_92C4_A361A6E9569C__INCLUDED_)
#define AFX_ABOUTDLG_H__5FE893A0_4568_4EB7_92C4_A361A6E9569C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
	enum TIMERS{STARS,INFO};
	CPoint star[5];
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUT };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	#ifndef WS_EX_LAYERED
	#define WS_EX_LAYERED           0x00080000
	#define LWA_COLORKEY            0x00000001
	#define LWA_ALPHA               0x00000002
	#endif // ndef WS_EX_LAYERED

// Preparation for the function we want to import from USER32.DLL
typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes)(HWND hWnd, 
                                  COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

lpfnSetLayeredWindowAttributes m_pSetLayeredWindowAttributes;
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPoint m_oldPoint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__5FE893A0_4568_4EB7_92C4_A361A6E9569C__INCLUDED_)
