#if !defined(AFX_FILEOPENDLG_H__88E20613_A266_4C84_9B54_9D6F8181602B__INCLUDED_)
#define AFX_FILEOPENDLG_H__88E20613_A266_4C84_9B54_9D6F8181602B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileOpenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileOpenDialog dialog

class CFileOpenDialog : public CFileDialog
{
private:
	CString m_strFilename,
			m_strFolderName,
			m_strAllnames;
//	CBitmapButton	m_select;
// Construction
public:
	CString listName(int index);
	int getCount(void);
	bool selectedFile(void);
	CFileOpenDialog(BOOL bOpenFileDialog, 
    LPCTSTR lpszDefExt = NULL,
    LPCTSTR lpszFileName = NULL,
    DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    LPCTSTR lpszFilter = NULL,
    CWnd* pParentWnd = NULL );

// Dialog Data
	//{{AFX_DATA(CFileOpenDialog)
	enum { IDD = IDD_FILE_OPEN };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOpenDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileOpenDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddToList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_listCounter;
	CString GetName(CString str,int index);
public:
	afx_msg void OnStnClickedText2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEOPENDLG_H__88E20613_A266_4C84_9B54_9D6F8181602B__INCLUDED_)
