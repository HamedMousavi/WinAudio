#if !defined(AFX_PLAYLISTDLG_H__ABD08734_5981_4A58_8C77_3F32FA03F12D__INCLUDED_)
#define AFX_PLAYLISTDLG_H__ABD08734_5981_4A58_8C77_3F32FA03F12D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayListDlg dialog

class CPlayListDlg : public CDialog
{
// Construction
public:
	void Animate( UINT AnimateModel );
	void LoadList();
	void SetPos(int x, int y);
	CPlayListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayListDlg)
	enum { IDD = IDD_PLAY_LIST_DLG };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayListDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_animIndex;
	#ifndef WS_EX_LAYERED
	#define WS_EX_LAYERED           0x00080000
	#define LWA_COLORKEY            0x00000001
	#define LWA_ALPHA               0x00000002
	#endif // ndef WS_EX_LAYERED

	// Preparation for the function we want to import from USER32.DLL
	typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes)(HWND hWnd, 
									  COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

	lpfnSetLayeredWindowAttributes m_pSetLayeredWindowAttributes;

	int m_posX,m_posY;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTDLG_H__ABD08734_5981_4A58_8C77_3F32FA03F12D__INCLUDED_)
