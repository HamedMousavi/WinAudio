//////////////////////////////////////////////////////////////////////////
//																		//
//						Win Audio By Hamed Mosavi						//
//																		//
//	-Hope it's usefull,and do whatever you would like					//
//		to do with this code(You are FREE).								//
//																		//
//	-Excuse me please, because my English is not very good.So perhaps	//
//		it's more difficault to understand my descriptions				//
//		than the code itself!!											//
//																		//
//	-I'm NOT responsible for any damages witch this code may cause to	//
//		your Computer, Car, House,... even if it killed you and ...!!	//
//																		//
//	-Hope You enjoy it.It's the best thing I can earn as a biginner in	//
//		visual c++ (after six month of learning without a teacher and	//
//		just with the help of an e-book on a CD and ofcurse				//
//		"TheCodeProject" web site and all other programmers and members)//
//		Here I thank them all.They helped me alot.						//
//																		//
//	-While using, if you encountered texts witch are not recognizable!	//
//		don't worry!This is my natural language (Farsi), you can safely	//
//		remove them from the source code.								//
//																		//
//////////////////////////////////////////////////////////////////////////

// WinAudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinAudio.h"
#include "WinAudioDlg.h"
#include "vfw.h"
#include "AboutDlg.h"

#define MOVE TRUE
#define DONT_MOVE FALSE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef	TTS_BALLOON
#define	TTS_BALLOON		0x40
#endif
/////////////////////////////////////////////////////////////////////////////
// CWinAudioDlg dialog

CWinAudioDlg::CWinAudioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinAudioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinAudioDlg)
	m_nMax = 0;
	m_nMin = 0;
	m_nPos = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bEnable = TRUE;
}

void CWinAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinAudioDlg)
	DDX_Control(pDX, IDC_ANIMATE, m_animate);
	DDX_Control(pDX, IDC_SLIDER,m_slider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinAudioDlg, CDialog)
	//{{AFX_MSG_MAP(CWinAudioDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EJECT, OnEject)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_PLAYORDER, OnPlayOrder)
	ON_BN_CLICKED(IDC_REPEATE, OnRepeateOrNot)
	ON_BN_CLICKED(IDC_NUMBER, OnAllOrOne)
	ON_BN_DOUBLECLICKED(IDC_PLAYORDER, OnDoubleclickedPlayOrder)
	ON_BN_DOUBLECLICKED(IDC_NUMBER, OnDoubleclickedNumber)
	ON_BN_CLICKED(IDC_FORWARD, OnForward)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_WINDOWS_MIXER, OnWindowsMixer)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_DOUBLECLICKED(IDC_REPEATE, OnDoubleclickedRepeate)
	ON_WM_HELPINFO()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CLOSE, OnExit)
	ON_BN_CLICKED(IDC_DISPLAY_ALBUM, OnDisplayAlbum)
	ON_BN_CLICKED(IDC_MIXER, OnMixer)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_BITMAPSLIDER_MOVED, OnBitmapSliderMoved)
	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinAudioDlg message handlers

BOOL CWinAudioDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	init();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinAudioDlg::OnPaint() 
{
	if (m_first) {
		m_first=FALSE;
		
	//	m_g.SetDC(this);
		m_g.Init();
		m_g.UpdateAll();
	} else {
		m_g.UpdateAll();
	}
	//graphical slider witch classes are designed and
	//also belong to "Joon-ho Ryu" they use
	//"Flicker Free Drawing In MFC" by Keith Rule.
	m_slider.RedrawWindow();

	//Marquee is a piece of Information you can see on the LCD! (like: album,artist,...).
	m_g.UpdateInfo(DONT_MOVE);

	//update trck no. display if needed
	if (m_files!=NULL) {
		CString tracktemp;
		tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
		//m_lcd.updateCurrTrack(tracktemp);
//		m_g.Init();
		m_g.UpdateCurrTrack(tracktemp);
	}
	///////////////////////////////////////////visual c++ codes vvv///
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		return;
	}
}

HCURSOR CWinAudioDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//I called ,the piece of "audio player" 
//witch shows information, an "LCD".

