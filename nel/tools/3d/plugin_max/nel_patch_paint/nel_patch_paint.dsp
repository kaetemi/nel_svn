# Microsoft Developer Studio Project File - Name="nel_patch_paint" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=nel_patch_paint - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nel_patch_paint.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nel_patch_paint.mak" CFG="nel_patch_paint - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nel_patch_paint - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "nel_patch_paint - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "nel_patch_paint - Win32 Hybrid" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "nel_patch_paint - Win32 ReleaseDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "nel_patch_paint - Win32 DebugFast" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "../../../../include" /I "../../../../src" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /Zm400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Maxscrpt.lib helpsys.lib winmm.lib libxml2.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib version.lib freetype.lib /nologo /base:"0x05830000" /subsystem:windows /dll /machine:I386 /out:"C:\3dsmax3_1\plugins\nelpaintpatch.dlm" /release
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Change version number
PreLink_Cmds=buildinc version.ver nel_patch_paint.rc	rc /l 0x409 /fo"Release/nel_patch_paint.res" /d "NDEBUG" nel_patch_paint.rc
# End Special Build Tool

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /GR /GX /Zi /Od /I "../../../../include" /I "../../../../src" /D "_WINDOWS" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /FR /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Maxscrpt.lib helpsys.lib winmm.lib stlport_vc6.lib libxml2.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib version.lib freetype.lib /nologo /base:"0x05830000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelpaintpatch.dlm" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\nel_patch_paint___W"
# PROP BASE Intermediate_Dir ".\nel_patch_paint___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Hybrid"
# PROP Intermediate_Dir "Hybrid"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"mods.h" /c
# ADD CPP /nologo /G6 /MD /W3 /Gm /GR /GX /ZI /Od /I "../../../../include" /I "../../../../src" /D "WIN32" /D "_WINDOWS" /D "__STL_DEBUG" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\..\maxsdk\plugin\mods.dlm"
# ADD LINK32 nl3d_debug.lib nlmisc_debug.lib libxml2.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib version.lib freetype.lib /nologo /base:"0x05830000" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"msvcrtd.lib" /out:"C:\3dsmax3_1\plugins\nelpaintpatch.dlm" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nel_patch_paint___Win32_ReleaseDebug"
# PROP BASE Intermediate_Dir "nel_patch_paint___Win32_ReleaseDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MD /W3 /GR /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /Zi /O2 /I "../../../../include" /I "../../../../src" /D "_WINDOWS" /D "NL_RELEASE_DEBUG" /D "WIN32" /D "NDEBUG" /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib Maxscrpt.lib helpsys.lib freetype.lib winmm.lib /nologo /base:"0x05830000" /subsystem:windows /dll /machine:I386 /out:"C:\3dsmax3_1\plugins\neleditpatch.dlm" /release
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 Maxscrpt.lib helpsys.lib winmm.lib libxml2.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib version.lib freetype.lib /nologo /base:"0x05830000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1\plugins\nelpaintpatch.dlm" /pdbtype:sept /release
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_patch_paint___Win32_DebugFast"
# PROP BASE Intermediate_Dir "nel_patch_paint___Win32_DebugFast"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugFast"
# PROP Intermediate_Dir "DebugFast"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /MDd /W3 /Gm /GR /GX /Zi /Od /I "..\..\include" /D "_WINDOWS" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /FR /Yu"stdafx.h" /FD /Zm200 /c
# ADD CPP /nologo /G6 /MDd /W3 /Gm /GR /GX /Zi /Od /I "../../../../include" /I "../../../../src" /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "NL_DEBUG_FAST" /FR /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Maxscrpt.lib helpsys.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib version.lib winmm.lib stlport_vc6.lib freetype.lib /nologo /base:"0x05830000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelpaintpatch.dlm"
# SUBTRACT BASE LINK32 /pdb:none /incremental:no
# ADD LINK32 Maxscrpt.lib helpsys.lib winmm.lib stlport_vc6.lib libxml2.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib delayimp.lib bmm.lib core.lib edmodel.lib geom.lib gfx.lib mesh.lib mnmath.lib paramblk2.lib maxutil.lib acap.lib version.lib freetype.lib /nologo /base:"0x05830000" /subsystem:windows /dll /debug /machine:I386 /out:"C:\3dsmax3_1 debug\exe\plugins\nelpaintpatch.dlm" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy "C:\3dsmax3_1 debug\exe\plugins\nelpaintpatch.dlm" "c:\3dsmax3_1\plugins"	echo copie dans max
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "nel_patch_paint - Win32 Release"
# Name "nel_patch_paint - Win32 Debug"
# Name "nel_patch_paint - Win32 Hybrid"
# Name "nel_patch_paint - Win32 ReleaseDebug"
# Name "nel_patch_paint - Win32 DebugFast"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\DllEntry.h
# End Source File
# Begin Source File

SOURCE=.\nel_patch_paint.h
# End Source File
# Begin Source File

SOURCE=.\paint_fill.h
# End Source File
# Begin Source File

SOURCE=.\paint_light.h
# End Source File
# Begin Source File

SOURCE=.\paint_tileset.h
# End Source File
# Begin Source File

SOURCE=.\paint_to_nel.h
# End Source File
# Begin Source File

SOURCE=.\paint_ui.h
# End Source File
# Begin Source File

SOURCE=.\paint_undo.h
# End Source File
# Begin Source File

SOURCE=.\paint_vcolor.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\pick_col.cur
# End Source File
# Begin Source File

SOURCE=.\pick_color.cur
# End Source File
# End Group
# Begin Group "Images"

# PROP Default_Filter "*.tga"
# Begin Source File

