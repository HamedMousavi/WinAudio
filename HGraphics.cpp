// HGraphics.cpp: implementation of the HGraphics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinAudio.h"
#include "HGraphics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define RecourceSkin IDB_SKIN
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HGraphics::HGraphics()
{
	m_inited=FALSE;
	m_repSgn=8;
}

HGraphics::~HGraphics()
{
	TRACE("\nEntering destructive...\n");
	ReleaseMemory();
}
void HGraphics::Init()
{
	TRACE("\n1.Start Init...\n");
	m_pDC=0;
	m_tTime="00 : 00 : 00";
	m_cTime="00 : 00 : 00";
//	m_vol=0;
	m_sign=1;
	m_trackNo="000/000";
	m_InvisibleColor=RGB(255,0,0);

	m_font.CreateFont(/*Height*/16,/*Width*/0,/*Rotation*/0,0,
		/*Bold*/400,/*Italic*/FALSE,/*Underline*/FALSE,
		/*MiddleLine*/FALSE,ANSI_CHARSET,OUT_TT_ONLY_PRECIS,
		CLIP_EMBEDDED,PROOF_QUALITY,FIXED_PITCH,"Tahoma");

	TRACE("\n2.Initializing signs... \n");
	InitSigns();
	TRACE("\n3.Initializing background... \n");
	InitBackground();
	TRACE("\n4.Inittializing rectangles... \n");
	InitRects();
	TRACE("\n5.creating pictures... \n");
	CreateLcdPictures();
	m_allFilesPlayedOnce=FALSE;
	m_inited=TRUE;
	TRACE("\n6.Exit Init... \n");
}

BOOL HGraphics::TransparentPicture(CDC *PicMemDC, CRect PicRect, int ID,CBitmap* Bitmap)
{
	TRACE("\n7.Start Transparenting process...\n");
	if (!m_pDC || ID==0 || !PicMemDC) return FALSE;
	if (PicRect.bottom-PicRect.top==0 || PicRect.right-PicRect.left==0)
		return FALSE;
	
	CBitmap			*OldBMP;
	COLORREF	PixelColor;
	CPoint		DCPoint,BitmapPoint;
	
	Bitmap->LoadBitmap(ID);

	if (!PicMemDC->CreateCompatibleDC(m_pDC)) return FALSE;
	
	OldBMP=PicMemDC->SelectObject(Bitmap);
	m_oldBitmap=(HBITMAP) OldBMP->GetSafeHandle();
	
	for(int i=0;i<PicRect.right-PicRect.left;i++)
		for(int j=0;j<PicRect.bottom-PicRect.top;j++) {
			
			DCPoint.x=PicRect.left+i;
			DCPoint.y=PicRect.top+j;
			BitmapPoint.x=i;
			BitmapPoint.y=j;
			
			PixelColor=PicMemDC->GetPixel(BitmapPoint);
			if (PixelColor==m_InvisibleColor) {
				PixelColor=m_skinTempDC.GetPixel(DCPoint);
				PicMemDC->SetPixel(BitmapPoint,PixelColor);
			}
		}

	TRACE("\nEnd transparenting...\n");
	return TRUE;
}

BOOL HGraphics::CreatePicture(CDC *PicMemDC, CRect PicRect,CBitmap* Bitmap)
{
	TRACE("\nStart Create Pictures... \n");

	if (!m_pDC || !PicMemDC) return FALSE;
	if (PicRect.bottom-PicRect.top==0 || PicRect.right-PicRect.left==0)
		return FALSE;

	COLORREF	PixelColor;
	CPoint		DCPoint,BitmapPoint;

	if (!PicMemDC->CreateCompatibleDC(m_pDC)) return FALSE;

	Bitmap->CreateCompatibleBitmap(m_pDC,PicRect.right-PicRect.left,
		PicRect.bottom-PicRect.top);
	PicMemDC->SelectObject(Bitmap);

	for(int i=0;i<(PicRect.right-PicRect.left);i++)
		for(int j=0;j<(PicRect.bottom-PicRect.top);j++) {
			
			DCPoint.x=PicRect.left+i;
			DCPoint.y=PicRect.top+j;
			BitmapPoint.x=i;
			BitmapPoint.y=j;
			
			PixelColor=m_pDC->GetPixel(DCPoint);
			PicMemDC->SetPixel(BitmapPoint,(PixelColor));
		}

	TRACE("\nEnd create pictures...\n");
	return TRUE;
}

