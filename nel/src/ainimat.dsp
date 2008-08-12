# Microsoft Developer Studio Project File - Name="ainimat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ainimat - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ainimat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ainimat.mak" CFG="ainimat - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ainimat - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ainimat - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ainimat - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "ainimat - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE "ainimat - Win32 ReleaseProfile" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ainimat - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/Release/ainimat"
# PROP Intermediate_Dir "../obj/Release/ainimat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /I "../include" /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\nlainimat.lib"

!ELSEIF  "$(CFG)" == "ainimat - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/debug/ainimat"
# PROP Intermediate_Dir "../obj/debug/ainimat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /I "../include" /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STL_DEBUG" /FR /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\nlainimat_debug.lib"

!ELSEIF  "$(CFG)" == "ainimat - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseDebug"
# PROP BASE Intermediate_Dir "ReleaseDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/releasedebug"
# PROP Intermediate_Dir "../obj/releasedebug/ainimat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /I "../include" /MD /W3 /GR /GX /Zi /O2 /D "_LIB" /D "LIBXML_STATIC" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "NL_RELEASE_DEBUG" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\nlainimat_rd.lib"

!ELSEIF  "$(CFG)" == "ainimat - Win32 DebugFast"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ainimat___Win32_DebugFast"
# PROP BASE Intermediate_Dir "ainimat___Win32_DebugFast"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/debugfast/ainimat"
# PROP Intermediate_Dir "../obj/debugfast/ainimat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "__STL_DEBUG" /YX /FD /GZ /c
# ADD CPP /nologo /I "../include" /MDd /W3 /GR /GX /Zi /Od /D "_LIB" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\nlainimat_debug.lib"
# ADD LIB32 /nologo /out:"..\lib\nlainimat_debug_fast.lib"

!ELSEIF  "$(CFG)" == "ainimat - Win32 ReleaseProfile"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ainimat___Win32_ReleaseProfile"
# PROP BASE Intermediate_Dir "ainimat___Win32_ReleaseProfile"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/releaseprofile/ainimat"
# PROP Intermediate_Dir "../obj/releaseprofile/ainimat"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /I "../include" /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\nlainimat.lib"
# ADD LIB32 /nologo /out:"..\lib\nlainimat_profile.lib"

!ENDIF 

# Begin Target

# Name "ainimat - Win32 Release"
# Name "ainimat - Win32 Debug"
# Name "ainimat - Win32 ReleaseDebug"
# Name "ainimat - Win32 DebugFast"
# Name "ainimat - Win32 ReleaseProfile"
# Begin Group "nimat"

# PROP Default_Filter ""
# Begin Group "nimat_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ai\nimat\classifier.cpp
# End Source File
# Begin Source File

SOURCE=.\ai\nimat\mhics.cpp
# End Source File
# Begin Source File

SOURCE=.\ai\nimat\sensors_motivations_actions_def.cpp
# End Source File
# End Group
# Begin Group "nimat_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\nel\ai\nimat\classifier.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\ai\nimat\mhics.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\ai\nimat\sensors_motivations_actions_def.h
# End Source File
# End Group
# End Group
# End Target
# End Project
