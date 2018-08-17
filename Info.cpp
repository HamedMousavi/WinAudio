// Info.cpp: implementation of the Info class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinAudio.h"
#include "Info.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Info::Info()
{
	init();
}

Info::~Info()
{
}

CString Info::getInfo(CString filePath,CString fileName)
{

//----------------------------------------------------------------------------------
   const char genres[127][30] =
	{{"Blues"},{"Classic Rock"},{"Country"},
	{"Dance"},{"Disco"},{"Funk"},{"Grunge"},
	{"Hip-Hop"},{"Jazz"},{"Metal"},{"New Age"},
	{"Oldies"},{"Other"},{"Pop"},{"R&B"},{"Rap"},
	{"Reggae"},{"Rock"},{"Techno"},{"Industrial"},
	{"Alternative"},{"Ska"},{"Death Metal"},
	{"Pranks"},{"Soundtrack"},{"Euro-Techno"},
	{"Ambient"},{"Trip-Hop"},{"Vocal"},
	{"Jazz+Funk"},{"Fusion"},{"Trance"},
	{"Classical"},{"Instrumental"},{"Acid"},
	{"House"},{"Game"},{"Sound Clip"},{"Gospel"},
	{"Noise"},{"AlternRock"},{"Bass"},{"Soul"},
	{"Punk"},{"Space"},{"Meditative"},
	{"Instrumental Pop"},{"Instrumental Rock"},
	{"Ethnic"},{"Gothic"},{"Darkwave"},
	{"Techno-Industrial"},{"Electronic"},
	{"Pop-Folk"},{"Eurodance"},{"Dream"},
	{"Southern Rock"},{"Comedy"},{"Cult"},
	{"Gangsta"},{"Top 40"},{"Christian Rap"},
	{"Pop/Funk"},{"Jungle"},{"Native American"},
	{"Cabaret"},{"New Wave"},{"Psychadelic"},
	{"Rave"},{"Showtunes"},{"Trailer"},{"Lo-Fi"},
	{"Tribal"},{"Acid Punk"},{"Acid Jazz"},
	{"Polka"},{"Retro"},{"Musical"},
	{"Rock & Roll"},{"Hard Rock"},{"Folk"},
	{"Folk-Rock"},{"National Folk"},{"Swing"},
	{"Fast Fusion"},{"Bebob"},{"Latin"},{"Revival"},
	{"Celtic"},{"Bluegrass"},{"Avantgarde"},
	{"Gothic Rock"},{"Progressive Rock"},{"Psychedelic Rock"},
	{"Symphonic Rock"},{"Slow Rock"},{"Big Band"},{"Chorus"},
	{"Easy Listening"},{"Acoustic"},{"Humour"},{"Speech"},
	{"Chanson"},{"Opera"},{"Chamber Music"},{"Sonata"},
	{"Symphony"},{"Booty Brass"},{"Primus"},{"Porn Groove"},
	{"Satire"},{"Slow Jam"},{"Club"},{"Tango"},{"Samba"},
	{"Folklore"},{"Ballad"},{"Poweer Ballad"},{"Rhytmic Soul"},
	{"Freestyle"},{"Duet"},{"Punk Rock"},{"Drum Solo"},
	{"A Capela"},{"Euro-House"},{"Dance Hall"},{"Unknown"}};
//----------------------------------------------------------------------------------
	FILE *fp;

	fp=fopen(filePath,"rb");
	if (!fp) {
		return "Sorry!Can't find file";
	}

	fseek(fp,-128,SEEK_END);
	fread(&music,sizeof(MusicTag),1,fp);

	fclose(fp);

	char tempT,tempAr,tempAl,tempC,tempY;

	//Checking for TAG
	if (music.tag[0]!='T' || music.tag[1]!='A' || music.tag[2]!='G') {
		m_title=m_artist=m_album=m_comments=m_genre=m_year="--";
		readInfo(filePath);
		return ("Info Not Available. [File:"+filePath+"]");
	}

	//BackingUp last characters to exchange with "End Of Line"
	if (music.title[0]!='\0') tempT=music.title[29];
	else tempT=' ';

	if (music.artist[0]!='\0') tempAl=music.album[29];
	else tempAl=' ';

	if (music.album[0]!='\0') tempAr=music.artist[29];
	else tempAr=' ';

	if (music.year[0]!='\0') tempC=music.comment[29];
	else tempC=' ';

	if (music.genre[0]!='\0') tempY=music.year[3];
	else tempY=' ';

	//Ending lines
	music.title[29]='\0';
	music.artist[29]='\0';
	music.album[29]='\0';
	music.comment[29]='\0';
	music.year[3]='\0';
	music.genre[1]='\0';

	//if last char was a null char change it!
	if (tempT=='\0') tempT=' ';
	if (tempAl=='\0') tempAl=' ';
	if (tempAr=='\0') tempAr=' ';
	if (tempC=='\0') tempC=' ';
	if (tempY=='\0') tempY=' ';

	//Updating relative string variables
	m_title=(CString) music.title+tempT;
	m_artist=(CString) music.artist+tempAr;
	m_album=(CString) music.album+tempAl;
	m_year=(CString) music.year+tempY;
	m_comments=(CString) music.comment+tempC;

	if (m_title=="") m_title="Unknown";
	if (m_artist=="") m_artist="Unknown";
	if (m_album=="") m_album="Unknown";
	if (m_year=="") m_year="Unknown";
	if (m_comments=="") m_comments="Unknown";

	//Finding Genre
	if (music.genre[0]>0 && music.genre[0]<126)
		m_genre=(CString) genres[music.genre[0]];
	else m_genre=(CString) genres[126];

//	OnHead(m_fileName);
	readInfo(filePath);

	m_title.TrimLeft();
	m_title.TrimRight();
	m_artist.TrimLeft();
	m_artist.TrimRight();
	m_album.TrimLeft();
	m_album.TrimRight();
	m_year.TrimLeft();
	m_year.TrimRight();
	m_comments.TrimLeft();
	m_comments.TrimRight();
	m_genre.TrimLeft();
	m_genre.TrimRight();
	
	CString tmp;
	tmp="[ Title : ";
	tmp+=m_title;
	tmp+=" ]   [ Artist : ";
	tmp+=m_artist;
	tmp+=" ]   [ Album : ";
	tmp+=m_album;
	tmp+=" ]   [ Year : ";
	tmp+=m_year;
	tmp+=" ]   [ Genre : ";
	tmp+=m_genre;
	tmp+=" ]   [ Comments : ";
	tmp+=m_comments;
	tmp+=" ]   [ File : ";
	tmp+=filePath;
	tmp+=" ]";

	return tmp;
}
int Info::btoi(CString byte)
{
	int ans,count;
	ans=0; count=2;
	for (int i=byte.GetLength();i>1;i--) {
		ans+=(atoi((CString)byte[i-2]))*count;
		count*=2;
	}
	if ( (byte[byte.GetLength()-1])=='1' ) ans++;
	return ans;
}