void HGraphics::SetDC(CWnd *pdc)
{
	TRACE("\nSetting DC \n");
	m_boddey=pdc;
}

void HGraphics::InitRects()
{
	m_LCDTtimeRect.SetRect(60,20,132,35);
	m_LCDCtimeRect.SetRect(60,35,132,50);
	m_LCDtrackRect.SetRect(60,50,132,67);
	m_LCDinfoRect.SetRect(17,101,278,119);
	m_LCDvolumeRect.SetRect(259,39,278,100);
	m_lcdRect.SetRect(19,25,300,114);
	
	m_LCDrepSgnRect[0].SetRect(22,68,46,95);
	m_LCDrepSgnRect[1].SetRect(22,68,46,95);
	m_LCDrepSgnRect[2].SetRect(46,68,90,95);
	m_LCDrepSgnRect[3].SetRect(46,68,90,95);
	m_LCDrepSgnRect[4].SetRect(86,68,134,95);
	m_LCDrepSgnRect[5].SetRect(86,68,134,95);
	m_LCDplaySgnRect.SetRect(235,20,250,32);
	TRACE("\nEnd initializing rectangles... \n");
}

void HGraphics::InitSigns()
{
 	m_repSign[0]=OG_SGN_ONE;
	m_repSign[1]=OG_SGN_ALL;
	m_repSign[2]=OG_SGN_RAND;
	m_repSign[3]=OG_SGN_N_RAND;
	m_repSign[4]=OG_SGN_REP;
	m_repSign[5]=OG_SGN_N_REP;

	m_playSign[0]=IDB_LCD_OG_SGN_PLAY;
	m_playSign[1]=IDB_LCD_OG_SGN_STOP;
	m_playSign[2]=IDB_LCD_OG_SGN_PAUSE;
	TRACE("\nEnd initializing signs... \n");
}

void HGraphics::CreateLcdPictures()
{
	TRACE("\nStart Creating lcd pictures\n");
	CreatePicture(&m_LCDTtimeDC,m_LCDTtimeRect,&m_LCDTtime);
	CreatePicture(&m_LCDCtimeDC,m_LCDCtimeRect,&m_LCDCtime);
	CreatePicture(&m_LCDtrackDC,m_LCDtrackRect,&m_LCDtrack);
	CreatePicture(&m_LCDvolumeDC,m_LCDvolumeRect,&m_LCDvolume);
	CreatePicture(&m_LCDinfoDC,m_LCDinfoRect,&m_LCDinfo);

	// !! Important !!
	//Backgtround skin MUST be PAINTed before calling this function
	for (int i=0;i<6;i++)
		TransparentPicture(&m_LCDrepSgnDC[i],
							m_LCDrepSgnRect[i],
							m_repSign[i],&m_LCDrepSgn[i]);
	
	for (int j=0;j<3;j++)
		TransparentPicture(&m_LCDplaySgnDC[j],
							m_LCDplaySgnRect,
							m_playSign[j],&m_LCDplaySgn[j]);
	TRACE("\nEnd creating lcd pictures...\n");
}

void HGraphics::InitBackground()
{
	CBitmap *oldSkin;
	CFont *oldFont;

	m_pDC=new CClientDC(m_boddey);
	
	m_skinDC.CreateCompatibleDC(m_pDC);
	oldFont=(CFont*) m_skinDC.SelectObject(&m_font);
	m_oldFont=(HFONT) oldFont->GetSafeHandle();
	m_skinDC.SetTextColor(RGB(255,255,0));
	m_skinDC.SetBkColor(TRANSPARENT);

	m_skinTempDC.CreateCompatibleDC(m_pDC);
	m_skinTempDC.SelectObject(&m_font);
	m_skinTempDC.SetTextColor(RGB(255,255,0));
	m_skinTempDC.SetBkColor(TRANSPARENT);

	
	m_skinBitmap=new CBitmap;
	m_skinTempBitmap=new CBitmap;
	m_skinBitmap->LoadBitmap(RecourceSkin);
	m_skinTempBitmap->LoadBitmap(RecourceSkin);

	oldSkin=(CBitmap*) m_skinDC.SelectObject(m_skinBitmap);
	m_skinTempDC.SelectObject(m_skinTempBitmap);
	
	m_oldSkin=(HBITMAP)oldSkin->GetSafeHandle();
	m_pDC->BitBlt(1,0,555,146,&m_skinTempDC,0,0,SRCCOPY);	
	
	// must release m_skindc & m_skintempdc (m_oldSkin) & (m_oldFont)
	//and delete m_skinbitmap
	TRACE("\nEnd init background... \n");
}

