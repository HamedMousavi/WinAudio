// HMixer.cpp: implementation of the CHMixer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinAudio.h"
#include "HMixer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHMixer::CHMixer()
{
	Initialize();
}

CHMixer::~CHMixer()
{
//	TRACE( "Exiting..." );
	mixerClose(m_hMixer);
}
//Get current components volume
UINT CHMixer::GetVolume(unsigned long idComponent)
{
	if ( !m_initialized ) 
		if ( !Initialize() ) return 0;

	if ( !mixerIsOpen ) OpenMixer();
	if ( !mixerIsOpen ) return 0;

	MMRESULT result = MMSYSERR_NOERROR;

	mixerCDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mixerCDetails.dwControlID = idComponent;
	mixerCDetails.cChannels = 1;
	mixerCDetails.cMultipleItems = 0;
	mixerCDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mixerCDetails.paDetails = &mixerUnsigned;
	result = mixerGetControlDetails((HMIXEROBJ)(m_hMixer),
								 &mixerCDetails,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_GETCONTROLDETAILSF_VALUE);
	if ( result!= MMSYSERR_NOERROR)
	{
		return 0;
	}
	return mixerUnsigned.dwValue;
}
//Adjust current components volume
BOOL CHMixer::SetVolume(unsigned long idComponent, UINT newVolume)
{
	if (newVolume>65535) return FALSE;
	MMRESULT result;
	int temp=m_lineNumber;

	if (!FindComponent(idComponent)) {
		m_lineNumber=temp;
		return FALSE;
	}

	mixerUnsigned.dwValue  = newVolume;
	result = mixerSetControlDetails
		((HMIXEROBJ)m_hMixer, &mixerCDetails, 0L);

	if (result!=MMSYSERR_NOERROR) {
		m_lineNumber=temp;
		return FALSE;
	}
	m_lineNumber=temp;
	return TRUE;
}
//UNDONE
BOOL CHMixer::GetComponentActiveStat(unsigned long idComponent)
{
	if ( !mixerIsOpen ) return FALSE;
	return false;
}
//UNDONE
BOOL CHMixer::SetComponentActivity(unsigned long idComponent)
{
	if ( !mixerIsOpen ) return FALSE;
	return false;
}
//Private
BOOL CHMixer::FindComponent(unsigned long idComponent)
{
	MMRESULT result = MMSYSERR_NOERROR;

	if ( !mixerIsOpen ) return FALSE;
	if ( idComponent==NULL ) return FALSE;

	mixerLine.cbStruct = sizeof(MIXERLINE);
	mixerLine.dwComponentType= idComponent;

	result = mixerGetLineInfo((HMIXEROBJ)m_hMixer,&mixerLine,
		MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE );

	if (result !=MMSYSERR_NOERROR  ) {
//		TRACE("\n1.Err Find Component...");
		return FALSE;
	}
	m_lineNumber++;

	mixerControl.cbStruct = sizeof(MIXERCONTROL);
	mixerLControls.cbmxctrl=sizeof(MIXERCONTROL);
	mixerLControls.cbStruct = sizeof(MIXERLINECONTROLS);
	mixerLControls.cControls=1;
	mixerLControls.pamxctrl=&mixerControl;

	mixerLControls.dwLineID=mixerLine.dwLineID;
	mixerLControls.dwControlType=MIXERCONTROL_CONTROLTYPE_VOLUME;

	result = mixerGetLineControls((HMIXEROBJ)m_hMixer,&mixerLControls,
		MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE);

	if (result !=MMSYSERR_NOERROR  ) {
//		TRACE("\n2.Err Find Component:");
//		TRACE(mixerLine.szName);
		return FALSE;
	}
	//retrieving control details
	mixerCDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mixerCDetails.dwControlID = mixerControl.dwControlID;
	mixerCDetails.cChannels=1;
	mixerCDetails.cMultipleItems=0;
	mixerCDetails.cbDetails =sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mixerCDetails.paDetails=&mixerUnsigned;

	result = mixerGetControlDetails( (HMIXEROBJ)m_hMixer,&mixerCDetails,
		MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE);

	if (result!=MMSYSERR_NOERROR) {
//		TRACE("\n3.Err Find Component...");
		return FALSE;
	}
	return TRUE;
}
//Gives number of available lines in mixer
UINT CHMixer::GetLineNumber()
{
	return m_lineNumber;
}
//Gives number of available controls in mixer
UINT CHMixer::GetControlNumber()
{
	if ( !m_initialized ) {
		if ( !Initialize() ) return 0;
	}
	if ( !mixerIsOpen )
		if (!OpenMixer()) return 0;
	if ( !IdentifyControls() ) return 0;
	
	return 	m_controlNumber;
}
//Opening Mixer
BOOL CHMixer::OpenMixer()
{
	if ( !m_initialized ) {
		if ( !Initialize() ) return FALSE;
	}

	MMRESULT	result;

	result = mixerOpen(&m_hMixer,0,0L,
		NULL, MIXER_OBJECTF_HMIXER );

	if ( result!=MMSYSERR_NOERROR ) {
		lastError = result;
		return FALSE;
	}
	mixerIsOpen = TRUE;
	return TRUE;
}
//Returns list of all available components
BOOL CHMixer::GetControlList(unsigned long *id)
{
	if ( !m_initialized ) {
		if ( !Initialize() ) return FALSE;
	}
	if ( id==NULL ) return FALSE;
	if ( !mixerIsOpen )
		if (!OpenMixer()) return FALSE;
	
	for (UINT i=0;i<m_controlNumber;i++)
		id[i] = m_controlID[i];
	return TRUE;
}
//Private
BOOL CHMixer::Initialize()
{
	m_initialized = FALSE;
	
	lastError=0;
	m_hMixer = NULL;
	m_pWnd = NULL;
	mixerID = 0;
	mixerIsOpen=FALSE;
	capsIdentified = FALSE;
	m_controlNumber = 0;
	m_lineNumber = 0;
	for (int i=0;i<20;i++) m_controlID[i]=0;
//	if ( !GetParentPointer() ) return FALSE;

	mixerCaps.cDestinations=0;
	mixerCaps.fdwSupport=0;
	strcpy(mixerCaps.szPname,"Error:No name can be found...\0");
	mixerCaps.vDriverVersion=0;
	mixerCaps.wMid=0;
	mixerCaps.wPid=0;

	m_initialized = TRUE;
	return TRUE;
}
//Use this function to give mixer a pointer of the 
//parent dialog, so dialog will recive Windows mixer events.
BOOL CHMixer::SetParentPointer(CWnd *pWnd)
{
	return FALSE;
}
//Private
BOOL CHMixer::GetParentPointer()
{
	BOOL result=FALSE;
	(m_pWnd==NULL)? result=FALSE:result=TRUE;
	return result;
}
//Private
void CHMixer::IdentifyCapabilities()
{
	if ( !mixerIsOpen ) return;
	
	MMRESULT result;
	result = MMSYSERR_NOERROR;

	//Asking for a valid ID
	result = mixerGetID((HMIXEROBJ)m_hMixer,&mixerID,MIXER_OBJECTF_HMIXER);

	if (result !=MMSYSERR_NOERROR ) {
		return;
	}

	//Finding Mixer capabilities
	result = mixerGetDevCaps(mixerID,&mixerCaps,sizeof(mixerCaps));

	if (result !=MMSYSERR_NOERROR ) {
		return;
	}
	capsIdentified = TRUE;
}
//Returns Name of your sound card "Product Name" Identified by your Manufactorer.
CString CHMixer::GetProductName()
{
	if ( !m_initialized ) 
		if ( !Initialize() ) return "Error: can not do initialization.";

	if ( !mixerIsOpen ) OpenMixer();
	if ( !mixerIsOpen ) return "Error: Mixer is closed.Make sure you have a Sound Card installed on your system.";
	if ( !capsIdentified ) IdentifyCapabilities();
	if ( !capsIdentified ) return "Error: Can not Find Capabilities of your mixer.";

	return mixerCaps.szPname;
}
//Private
BOOL CHMixer::IdentifyControls()
{
	if ( !m_initialized ) {
		if ( !Initialize() ) return FALSE;
	}
	if ( !mixerIsOpen ) 
		if (!OpenMixer()) return FALSE;

	component[0]=MIXERLINE_COMPONENTTYPE_DST_DIGITAL ;
	component[1]=MIXERLINE_COMPONENTTYPE_DST_HEADPHONES ;
	component[2]=MIXERLINE_COMPONENTTYPE_DST_LINE;
	component[3]=MIXERLINE_COMPONENTTYPE_DST_MONITOR;
	component[4]=MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	component[5]=MIXERLINE_COMPONENTTYPE_DST_TELEPHONE;
	component[6]=MIXERLINE_COMPONENTTYPE_DST_UNDEFINED;
	component[7]=MIXERLINE_COMPONENTTYPE_DST_VOICEIN;
	component[8]=MIXERLINE_COMPONENTTYPE_DST_WAVEIN;

	component[9]=MIXERLINE_COMPONENTTYPE_SRC_ANALOG;
	component[10]=MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY;
	component[11]=MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC;
	component[12]=MIXERLINE_COMPONENTTYPE_SRC_DIGITAL;
	component[13]=MIXERLINE_COMPONENTTYPE_SRC_LINE;
	component[14]=MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
	component[15]=MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER;
	component[16]=MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER;
	component[17]=MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE ;
	component[18]=MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED;
	component[19]=MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT ;

//	TRACE("\n\nFinding controls Started...\n\n");

	m_controlNumber=0;
	m_lineNumber=0;
	for (int i=0;i<20;i++) {
		if (FindComponent(component[i])) {
			m_controlID[m_controlNumber]=mixerControl.dwControlID;//component[i];
			m_component[m_controlNumber]=component[i];
			m_label[m_controlNumber++] =mixerLine.szName;

//			TRACE("\n\t\t\t\t\t\t[");
//			TRACE(mixerLine.szName);
//			TRACE("]*");
		}
	}
//	TRACE("\nEnd of finding controls...\n\n");
	return TRUE;
}
//Asking for control labels
BOOL CHMixer::GetControlListLabel(CString *name)
{
	if (name==NULL) return FALSE;

	for (UINT i=0;i<m_controlNumber;i++)
		name[i]=m_label[i];

	return TRUE;
}
//Finding IDs of available components
BOOL CHMixer::GetComponentIDList(unsigned long *id)
{
	if ( !m_initialized ) {
		if ( !Initialize() ) return FALSE;
	}
	if ( id==NULL ) return FALSE;
	if ( !mixerIsOpen )
		if (!OpenMixer()) return FALSE;
	
	for (UINT i=0;i<m_controlNumber;i++)
		id[i] = m_component[i];
	return TRUE;
}
