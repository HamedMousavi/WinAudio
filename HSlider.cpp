// HSlider.cpp : implementation file
//

#include "stdafx.h"
#include "WinAudio.h"
#include "HSlider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHSlider

CHSlider::CHSlider()
{
	m_ID=0;
}

CHSlider::CHSlider(unsigned long cID,unsigned long newID,CString label)
{
	m_controlID=cID;
	m_ID=newID;
	m_label=label;
}

CHSlider::~CHSlider()
{
}


BEGIN_MESSAGE_MAP(CHSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CHSlider)
	ON_NOTIFY_REFLECT(NM_RELEASEDCAPTURE, OnReleasedcapture)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHSlider message handlers

void CHSlider::OnReleasedcapture(NMHDR* pNMHDR, LRESULT* pResult) 
{
	::PostMessage(GetParent()->GetSafeHwnd(),
		WM_MOVED,m_ID,GetPos());
	*pResult = 0;
}

void CHSlider::SetID(unsigned long newID)
{
	m_ID = newID;
}

void CHSlider::OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	::PostMessage(GetParent()->GetSafeHwnd(),
		WM_MOVED,m_ID,GetPos());
	*pResult = 0;

}

unsigned long CHSlider::GetID()
{
	return m_controlID;
}

unsigned long CHSlider::GetComponentID()
{
	return m_ID;
}
