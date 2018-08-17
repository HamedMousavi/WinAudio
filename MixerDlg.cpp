// MixerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winaudio.h"
#include "MixerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMixerDlg dialog


CMixerDlg::CMixerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMixerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMixerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMixerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMixerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMixerDlg, CDialog)
	//{{AFX_MSG_MAP(CMixerDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOVED,OnMixerBarMoved)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMixerDlg message handlers

void CMixerDlg::OnOK() 
{
//	CDialog::OnOK();
}

void CMixerDlg::OnCancel() 
{
//	CDialog::OnCancel();
}

BOOL CMixerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UINT num = mixer.GetControlNumber();
	m_str= new CString [num];
	mixer.GetControlListLabel(m_str);
	
	id=new unsigned long [num];
	controlId=new unsigned long [num];
	mixer.GetComponentIDList(id);
	mixer.GetControlList(controlId);

	for (UINT i=0;i<num;i++) {
		bar[i] = new CHSlider(i,id[i],m_str[i]);
		bar[i]->Create(TBS_VERT | TBS_BOTH | TBS_NOTICKS,
			CRect(((i+1)*30)+2,8,((i+1)*30)+30,68),this,i);
		bar[i]->SetRange(0,65535,TRUE);
		bar[i]->SetPos(65535-mixer.GetVolume(controlId[i]));

		bar[i]->ShowWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CMixerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetWindowPos(0,m_posX+20,m_posY-100,318,102,0);
	CRgn rgn;
		
	rgn.CreateRoundRectRgn(0,0,318,102,10,10);
	SetWindowRgn((HRGN)rgn.GetSafeHandle(),FALSE);

	
	return 0;
}

void CMixerDlg::SetPos(int x, int y)
{
	m_posX=x;
	m_posY=y;
}
LRESULT CMixerDlg::OnMixerBarMoved(WPARAM wParam,LPARAM lParam)
{
	mixer.SetVolume(wParam,65535-(UINT)lParam);
	return 0;
}

void CMixerDlg::PostNcDestroy() 
{
	delete[] *bar;
	delete[] id;
	delete[] controlId;
	delete[] m_str;
	CDialog::PostNcDestroy();
}