void HGraphics::UpdateAll()
{
	TRACE("\nStart updating all... \n");

	if (!m_inited) return;

	m_skinTempDC.BitBlt(0,0,550,149,&m_skinDC,0,0,SRCCOPY);
	m_skinTempDC.SetBkMode(TRANSPARENT);

	//update dc texts
	m_skinTempDC.SetTextColor(RGB(200,245,250));
	m_skinTempDC.TextOut(20,18," Total");
	m_skinTempDC.TextOut(20,33," Curr.");
	m_skinTempDC.TextOut(20,48," Track");
	m_skinTempDC.TextOut(255,18," Vol.");

/*	if (m_allFilesPlayedOnce) {
		m_skinTempDC.SetTextColor(RGB(250,255,0));
		m_skinTempDC.TextOut(139,19,"All Played Once");
//	m_skinTempDC.SetTextColor(RGB(250,0,0));
//	m_skinTempDC.TextOut(140,18,"All Played Once");
	}*/
	
	//update total time
	m_skinTempDC.SetTextColor(RGB(250,250,0)/*m_clockTextColor*/);
	m_skinTempDC.TextOut(m_LCDTtimeRect.left,m_LCDTtimeRect.top,
						 m_tTime);

	//updateVolume(m_vol);
	DrawVolumeBar(FALSE);

	//update Current Time
	m_skinTempDC.TextOut(m_LCDCtimeRect.left,
						 m_LCDCtimeRect.top,m_cTime);

	//update current track no
	m_skinTempDC.TextOut(m_LCDtrackRect.left,m_LCDtrackRect.top,
						 m_trackNo);

	//update sign
	SetPlaySign(m_sign,FALSE);

	//update repeate sign
	SetRepSign(m_repSgn,FALSE);

	m_pDC->BitBlt(1,0,555,146,&m_skinTempDC,0,0,SRCCOPY);
	TRACE("\nEnd updating all... \n");
}

void HGraphics::DotLine(int x1, int y1, int x2, int y2, BOOL screenDC)
{
	COLORREF	m_VColor;
	m_VColor=RGB(190,200,220);
	
	while (x1<x2) {
		if (screenDC) m_pDC->SetPixel(x1,y1,m_VColor);
		else m_skinTempDC.SetPixel(x1-1,y1,m_VColor);

		x1+=2;
	}
}

void HGraphics::DrawVolumeBar(BOOL screenDC)
{
	TRACE("\nDrawing volume...\n");
	for (int i=0;i<(m_vol/50);i++)
		DotLine(260,97-(i*3),275,97-(i*3),screenDC);
}

void HGraphics::SetPlaySign(int sign, BOOL screenDC)
{
	TRACE("\nSetting playing signs...\n");
	if (sign<0 || sign>3) return;
	
	if (screenDC) m_pDC->BitBlt(m_LCDplaySgnRect.left,
		m_LCDplaySgnRect.top,
		m_LCDplaySgnRect.right-m_LCDplaySgnRect.left,
		m_LCDplaySgnRect.bottom-m_LCDplaySgnRect.top,
		&m_LCDplaySgnDC[sign],0,0,SRCCOPY);

	else m_skinTempDC.BitBlt(m_LCDplaySgnRect.left,
		m_LCDplaySgnRect.top,
		m_LCDplaySgnRect.right-m_LCDplaySgnRect.left,
		m_LCDplaySgnRect.bottom-m_LCDplaySgnRect.top,
		&m_LCDplaySgnDC[sign],0,0,SRCCOPY);

	m_sign=sign;
}

