# Microsoft Developer Studio Project File - Name="driver_fmod" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=driver_fmod - Win32 DebugInstrument
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "driver_fmod.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "driver_fmod.mak" CFG="driver_fmod - Win32 DebugInstrument"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "driver_fmod - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_fmod - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_fmod - Win32 DebugFast" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_fmod - Win32 ReleaseDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_fmod - Win32 DebugInstrument" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "driver_fmod - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../obj/Release/driver_fmod"
# PROP Intermediate_Dir "../../../../obj/Release/driver_fmod"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../../../include" /I "../../.." /D "NDEBUG" /D "NLSOUND_PROFILE" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:none /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_r.dll" /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/Debug/driver_fmod"
# PROP Intermediate_Dir "../../../../obj/Debug/driver_fmod"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../../../../include" /I "../../.." /D "_DEBUG" /D "__STL_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_d.dll" /pdbtype:sept /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 DebugFast"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugFast"
# PROP BASE Intermediate_Dir "DebugFast"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/DebugFast/driver_fmod"
# PROP Intermediate_Dir "../../../../obj/DebugFast/driver_fmod"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /D "_DEBUG" /D "__STL_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../../include" /I "../../.." /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_d.dll" /pdbtype:sept
# ADD LINK32 fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_df.dll" /pdbtype:sept /libpath:"../../../../lib" /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseDebug"
# PROP BASE Intermediate_Dir "ReleaseDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../obj/ReleaseDebug/driver_fmod"
# PROP Intermediate_Dir "../../../../obj/ReleaseDebug/driver_fmod"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "NLSOUND_PROFILE" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../../../../include" /I "../../.." /D "NL_RELEASE_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "NDEBUG" /D "LIBXML_STATIC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:none /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_r.dll"
# ADD LINK32 fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_rd.dll" /pdbtype:sept /libpath:"../../../../nel/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 DebugInstrument"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "driver_fmod___Win32_DebugInstrument"
# PROP BASE Intermediate_Dir "driver_fmod___Win32_DebugInstrument"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/DebugInstrument/driver_fmod"
# PROP Intermediate_Dir "../../../../obj/DebugInstrument/driver_fmod"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../../include" /I "../../.." /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../../../../include" /I "../../.." /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_FMOD_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /D "NL_DEBUG_INSTRUMENT" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_fmod_win_df.dll" /pdbtype:sept /libpath:"../../../../lib" /libpath:"../../../../nel/lib"
# ADD LINK32 fmodvc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"../../../../lib/nel_drv_fmod_win_di.pdb" /debug /machine:I386 /def:".\driver_fmod.def" /out:"../../../../lib/nel_drv_fmod_win_di.dll" /libpath:"../../../../lib" /libpath:"../../../../nel/lib" /fixed:no
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "driver_fmod - Win32 Release"
# Name "driver_fmod - Win32 Debug"
# Name "driver_fmod - Win32 DebugFast"
# Name "driver_fmod - Win32 ReleaseDebug"
# Name "driver_fmod - Win32 DebugInstrument"
# Begin Source File

SOURCE=.\buffer_fmod.cpp
# End Source File
# Begin Source File

SOURCE=.\buffer_fmod.h
# End Source File
# Begin Source File

SOURCE=.\driver_fmod.def

!IF  "$(CFG)" == "driver_fmod - Win32 Release"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 Debug"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 DebugFast"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "driver_fmod - Win32 DebugInstrument"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\listener_fmod.cpp
# End Source File
# Begin Source File

SOURCE=.\listener_fmod.h
# End Source File
# Begin Source File

SOURCE=.\music_channel_fmod.cpp
# End Source File
# Begin Source File

SOURCE=.\music_channel_fmod.h
# End Source File
# Begin Source File

SOURCE=.\sound_driver_fmod.cpp
# End Source File
# Begin Source File

SOURCE=.\sound_driver_fmod.h
# End Source File
# Begin Source File

SOURCE=.\source_fmod.cpp
# End Source File
# Begin Source File

SOURCE=.\source_fmod.h
# End Source File
# Begin Source File

SOURCE=.\stdfmod.cpp
# End Source File
# Begin Source File

SOURCE=.\stdfmod.h
# End Source File
# End Target
# End Project