//Increses The Volume and Updates LCD.
void CWinAudioDlg::OnPlus() 
{
	if (m_volume<1000)
		m_volume+=50;
	
	//Redraw volumebar in LCD window.
	m_g.UpdateVolume(m_volume);

	//if music is playing also increse volume in real time
	//else when m_volume is updated after this music will be
	//played with this amount of volume.
	if (m_playing) SetMusicVolume(m_volume);
}
//Decreses The Volume and Updates LCD
void CWinAudioDlg::OnMinus() 
{
	if (m_volume>0)
		m_volume-=50;

	//For more information look at the previous fuction Infos..
	m_g.UpdateVolume(m_volume);
	if (m_playing)SetMusicVolume(m_volume);
}
//Displays Open dilog and ...
void CWinAudioDlg::OnEject() 
{
	if (m_OpenDlg) {
		CFileOpenDialog *temp;
		temp=fDlg;
		delete temp;
	}
	//CFileOpenDialog is an overloaded dialog class from CFileDialog
	//the problem was that if number of files we select, 
	//(using multi select capability) in FileOpenDialig, grows 
	//when the user selects "Open" this dialog returns "IDCANCEL".
	//So we have to override it to solve this problem.
	//For more information read documentation,please.
	fDlg=new CFileOpenDialog(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
	"MP3 Files (*.mp3)|*.mp3|AVI Files (*.avi)|*.avi|MIDI Files (*.mid)|*.avi|Wave Files (*.WAV)|*.WAV|All Files (*.*)|*.*|");

	m_OpenDlg=TRUE;
	//If user did NOT selected any file(s)
 	if (fDlg->DoModal()==(IDCANCEL) && (!fDlg->selectedFile()) ) { 
		return;
	} else if (fDlg->selectedFile()) {  //if a(some) file(s) have been 
									    //selected [* By Adding it to bottom list of file open and NOT by Dblclicking on it directly!].
		if (m_playing) {				//if music is playing now!
			OnStop();					//stop playing
		}
		HINSTANCE	tmp=(AfxGetInstanceHandle());
		HWND*	musicWndPtr=&musicWnd;
		
		m_repCounter=0;

		//Load new selected list of files
		UpdateList();
/******************************************************************		
		//If NOT able to create the music[MCIWndCreate func.].
		if (! m_music.create(&m_animate,&tmp,m_files[0],musicWndPtr)){
			MessageBox("Unable To Create The Music");//-------------------------------
			return;
		}
*******************************************************************/		
		//Select first file to play.
		m_fileName=m_files[0];
		
		//Play the current file.
		OnPlay();

		//Display number of tracks and currently playing track
		CString tracktemp;
		tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
		//m_lcd.updateCurrTrack(tracktemp);
		m_g.UpdateCurrTrack(tracktemp);
		return;
		//In CFileOpen dialog if we select just on file by 
		//DobbleClicking on it or selecting it and openning
		//the dialog returns true file name.
		//So we have one file selected and we have to play it as well.
	} else {

		HINSTANCE	tmp=(AfxGetInstanceHandle());
		HWND*	musicWndPtr=&musicWnd;
		m_fileName=fDlg->GetPathName();
		m_files=new CString;
		m_files[0]=m_fileName;
		
		//If any ERROR occured.
		if (m_fileName=="") return;
		if (fDlg->GetFileName()=="") return;

		m_repCounter=0;
		//Number of files available.
		m_fileCounter=1;
		//If something is playing...
		if (m_playing) {
			OnStop();
		}
		//So certainly nothing is playing now.
		OnPlay();
		//Display "1 out of 1" as number of tracks.
		m_g.UpdateCurrTrack("1 / 1");

//		if (IsPlayListDialogModal()) {
		if (m_pListIsVisible) {
			m_listDlg.LoadList();
		}
		return;
	}
}
//Stops every things
void CWinAudioDlg::OnStop() 
{
	//If nothing is playing at the moment.
	if (!m_playing) return;
	else {					//If something is playing
		//Current sign is a rectangle representing STOP
		m_sign=STOP;
		//Stop mobile information at the buttom of the LCD.
		KillTimer(MARQUEE);
		//Stop Reverse timer displaying remaind time.
		KillTimer(CCLOCK);
		//Stop spectrum!!!
		KillTimer(SPECTRUM);
		//Display zero timer.
		m_g.UpdateCurrTime("00 : 00 : 00");
		//Clean information area on the LCD.
		m_g.UpdateInfo(DONT_MOVE);
		//m_MarqueeTxt.setText("");
		m_g.SetMarqueeText("");
		m_oneReaded=FALSE;//????????????????????????????????????//

		/* Under Construction
		int bar[8];
		for (int i=0;i<8;i++)
			bar[i]=1;
		//m_lcd.UpdateSpect(bar);
		*/

		if (! StopMusic()) {
			MessageBox("Can not Stop?!!");
			return;
		}
		//now Everybody know that we are not playing any sound!
		m_playing=FALSE;
		//Display stop sign because every thing just stoped.
		m_g.SetPlaySign(STOP,TRUE);
	}
}
//Plays music witch defined in 'm_fileName' Variable
void CWinAudioDlg::OnPlay() 
{
	//If any error occured,however I don't think so...!.
	if (m_fileName=="") return;
	//If a sound is playing so we have to PAUSE
	//because the play button is also used as pause button.
	//But wat if sound had been paused before? well, RESUME it.
	if ( m_playing ) {
		if (m_pause) {
			Resume();
			return;
		} else  {
			Pause();
			return;
		}
	}
	else {		//If nothing is playing we have to PLAY
		//int err;
		//Current sign is a triangle to show playing.
		m_sign=PLAY;
		//Volume must be set
		SetMusicVolume(m_volume);
		//Try to play the sound(Or music or...)
		//try {
			PlayMusic(m_fileName);
			CString temp;
			temp=m_fileName;
			temp.Delete(0,temp.ReverseFind('\\')+1);

			SetWindowText("Win Audio - "+temp);
		//	throw (1);
		//} catch(int err) {
			//OnStop();
			//MessageBox("Err ");
			//return;
		//}
		//Now, everybody in the programme know that we are playing!
		m_playing=TRUE;

		//Display mobile Information at the buttom of the LCD
		RunInfo();

		//Update playlist active sell!
		if (m_pListIsVisible) {
			m_listDlg.m_list.SetCurSel(m_repCounter);
			m_listDlg.Invalidate();
		}
	}
}
//Minimize Dialog
void CWinAudioDlg::OnMinimize() 
{
	CloseWindow();
}
//Close dialog and Save vital information for next loading
void CWinAudioDlg::OnExit() 
{
	//If some music is playing now,Stop it.
	if (m_playing) {
		m_debug="m_playing,OnClose,4";
		OnStop();
	}
	//save current status to file
	if(!SaveInfo()){
		MessageBox("Disk Error:Can not save layout information.");
	}
	//Delete allocated array using "new" function.[free memory].
	if (m_files!=NULL && m_fileCounter>1) delete []m_files;
	else if (m_files!=NULL) delete m_files;
	//delete the overloaded FileOpenDialog
	if (fDlg!=NULL)	delete(fDlg);

	if (m_randIndex!=NULL) delete m_randIndex;
	if (m_mixerDlgIsVisible) m_mDlg.DestroyWindow();
	if (m_pListIsVisible) m_listDlg.DestroyWindow();

	m_g.~HGraphics();
	//end the program.
	exit(0);
}
//Beginning Initialization (Will be Called in InitDialog Func)
void CWinAudioDlg::init()
{
	//Main rectangle of the programme
	m_skinRect.bottom=146;
	m_skinRect.left=1;
	m_skinRect.right=555;
	m_skinRect.top=0;

	//Mixer dialog [under construction].
	m_mixerDlgStat=false;

	//To display any type of region (later, if we wanted.).
	CRgn skinRgn;
	
	skinRgn.CreateRectRgn(m_skinRect.left,m_skinRect.top,
		m_skinRect.right,m_skinRect.bottom);
	SetWindowRgn(skinRgn,TRUE);

	m_randIndex=NULL;
	//Represent the leftouse button situation.
	//TRUE if it is down know.
	m_LButtonDown=FALSE;

	//TRUE if we are playing something now.
	m_playing=FALSE;

	//TRUE if sound has been Paused.
	m_pause=FALSE;

	//TRUE if this is the first sound witch is playing now.
	//Declared to do some works at first playing.[reserved!]
	m_first=TRUE;

	//If any music has been readed[reserved for later use].
	m_oneReaded=FALSE;

	m_repSituation=NORM_NOREP_ALL;

	//Current volume
	if (!LoadInfo()) {
		m_volume=0;

		//Number of files currently selected.
		m_fileCounter=0;
		//pointer to list of all files array.
		m_files=NULL;
	//SetWindowPos(0,0,0,?,?,0);

	//error : Cannot Load Last Status!
	}

	//Current track.
	m_repCounter=0;
	fDlg=NULL;

	//Nothing is playing ,so current sign is STOP rectangle
	m_sign=STOP;
	//Default color of volume display in LCD.
	m_volumeColor=RGB(133,133,133);
	
	//Verifications to display BITMAP Buttons.
	VERIFY(m_close.AutoLoad(IDC_CLOSE,this));
	VERIFY(m_eject.AutoLoad(IDC_EJECT,this));
	VERIFY(m_play.AutoLoad(IDC_PLAY,this));
	VERIFY(m_stop.AutoLoad(IDC_STOP,this));
	VERIFY(m_minimize.AutoLoad(IDC_MINIMIZE,this));
	VERIFY(m_back.AutoLoad(IDC_BACK,this));
	VERIFY(m_forward.AutoLoad(IDC_FORWARD,this));
	VERIFY(m_next.AutoLoad(IDC_NEXT,this));
	VERIFY(m_previous.AutoLoad(IDC_PREVIOUS,this));

	VERIFY(m_number.AutoLoad(IDC_NUMBER,this));
	VERIFY(m_playOrder.AutoLoad(IDC_PLAYORDER,this));
	VERIFY(m_repeate.AutoLoad(IDC_REPEATE,this));

	VERIFY(m_about.AutoLoad(IDC_ABOUT,this));
	VERIFY(m_playList.AutoLoad(IDC_DISPLAY_ALBUM,this));
	VERIFY(m_mixer.AutoLoad(IDC_MIXER,this));

	//Set Buttons Position!
	GetDlgItem(IDC_CLOSE)->SetWindowPos(0,517,14,24,24,0);
	GetDlgItem(IDC_MINIMIZE)->SetWindowPos(0,490,15,24,24,0);
	GetDlgItem(IDC_ABOUT)->SetWindowPos(0,461,15,24,24,0);
	GetDlgItem(IDC_DISPLAY_ALBUM)->SetWindowPos(0,90,0,42,11,0);
	
	GetDlgItem(IDC_MIXER)->SetWindowPos(0,135,0,42,11,0);

	GetDlgItem(IDC_NEXT)->SetWindowPos(0,516,63,24,24,0);
	GetDlgItem(IDC_PREVIOUS)->SetWindowPos(0,486,75,24,24,0);
	GetDlgItem(IDC_FORWARD)->SetWindowPos(0,458,82,24,24,0);
	GetDlgItem(IDC_BACK)->SetWindowPos(0,429,88,24,24,0);
	GetDlgItem(IDC_PLAY)->SetWindowPos(0,399,92,24,24,0);
	GetDlgItem(IDC_STOP)->SetWindowPos(0,369,95,24,24,0);
	GetDlgItem(IDC_EJECT)->SetWindowPos(0,341,97,24,24,0);
	
	GetDlgItem(IDC_NUMBER)->SetWindowPos(0,299,68,25,23,0);
	GetDlgItem(IDC_PLAYORDER)->SetWindowPos(0,291,93,23,15,0);
	GetDlgItem(IDC_REPEATE)->SetWindowPos(0,317,100,21,20,0);

	//Give "this" Ptr to LCD to create compatible DC when needed.
	//I think if we just create a pointer to DC, it will not 
	//be usefull.
	m_g.SetDC(this);

	//Display name in windows taskbar.
	this->SetWindowText("Win Audio");

	//Two buttons (+,-) on the screen are not button!
	//In order to create a button witch can work repeatedly
	//while mouse is on it and left button is pressed I just
	//used two pictures.To control these pictures I declared
	//some variables
	m_volumePressed=RELEASED;

	CRect tmpRect;
	GetWindowRect(tmpRect);
////////////////////////////////////////////////////////////////////
//		[CBitmap Slider class by "Joon-ho Ryu" using]
//		["Flicker Free Drawing In MFC" by Keith Rule]

	m_slider.SetBitmapChannel( IDB_CHANNEL, IDB_CHANNEL_ACTIVE );
	m_slider.SetBitmapThumb( IDB_THUMB, IDB_THUMB_ACTIVE, TRUE );
	m_slider.DrawFocusRect( FALSE );

	m_nMin = 0;
	m_nMax = 100;
	m_nPos = 0;

	m_slider.SetRange( m_nMin, m_nMax );
	m_slider.SetPos( m_nPos );

	m_slider.SetMargin( 0,0,0,0);
////////////////////////////////////////////////////////////////////
	m_OpenDlg=FALSE;
	InitInfoTooltip();
	
	CRgn rgn;
	rgn.CreateRoundRectRgn(3,1,550,145,20,20);
	SetWindowRgn((HRGN)rgn.GetSafeHandle(),FALSE);

	m_PlusRect=CRect(301,24,333,36);
	m_minusRect=CRect(301,39,333,52);
	m_captured=FALSE;

	// No tooltip created
	m_toolTip.m_hWnd = NULL;
	// Create ToolTip control
	m_toolTip.Create(this, TTS_ALWAYSTIP |  TTS_BALLOON);
	// Enable multiline
	m_toolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
	//m_ToolTip.SendMessage(TTM_SETTITLE, TTI_INFO, (LPARAM)_T("Title"));
	CRect r;
	GetClientRect(r);
	m_toolTip.AddTool(this,"Press left mouse button and hold down to change music volume",r, 1);
	m_toolTip.Activate(TRUE);

	m_canChangeVolume=TRUE;
	m_readOnce=FALSE;
	m_pListIsVisible = FALSE;
	m_mixerDlgIsVisible = FALSE;

	Invalidate(TRUE);

}	//end of init() function

