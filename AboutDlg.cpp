// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinAudio.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==STARS) {
/*		CClientDC dc(this);
		int i=0;
		for(i=0;i<5;i++) {
			dc.SetPixel(star[i].x,star[i].y,RGB(0,0,0));
			star[i].x=15+rand()%150;
			star[i].y=15+rand()%15;
			dc.SetPixel(star[i].x,star[i].y,RGB(255,255,255));

		}*/
		/*5*setpixel()*/
	} else if (nIDEvent==INFO) {
		/*run info*/
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//stars - info - stars
	SetTimer(STARS,50,0);
	SetTimer(INFO,2000,0);
	for(int i=0;i<5;i++) {
		star[i].x=rand()%50;
		star[i].y=rand()%50;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(INFO);
	KillTimer(STARS);
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_oldPoint=point;
	SetCapture( );
	CDialog::OnLButtonDown(nFlags, point);
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}

void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (nFlags==MK_LBUTTON) {
		CRect rect;
		GetWindowRect(rect);
		MoveWindow(rect.left+(point.x-m_oldPoint.x),rect.top+(point.y-m_oldPoint.y)
			,rect.right-rect.left,rect.bottom-rect.top);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CAboutDlg::WinHelp(DWORD dwData, UINT nCmd) 
{
//	CDialog::WinHelp(dwData, nCmd);
}

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	OSVERSIONINFO os = { sizeof(os) };
	GetVersionEx(&os);
	// use m_bWin2k before any call to the
	// m_pSetLayeredWindowAttributes to make sure we are runninng Win2K
	BOOL m_bWin2K = ( VER_PLATFORM_WIN32_NT == os.dwPlatformId && 
                  os.dwMajorVersion >= 5 ); 
	if (!m_bWin2K) return 0;

	// Here we import the function from USER32.DLL
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	m_pSetLayeredWindowAttributes = 
						   (lpfnSetLayeredWindowAttributes)GetProcAddress(hUser32, 
						   "SetLayeredWindowAttributes");

	// If the import did not succeed, make sure your app can handle it!
	if (NULL == m_pSetLayeredWindowAttributes)
		return FALSE; //Bail out!!!

	//AnimateWindow(GetSafeHwnd(),200,AW_BLEND);

	HWND hwnd=GetSafeHwnd();
	// Set WS_EX_LAYERED on this window 
	SetWindowLong(hwnd, GWL_EXSTYLE,
		GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Make this window 80% alpha and remove "RED = (RGB(255,0,0))" Color of the photo "about.bmp"
	m_pSetLayeredWindowAttributes(hwnd, RGB(255,0,0), (255 * 80) / 100, LWA_COLORKEY | LWA_ALPHA);
	
	
	return 0;
}

void CAboutDlg::OnClose() 
{
	CDialog::OnCancel();
}