void HGraphics::SetRepSign(int sign, BOOL screenDC)
{
	TRACE("\nSetting repeate mode signs...\n");
	int sgn1=0,sgn2=0,sgn3=0;

	m_repSgn=sign;
	
	switch (sign) {		//0,2,4
	case (1):			//Repeate one | OnPlay->Randomize	([<-?>])
		sgn1=0;sgn2=2;sgn3=4;
		break;			//1,2,4
	case (2):			//Repeate | All | Randomize			([<-_-_->])
		sgn1=1;sgn2=2;sgn3=4;
		break;			//0,2,5
	case (3):			//Don't Repeate one | OnPlay->Randomize ( ->?| )
		sgn1=0;sgn2=2;sgn3=5;
		break;			//1,2,5
	case (4):			//Don't Repeate | All | Randomize	(-_-_->|)
		sgn1=1;sgn2=2;sgn3=5;
		break;			//0,3,4
	case (5):			//Repeate one | Don't Random		( [<->]  )
		sgn1=0;sgn2=3;sgn3=4;
		break;			//1,3,4	
	case (6):			//Repeate | All | Don't Random		([<---->])
		sgn1=1;sgn2=3;sgn3=4;
		break;			//0,3,5
	case (7):			//Don't Repeate one | Don't Random   (->|)
		sgn1=0;sgn2=3;sgn3=5;
		break;			//1,3,5
	case (8):			//Don't Repeate | All | Don't Random (--->|)
		sgn1=1;sgn2=3;sgn3=5;
		break;
	}
	if (screenDC) {
	TRACE("\nScreenDC......................[OK]\n");
	TRACE("\n[1]\n");
		m_pDC->BitBlt(m_LCDrepSgnRect[sgn1].left,
			m_LCDrepSgnRect[sgn1].top,
			m_LCDrepSgnRect[sgn1].right-m_LCDrepSgnRect[sgn1].left,
			m_LCDrepSgnRect[sgn1].bottom-m_LCDrepSgnRect[sgn1].top,
			&m_LCDrepSgnDC[sgn1],0,0,SRCCOPY);
	TRACE("\n[2]\n");		
		m_pDC->BitBlt(m_LCDrepSgnRect[sgn2].left,
			m_LCDrepSgnRect[sgn2].top,
			m_LCDrepSgnRect[sgn2].right-m_LCDrepSgnRect[sgn2].left,
			m_LCDrepSgnRect[sgn2].bottom-m_LCDrepSgnRect[sgn2].top,
			&m_LCDrepSgnDC[sgn2],0,0,SRCCOPY);
	TRACE("\n[3]\n");
		m_pDC->BitBlt(m_LCDrepSgnRect[sgn3].left,
			m_LCDrepSgnRect[sgn3].top,
			m_LCDrepSgnRect[sgn3].right-m_LCDrepSgnRect[sgn3].left,
			m_LCDrepSgnRect[sgn3].bottom-m_LCDrepSgnRect[sgn3].top,
			&m_LCDrepSgnDC[sgn3],0,0,SRCCOPY);
	} else {
	TRACE("\nTempDC......................[OK?!!]\n");
	if (!m_skinTempDC) {
		TRACE("\n[Certain Error********************************************************]\n");
	}

	TRACE("\n[1] [%d,%d,%d,%d]\n",m_LCDrepSgnRect[sgn1].left-1,m_LCDrepSgnRect[sgn1].top,	m_LCDrepSgnRect[sgn1].right-m_LCDrepSgnRect[sgn1].left,	m_LCDrepSgnRect[sgn1].bottom-m_LCDrepSgnRect[sgn1].top);
		m_skinTempDC.BitBlt(m_LCDrepSgnRect[sgn1].left-1,
			m_LCDrepSgnRect[sgn1].top,
			m_LCDrepSgnRect[sgn1].right-m_LCDrepSgnRect[sgn1].left,
			m_LCDrepSgnRect[sgn1].bottom-m_LCDrepSgnRect[sgn1].top,
			&m_LCDrepSgnDC[sgn1],0,0,SRCCOPY);
		
	TRACE("\n[2] [%d,%d,%d,%d]\n",m_LCDrepSgnRect[sgn1].left-1,m_LCDrepSgnRect[sgn1].top,	m_LCDrepSgnRect[sgn1].right-m_LCDrepSgnRect[sgn1].left,	m_LCDrepSgnRect[sgn1].bottom-m_LCDrepSgnRect[sgn1].top);
//	TRACE("\n[2]\n");
		m_skinTempDC.BitBlt(m_LCDrepSgnRect[sgn2].left-1,
			m_LCDrepSgnRect[sgn2].top,
			m_LCDrepSgnRect[sgn2].right-m_LCDrepSgnRect[sgn2].left,
			m_LCDrepSgnRect[sgn2].bottom-m_LCDrepSgnRect[sgn2].top,
			&m_LCDrepSgnDC[sgn2],0,0,SRCCOPY);

	TRACE("\n[3] [%d,%d,%d,%d]\n",m_LCDrepSgnRect[sgn1].left-1,m_LCDrepSgnRect[sgn1].top,	m_LCDrepSgnRect[sgn1].right-m_LCDrepSgnRect[sgn1].left,	m_LCDrepSgnRect[sgn1].bottom-m_LCDrepSgnRect[sgn1].top);
//	TRACE("\n[3]\n");
		m_skinTempDC.BitBlt(m_LCDrepSgnRect[sgn3].left-1,
			m_LCDrepSgnRect[sgn3].top,
			m_LCDrepSgnRect[sgn3].right-m_LCDrepSgnRect[sgn3].left,
			m_LCDrepSgnRect[sgn3].bottom-m_LCDrepSgnRect[sgn3].top,
			&m_LCDrepSgnDC[sgn3],0,0,SRCCOPY);
	}
	TRACE ("\n[sgn1=%d][sgn2=%d][sgn3=%d]\n",sgn1,sgn2,sgn3);
	TRACE("\nEnd setting rep signs. \n");
}