//Redraws The Whole Skin
void CWinAudioDlg::DrawSkin()
{
	//Create a DeviceContext to use as amemory
	CDC			dcMem;
	//Create a bitmap object
	CBitmap		m_skin;
	//Create a ClientDeviceContext
	CClientDC	dc(this);

	//load picture of skin in to the Bitmap var.
	m_skin.LoadBitmap(IDB_SKIN);
	//Use dcMem to select the picture
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(m_skin);
	//Move picture from memory to real DC
	dc.BitBlt(m_skinRect.left+1,m_skinRect.top,m_skinRect.right,m_skinRect.bottom,
		&dcMem,0,0,SRCCOPY);
	//All variables will be deleted when returning.
}
//Left Mouse Button is Down?
void CWinAudioDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//Everybody know that left button is down
	m_LButtonDown=TRUE;
	//m_oldPoint is used to know where was the last point, witch
	//mouse clicked.I will use it later in other functions.
	m_oldPoint=point;

	//If point is inside volume (+) rectangle on the screen...
	if ( PtInRect(m_PlusRect,point) ) {
		//Increase volume
		OnPlus();
		//We can control other things when we check this var. later.
		m_volumePressed=PLUS_PRESSED;
		//If user hold down the mouse button on the volume
		//it should increase in some intervals.
		SetTimer(VOLUMES,100,0);
		//And at last user should be able to see the result
		//on the LCD
		m_g.UpdateVolumeButton(PLUS_PRESSED);
		//Do the same if mouse is in Volume decrease (-) rectangle.
	} else if ( PtInRect(m_minusRect,point) ) {
		OnMinus();
		m_volumePressed=MINUS_PRESSED;
		SetTimer(VOLUMES,100,0);
		m_g.UpdateVolumeButton(MINUS_PRESSED);
	}else {
		SetCapture( );
	}

	CDialog::OnLButtonDown(nFlags, point);
}

//Left Mouse Button Released...
void CWinAudioDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//Left mouse button is not down now
	m_LButtonDown=FALSE;
	//If the previous point in witch the mouse had been clicked
	//was in a special rectangle like (+) or (-) then we are sure
	//that a timer (VOLUME) had ben started so...
	if ( !(m_volumePressed==RELEASED) ) {
//		ReleaseCapture();
		//Mouse button released
		m_volumePressed=RELEASED;
		//Stop VOLUME timer
		KillTimer(VOLUMES);
		//Update screen for user
		m_g.UpdateVolumeButton(RELEASED);
		CDialog::OnLButtonUp(nFlags, point);
		return;
	}
	//Else mouse had been in the screen rectangle but not in a special
	//area so mouse had been captured in order to make movement of the
	//audio on the screen available, now it's time to release mouse 
	//capture so we can process it's other events.
	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}
