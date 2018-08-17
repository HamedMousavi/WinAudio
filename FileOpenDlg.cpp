// FileOpenDlg.cpp : implementation f	//}}AFX_DATA_MAP
e
//

#include "stdafx.h"
#include "WinAudio.h"
#include "FileOpenDlg.h"
#include ".\fileopendlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileOpenDialog dialog


CFileOpenDialog::CFileOpenDialog(BOOL bOpenFileDialog,
        LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags,
        LPCTSTR lpszFilter, CWnd* pParentWnd)
    : CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName,
        dwFlags, lpszFilter, pParentWnd)
{
    //{{AFX_DATA_INIT(CSpecialFileDialog)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_ofn.Flags |= OFN_ENABLETEMPLATE;
    m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_FILE_OPEN);
    m_ofn.lpstrTitle = "Select File";
}
void CFileOpenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileOpenDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileOpenDialog, CDialog)
	//{{AFX_MSG_MAP(CFileOpenDialog)
	ON_BN_CLICKED(IDC_ADD_TO_LIST, OnAddToList)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_TEXT2, OnStnClickedText2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileOpenDialog message handlers

BOOL CFileOpenDialog::OnInitDialog() 
{
	m_listCounter=0;
	m_strAllnames="";
	m_strFolderName	="";
	m_strFilename="";
//	VERIFY(m_select.AutoLoad(IDC_ADD_TO_LIST,this));

	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileOpenDialog::OnAddToList() 
{
	//ask informations in the edit box,witch lists 
	//names of the selected files.
	GetParent()->GetDlgItem(0x480)->GetWindowText(m_strFilename);
	
	if (m_strFilename=="") {
		m_listCounter=0;
		return;
	}
	m_strFolderName=GetFolderPath();
	m_strFolderName+="\\";
	   
	char ch='@';
	int counter=0,length=0;

	while (counter<m_strFilename.GetLength()-1) {
		ch=m_strFilename[counter++];
		if (ch=='"') length++;
	};
		
	length/=2;
	m_listCounter+=length;
 ////////////////////////////////////////////////////
	if (length==0) {
		if (m_strFilename=="") return;
		
		m_listCounter++;
		length++;
		CString name=m_strFolderName+m_strFilename;//+"."+GetFileExt();

		((CListBox*)GetDlgItem(IDC_SELECTED_LIST))->AddString(name);

		m_strAllnames=m_strAllnames+"\""+name+"\" ";
		return;
	}

	for (int i=0;i<length;i++) {
		CString name=m_strFolderName+GetName(m_strFilename,i);

		((CListBox*)GetDlgItem(IDC_SELECTED_LIST))->AddString(name);
			
		m_strAllnames=m_strAllnames+"\""+name+"\" ";
	}
}

CString CFileOpenDialog::GetName(CString str, int index)
{
	char ch;
	int charNum=0,
		comma=0;
	CString ans="";
	int len,splitter;
	splitter=2*index+1;

	len=str.GetLength();

	for (int i=0;i<len;i++){
		ch=str[charNum++];
		
		if (charNum>=len) return "EOL";

		if (ch=='"') {
			comma++;
//			ch=str[charNum];
			if (comma<splitter) ch=str[charNum++];
			if (comma==splitter+1)	return ans;
		}
		if (comma>=splitter && comma<splitter+1) {
			if (ch!='"') ans+=ch;
		}
	}
	return "";
}

bool CFileOpenDialog::selectedFile()
{
	if (m_strFilename=="") return false;
	else return true;
}

int CFileOpenDialog::getCount()
{
	return m_listCounter;
}

CString CFileOpenDialog::listName(int index)
{
	return GetName(m_strAllnames,index);
}

void CFileOpenDialog::OnStnClickedText2()
{
	// TODO: Add your control notification handler code here
}