SOURCE=.\_0.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_0.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_0.tga
InputName=_0

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_0.tga
InputName=_0

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_0.tga
InputName=_0

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_0.tga
InputName=_0

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_0.tga
InputName=_0

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_1.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_1.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_1.tga
InputName=_1

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_1.tga
InputName=_1

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_1.tga
InputName=_1

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_1.tga
InputName=_1

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_1.tga
InputName=_1

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_10.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_10.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_10.tga
InputName=_10

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_10.tga
InputName=_10

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_10.tga
InputName=_10

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_10.tga
InputName=_10

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_10.tga
InputName=_10

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_11.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_11.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_11.tga
InputName=_11

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_11.tga
InputName=_11

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_11.tga
InputName=_11

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_11.tga
InputName=_11

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_11.tga
InputName=_11

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_128.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_128.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_128.tga
InputName=_128

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_128.tga
InputName=_128

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_128.tga
InputName=_128

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_128.tga
InputName=_128

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_128.tga
InputName=_128

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_2.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_2.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_2.tga
InputName=_2

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_2.tga
InputName=_2

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_2.tga
InputName=_2

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_2.tga
InputName=_2

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_2.tga
InputName=_2

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_256.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_256.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_256.tga
InputName=_256

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_256.tga
InputName=_256

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_256.tga
InputName=_256

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_256.tga
InputName=_256

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_256.tga
InputName=_256

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_3.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_3.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_3.tga
InputName=_3

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_3.tga
InputName=_3

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_3.tga
InputName=_3

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_3.tga
InputName=_3

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_3.tga
InputName=_3

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_4.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_4.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_4.tga
InputName=_4

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_4.tga
InputName=_4

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_4.tga
InputName=_4

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_4.tga
InputName=_4

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_4.tga
InputName=_4

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_5.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_5.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_5.tga
InputName=_5

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_5.tga
InputName=_5

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_5.tga
InputName=_5

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_5.tga
InputName=_5

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_5.tga
InputName=_5

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_6.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_6.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_6.tga
InputName=_6

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_6.tga
InputName=_6

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_6.tga
InputName=_6

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_6.tga
InputName=_6

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_6.tga
InputName=_6

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_7.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_7.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_7.tga
InputName=_7

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_7.tga
InputName=_7

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_7.tga
InputName=_7

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_7.tga
InputName=_7

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_7.tga
InputName=_7

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_8.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_8.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_8.tga
InputName=_8

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_8.tga
InputName=_8

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_8.tga
InputName=_8

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_8.tga
InputName=_8

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_8.tga
InputName=_8

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_9.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_9.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_9.tga
InputName=_9

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_9.tga
InputName=_9

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_9.tga
InputName=_9

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_9.tga
InputName=_9

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_9.tga
InputName=_9

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_small.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\_small.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_small.tga
InputName=_small

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_small.tga
InputName=_small

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_small.tga
InputName=_small

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_small.tga
InputName=_small

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\_small.tga
InputName=_small

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\all.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\all.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\all.tga
InputName=all

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\all.tga
InputName=all

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\all.tga
InputName=all

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\all.tga
InputName=all

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\all.tga
InputName=all

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\goofy.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\goofy.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\goofy.tga
InputName=goofy

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\goofy.tga
InputName=goofy

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\goofy.tga
InputName=goofy

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\goofy.tga
InputName=goofy

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\goofy.tga
InputName=goofy

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\large.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\large.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\large.tga
InputName=large

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\large.tga
InputName=large

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\large.tga
InputName=large

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\large.tga
InputName=large

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\large.tga
InputName=large

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\light.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\light.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\light.tga
InputName=light

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\light.tga
InputName=light

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\light.tga
InputName=light

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\light.tga
InputName=light

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\light.tga
InputName=light

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lock.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\lock.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\lock.tga
InputName=lock

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\lock.tga
InputName=lock

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\lock.tga
InputName=lock

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\lock.tga
InputName=lock

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\lock.tga
InputName=lock

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\medium.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\medium.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\medium.tga
InputName=medium

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\medium.tga
InputName=medium

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\medium.tga
InputName=medium

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\medium.tga
InputName=medium

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\medium.tga
InputName=medium

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nothing.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\nothing.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\nothing.tga
InputName=nothing

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\nothing.tga
InputName=nothing

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\nothing.tga
InputName=nothing

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\nothing.tga
InputName=nothing

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\nothing.tga
InputName=nothing

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\oriented.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\oriented.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\oriented.tga
InputName=oriented

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\oriented.tga
InputName=oriented

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\oriented.tga
InputName=oriented

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\oriented.tga
InputName=oriented

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\oriented.tga
InputName=oriented

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\regular.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\regular.tga

!IF  "$(CFG)" == "nel_patch_paint - Win32 Release"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\regular.tga
InputName=regular

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Debug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\regular.tga
InputName=regular

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 Hybrid"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\regular.tga
InputName=regular

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 ReleaseDebug"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\regular.tga
InputName=regular

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "nel_patch_paint - Win32 DebugFast"

# Begin Custom Build - Generate $(InputName).cpp
ProjDir=.
InputPath=.\regular.tga
InputName=regular

"$(ProjDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bin2c $(InputPath) $(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DllEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_patch_paint.cpp
# End Source File
# Begin Source File

SOURCE=.\nel_patch_paint.def
# End Source File
# Begin Source File

SOURCE=.\nel_patch_paint.rc
# End Source File
# Begin Source File

SOURCE=.\paint.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_data.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_file.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_fill.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_light.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_main.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_mod.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_pops.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_record.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_restore.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_rollup.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_tileset.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_to_nel.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_ui.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_undo.cpp
# End Source File
# Begin Source File

SOURCE=.\paint_vcolor.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\keys.cfg
# End Source File
# Begin Source File

SOURCE=.\user_guide.txt
# End Source File
# End Target
# End Project