//Mouse is Moving
void CWinAudioDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( (!m_captured) && (PtInRect(m_PlusRect,point) ||
		PtInRect(m_minusRect,point)) && (m_volumePressed==RELEASED) && (!m_LButtonDown)) {
		m_captured=TRUE;
		SetCapture();
        ::SetCursor(::LoadCursor(NULL, IDC_HAND));
		
	}
	if (!(PtInRect(m_PlusRect,point) || PtInRect(m_minusRect,point))) {
		if (m_captured) {
			ReleaseCapture();
			m_captured=FALSE;
		}
		m_toolTip.Pop();
	}
	//Count current rectangle dimentions.
	CRect	clntRect;
	GetClientRect(clntRect);
	//If the point (when mouse clicked[OnLbuttonDown]) was inside
	//the volume (+ or -) buttons begin!
	if ( PtInRect(m_PlusRect,m_oldPoint) ||  
		 PtInRect(m_minusRect,m_oldPoint)) {
		

		//If now left button is down while moving
		//and if CURRENT point is NOT inside them
		if ( ( m_LButtonDown ) && 
			!( (PtInRect(m_PlusRect,point)) || 
			   (PtInRect(m_minusRect,point)) )) {
			//Hey!enough increasing volume
			m_volumePressed=RELEASED;
			KillTimer(VOLUMES);
			m_g.UpdateVolumeButton(RELEASED);
		} else {  //If it is still in one of those (+ , -)
			CDialog::OnMouseMove(nFlags, point);
			return;
		}
		return;
	//Else If mouse had been on the skin when left button pressed and
	//it is down yet, we have to move the audio on the screen.
	} else {
	//	ReleaseCapture();
		if (m_LButtonDown) {

/*---UNDONE
			if (m_mixerDlgStat==true) {
			mDlg.animationClose();
			mDlg.ShowWindow(SW_HIDE);
			mDlg.DestroyWindow();
			m_mixerDlgStat=false;
		}
*/
		//Move window to the new place.
			CRect rect;
			GetWindowRect(rect);

			MoveWindow(rect.left+(point.x-m_oldPoint.x),rect.top+(point.y-m_oldPoint.y),
				 m_skinRect.right-m_skinRect.left+1,
				 m_skinRect.bottom-m_skinRect.top);
			if (m_pListIsVisible) {
				CRect lstRect;
				m_listDlg.GetWindowRect(lstRect);

				m_listDlg.MoveWindow(lstRect.left+(point.x-m_oldPoint.x),lstRect.top+(point.y-m_oldPoint.y),
					lstRect.right-lstRect.left,
					lstRect.bottom-lstRect.top,TRUE);
			}
			if (m_mixerDlgIsVisible) {
				CRect lstRect;
				m_mDlg.GetWindowRect(lstRect);

				m_mDlg.GetWindowRect(lstRect);
				m_mDlg.MoveWindow(lstRect.left+(point.x-m_oldPoint.x),lstRect.top+(point.y-m_oldPoint.y),
					lstRect.right-lstRect.left,
					lstRect.bottom-lstRect.top,TRUE);
			}
		};

	}
	CDialog::OnMouseMove(nFlags, point);
}
//Response to SetTimer() Funcs.
void CWinAudioDlg::OnTimer(UINT nIDEvent) 
{
	//Information timer
	if (nIDEvent==MARQUEE) {
		//Draw new Info. in memory.
		//m_MarqueeTxt.PrepareToUpdate();
		//Move inf. ffrom memory to screen
		//m_MarqueeTxt.TurnOn();
		m_g.UpdateInfo(MOVE);
	//Current Clock timer (Reverse clock)
	} else if (nIDEvent==CCLOCK) {
		//get time and update LCD and Slider
		CString time;
		time=GetMusicReverseTime();
		m_g.UpdateCurrTime(time);
		UpdateSlider();

		//If sound finished
		if (time=="00 : 00 : 00") {
			//m_debug="time=000,OnTimer";
			//Stop everything.
			OnStop();
			//We no longer need any clock timer
			KillTimer(CCLOCK);
			//If repeate is ON we have to continue.
			repeat();
		}
	//Spectrum timer
	} else if (nIDEvent==SPECTRUM) {
	//This item is under construction!
	//Create a random number for each peak in spectrum
	//and update LCD.
		/*int bar[8];
		for (int i=0;i<8;i++)
			bar[i]=rand()%32;
		//m_g.UpdateSpect(bar);*/
	} else if (nIDEvent==VOLUMES) {
		checkVolume();
	}
	CDialog::OnTimer(nIDEvent);
}
//Pausing Everything
void CWinAudioDlg::Pause()
{
	//Stop seek timer,peakmeter and sound
	KillTimer(CCLOCK);
	KillTimer(SPECTRUM);
	PauseMusic();
	//Change sign to pause
	m_g.SetPlaySign(PAUSE,TRUE);
	//Save the situation
	m_pause=TRUE;
}
//If paused then Resume
void CWinAudioDlg::Resume()
{
	//Update LCDs timer
	m_g.UpdateCurrTime(GetMusicReverseTime());
	//Rerun clock and spectrum timers
	SetTimer(CCLOCK,1000,0);
	SetTimer(SPECTRUM,100,0);
	//Resume playing
	ResumeMusic();
	//Change the Pause sign to PLAY
	m_g.SetPlaySign(PLAY,TRUE);
	m_pause=FALSE;
}
//Runs the Marquee (scrolling) text at the buttom of the LCD
//also puts the play sign & totalTime
void CWinAudioDlg::RunInfo()
{
	//Change sign to PLAY
	m_g.SetPlaySign(PLAY,TRUE);
	//Get information about the music from Info class
	m_infoStr=m_info.getInfo(m_fileName,m_fName);
	//Update total time on screen
	m_g.UpdateTotalTime(GetMusicTotalTime());
	//Set marquee object status
	/*m_MarqueeTxt.SetAll(this,m_infoStr,"Tahoma",
		1,1,0,120,263,145,16,0,RGB(220,250,255),
		RGB(300,300,300));*/
	m_g.SetMarqueeSpecifics(m_infoStr,"Arabic Transparent",1,0,120,263,145,16,
		RGB(220,250,255),RGB(300,300,300));
	//Run marquee , clock and spectrum timers
	SetTimer(MARQUEE,40,0);
	SetTimer(CCLOCK,1000,0);
	SetTimer(SPECTRUM,100,0);

//		[CBitmap Slider class by "Joon-ho Ryu" using]
//		["Flicker Free Drawing In MFC" by Keith Rule]
	InitSlider();
}
//this function checks for repeat situation witch user has selected
//Then updates the LCD sign and define a variables value [m_repCounter]
//to use when moving to next music file.
void CWinAudioDlg::repeat()
{
	CString tracktemp;
	//If just one file is selected
	if (m_fileCounter==1) {
		m_repCounter=1;
		return;
	}
	//Check and find the situation
	switch (m_repSituation) {
	case (RAND_REP_ONE):			//Repeate one | OnPlay->Randomize
		if (!m_oneReaded) {
			m_repCounter=rand()%(m_fileCounter-1);
			OnPlay();
			m_oneReaded=TRUE;
		} else 	OnPlay();
		break;
	case (RAND_REP_ALL):			//Repeate | All | Randomize
		m_repCounter=GetRandomNumber();//rand()%(m_fileCounter-1);

		OnStop();
		if (m_fileCounter!=1) {
			m_fileName=m_files[m_repCounter];
			tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
			m_g.UpdateCurrTrack(tracktemp);
			OnPlay();
		} else OnPlay();
		break;
	case (RAND_NOREP_ONE):			//Don't Repeate one | OnPlay->Randomize
		if (m_oneReaded==FALSE) {
			m_repCounter=GetRandomNumber();//rand()%(m_fileCounter-1);

			OnStop();
			m_fileName=m_files[m_repCounter];
			tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
			m_g.UpdateCurrTrack(tracktemp);
			OnPlay();
			m_oneReaded=TRUE;
		}
		break;
	case (RAND_NOREP_ALL):			//Don't Repeate | All | Randomize
		if (!m_readOnce) {
			m_repCounter=GetRandomNumber();//rand()%(m_fileCounter-1);
			OnStop();
			m_fileName=m_files[m_repCounter];
			tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
			m_g.UpdateCurrTrack(tracktemp);
			OnPlay();
		} else {
			m_readOnce=FALSE;
			m_g.m_allFilesPlayedOnce=FALSE;
			OnStop();
		}
		break;
	case (NORM_REP_ONE):			//Repeate one | Don't Random
		OnPlay();
		break;		
	case (NORM_REP_ALL):			//Repeate | All | Don't Random

		if (m_repCounter+1>=m_fileCounter)
			m_repCounter=-1;
		OnNext();
		break;
	case (NORM_NOREP_ONE):			//Don't Repeate one | Don't Random
		break;
	case (NORM_NOREP_ALL):			//Don't Repeate | All | Don't Random
		OnNext();
		break;
	}
	m_g.SetRepSign(m_repSituation,TRUE);
}
//Updates list of Files after file open dialog closed
void CWinAudioDlg::UpdateList()
{
	//I'm not sure, well, in fact I don't know exactly,because I'm
	//just a new [and beginner] programmer, if this works correctly.
	//Each time user selects some files (in file open dialog),
	//'m_files' pointer will points to a new amount of memory rooms
	//[to store address of selected files](depending to the user 
	//selection).
	//then by selecting new amount of files I make temp to point 
	//to the same address of memory witch 'm_files' points now.
	//then I delete the whole block witch temp now points to it,hoping
	//that pointer will be safe but the block will be deleted.
	//Because either I don't want to loose the 'm_files' variable 
	//and I want to free previous block of informations in memory
	//[created by 'new' function]).
	//So I hope to be able to get new array of addresses on disk,
	//as user selects new files and also hope to destroy previous block.
	//If you know any better way I'll be happy to hear that from you.
	//My informations are available in about me text file.
	if (m_files!=NULL) {
		CString	*tmp;
		if (m_fileCounter>1) {
			tmp=m_files;
			delete []tmp;
		}
		delete []m_randIndex;
//		m_randIndex=NULL;
		m_files=NULL;
	}
	
	m_fileCounter=fDlg->getCount();

	m_files=new CString[m_fileCounter];
	m_randIndex = new (int [m_fileCounter]);

	for (int i=0;i<m_fileCounter;i++) {
		m_files[i]=fDlg->listName(i);
		m_randIndex[i]=i;
	}
	m_lastRec=m_fileCounter-1;
	
	//if playlist is open,Reload file names and re fill combo box
	if (IsPlayListDialogModal()) {
		m_listDlg.LoadList();
	}
}
//To let the Dialog not to be closed by pressing ENTER as default key
void CWinAudioDlg::OnOK()
{}
//To let the Dialog not to be closed by pressing Esc as default key
void CWinAudioDlg::OnCancel()
{}
/*
//If User Double clicks the Volume Increse Button
void CWinAudioDlg::OnDoubleclickedPlus() 
{
	OnPlus();
	OnPlus();
}

//If User Double clicks the Volume Dencrese Button
void CWinAudioDlg::OnDoubleclickedMinus() 
{
	OnMinus();
	OnMinus();
}
*/
//Select and play next sound (or music) when
// the next button(>|) will be clicked
void CWinAudioDlg::OnNext() 
{
/*	for(int i=0;i<1000000;i++)
	{
		for (int j=0;j<1000;j++)
		{
			if(i==j)
			{
			}
		}
	}*/
	//If there is not any files at all.
	if (m_files==NULL ) return;

	//Else increse current playing track number
	//If random then
	if ( (m_repSituation==RAND_REP_ONE)  | 
		(m_repSituation==RAND_REP_ALL)   | 
		(m_repSituation==RAND_NOREP_ONE) | 
		(m_repSituation==RAND_NOREP_ALL)) {
		m_repCounter=GetRandomNumber();
		if (m_readOnce) {
			m_readOnce=FALSE;
			m_g.m_allFilesPlayedOnce=FALSE;
		}

	} else m_repCounter++;

	//Check that we are not out of the range
	if (m_repCounter>=m_fileCounter) {
		m_repCounter--;
		return;
	}
	//If music is playing, stop it.
	if (m_playing) OnStop();

	//Load new file, create it, Update LCD and play the file.
	m_fileName=m_files[m_repCounter];
	CString tracktemp;
	tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
	m_g.UpdateCurrTrack(tracktemp);
	OnPlay();
}
//Select and play previous sound (or music) when
// the previous button(|<) will be clicked
void CWinAudioDlg::OnPrevious() 
{
	//This fuction is just like the previous, but it does reverse
	if (m_files==NULL || m_fileCounter==1) return;

	m_repCounter--;
	if (m_repCounter<0) {
		m_repCounter=0;
		return;
	}
	OnStop();
	m_fileName=m_files[m_repCounter];
		
	CString tracktemp;
	tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
	m_g.UpdateCurrTrack(tracktemp);
	OnPlay();
}
//Exchanges the playing order between Random and Normal when user 
//clickes On it's Button (one of the 3 pie shape buttons On the left)
void CWinAudioDlg::OnPlayOrder() 
{
	//For more information on m_repSituation look at the defined
	//REPEATE enumulator.
	int sit=m_repSituation;

	if (sit<=4) sit+=4;
	else sit-=4;

	m_repSituation=(REPEAT) sit;
	m_g.SetRepSign(m_repSituation,TRUE);
}
//Exchanges the playing order between Repeate and NoRepeate when user 
//clickes On it's Button (one of the 3 pie shape buttons On the left)
void CWinAudioDlg::OnRepeateOrNot() 
{
	int sit=m_repSituation;

	if (sit==1 || sit==2 || sit==5 || sit==6) sit+=2;
	else sit-=2;
	
	m_repSituation=(REPEAT) sit;
	m_g.SetRepSign(m_repSituation,TRUE);
}
//Exchanges the playing order between One and All when user 
//clickes On it's Button (one of the 3 pie shape buttons On the left)
void CWinAudioDlg::OnAllOrOne() 
{
	int m_sit=m_repSituation;

	if (m_sit%2==0) m_sit--;
	else m_sit++;

	m_repSituation=(REPEAT) m_sit;
	m_g.SetRepSign(m_repSituation,TRUE);
}
//Defined to work when user clickes very quickly more than one time.
void CWinAudioDlg::OnDoubleclickedPlayOrder() 
{
	OnPlayOrder();	
}
//Defined to work when user clickes very quickly more than one time.

