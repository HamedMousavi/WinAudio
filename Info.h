// Info.h: interface for the Info class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFO_H__FF48ED6A_51D5_4C29_BE7C_95F8EA0BA927__INCLUDED_)
#define AFX_INFO_H__FF48ED6A_51D5_4C29_BE7C_95F8EA0BA927__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Info  
{
	enum { V1L1=0,V1L2=1,V1L3=2,V2L1=3,V2L2L3=4 };
public:
	void readInfo(CString filePath);
	void init();
	CString getInfo(CString filePath,CString fileName);
	Info();
	virtual ~Info();
private:
	CString ByteToBinary(BYTE Byte);
	CString GetHead(BYTE byte1,BYTE byte2,BYTE byte3,BYTE byte4);
	int btoi(CString byte);
	
	struct Head {
		CString	frameSynch;
		CString	ID;
		CString	layerVer;
		CString	protection;
		CString	bitrate;
		CString	frequency;
		CString	padding;
		CString	reserved;
		CString	channelMode;
		CString	modeExtention;
		CString	copyright;
		CString	original;
		CString	emphasis;
		};

	struct MusicTag {
		char	tag[3];
		char	title[30];
		char	artist[30];
		char	album[30];
		char	year[4];
		char	comment[30];
		char	genre[2];
	};

	Head		MP3header;
	MusicTag	music;

	CString m_title,
			m_artist,
			m_album,
			m_year,
			m_genre,
			m_comments,
			m_head;

	int m_readByteNo;
	int m_tempBytes[16];
};
#endif // !defined(AFX_INFO_H__FF48ED6A_51D5_4C29_BE7C_95F8EA0BA927__INCLUDED_)
