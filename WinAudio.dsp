# Microsoft Developer Studio Project File - Name="WinAudio" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinAudio - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinAudio.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinAudio.mak" CFG="WinAudio - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinAudio - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinAudio - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinAudio - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x429 /d "NDEBUG"
# ADD RSC /l 0x429 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib Winmm.lib Kernel32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WinAudio - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x429 /d "_DEBUG"
# ADD RSC /l 0x429 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vfw32.lib Winmm.lib Kernel32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WinAudio - Win32 Release"
# Name "WinAudio - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOpenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\HMixer.cpp
# End Source File
# Begin Source File

SOURCE=.\HSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\Info.cpp
# End Source File
# Begin Source File

SOURCE=.\MixerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinAudio.cpp
# End Source File
# Begin Source File

SOURCE=.\WinAudio.rc
# End Source File
# Begin Source File

SOURCE=.\WinAudioDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BitmapSlider.h
# End Source File
# Begin Source File

SOURCE=.\FileOpenDlg.h
# End Source File
# Begin Source File

SOURCE=.\HGraphics.h
# End Source File
# Begin Source File

SOURCE=.\HMixer.h
# End Source File
# Begin Source File

SOURCE=.\HSlider.h
# End Source File
# Begin Source File

SOURCE=.\Info.h
# End Source File
# Begin Source File

SOURCE=.\MixerDlg.h
# End Source File
# Begin Source File

SOURCE=.\PlayListDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinAudio.h
# End Source File
# Begin Source File

SOURCE=.\WinAudioDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\about.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\aboutD.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\aboutU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\back_U.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bk1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BK_SKIN_GRAY.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BK_SKIN_OLIVER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BK_SKIN_ORIGINAL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BK_SKIN_SHARP_BLUE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BWD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Channel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Channel_Active.bmp
# End Source File
# Begin Source File

SOURCE=.\res\closeD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eject_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ejectD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exit_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ff_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FFD.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\listD.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\listU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Minimize_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minimizeD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minusD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minusU.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\MixerBK.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\mixerd.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\mixeru.bmp
# End Source File
# Begin Source File

SOURCE=.\res\next_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nextD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG2SignPlay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG2SignPuse.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG2SignStop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SGN_ALL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SGN_N_RAND.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SGN_N_REP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SGN_ONE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SGN_RAND.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SGN_REP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OG_SPECTRUM.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\playD.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\playList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plusD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plusU.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PrevD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rep1D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rep1U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rep2D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rep2U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rep3D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rep3U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop_U.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stopD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Thumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Thumb_Active.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WinAudio.ico
# End Source File
# Begin Source File

SOURCE=.\res\WinAudio.rc2
# End Source File
# End Group
# End Target
# End Project