void CWinAudioDlg::OnDoubleclickedRepeate() 
{
	OnRepeateOrNot();
}

//Defined to work when user clickes very quickly more than one time.
void CWinAudioDlg::OnDoubleclickedNumber() 
{
	OnAllOrOne();
}
//Seek forward once each time user clicks on it's button (>>)
void CWinAudioDlg::OnForward() 
{
	ForwardMusic(5000);
}
//Seek backward once each time user clicks on it's button (<<)
void CWinAudioDlg::OnBack() 
{
	BackwardMusic(5000);
}
//Under Construction
//Not ready yet
void CWinAudioDlg::OnWindowsMixer() 
{
	WinExec("sndvol32.exe", SW_SHOW);
}
//Do initializations for Bitmap slider (Seek navigator)
//		[CBitmap Slider class by "Joon-ho Ryu" using
//		 "Flicker Free Drawing In MFC" by Keith Rule]
void CWinAudioDlg::InitSlider()
{
	m_slider.SetRange(0,MCIWndGetLength(musicWnd));
	m_slider.SetPos(0);
}
//Change the current position
void CWinAudioDlg::UpdateSlider()
{
	m_slider.SetPos(MCIWndGetPosition(musicWnd));
}
//Find out witch process should be done after finding out
//where the mouse had been clicked on the skin and also
//realizing that it was on one of volume buttons
void CWinAudioDlg::checkVolume()
{
	if (m_volumePressed==RELEASED)
		return;
	else if (m_volumePressed==PLUS_PRESSED)
		OnPlus();
	else if (m_volumePressed==MINUS_PRESSED)
		OnMinus();
}
//I don't understand,why this function does not response
//when one or more item(s) places on the dialog.!!!!!!!!!???????
//However it does response when there is nothing on the dialog
void CWinAudioDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	MessageBox("a Key Preesed");	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
//For more information see "Joon-ho Ryu" CBitmapSlider class
//documentation on this web site (www.TheCodeProject.com).
//
//		[CBitmap Slider class by "Joon-ho Ryu" using
//		 "Flicker Free Drawing In MFC" by Keith Rule]
LRESULT CWinAudioDlg::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
{
	UINT curr=m_slider.GetPos();
	
	int tempVol=m_volume;
	SetMusicVolume(0);
	MCIWndStop(musicWnd);
	MCIWndSeek(musicWnd,curr);
	MCIWndPlay(musicWnd);
	SetMusicVolume(m_volume);

	return 0;
}
//Look above, please.thank you!
LRESULT CWinAudioDlg::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
//Best piece of this code!
//about programme and me!!
void CWinAudioDlg::OnAbout() 
{
	CAboutDlg adlg;
	adlg.DoModal();
}

