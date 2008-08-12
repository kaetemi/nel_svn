# Microsoft Developer Studio Project File - Name="driver_openal" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=driver_openal - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "driver_openal.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "driver_openal.mak" CFG="driver_openal - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "driver_openal - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_openal - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_openal - Win32 ReleaseDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_openal - Win32 DebugFast" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "driver_openal - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../obj/Release/driver_openal"
# PROP Intermediate_Dir "../../../../obj/Release/driver_openal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /I "../../../include" /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DRIVER_OPENAL_EXPORTS" /Yu"stdopenal.h" /FD /c
# SUBTRACT CPP /Fr
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 user32.lib ALut.lib OpenAL32.lib eax.lib eaxguid.lib gdi32.lib advapi32.lib /nologo /dll /pdb:none /machine:I386 /out:"../../../../lib/nel_drv_openal_win_r.dll" /libpath:"C:\Netshare\openal\win\alut\release" /libpath:"C:\Netshare\openal\win\openal32\release"

!ELSEIF  "$(CFG)" == "driver_openal - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/Debug/driver_openal"
# PROP Intermediate_Dir "../../../../obj/Debug/driver_openal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /I "../../../include" /MDd /W3 /GR /GX /Zi /Od /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENAL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "__STL_DEBUG" /Yu"stdopenal.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ALut.lib OpenAL32.lib eax.lib eaxguid.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_openal_win_d.dll"

!ELSEIF  "$(CFG)" == "driver_openal - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../obj/ReleaseDebug/driver_openal"
# PROP Intermediate_Dir "../../../../obj/ReleaseDebug/driver_openal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /I "../../../include" /MD /W3 /GR /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DRIVER_OPENAL_EXPORTS" /D "NL_RELEASE_DEBUG" /Yu"stdopenal.h" /FD /c
# SUBTRACT CPP /Fr
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ALut.lib OpenAL32.lib eax.lib eaxguid.lib /nologo /dll /debug /machine:I386 /out:"../../../../lib/nel_drv_openal_win_rd.dll" /libpath:"C:\Netshare\openal\win\alut\release" /libpath:"C:\Netshare\openal\win\openal32\release"

!ELSEIF  "$(CFG)" == "driver_openal - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/DebugFast/driver_openal"
# PROP Intermediate_Dir "../../../../obj/DebugFast/driver_openal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /I "../../../include" /MDd /W3 /GR /GX /Zi /Od /Ob1 /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENAL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "NL_DEBUG_FAST" /Yu"stdopenal.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ALut.lib OpenAL32.lib eax.lib eaxguid.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_openal_win_df.dll"

!ENDIF 

# Begin Target

# Name "driver_openal - Win32 Release"
# Name "driver_openal - Win32 Debug"
# Name "driver_openal - Win32 ReleaseDebug"
# Name "driver_openal - Win32 DebugFast"
# Begin Source File

SOURCE=.\buffer_al.cpp
# End Source File
# Begin Source File

SOURCE=.\buffer_al.h
# End Source File
# Begin Source File

SOURCE=.\driver_openal.def
# End Source File
# Begin Source File

SOURCE=.\listener_al.cpp
# End Source File
# Begin Source File

SOURCE=.\listener_al.h
# End Source File
# Begin Source File

SOURCE=.\sound_driver_al.cpp
# End Source File
# Begin Source File

SOURCE=.\sound_driver_al.h
# End Source File
# Begin Source File

SOURCE=.\source_al.cpp
# End Source File
# Begin Source File

SOURCE=.\source_al.h
# End Source File
# Begin Source File

SOURCE=.\stdopenal.cpp
# ADD CPP /Yc"stdopenal.h"
# End Source File
# Begin Source File

SOURCE=.\stdopenal.h
# End Source File
# End Target
# End Project