void HGraphics::UpdateCurrTime(CString newTime)
{
	CDC tempMem;
	CBitmap tempBMP,*oldBmp;
	CFont*	oldFont;

	tempBMP.CreateCompatibleBitmap(m_pDC,
		(m_LCDCtimeRect.right-m_LCDCtimeRect.left),
		(m_LCDCtimeRect.bottom-m_LCDCtimeRect.top));

	tempMem.CreateCompatibleDC(m_pDC);
	
	oldBmp=(CBitmap*)tempMem.SelectObject(&tempBMP);
	oldFont=(CFont*)tempMem.SelectObject(&m_font);

	tempMem.SetTextColor(RGB(255,255,0));
	tempMem.SetBkMode(TRANSPARENT);

	tempMem.BitBlt(/*m_LCDCtimeRect.left*/0,
		/*m_LCDCtimeRect.top*/0,
		m_LCDCtimeRect.right-m_LCDCtimeRect.left,
		m_LCDCtimeRect.bottom-m_LCDCtimeRect.top,
		&m_LCDCtimeDC,0,0,SRCCOPY);

	tempMem.TextOut(1,0,newTime);

	m_pDC->BitBlt(m_LCDCtimeRect.left,
		m_LCDCtimeRect.top,
		m_LCDCtimeRect.right-m_LCDCtimeRect.left,
		m_LCDCtimeRect.bottom-m_LCDCtimeRect.top,
		&tempMem,0,0,SRCCOPY);

	m_cTime=newTime;
	tempMem.SelectObject(oldBmp);
	tempBMP.DeleteObject();
	tempMem.SelectObject(oldFont);
}