BOOL CWinAudioDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	OnAbout();
//	return CDialog::OnHelpInfo(pHelpInfo);
	return TRUE;
}

void CWinAudioDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl==IDC_ABOUT) {

		m_g.UpdateAll();
		
		//graphical slider witch classes are designed and
		//also belong to "Joon-ho Ryu" they use
		//"Flicker Free Drawing In MFC" by Keith Rule.
		m_slider.RedrawWindow();
	};
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

bool CWinAudioDlg::SaveInfo()
{
	FILE *fp;
	CString fileName,s;
	
	GetModuleFileName(NULL,s.GetBuffer(512),512);
	s.ReleaseBuffer();
	//remove executable file name
	s.Delete(s.ReverseFind('\\'),s.GetLength()-s.ReverseFind('\\'));
	fileName=s;
	fileName+="\\layout.hda";

	struct fileInfo {
		int   vol;
		int   repStat;
		int	  fileCount;
		CRect pos;
	};
	fileInfo info;

	info.vol=m_volume;
	info.repStat=m_repSituation;
	CRect tempR;
	GetWindowRect(tempR);
	info.pos=tempR;
	info.fileCount=m_fileCounter;

	if ( !(fp=fopen(fileName,"rb+wb")) ) {
		if (!(fp=fopen(fileName,"wb"))){
			MessageBox("Disk Error! Cannot Save Info Into Disk File.");
			return false;
		}
	}

	int x=fwrite(&info,sizeof(fileInfo),1,fp);
	fclose(fp);
//	CString temp;
//	temp.Format("Resault=%d , Rep=%d , Volume=%d",
//		x,m_repSituation,m_volume);
//	MessageBox(temp);

	char buff[80];
	CString name="";
	fileName=s;
	fileName+="\\files.hda";

	if ( !(fp=fopen(fileName,"rb+wb")) ) {
		if (!(fp=fopen(fileName,"wb"))){
			MessageBox("Disk Error! Cannot Save Info Into Disk File.");
			return false;
		}
	}

	if (m_files!=NULL) {

		for (int i=0;i<m_fileCounter;i++) {
			for (int j=0;j<80;j++) buff[j]=' ';
			name=CString(m_files[i]);
			name.TrimLeft();
			name.TrimRight();
			fputs(name,fp);
			fputs("\r\n",fp);
		}
	} else if (m_fileName!="") {
		fputs(m_fileName,fp);
		fputs("\r\n",fp);
	}
	fclose(fp);
	
	return true;
}

bool CWinAudioDlg::LoadInfo()
{
	m_volume=0;
	m_repSituation=NORM_NOREP_ALL;

	FILE *fp;
	CString fileName,s;

	GetModuleFileName(NULL,s.GetBuffer(512),512);
	s.ReleaseBuffer();
	//remove executable file name
	s.Delete(s.ReverseFind('\\'),s.GetLength()-s.ReverseFind('\\'));
	fileName=s;
	fileName+="\\layout.hda";
	//fileName=s;
	struct fileInfo {
		int   vol;
		int   repStat;
		int	  fileCount;
		CRect pos;
	};
	fileInfo info;

	if (!(fp=fopen(fileName,"r")) ) {
		m_volume=0;
		m_repSituation=NORM_NOREP_ALL;
		return false;
	}
	int x=fread(&info,sizeof(fileInfo),1,fp);
	m_volume=info.vol;
	m_repSituation=(REPEAT)info.repStat;

	m_g.SetDefinitionData(m_volume,m_repSituation);
	SetWindowPos(0,info.pos.left,info.pos.top,
		info.pos.right-info.pos.left,
		info.pos.bottom-info.pos.top,0);
		
	m_fileCounter=info.fileCount;

	fclose(fp);
//////////////////////////////////////////////////////////////
	if (m_fileCounter==0) {
		m_files=NULL;
		//Number of files currently selected.
		m_fileCounter=0;
		return true;
	}
	CString str="";
	fileName=s;
	fileName+="\\files.hda";

	if (!(fp=fopen(fileName,"r")) ) {
		m_volume=0;
		m_repSituation=NORM_NOREP_ALL;
		return false;
	}
	if (m_fileCounter>1) m_files=new CString[m_fileCounter]; 
	else m_files = new CString;
	m_randIndex = new (int [m_fileCounter]);

	char buff[80];

	for (int i=0;i<m_fileCounter;i++) {
		//int x=fwrite(&fileName,sizeof(fileInfo),1,fp);
		fgets(buff,80,fp);
		str=buff;
		//str.Delete(str.ReverseFind('\r\n'),str.GetLength()-str.ReverseFind('\r\n'));
		str.TrimLeft();
		str.TrimRight();
		m_files[i]=str;

		str="";
		for (int j=0;j<80;j++) buff[j]=' ';
		m_randIndex[i]=i;
	}
	m_lastRec=m_fileCounter-1;
	fclose(fp);

	m_fileName=m_files[0];
	return true;
}

