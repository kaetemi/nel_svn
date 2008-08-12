# Microsoft Developer Studio Project File - Name="nel_mesh_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=nel_mesh_lib - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nel_mesh_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nel_mesh_lib.mak" CFG="nel_mesh_lib - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nel_mesh_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "nel_mesh_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "nel_mesh_lib - Win32 Hybrid" (based on "Win32 (x86) Static Library")
!MESSAGE "nel_mesh_lib - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "nel_mesh_lib - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nel_mesh_lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../../../include" /I "../../../../src" /D "WIN32" /D "_MBCS" /D "_LIB" /D "NDEBUG" /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "D:\3DSMAX3\Maxsdk\include" /I "../../../../include" /I "../../../../src" /D "_MBCS" /D "_LIB" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /FR /Yu"stdafx.h" /FD /GZ /Zm300 /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_mesh_lib___Win32_Hybrid"
# PROP BASE Intermediate_Dir "nel_mesh_lib___Win32_Hybrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "nel_mesh_lib___Win32_Hybrid"
# PROP Intermediate_Dir "nel_mesh_lib___Win32_Hybrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "../../../../include" /I "../../../../src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nel_mesh_lib___Win32_ReleaseDebug"
# PROP BASE Intermediate_Dir "nel_mesh_lib___Win32_ReleaseDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../../../../include" /I "../../../../src" /D "_MBCS" /D "_LIB" /D "NL_RELEASE_DEBUG" /D "WIN32" /D "NDEBUG" /Yu"stdafx.h" /FD /Zm200 /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 DebugFast"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "nel_mesh_lib___Win32_DebugFast"
# PROP BASE Intermediate_Dir "nel_mesh_lib___Win32_DebugFast"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugFast"
# PROP Intermediate_Dir "DebugFast"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "D:\3DSMAX3\Maxsdk\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STL_DEBUG" /Yu"stdafx.h" /FD /GZ /Zm200 /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "D:\3DSMAX3\Maxsdk\include" /I "../../../../include" /I "../../../../src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NL_DEBUG_FAST" /Fr /Yu"stdafx.h" /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "nel_mesh_lib - Win32 Release"
# Name "nel_mesh_lib - Win32 Debug"
# Name "nel_mesh_lib - Win32 Hybrid"
# Name "nel_mesh_lib - Win32 ReleaseDebug"
# Name "nel_mesh_lib - Win32 DebugFast"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\calc_lm.cpp
# End Source File
# Begin Source File

SOURCE=.\calc_lm_plane.cpp
# End Source File
# Begin Source File

SOURCE=.\calc_lm_rad.cpp
# End Source File
# Begin Source File

SOURCE=.\calc_lm_rt.cpp
# End Source File
# Begin Source File

SOURCE=.\export_anim.cpp
# End Source File
# Begin Source File

SOURCE=.\export_collision.cpp
# End Source File
# Begin Source File

SOURCE=.\export_flare.cpp
# End Source File
# Begin Source File

SOURCE=.\export_light.cpp
# End Source File
# Begin Source File

SOURCE=.\export_lod_character.cpp
# End Source File
# Begin Source File

SOURCE=.\export_material.cpp
# End Source File
# Begin Source File

SOURCE=.\export_mesh.cpp

!IF  "$(CFG)" == "nel_mesh_lib - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 Debug"

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 ReleaseDebug"

!ELSEIF  "$(CFG)" == "nel_mesh_lib - Win32 DebugFast"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\export_mesh_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\export_misc.cpp
# End Source File
# Begin Source File

SOURCE=.\export_particle_system.cpp
# End Source File
# Begin Source File

SOURCE=.\export_radial_normal.cpp
# End Source File
# Begin Source File

SOURCE=.\export_remanence.cpp
# End Source File
# Begin Source File

SOURCE=.\export_scene.cpp
# End Source File
# Begin Source File

SOURCE=.\export_script.cpp
# End Source File
# Begin Source File

SOURCE=.\export_skinning.cpp
# End Source File
# Begin Source File

SOURCE=.\export_vegetable.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\calc_lm.h
# End Source File
# Begin Source File

SOURCE=.\calc_lm_plane.h
# End Source File
# Begin Source File

SOURCE=.\calc_lm_rt.h
# End Source File
# Begin Source File

SOURCE=.\export_appdata.h
# End Source File
# Begin Source File

SOURCE=.\export_nel.h
# End Source File
# Begin Source File

SOURCE=.\export_radial_normal.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