void HGraphics::UpdateCurrTrack(CString newTrackNumber)
{
	m_trackNo=newTrackNumber;
	CDC tempMem;
	CBitmap tempBMP,*oldBmp;
	CFont*	oldFont;

	tempBMP.CreateCompatibleBitmap(m_pDC,
		(m_LCDtrackRect.right-m_LCDtrackRect.left),
		(m_LCDtrackRect.bottom-m_LCDtrackRect.top));

	tempMem.CreateCompatibleDC(m_pDC);
	
	oldBmp=(CBitmap*)tempMem.SelectObject(&tempBMP);
	oldFont=(CFont*)tempMem.SelectObject(&m_font);

	tempMem.SetTextColor(RGB(255,255,0));
	tempMem.SetBkMode(TRANSPARENT);

	tempMem.BitBlt(/*m_LCDtrackRect.left*/0,
		/*m_LCDtrackRect.top*/0,
		m_LCDtrackRect.right-m_LCDtrackRect.left,
		m_LCDtrackRect.bottom-m_LCDtrackRect.top,
		&m_LCDtrackDC,0,0,SRCCOPY);

	tempMem.TextOut(1,0,newTrackNumber);

	m_pDC->BitBlt(m_LCDtrackRect.left,
		m_LCDtrackRect.top,
		m_LCDtrackRect.right-m_LCDtrackRect.left,
		m_LCDtrackRect.bottom-m_LCDtrackRect.top,
		&tempMem,0,0,SRCCOPY);

	tempMem.SelectObject(oldBmp);
	tempBMP.DeleteObject();
	tempMem.SelectObject(oldFont);
}

void HGraphics::UpdateInfo(BOOL move)
{
	CDC tempMem;
	CBitmap tempBMP,*oldBmp;
	CFont*	oldFont;
	CRect tempRect;

	if (move) MarqueeForward();

	tempBMP.CreateCompatibleBitmap(m_pDC,
		(m_LCDinfoRect.right-m_LCDinfoRect.left),
		(m_LCDinfoRect.bottom-m_LCDinfoRect.top));

	tempMem.CreateCompatibleDC(m_pDC);
	
	oldBmp=(CBitmap*)tempMem.SelectObject(&tempBMP);
	oldFont=(CFont*)tempMem.SelectObject(&m_marqueeFont);

	tempMem.SetTextColor(m_marqueeFntCol);
	tempMem.SetBkMode(TRANSPARENT);

	tempMem.BitBlt(/*m_LCDinfoRect.left*/0,
		/*m_LCDinfoRect.top*/0,
		m_LCDinfoRect.right-m_LCDinfoRect.left,
		m_LCDinfoRect.bottom-m_LCDinfoRect.top,
		&m_LCDinfoDC,0,0,SRCCOPY);

	tempRect.top=m_marqueeRect.top-120;
	tempRect.left=m_marqueeRect.left;
	tempRect.bottom=m_marqueeRect.bottom;
	tempRect.right=m_marqueeRect.right;
	tempMem.DrawText(m_marqueeText,tempRect,0);

	m_pDC->BitBlt(m_LCDinfoRect.left,
		m_LCDinfoRect.top,
		m_LCDinfoRect.right-m_LCDinfoRect.left,
		m_LCDinfoRect.bottom-m_LCDinfoRect.top,
		&tempMem,0,0,SRCCOPY);

	tempMem.SelectObject(oldBmp);
	tempBMP.DeleteObject();
	tempMem.SelectObject(oldFont);
}

void HGraphics::UpdateTotalTime(CString newTime)
{
	CDC tempMem;
	CBitmap tempBMP,*oldBmp;
	CFont*	oldFont;

	tempBMP.CreateCompatibleBitmap(m_pDC,
		(m_LCDTtimeRect.right-m_LCDTtimeRect.left),
		(m_LCDTtimeRect.bottom-m_LCDTtimeRect.top));

	tempMem.CreateCompatibleDC(m_pDC);
	
	oldBmp=(CBitmap*)tempMem.SelectObject(&tempBMP);
	oldFont=(CFont*)tempMem.SelectObject(&m_font);

	tempMem.SetTextColor(RGB(255,255,0));
	tempMem.SetBkMode(TRANSPARENT);

	tempMem.BitBlt(/*m_LCDCtimeRect.left*/0,
		/*m_LCDCtimeRect.top*/0,
		m_LCDTtimeRect.right-m_LCDTtimeRect.left,
		m_LCDTtimeRect.bottom-m_LCDTtimeRect.top,
		&m_LCDTtimeDC,0,0,SRCCOPY);

	tempMem.TextOut(1,0,newTime);

	m_pDC->BitBlt(m_LCDTtimeRect.left,
		m_LCDTtimeRect.top,
		m_LCDTtimeRect.right-m_LCDTtimeRect.left,
		m_LCDTtimeRect.bottom-m_LCDTtimeRect.top,
		&tempMem,0,0,SRCCOPY);

	m_tTime=newTime;
	tempMem.SelectObject(oldBmp);
	tempBMP.DeleteObject();
	tempMem.SelectObject(oldFont);
}

