# Microsoft Developer Studio Project File - Name="nel_export" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nel_export - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nel_export.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nel_export.mak" CFG="nel_export - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nel_export - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nel_export - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "nel_export - Win32 Hybrid" (based on "Win32 (x86) Application")
!MESSAGE "nel_export - Win32 ReleaseDebug" (based on "Win32 (x86) Application")
!MESSAGE "nel_export - Win32 DebugFast" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nel_export - Win32 Release"

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
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "../../../../include" /I "../../../../src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"std_afx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib freetype.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /machine:I386 /out:"C:\3dsmax3_1\plugins\nelexport.dlu" /libpath:"D:\3DSMAX3\Maxsdk\lib" /release
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Change version number
PreLink_Cmds=buildinc version.ver nel_export.rc	rc /l 0x40c /fo"Release/nel_export.res" /d "NDEBUG" nel_export.rc
# End Special Build Tool

!ELSEIF  "$(CFG)" == "nel_export - Win32 Debug"

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
# ADD CPP /nologo /G6 /MDd /W3 /GR /GX /Zi /Od /I "../../../../include" /I "../../../../src" /D "_WINDOWS" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /FR /Yu"std_afx.h" /FD /Zm400 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib libxml2.lib freetype.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelexport.dlu" /pdbtype:sept /libpath:"D:\3DSMAX3\Maxsdk\lib"
# SUBTRACT LINK32 /incremental:no
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy dans max normal
PostBuild_Cmds=xcopy "C:\3dsmax3_1 debug\exe\*.dl*" "C:\3dsmax3_1" /D /S /Y
# End Special Build Tool

!ELSEIF  "$(CFG)" == "nel_export - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_export___Win32_Hybrid"
# PROP BASE Intermediate_Dir "nel_export___Win32_Hybrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Hybrid"
# PROP Intermediate_Dir "Hybrid"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MD /W3 /Gm /GR /GX /ZI /Od /I "../../../../include" /I "../../../../src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__STL_DEBUG" /FR /Yu"std_afx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 freetype.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /debug /machine:I386 /out:"c:\3DSMAX3_1\plugins\Nel_export.dlu" /pdbtype:sept /libpath:"D:\3DSMAX3\Maxsdk\lib"

!ELSEIF  "$(CFG)" == "nel_export - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nel_export___Win32_ReleaseDebug"
# PROP BASE Intermediate_Dir "nel_export___Win32_ReleaseDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "D:\3DSMAX3\Maxsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__STL_DEBUG" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /Zi /O2 /I "../../../../include" /I "../../../../src" /D "_WINDOWS" /D "NL_RELEASE_DEBUG" /D "WIN32" /D "NDEBUG" /Yu"std_afx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /machine:I386 /out:"D:\3DSMAX3\stdplugs\Nel_export.dlu" /libpath:"D:\3DSMAX3\Maxsdk\lib" /release
# ADD LINK32 version.lib freetype.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"C:\3dsmax3_1\plugins\nelexport.dlu" /pdbtype:sept /libpath:"D:\3DSMAX3\Maxsdk\lib" /release

!ELSEIF  "$(CFG)" == "nel_export - Win32 DebugFast"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_export___Win32_DebugFast"
# PROP BASE Intermediate_Dir "nel_export___Win32_DebugFast"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugFast"
# PROP Intermediate_Dir "DebugFast"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MDd /W3 /GR /GX /Zi /Od /I "D:\3DSMAX3\Maxsdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__STL_DEBUG" /Yu"std_afx.h" /FD /Zm200 /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G6 /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../../include" /I "../../../../src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "NL_DEBUG_FAST" /Fr /Yu"std_afx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 freetype.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelexport.dlu" /pdbtype:sept /libpath:"D:\3DSMAX3\Maxsdk\lib"
# ADD LINK32 version.lib freetype.lib comctl32.lib bmm.lib core.lib geom.lib gfx.lib mesh.lib maxutil.lib maxscrpt.lib gup.lib paramblk2.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libxml2.lib /nologo /base:"0x105b0000" /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelexport.dlu" /pdbtype:sept /libpath:"D:\3DSMAX3\Maxsdk\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy dans max normal
PostBuild_Cmds=copy "c:\3dsmax3_1 debug\exe\plugins\nelexport.dlu" "c:\3dsmax3_1\plugins"	echo copie dans max
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "nel_export - Win32 Release"
# Name "nel_export - Win32 Debug"
# Name "nel_export - Win32 Hybrid"
# Name "nel_export - Win32 ReleaseDebug"
# Name "nel_export - Win32 DebugFast"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DllEntry.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\nel_export.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\nel_export.def
# End Source File
# Begin Source File

SOURCE=.\nel_export.rc
# End Source File
# Begin Source File

SOURCE=.\nel_export_collision.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_export_export.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\nel_export_filetools.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\nel_export_node_properties.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_export_scene.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_export_script.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\nel_export_swt.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_export_view.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\nel_export_zone.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\progress.cpp
# End Source File
# Begin Source File

SOURCE=.\std_afx.cpp
# ADD CPP /Yc"std_afx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\nel_export.h
# End Source File
# Begin Source File

SOURCE=.\nel_export_scene.h
# End Source File
# Begin Source File

SOURCE=.\progress.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\std_afx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# End Group
# End Target
# End Project
