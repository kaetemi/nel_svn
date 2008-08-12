# Microsoft Developer Studio Project File - Name="driver_opengl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=driver_opengl - Win32 DebugInstrument
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "driver_opengl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "driver_opengl.mak" CFG="driver_opengl - Win32 DebugInstrument"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "driver_opengl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_opengl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_opengl - Win32 ReleaseDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_opengl - Win32 DebugFast" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "driver_opengl - Win32 DebugInstrument" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "driver_opengl - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../obj/Release/driver_opengl"
# PROP Intermediate_Dir "../../../../obj/Release/driver_opengl"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../../../include" /I "../../.." /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENGL_EXPORTS" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /Yu"stdopengl.h" /FD /c
# SUBTRACT CPP /Fr
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 dinput.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /dll /pdb:none /machine:I386 /out:"../../../../lib/nel_drv_opengl_win_r.dll" /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/Debug/driver_opengl"
# PROP Intermediate_Dir "../../../../obj/Debug/driver_opengl"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../../../../include" /I "../../.." /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENGL_EXPORTS" /D "__STL_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /Yu"stdopengl.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 dinput.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_opengl_win_d.dll" /pdbtype:sept /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../../obj/ReleaseDebug/driver_opengl"
# PROP Intermediate_Dir "../../../../obj/ReleaseDebug/driver_opengl"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../../../../include" /I "../../.." /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENGL_EXPORTS" /D "NL_RELEASE_DEBUG" /D "LIBXML_STATIC" /D "WIN32" /D "NDEBUG" /D "_MBCS" /Yu"stdopengl.h" /FD /c
# SUBTRACT CPP /Fr
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 dinput.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /dll /debug /machine:I386 /out:"../../../../lib/nel_drv_opengl_win_rd.dll" /pdbtype:sept /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/DebugFast/driver_opengl"
# PROP Intermediate_Dir "../../../../obj/DebugFast/driver_opengl"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../../include" /I "../../.." /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENGL_EXPORTS" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /Yu"stdopengl.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Fr
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 dinput.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_opengl_win_df.dll" /pdbtype:sept /libpath:"../../../../lib" /libpath:"../../../../nel/lib"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 DebugInstrument"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "driver_opengl___Win32_DebugInstrument"
# PROP BASE Intermediate_Dir "driver_opengl___Win32_DebugInstrument"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../../obj/DebugInstrument/driver_opengl"
# PROP Intermediate_Dir "../../../../obj/DebugInstrument/driver_opengl"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../../../../include" /I "../../.." /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENGL_EXPORTS" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /Yu"stdopengl.h" /FD /GZ /c
# SUBTRACT BASE CPP /Gf /Fr
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../../../../include" /I "../../.." /D "_WINDOWS" /D "_USRDLL" /D "DRIVER_OPENGL_EXPORTS" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /D "NL_DEBUG_INSTRUMENT" /Yu"stdopengl.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dinput.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"../../../../lib/nel_drv_opengl_win_df.dll" /pdbtype:sept /libpath:"../../../../lib" /libpath:"../../../../nel/lib"
# ADD LINK32 dinput.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /dll /incremental:no /pdb:"../../../../lib/nel_drv_opengl_win_di.pdb" /debug /machine:I386 /def:".\driver_opengl.def" /out:"../../../../lib/nel_drv_opengl_win_di.dll" /libpath:"../../../../lib" /libpath:"../../../../nel/lib" /fixed:no
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "driver_opengl - Win32 Release"
# Name "driver_opengl - Win32 Debug"
# Name "driver_opengl - Win32 ReleaseDebug"
# Name "driver_opengl - Win32 DebugFast"
# Name "driver_opengl - Win32 DebugInstrument"
# Begin Source File

SOURCE=.\driver_opengl.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl.def

!IF  "$(CFG)" == "driver_opengl - Win32 Release"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 Debug"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 DebugFast"

!ELSEIF  "$(CFG)" == "driver_opengl - Win32 DebugInstrument"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\driver_opengl.h
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_extension.h
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_extension_def.h
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_light.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_material.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_states.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_states.h
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_texture.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_vertex.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_vertex_buffer_hard.cpp
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_vertex_buffer_hard.h
# End Source File
# Begin Source File

SOURCE=.\driver_opengl_vertex_program.cpp
# End Source File
# Begin Source File

SOURCE=.\stdopengl.cpp
# ADD CPP /Yc"stdopengl.h"
# End Source File
# Begin Source File

SOURCE=.\stdopengl.h
# End Source File
# End Target
# End Project
