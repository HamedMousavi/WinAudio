// PlayListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winaudio.h"
#include "PlayListDlg.h"
#include "WinAudioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayListDlg dialog


CPlayListDlg::CPlayListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPlayListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayListDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayListDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayListDlg)
	ON_WM_CREATE()
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayListDlg message handlers

void CPlayListDlg::OnOK() 
{
//	CDialog::OnOK();
}

void CPlayListDlg::OnCancel() 
{
//	CDialog::OnCancel();
}

int CPlayListDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
		SetWindowPos(0,m_posX+20,m_posY-100,200,102,0);
		CRgn rgn;
		
		rgn.CreateRoundRectRgn(0,0,200,102,10,10);
		SetWindowRgn((HRGN)rgn.GetSafeHandle(),FALSE);
	return 0;
}

void CPlayListDlg::SetPos(int x, int y)
{
	m_posX=x;
	m_posY=y;
}

BOOL CPlayListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_animIndex=0;
	SetWindowPos(0,m_posX+20,m_posY-100,200,101,0);

	CRect rct;
	GetClientRect(rct);

	GetDlgItem(IDC_LIST)->SetWindowPos(0,rct.left+5 ,
		rct.top+5 ,(rct.right-rct.left)-10 ,
		(rct.bottom-rct.top)-10 ,0);

	Animate(0);
	m_list.Invalidate(TRUE);
	m_list.RedrawWindow();
	LoadList();

//	GetDlgItem(IDC_LIST)->Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayListDlg::OnDblclkList() 
{
	( (CWinAudioDlg*)GetParent() )->PlayFromList(m_list.GetCurSel());
}

HBRUSH CPlayListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	HBRUSH			colBrush;

	if (nCtlColor==CTLCOLOR_DLG) {
		pDC->SetBkColor(RGB(220,223,235));
		colBrush=CreateSolidBrush(RGB(220,223,235));
		return colBrush;
	} else {
		pDC->SetBkColor(RGB(255,220,170));//RGB(187,190,209));
		pDC->SetTextColor(RGB(50,50,150));
		colBrush=CreateSolidBrush(RGB(255,220,170));//RGB(187,190,209));
		return colBrush;
	}
	return hbr;
}

void CPlayListDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Do not call CDialog::OnPaint() for painting messages

/*	CRect rect;
	GetClientRect(rect);

	int cx,cy;
	cx=rect.right-rect.left;
	cy=rect.bottom-rect.top;
//	TRACE("cx=%d cy=%d\n",cx,cy);

	CDC dcMem;
	CBitmap bmp,*old;

	dcMem.CreateCompatibleDC(&dc);
	bmp.LoadBitmap(IDB_PLAY_LIST);
	old = dcMem.SelectObject(&bmp);
	dc.BitBlt(0,0,cx,cy,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(old);*/
}

void CPlayListDlg::LoadList()
{
	m_list.ResetContent();
	int lim = ( (CWinAudioDlg*)GetParent() )->GetNumberOfFiles();
	for (int i=0;i<lim;i++) {
		m_list.AddString( ((CWinAudioDlg*)GetParent())->GetFileName(i) );
	}
	int curr=( ((CWinAudioDlg*)GetParent() )->GetCurentIndex());
	m_list.SetCurSel(curr);
	m_list.Invalidate();
}
void CPlayListDlg::Animate(UINT AnimateModel/* 0=BLEND open 1=BLEND close */)
{
	OSVERSIONINFO os = { sizeof(os) };
	GetVersionEx(&os);
	// use m_bWin2k before any call to the
	// m_pSetLayeredWindowAttributes to make sure we are runninng Win2K
	BOOL m_bWin2K = ( VER_PLATFORM_WIN32_NT == os.dwPlatformId && 
				  os.dwMajorVersion >= 5 ); 
	if (!m_bWin2K) return;


	if (AnimateModel==0) {
		AnimateWindow(GetSafeHwnd(),200,AW_BLEND );
		Invalidate(FALSE);
	} else {
		AnimateWindow(GetSafeHwnd(),200,AW_HIDE | AW_BLEND );
	}
}