void CWinAudioDlg::InitInfoTooltip()
{
	EnableToolTips();
}

BOOL CWinAudioDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT pResult)
{
	TOOLTIPTEXT *pTTT=(TOOLTIPTEXT*) pNMHDR;
	UINT nID=pNMHDR->idFrom;
	if (pTTT->uFlags & TTF_IDISHWND) {
		nID=::GetDlgCtrlID((HWND)nID);
		if (nID==IDC_TOOLTIP) {
			LPTSTR lpsz = new TCHAR[m_infoStr.GetLength()+1];
			_tcscpy(lpsz, m_infoStr);
			pTTT->lpszText=lpsz;
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_PLAY) {
			pTTT->lpszText="Play/Pause (Farsi: ÎÔ/ÊæÞÝ ãæÞÊ)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_EJECT) {
			pTTT->lpszText="Open new File(s) (Farsi: ÈÇÒ˜ÑÏä ÝÇíá ÌÏíÏ)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_NUMBER) {
			pTTT->lpszText="Play just one file or all selected files (Farsi: ÇÌÑÇí í˜ ÝÇíá íÇ åãå ÝÇíáåÇí ÇäÊÎÇÈ ÔÏå)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_PLAYORDER) {
			pTTT->lpszText="Play files normal (serial) or Random (Farsi: ÇÌÑÇí ÝÇíáåÇ Èå ÕæÑÊ äÑãÇá íÇ ÊÕÇÏÝí)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_REPEATE) {
			pTTT->lpszText="Repeate playing after all files played once or Not (Farsi: Ê˜ÑÇÑ ÝÇíáåÇ Ó ÇÒ í˜ÈÇÑ ÎÔ ÔÏä åãå ÂäåÇ)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_STOP) {
			pTTT->lpszText="Stop Playing (Farsi: ÊæÞÝ ˜Çãá ãæÓíÞí)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_BACK) {
			pTTT->lpszText="Backward, 5 Sec. (Farsi: ÈÇÒÔÊ Èå ÚÞÈ Èå ÇäÏÇÒå 5 ËÇäíå)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_FORWARD) {
			pTTT->lpszText="Forward, 5 Sec. (Farsi: ÍÑ˜Ê Èå Ìáæ Èå ÇäÏÇÒå 5 ËÇäíå)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_PREVIOUS) {
			pTTT->lpszText="Play previous sound(Music) in the selected list (Farsi: ÇÌÑÇí ãæÒí˜ ÞÈáí)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_NEXT) {
			pTTT->lpszText="Play next sound(Music) in the selected list (Farsi: ÇÌÑÇí ãæÒí˜ ÈÚÏí)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_MINIMIZE) {
			pTTT->lpszText="Minimize AudioPlayer (Farsi: ÇäÊÞÇá äÌÑå Èå äæÇÑ æÙíÝå)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_CLOSE) {
			pTTT->lpszText="Exit(Farsi: ÎÑæÌ)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_ABOUT) {
			pTTT->lpszText="About Win Audio...(Farsi: ... ÏÑ ãæÑÏ ÈÑäÇãå)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_SLIDER) {
			pTTT->lpszText="Navigation bar (Farsi: äæÇÑ ˜äÊÑá ãæÞÚíÊ ÌÇÑí ãæÒí˜)";
			pTTT->hinst=AfxGetResourceHandle();
			return(TRUE);
		} else if (nID==IDC_MIXER) {
			pTTT->lpszText="Sound Mixer bar (Farsi:ãíßÓÑ ÕÏÇ)";
			pTTT->hinst=AfxGetResourceHandle();
		} else if (nID==IDC_DISPLAY_ALBUM) {
			pTTT->lpszText="List of selected files (Farsi:áíÓÊ ÝÇíáåÇí ÇäÊÎÇÈ ÔÏå ÈÑÇí ÎÔ)";
			pTTT->hinst=AfxGetResourceHandle();
		} else {
//			MessageBox("NOTIFY");
		}
	} 
	return(FALSE);
}

BOOL CWinAudioDlg::CreateMusic(CString file)
{
	if (m_playing) return(FALSE);

	if (musicWnd=MCIWndCreate(m_animate.GetSafeHwnd(),
		AfxGetInstanceHandle(),MCIWNDF_NOOPEN|MCIWNDF_NOPLAYBAR|
		MCIWNDF_NOMENU,file)) return(TRUE);
	else return(FALSE);
}

BOOL CWinAudioDlg::PlayMusic(CString file)
{
	if (m_playing) return(FALSE);

	if (!CreateMusic(file)) return(FALSE);
	
	CString str,mp3;
	str=file[file.GetLength()-3];
	str+=file[file.GetLength()-2];
	str+=file[file.GetLength()-1];
	str.MakeLower();

	if (str=="mp3" || str=="avi" ) m_canChangeVolume=TRUE;
	else m_canChangeVolume=FALSE;
	if (m_canChangeVolume) MCIWndSetVolume(musicWnd,m_volume);

	MCIWndPlay(musicWnd);
	return(TRUE);
}

void CWinAudioDlg::SetMusicVolume(int newVolume)
{
	if (m_canChangeVolume) MCIWndSetVolume(musicWnd,newVolume);
}

BOOL CWinAudioDlg::PauseMusic()
{
	if (!m_playing) return(FALSE);

	MCIWndPause(musicWnd);
	return(TRUE);
}

BOOL CWinAudioDlg::ResumeMusic()
{
	if (!m_playing) return(FALSE);
	
	MCIWndResume(musicWnd);
	return(TRUE);
}

BOOL CWinAudioDlg::ForwardMusic(int step)
{
	if (!m_playing) return(FALSE);
	
	int curr=MCIWndGetPosition(musicWnd);
	MCIWndStop(musicWnd);
	curr+=step;

	if (curr<MCIWndGetLength(musicWnd))
		MCIWndSeek(musicWnd,curr);

	MCIWndPlay(musicWnd);
	return(TRUE);
}

BOOL CWinAudioDlg::BackwardMusic(int step)
{
	if (!m_playing) return(FALSE);
	
	int curr=MCIWndGetPosition(musicWnd);
	MCIWndStop(musicWnd);
	curr-=step;

	if (curr>0) 
		MCIWndSeek(musicWnd,curr);

	MCIWndPlay(musicWnd);
	return(TRUE);
}

BOOL CWinAudioDlg::StopMusic()
{
	if (!m_playing) return(FALSE);

	MCIWndStop(musicWnd);
	MCIWndDestroy(musicWnd);

	return(TRUE);
}

