# Microsoft Developer Studio Project File - Name="sound_lowlevel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sound_lowlevel - Win32 DebugInstrument
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sound_lowlevel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sound_lowlevel.mak" CFG="sound_lowlevel - Win32 DebugInstrument"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sound_lowlevel - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sound_lowlevel - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sound_lowlevel - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "sound_lowlevel - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE "sound_lowlevel - Win32 DebugInstrument" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sound_lowlevel - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../obj/Release/sound_lowlevel"
# PROP Intermediate_Dir "../../../obj/Release/sound_lowlevel"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../../include" /D "NDEBUG" /D "_LIB" /D "_AFXDLL" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../../../lib/nlsound_lowlevel_r.lib"

!ELSEIF  "$(CFG)" == "sound_lowlevel - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../obj/Debug/sound_lowlevel"
# PROP Intermediate_Dir "../../../obj/Debug/sound_lowlevel"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../../../include" /D "__STL_DEBUG" /D "_DEBUG" /D "_LIB" /D "_AFXDLL" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../../../lib/nlsound_lowlevel_d.lib"

!ELSEIF  "$(CFG)" == "sound_lowlevel - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../obj/ReleaseDebug/sound_lowlevel"
# PROP Intermediate_Dir "../../../obj/ReleaseDebug/sound_lowlevel"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../../../include" /D "NL_RELEASE_DEBUG" /D "_LIB" /D "_AFXDLL" /D "LIBXML_STATIC" /D "WIN32" /D "NDEBUG" /D "_MBCS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../../../lib/nlsound_lowlevel_rd.lib"

!ELSEIF  "$(CFG)" == "sound_lowlevel - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../obj/DebugFast/sound_lowlevel"
# PROP Intermediate_Dir "../../../obj/DebugFast/sound_lowlevel"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../include" /I "..\..\..\include" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_LIB" /D "_AFXDLL" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../../../lib/nlsound_lowlevel_df.lib"

!ELSEIF  "$(CFG)" == "sound_lowlevel - Win32 DebugInstrument"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sound_lowlevel___Win32_DebugInstrument"
# PROP BASE Intermediate_Dir "sound_lowlevel___Win32_DebugInstrument"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../obj/DebugInstrument/sound_lowlevel"
# PROP Intermediate_Dir "../../../obj/DebugInstrument/sound_lowlevel"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../include" /I "..\..\..\include" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_LIB" /D "_AFXDLL" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /FD /GZ /c
# SUBTRACT BASE CPP /Gf /Gy /Fr /YX
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../../../include" /I "..\..\..\include" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_LIB" /D "_AFXDLL" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /D "NL_DEBUG_INSTRUMENT" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../../lib/nlsound_lowlevel_df.lib"
# ADD LIB32 /nologo /out:"../../../lib/nlsound_lowlevel_di.lib"

!ENDIF 

# Begin Target

# Name "sound_lowlevel - Win32 Release"
# Name "sound_lowlevel - Win32 Debug"
# Name "sound_lowlevel - Win32 ReleaseDebug"
# Name "sound_lowlevel - Win32 DebugFast"
# Name "sound_lowlevel - Win32 DebugInstrument"
# Begin Source File

SOURCE=.\buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\buffer.h
# End Source File
# Begin Source File

SOURCE=.\listener.cpp
# End Source File
# Begin Source File

SOURCE=.\listener.h
# End Source File
# Begin Source File

SOURCE=.\loader.cpp
# End Source File
# Begin Source File

SOURCE=.\loader.h
# End Source File
# Begin Source File

SOURCE=.\sound_driver.cpp
# End Source File
# Begin Source File

SOURCE=.\sound_driver.h
# End Source File
# Begin Source File

SOURCE=.\source.cpp
# End Source File
# Begin Source File

SOURCE=.\source.h
# End Source File
# End Target
# End Project
