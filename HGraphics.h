// HGraphics.h: interface for the HGraphics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HGraphics_H__CD8954BF_035F_4275_8DA3_9ABF043E2D9E__INCLUDED_)
#define AFX_HGraphics_H__CD8954BF_035F_4275_8DA3_9ABF043E2D9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class HGraphics  
{
public:
	void SetDefinitionData(int fileVolume,int repSituation);
	void SetMarqueeText(CString mText);
	void SetMarqueeSpecifics(CString text, CString fontName, int speed, int x1, int y1, int x2, int y2, int fontSize, COLORREF fontColor, COLORREF fontBK);
	void UpdateVolumeButton(int Type);
	void UpdateVolume(int newVolume);
	void UpdateTotalTime(CString newTime);
	void UpdateInfo(BOOL move);
	void UpdateCurrTrack(CString newTrackNumber);
	void UpdateCurrTime(CString newTime);
	void SetRepSign(int sign,BOOL screenDC);
	void SetPlaySign(int sign,BOOL screenDC);
	void UpdateAll(void);
	void SetDC(CWnd* pdc);
	void Init(void);
	HGraphics();
	virtual ~HGraphics();
	void ReleaseMemory(void);
	BOOL m_allFilesPlayedOnce;
private:
	void DrawVolumeBar(CDC* dc);
	void MarqueeForward(void);
	void DrawVolumeBar(BOOL screenDC=FALSE);
	void DotLine(int x1, int y1, int x2, int y2,BOOL screenDC=TRUE);
	void InitBackground(void);
	void CreateLcdPictures(void);
	void InitSigns(void);
	void InitRects(void);
	BOOL CreatePicture(CDC *PicMemDC,CRect PicRect,CBitmap* Bitmap);
	BOOL TransparentPicture(CDC* PicMemDC,CRect PicRect,int ID,CBitmap* Bitmap);

	COLORREF	m_InvisibleColor;
	HBITMAP		m_oldBitmap,m_oldSkin;
	HFONT		m_oldFont;
	
	CBitmap		m_LCDTtime,m_LCDCtime,
				m_LCDtrack,m_LCDinfo,
				m_LCDvolume,m_LCDrepSgn[6],
				m_LCDplaySgn[3],*m_skinBitmap,*m_skinTempBitmap;
	
	CRect		m_LCDTtimeRect,m_LCDCtimeRect,
				m_LCDtrackRect,m_LCDplaySgnRect,
				m_LCDinfoRect,m_LCDvolumeRect,
				m_LCDrepSgnRect[6],m_lcdRect;
	
	CDC 		m_skinDC,m_skinTempDC,
				m_LCDTtimeDC,m_LCDCtimeDC,
				m_LCDtrackDC,m_LCDplaySgnDC[3],
				m_LCDinfoDC,m_LCDvolumeDC,
				m_LCDrepSgnDC[6];
	
	CClientDC*	m_pDC;
	CWnd*		m_boddey;

	int			m_ID,m_vol,m_sign,m_repSgn,
				m_spectVal[8],
				m_repSign[6],m_playSign[3];
	CString		m_tTime,m_cTime,
				m_trackNo;
	BOOL		m_inited;
	CFont		m_font;

	CFont		m_marqueeFont;
	CRect		m_marqueeRect;
	CString		m_marqueeText,
				m_marqueeFontName,
				m_marqueeTempText;
	int			m_marqueeX1,
				m_marqueeY1,
				m_marqueeX2,
				m_marqueeY2,
				m_marqueeXTemp,
				m_marqueeFontSize,
				m_marqueeSpeed,
				m_marqueePassedCharNumber;
	COLORREF	m_marqueeFntCol,m_marqueeFntBkCol;
	bool		m_marqueeSetAll;
	CSize		m_marqueeStringSize;
};
#endif // !defined(AFX_HGraphics_H__CD8954BF_035F_4275_8DA3_9ABF043E2D9E__INCLUDED_)