CString CWinAudioDlg::GetMusicTotalTime()
{
	if (!m_playing) return("00 : 00 : 00");
	int		hour,
			minute,
			second;
	double	m_length;

	CString min,
			totalTime;

	MCIWndSetTimeFormat(musicWnd ,"ms");
 	m_length=MCIWndGetLength(musicWnd);
//	m_lengthConst=m_length;
	m_length/=1000;
	if (m_length<60) {
		
		CString temp;
		temp.Format("%2.0f",m_length);
		if (m_length<10)
			totalTime="00 : 00 : 0"+temp;
		else totalTime="00 : 00 : "+temp;

		m_tS=(int)m_length;
		m_tM=0;
		m_tH=0;
		return totalTime;
	}

	hour=(int)(m_length/3600);
	
	int m_fLength=(int)m_length;
	
	if ( hour<1 ){
		minute=(m_fLength/60);
		second=(m_fLength%60);
		hour=0;
	} else {
		minute=(m_fLength%3600) /60;
		second=(m_fLength%3600) %60;
	}
	
	m_tS=second;
	m_tM=minute;
	m_tH=hour;

	CString temp;
	
	if (hour<10) min="0";
	else min="";
	
	temp.Format("%d",hour);
	min+=temp;
	min+=" : ";

	if (minute<10) min+="0";
	temp.Format("%d",minute);
	min+=temp;
	min+=" : ";

	if (second<10) min+="0";
	temp.Format("%d",second);
	min+=temp;

	totalTime=min;

	return min;
}

void CWinAudioDlg::CountElapsedTime()
{
	double length,temp;
	int hour,minute,second;

	length=MCIWndGetPosition(musicWnd);
	temp=MCIWndGetLength(musicWnd)-length;
	temp/=1000;
	if (temp<60) {
		m_tS=(int)temp;
		m_tM=0;
		m_tH=0;
		return;
	}

	hour=(int)(temp/3600);

	int m_fLength=(int)temp;

	if ( hour<1 ){
		minute=(m_fLength/60);
		second=(m_fLength%60);
		hour=0;
	} else {
		minute=(m_fLength%3600) /60;
		second=(m_fLength%3600) %60;
	}
	
	m_tS=second;
	m_tM=minute;
	m_tH=hour;
}

CString CWinAudioDlg::GetMusicReverseTime()
{
	if (!m_playing) return("00 : 00 : 00");

	CountElapsedTime();
	
	if (m_tH==0 && m_tM==0 && m_tS==0) {
		m_currentTime="00 : 00 : 00";
		return m_currentTime;
	}
	if (m_tS<0) {
		if (m_tM>0) m_tM--;
		m_tS=59;
	}
	if (m_tM<0) {
		if (m_tH>0) m_tH--;
		m_tM=59;
	}
	CString tempH="",tempM="",tempS="";

	tempH.Format("%d",m_tH);
	if (m_tH<10) tempH="0"+tempH;

	tempM.Format("%d",m_tM);
	if (m_tM<10) tempM="0"+tempM;

	tempS.Format("%d",m_tS);
	if (m_tS<10) tempS="0"+tempS;

	m_currentTime=tempH+" : "+tempM+" : "+tempS;
	return m_currentTime;
}

UINT CWinAudioDlg::GetRandomNumber()
{
	int res=0;
	int Rand;
	if (m_lastRec!=0)	Rand=rand()%m_lastRec;
	else Rand=0;

	res=m_randIndex[Rand];

	if (Rand==m_lastRec) {
		m_lastRec--;
	} else m_randIndex[Rand]=m_randIndex[m_lastRec--];

	//m_readOnce=FALSE;

	if (m_lastRec<0) {		//all files repeated once (or once again!)
		m_lastRec=m_fileCounter-1;
		for (int i=0;i<m_fileCounter;i++)	m_randIndex[i]=i;
		m_readOnce=TRUE;
		m_g.m_allFilesPlayedOnce=TRUE;
	}
	return res;
}


int CWinAudioDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


BOOL CWinAudioDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (m_captured) m_toolTip.RelayEvent(pMsg);
	//m_toolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CWinAudioDlg::StrToChar(CString &source, char *dest, int count)
{
	for (int i=0;i<count;i++)
		dest[i]=source[i];
}

void CWinAudioDlg::OnDisplayAlbum() 
{
	CRect rct;
	GetWindowRect(rct);
	m_listDlg.SetPos(rct.left,rct.top);

	if (IsPlayListDialogModal()) ClosePlayList();
	else OpenPlayList();

}

CString CWinAudioDlg::GetFileName(int index)
{

	CString rowNumStr = "";
	CString tempStr = "Nothing";// = m_files;
	rowNumStr.Format("[%d] : ",index+1);

	if (m_files!=NULL && index<m_fileCounter) {
		tempStr = m_files[index];
		tempStr.Delete(0,tempStr.ReverseFind('\\')+1);
		tempStr=rowNumStr+tempStr;
	}
	else if (m_fileName!="") {
		tempStr = m_fileName;
		tempStr.Delete(0,tempStr.ReverseFind('\\')+1);
		tempStr=rowNumStr+tempStr;
	}
	return tempStr;
}

UINT CWinAudioDlg::GetNumberOfFiles()
{
//	CString str;
//	str.Format("%d",m_fileCounter);
//	MessageBox(str);
	return m_fileCounter;
}

void CWinAudioDlg::PlayFromList(int index)
{
	//If there is not any files at all.
	if (m_files==NULL ) return;

	m_repCounter = index;
	//Check that we are not out of the range
	if (m_repCounter>=m_fileCounter) {
		//m_repCounter=0;
		return;
	}
	//If music is playing, stop it.
	if (m_playing) OnStop();

	//Load new file, create it, Update LCD and play the file.
	m_fileName=m_files[m_repCounter];
	CString tracktemp;
	tracktemp.Format("%d / %d",m_repCounter+1,m_fileCounter);
	m_g.UpdateCurrTrack(tracktemp);
	OnPlay();

}

UINT CWinAudioDlg::GetCurentIndex()
{
	if (!m_playing) return 0;
	else return m_repCounter;
}

BOOL CWinAudioDlg::IsPlayListDialogModal()
{
	return 	m_pListIsVisible;
}

void CWinAudioDlg::OpenPlayList()
{
	if (!m_pListIsVisible) {
		m_listDlg.Create(IDD_PLAY_LIST_DLG);
		m_listDlg.ShowWindow(SW_SHOW);
		m_pListIsVisible = TRUE;
	}
}

void CWinAudioDlg::ClosePlayList()
{
	if (m_pListIsVisible) {
		m_listDlg.Animate(1);
		m_listDlg.DestroyWindow();
		m_pListIsVisible = FALSE;
	}
}

void CWinAudioDlg::OnMixer() 
{
	CRect rct;
	GetWindowRect(rct);

	if (!m_mixerDlgIsVisible) {
		m_mDlg.SetPos(rct.left+200,rct.top);
		m_mDlg.Create(IDD_MIXER_DLG);
		m_mDlg.ShowWindow(SW_SHOW);
		m_mixerDlgIsVisible = TRUE;
	} else {
		m_mDlg.ShowWindow(SW_HIDE);
		m_mDlg.DestroyWindow();
		m_mixerDlgIsVisible = FALSE;
	}
}
