// WinAudioDlg.h : header file
//

#if !defined(AFX_WinAudioDlg_H__31629E89_511A_454E_879B_79245FFC8125__INCLUDED_)
#define AFX_WinAudioDlg_H__31629E89_511A_454E_879B_79245FFC8125__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinAudioDlg dialog
#include "Info.h"
#include "FileOpenDlg.h"
#include "BitmapSlider.h"
#include "HGraphics.h"
#include "PlayListDlg.h"
#include "MixerDlg.h"

class CWinAudioDlg : public CDialog
{
public:
// Construction
	CWinAudioDlg(CWnd* pParent = NULL);	// standard constructor

//Implementation
private:
	BOOL m_mixerDlgIsVisible;
	CMixerDlg m_mDlg;
	void ClosePlayList();
	void OpenPlayList();
	BOOL IsPlayListDialogModal();
	BOOL m_pListIsVisible;
	void StrToChar(CString& source,char* dest,int count);
	BOOL m_readOnce;
	BOOL m_canChangeVolume;

	CToolTipCtrl m_toolTip;			// Tooltip

	CPlayListDlg m_listDlg;
	BOOL m_captured;
	CRect m_minusRect;
	UINT GetRandomNumber();
	CString GetMusicReverseTime(void);
	void CountElapsedTime(void);
	CString GetMusicTotalTime();
	BOOL StopMusic();
	BOOL BackwardMusic(int step);
	BOOL ForwardMusic(int step);
	BOOL ResumeMusic();
	BOOL PauseMusic();
	void SetMusicVolume(int newVolume);
	BOOL PlayMusic(CString file);
	BOOL CreateMusic(CString file);
	BOOL OnToolTipNotify(UINT id,NMHDR *pNMHDR,LRESULT pResult);
	void OnPlus();
	void OnMinus();
	void InitInfoTooltip();
	bool LoadInfo(void);
	bool SaveInfo(void);
	bool m_OpenDlg;
	void checkVolume();
	void InitSlider(void);
	void UpdateList(void);
	void repeat(void);
	void RunInfo(void);
	enum SIGNS { PLAY,STOP,PAUSE,FF,BW };
	enum TIMES { MARQUEE,CCLOCK,SPECTRUM,VOLUMES };
	enum REPEAT{ RAND_REP_ONE=1,RAND_REP_ALL=2,
				 RAND_NOREP_ONE=3,RAND_NOREP_ALL=4,
				 NORM_REP_ONE=5,NORM_REP_ALL=6,
				 NORM_NOREP_ONE=7,NORM_NOREP_ALL=8 };
	enum VOLUME{ PLUS_PRESSED,MINUS_PRESSED,RELEASED};

	int    *m_randIndex;
	HGraphics m_g;
	VOLUME	m_volumePressed;
	CRect	m_skinRect;

	REPEAT	m_repSituation;

	int		m_repCounter;
	int		m_lastRec;

	bool	m_LButtonDown,
			m_playing,								//ok
			m_pause,
			m_first,
			m_oneReaded,
			m_mixerDlgStat;

	CBitmapButton
			m_about,
			m_playList,
			m_mixer,
			m_close,
			m_minimize,
			m_eject,
			m_back,
			m_forward,
			m_play,
			m_stop,
			m_next,
			m_previous,
			m_number,
			m_playOrder,
			m_repeate;
	CString		m_fileName,m_infoStr;
	COLORREF	m_volumeColor;

	CPoint		m_oldPoint;
	CString		totalTime,m_currentTime,m_fName;
	int			m_volume,							//ok
				m_fileCounter;						//ok
	HWND		musicWnd;							//ok
	SIGNS		m_sign;
	
//	HMarquee	m_MarqueeTxt;
	Info		m_info;
//	LCD			m_lcd;
	CString		*m_files;							//ok
    CFileOpenDialog *fDlg;							//ok
	CString		m_debug;
	int			m_tS,
				m_tH,
				m_tM;
public:
	UINT GetCurentIndex();
	void PlayFromList(int index);
	UINT GetNumberOfFiles();
	CString GetFileName(int index);
	CRect m_PlusRect;
	void UpdateSlider(void);
	void OnCancel();
	void OnOK();
	void Resume(void);
	void Pause(void);
	void DrawSkin(void);
	void init(void);
// Dialog Data
	//{{AFX_DATA(CWinAudioDlg)
	enum { IDD = IDD_WINAUDIO_DIALOG };
	CAnimateCtrl	m_animate;
	CBitmapSlider m_slider;
	int		m_nMax;
	int		m_nMin;
	int		m_nPos;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinAudioDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bEnable;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinAudioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEject();
	afx_msg void OnStop();
	afx_msg void OnPlay();
	afx_msg void OnMinimize();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNext();
	afx_msg void OnPrevious();
	afx_msg void OnPlayOrder();
	afx_msg void OnRepeateOrNot();
	afx_msg void OnAllOrOne();
	afx_msg void OnDoubleclickedPlayOrder();
	afx_msg void OnDoubleclickedNumber();
	afx_msg void OnForward();
	afx_msg void OnBack();
	afx_msg void OnWindowsMixer();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAbout();
	afx_msg void OnDoubleclickedRepeate();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnExit();
	afx_msg void OnDisplayAlbum();
	afx_msg void OnMixer();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnBitmapSliderMoved(WPARAM Wparam,LPARAM Lparam);
	afx_msg LRESULT OnBitmapSliderMoving(WPARAM Wparam,LPARAM Lparam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WinAudioDlg_H__31629E89_511A_454E_879B_79245FFC8125__INCLUDED_)