void HGraphics::UpdateVolume(int newVolume)
{
	m_vol=newVolume;
	CDC tempMem;
	CBitmap tempBMP,*oldBmp;
	CFont*	oldFont;

	tempBMP.CreateCompatibleBitmap(m_pDC,
		(m_LCDvolumeRect.right-m_LCDvolumeRect.left),
		(m_LCDvolumeRect.bottom-m_LCDvolumeRect.top));

	tempMem.CreateCompatibleDC(m_pDC);
	
	oldBmp=(CBitmap*)tempMem.SelectObject(&tempBMP);
	oldFont=(CFont*)tempMem.SelectObject(&m_font);

	tempMem.SetTextColor(RGB(255,255,0));
	tempMem.SetBkMode(TRANSPARENT);

	tempMem.BitBlt(/*m_LCDCtimeRect.left*/0,
		/*m_LCDCtimeRect.top*/0,
		m_LCDvolumeRect.right-m_LCDvolumeRect.left,
		m_LCDvolumeRect.bottom-m_LCDvolumeRect.top,
		&m_LCDvolumeDC,0,0,SRCCOPY);

	DrawVolumeBar(&tempMem);

	m_pDC->BitBlt(m_LCDvolumeRect.left,
		m_LCDvolumeRect.top,
		m_LCDvolumeRect.right-m_LCDvolumeRect.left,
		m_LCDvolumeRect.bottom-m_LCDvolumeRect.top,
		&tempMem,0,0,SRCCOPY);

	tempMem.SelectObject(oldBmp);
	tempBMP.DeleteObject();
	tempMem.SelectObject(oldFont);
	tempMem.DeleteDC();
}

void HGraphics::UpdateVolumeButton(int Type)
{
	CDC tempMem;
	CBitmap tempBMP,*oldBmp;

	tempMem.CreateCompatibleDC(m_pDC);
	
	CBitmap		sgn,sgn2;

	//336,22,359,43)
	//336,45,359,66)

	switch (Type) {
	case (0):
		sgn.LoadBitmap(IDB_PLUSD);
		oldBmp=(CBitmap*)tempMem.SelectObject(&sgn);
		m_pDC->BitBlt(301,24,333,36,//)(296,15,326,43,
			&tempMem,0,0,SRCCOPY);
		break;
	case (1):
		sgn.LoadBitmap(IDB_MINUSD);
		oldBmp=(CBitmap*)tempMem.SelectObject(&sgn);
		m_pDC->BitBlt(301,39,333,52,//)(296,35,326,66,
			&tempMem,0,0,SRCCOPY);
		break;
	case (2):
		sgn.LoadBitmap(IDB_PLUSU);
		oldBmp=(CBitmap*)tempMem.SelectObject(&sgn);
		m_pDC->BitBlt(301,24,333,36,//(296,15,326,43,
			&tempMem,0,0,SRCCOPY);
	
		sgn2.LoadBitmap(IDB_MINUSU);
		oldBmp=(CBitmap*)tempMem.SelectObject(&sgn2);
		m_pDC->BitBlt(301,39,333,52,//(296,35,326,66,
			&tempMem,0,0,SRCCOPY);
		break;
	}
	tempMem.SelectObject(oldBmp);
	sgn.DeleteObject();
	sgn2.DeleteObject();
	tempMem.DeleteDC();
}