CString Info::GetHead(BYTE byte1, BYTE byte2, BYTE byte3, BYTE byte4)
{
//tacles-------------------------------------------------------------------------------------v
	const char ID[4][33] = { {"MPEG 2.5"},{"reserved"},
							 {"MPEG 2"},
							 {"MPEG 1"} };
	
	const char Layer[4][10]={{"reserved"},{"Layer III"},
							 {"Layer II"},{"Layer I"} };
						// L1V1 L1V2 L1V3 L2V1 L2-V2&V3
	int Bitrate[22][5]={	 32, 32, 32, 32,  8,
							 32, 32, 32, 32,  8, 
							 64, 48, 40, 48, 16,
							 96, 56, 48, 56, 24, 
							128, 64, 56, 64, 32, 
							160, 80, 64, 80, 40, 
							192, 96, 80, 96, 48, 
							224,112, 96,112, 56, 
							256,128,112,128, 64, 
							288,160,128,144, 80, 
							320,192,160,160, 96, 
							352,224,192,176,112, 
							384,256,224,192,128, 
							416,320,256,224,144, 
							448,384,320,256,160 };

						//  Mpeg1  Mpeg2  Mpeg2.5
	int SamplingRate[3][3]={44100, 22050, 11025, 
							48000, 24000, 12000, 
							32000, 16000,  8000, };
	const char ChannelMode[4][15]={ {"Stereo"},{"Joint Stereo"},
									{"Dual Channel"},{"Single Channel"} };
//tacles-------------------------------------------------------------------------------------^
	CString ans;
	ans="";
	ans=(ByteToBinary(byte1) + ByteToBinary(byte2)+
		 ByteToBinary(byte3) + ByteToBinary(byte4));
	
	MP3header.frameSynch=ans.Mid(0,11);
	MP3header.ID=ans.Mid(11,2);
	MP3header.layerVer=ans.Mid(13,2);
	MP3header.protection=ans.Mid(15,1);
	MP3header.bitrate=ans.Mid(16,4);
	MP3header.frequency=ans.Mid(20,2);
	MP3header.padding=ans.Mid(22,1);
	MP3header.reserved=ans.Mid(23,1);
	MP3header.channelMode=ans.Mid(24,2);
	MP3header.modeExtention=ans.Mid(26,2);
	MP3header.copyright=ans.Mid(28,1);
	MP3header.original=ans.Mid(29,1);
	MP3header.emphasis=ans.Mid(30,2);
	
//	ans="";
	ans=ID[btoi(MP3header.ID)];
	ans+="-";
	ans+=Layer[btoi(MP3header.layerVer)];
	ans+="-";
	
	int VL;CString tmp;
	VL=0;
	
	if (btoi(MP3header.ID)==3) {
		if (btoi(MP3header.layerVer)==1) VL=V1L3;
		else if (btoi(MP3header.layerVer)==2) VL=V1L2;
		else VL=V1L1;
	} else {
		if (btoi(MP3header.layerVer)==3) VL=V2L1;
		else VL=V2L2L3;
	};
	tmp.Format("%d",(Bitrate[btoi(MP3header.bitrate)][VL]));
	ans+=tmp;
	
	ans+=" kbps-";
	if (btoi(MP3header.ID)==3) VL=0;
	else if (atoi(MP3header.ID)==0) VL=2;
	else VL=1;
	tmp.Format("%d",SamplingRate[btoi(MP3header.frequency)][VL]);
	ans+=tmp;
	ans+=" Hz-";
	ans+=ChannelMode[btoi(MP3header.channelMode)];
	return ans;
}

