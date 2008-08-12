# Microsoft Developer Studio Project File - Name="nel_patch_converter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nel_patch_converter - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nel_patch_converter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nel_patch_converter.mak" CFG="nel_patch_converter - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nel_patch_converter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nel_patch_converter - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "nel_patch_converter - Win32 Hybrid" (based on "Win32 (x86) Application")
!MESSAGE "nel_patch_converter - Win32 ReleaseDebug" (based on "Win32 (x86) Application")
!MESSAGE "nel_patch_converter - Win32 DebugFast" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nel_patch_converter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /I "../../../../include" /I "../../../../src" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "NL_NO_DEFINE_NEW" /FR /YX /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 maxscrpt.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib freetype.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /machine:I386 /out:"C:\3dsmax3_1\plugins\nelconvertpatch.dlm" /libpath:"C:\3dsmax3_1\Maxsdk\lib" /release
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Change version number
PreLink_Cmds=buildinc version.ver nel_patch_converter.rc	rc /l 0x40c /fo"Release/nel_patch_converter.res" /d "NDEBUG" nel_patch_converter.rc
# End Special Build Tool

!ELSEIF  "$(CFG)" == "nel_patch_converter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /GR /GX /Zi /Od /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /I "../../../../include" /I "../../../../src" /D "__STL_DEBUG" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "NL_NO_DEFINE_NEW" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 maxscrpt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib version.lib freetype.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelconvertpatch.dlm" /pdbtype:sept /libpath:"C:\3dsmax3_1\Maxsdk\lib"

!ELSEIF  "$(CFG)" == "nel_patch_converter - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_patch_converter___Win32_Hybrid"
# PROP BASE Intermediate_Dir "nel_patch_converter___Win32_Hybrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Hybrid"
# PROP Intermediate_Dir "Hybrid"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MD /W3 /Gm /GR /GX /ZI /Od /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /I "../../../../include" /I "../../../../src" /D "__STL_DEBUG" /D "WIN32" /D "_WINDOWS" /D "NL_NO_DEFINE_NEW" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 delayimp.lib edmodel.lib mnmath.lib acap.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib version.lib freetype.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"msvcrtd.lib" /out:"C:\3dsmax3_1\plugins\nelconvertpatch.dlm" /pdbtype:sept /libpath:"C:\3dsmax3_1\Maxsdk\lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "nel_patch_converter - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nel_patch_converter___Win32_ReleaseDebug"
# PROP BASE Intermediate_Dir "nel_patch_converter___Win32_ReleaseDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /Zi /O2 /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /I "../../../../include" /I "../../../../src" /D "NL_RELEASE_DEBUG" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "NL_NO_DEFINE_NEW" /FR /YX /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 maxscrpt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /machine:I386 /out:"C:\3dsmax3_1\plugins\nelconvertpatch.dlm" /libpath:"C:\3dsmax3_1\Maxsdk\lib" /release
# ADD LINK32 maxscrpt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib version.lib freetype.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1\plugins\nelconvertpatch.dlm" /pdbtype:sept /libpath:"C:\3dsmax3_1\Maxsdk\lib" /release

!ELSEIF  "$(CFG)" == "nel_patch_converter - Win32 DebugFast"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_patch_converter___Win32_DebugFast"
# PROP BASE Intermediate_Dir "nel_patch_converter___Win32_DebugFast"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugFast"
# PROP Intermediate_Dir "DebugFast"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MDd /W3 /Gm /GR /GX /Zi /Od /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__STL_DEBUG" /FD /c
# SUBTRACT BASE CPP /Fr /YX /Yc /Yu
# ADD CPP /nologo /G6 /MDd /W3 /Gm /GR /GX /Zi /Od /Ob1 /I "C:\3dsmax3_1\Maxsdk\include ..\RPO" /I "../../../../include" /I "../../../../src" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "WIN32" /D "_WINDOWS" /D "NL_NO_DEFINE_NEW" /Fr /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 maxscrpt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib version.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelconvertpatch.dlm" /pdbtype:sept /libpath:"C:\3dsmax3_1\Maxsdk\lib"
# ADD LINK32 maxscrpt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib paramblk2.lib maxutil.lib Maxscrpt.lib version.lib freetype.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelconvertpatch.dlm" /pdbtype:sept /libpath:"C:\3dsmax3_1\Maxsdk\lib"

!ENDIF 

# Begin Target

# Name "nel_patch_converter - Win32 Release"
# Name "nel_patch_converter - Win32 Debug"
# Name "nel_patch_converter - Win32 Hybrid"
# Name "nel_patch_converter - Win32 ReleaseDebug"
# Name "nel_patch_converter - Win32 DebugFast"
# Begin Source File

SOURCE=.\DllEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_patch_converter.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_patch_converter.def
# End Source File
# Begin Source File

SOURCE=.\nel_patch_converter.h
# End Source File
# Begin Source File

SOURCE=.\nel_patch_converter.rc
# End Source File
# Begin Source File

SOURCE=.\PO2RPO.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\rykolscript.txt
# End Source File
# Begin Source File

SOURCE=.\script.cpp
# End Source File
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# End Target
# End Project