void HGraphics::ReleaseMemory()
{
	TRACE("\nRealeasing Memory...\n");
	m_skinDC.SelectObject(m_oldSkin);
	m_skinDC.SelectObject(m_oldFont);
	m_skinTempDC.SelectObject(m_oldSkin);
	m_skinTempDC.SelectObject(m_oldFont);
	m_pDC->ReleaseAttribDC();
	delete m_pDC;
	delete m_skinBitmap;
	delete m_skinTempBitmap;
	m_font.DeleteObject();

	for (int i=0;i<6;i++) {
		m_LCDrepSgnDC[i].SelectObject(m_oldBitmap);
		m_LCDrepSgn[i].DeleteObject();
	}
	
	for (int j=0;j<3;j++) {
		m_LCDplaySgnDC[j].SelectObject(m_oldBitmap);
		m_LCDplaySgn[j].DeleteObject();
	}
	m_LCDTtimeDC.SelectObject(m_oldBitmap);
	m_LCDTtime.DeleteObject();
	m_LCDCtimeDC.SelectObject(m_oldBitmap);
	m_LCDCtime.DeleteObject();
	m_LCDtrackDC.SelectObject(m_oldBitmap);
	m_LCDtrack.DeleteObject();
	m_LCDvolumeDC.SelectObject(m_oldBitmap);
	m_LCDvolume.DeleteObject();
	m_LCDinfoDC.SelectObject(m_oldBitmap);
	m_LCDinfo.DeleteObject();

	m_LCDTtimeDC.DeleteDC();
	m_LCDCtimeDC.DeleteDC();
	m_LCDtrackDC.DeleteDC();
	m_LCDvolumeDC.DeleteDC();
	m_LCDinfoDC.DeleteDC();

}

void HGraphics::SetMarqueeSpecifics(CString text, 
	 CString fontName, int speed, int x1, int y1,
	 int x2, int y2, int fontSize, COLORREF fontColor,
	 COLORREF fontBK)
{
	m_marqueeFntBkCol=fontBK;
	m_marqueeText=text;
	m_marqueeFntCol=fontColor;
	m_marqueeFontName=fontName;
	m_marqueeFontSize=fontSize;
	m_marqueeX1=x1;
	m_marqueeY1=y1;
	m_marqueeX2=x2;
	m_marqueeY2=y2;
	m_marqueePassedCharNumber=1;
	m_marqueeTempText=m_marqueeText;
	m_marqueeSpeed=speed;

	m_marqueeStringSize=(m_pDC->GetTextExtent(m_marqueeTempText));

	if (speed==1) m_marqueeXTemp=x2;
	else m_marqueeXTemp=m_marqueeX1-m_marqueeStringSize.cx;
	
	m_marqueeFont.DeleteObject();

	m_marqueeFont.CreateFont(m_marqueeFontSize,0,0,0,0,FALSE,
		FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS ,m_marqueeFontName);

	m_marqueeRect.bottom=m_marqueeY2;
	m_marqueeRect.right=m_marqueeX2;

	m_marqueeText.TrimRight();
	m_marqueeText.TrimLeft();
	m_marqueeSetAll=TRUE;
}

void HGraphics::SetMarqueeText(CString mText)
{
	m_marqueeText=mText;
	m_marqueeStringSize=m_pDC->GetTextExtent(m_marqueeTempText);
	UpdateInfo(FALSE);
}

void HGraphics::MarqueeForward()
{
	if (!m_marqueeSetAll) return;

	m_marqueePassedCharNumber+=m_marqueeSpeed;
	m_marqueeXTemp--;

	if ( (m_marqueeXTemp+(m_marqueeStringSize.cx))<=m_marqueeX1) {
			m_marqueeText=m_marqueeTempText;
			m_marqueePassedCharNumber=0;
			m_marqueeXTemp=m_marqueeX2;
		}
	m_marqueeRect.top=m_marqueeY1;
	m_marqueeRect.left=m_marqueeXTemp;
}

void HGraphics::DrawVolumeBar(CDC *dc)
{
	COLORREF	m_VColor;
	m_VColor=RGB(190,200,220);
	int x1=2,y1=1,x2=17,y2=0,temp;

	temp=x1;
	for (int i=0;i<(m_vol/50);i++) {
		x1=temp;
		y1=58-(i*3);
		y2=y1;
		while (x1<x2) {
			dc->SetPixel(x1-1,y1,m_VColor);
			x1+=2;
		}
	}
}

void HGraphics::SetDefinitionData(int fileVolume, int repSituation)
{
	m_vol=fileVolume;
	m_repSgn=repSituation;
}