CString Info::ByteToBinary(BYTE Byte)
{
	int x,y,i;
	CString temp,ans;

	temp="";
	ans ="";
	x	=Byte;
	y	=0;
	i	=0;
	while (x>=2) {
		y=x%2;
		temp.Format("%d",y);
		ans+=temp;
		x/=2;
		i++;
	}
	temp.Format("%d",x);
	ans+=temp;
	if (i<7) {
		for (;i<7;i++)
			ans+="0";
	}
	ans.MakeReverse();
	return	ans;
}

void Info::init()
{
	m_readByteNo=0;
}

void Info::readInfo(CString filePath)
{
	FILE *fp;
	BYTE	aByte,bByte,cByte,dByte;
	aByte=bByte=cByte=dByte=0;

	fp=fopen(filePath,"rb");

	//finding first info
	//first '256'
	while (aByte!=255) {
		fread(&aByte,sizeof(BYTE),1,fp);
		if (feof(fp)) {
//			MessageBox("Sorry! Can't Read...");
			fclose(fp);
			return;
		}
	}

	fread(&bByte,sizeof(BYTE),1,fp);
	fread(&cByte,sizeof(BYTE),1,fp);
	fread(&dByte,sizeof(BYTE),1,fp);
	//accounting...
	m_head=GetHead(aByte,bByte,cByte,dByte);

//	UpdateData(FALSE);
	fclose(fp);
}
