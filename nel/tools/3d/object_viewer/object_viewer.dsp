# Microsoft Developer Studio Project File - Name="object_viewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=object_viewer - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "object_viewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "object_viewer.mak" CFG="object_viewer - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "object_viewer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "object_viewer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "object_viewer - Win32 ReleaseDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "object_viewer - Win32 DebugFast" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "object_viewer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../../include" /I "../../../src" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "NL_NO_DEFINE_NEW" /Yu"std_afx.h" /FD /Zm400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 nlligo_r.lib nlgeorges_r.lib mfcs42.lib msvcrt.lib libc.lib libxml2.lib freetype.lib shlwapi.lib version.lib libjpeg.lib /nologo /subsystem:windows /dll /incremental:yes /machine:I386 /out:"../../../lib/object_viewer.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Change version number
PreLink_Cmds=buildinc version.ver object_viewer.rc	rc /l 0x40c /fo"Release/object_viewer.res" /d "NDEBUG" /d "_AFXDLL" object_viewer.rc
# End Special Build Tool

!ELSEIF  "$(CFG)" == "object_viewer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../../../include" /I "../../../src" /D "__STL_DEBUG" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "NL_NO_DEFINE_NEW" /FR /Yu"std_afx.h" /FD /D /GZ /Zm500 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 nlligo_d.lib nlgeorges_d.lib libxml2_debug.lib mfcs42d.lib freetype_debug.lib shlwapi.lib version.lib libjpeg.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../../../lib/object_viewer_debug.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "object_viewer - Win32 ReleaseDebug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "object_viewer___Win32_ReleaseDebug"
# PROP BASE Intermediate_Dir "object_viewer___Win32_ReleaseDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseDebug"
# PROP Intermediate_Dir "ReleaseDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"std_afx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../../../include" /I "../../../src" /D "NL_RELEASE_DEBUG" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "NL_NO_DEFINE_NEW" /Yu"std_afx.h" /FD /Zm400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mfcs42.lib msvcrt.lib libc.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../../lib/object_viewer.dll"
# ADD LINK32 mfcs42.lib libxml2.lib freetype.lib shlwapi.lib version.lib libjpeg.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../../../lib/object_viewer_rd.dll" /pdbtype:sept
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "object_viewer - Win32 DebugFast"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "object_viewer___Win32_DebugFast"
# PROP BASE Intermediate_Dir "object_viewer___Win32_DebugFast"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugFast"
# PROP Intermediate_Dir "DebugFast"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "__STL_DEBUG" /Yu"std_afx.h" /FD /D /GZ /Zm200 /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /Ob1 /I "../../../include" /I "../../../src" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_STLP_USE_DEBUG_LIB" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "NL_NO_DEFINE_NEW" /Yu"std_afx.h" /FD /D /GZ /Zm500 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mfcs42d.lib msvcrtd.lib libc.lib version.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../../../lib/object_viewer_debug.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none /incremental:no
# ADD LINK32 shlwapi.lib nlligo_df.lib nlgeorges_df.lib freetype_debug.lib libxml2_debug.lib version.lib libjpeg.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"../../../lib/object_viewer_debug_fast.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "object_viewer - Win32 Release"
# Name "object_viewer - Win32 Debug"
# Name "object_viewer - Win32 ReleaseDebug"
# Name "object_viewer - Win32 DebugFast"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\about_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\animation_dlg.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\animation_set_dlg.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\blend_wnd.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\choose_bg_color_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\choose_frame_delay.cpp
# End Source File
# Begin Source File

SOURCE=.\choose_name.cpp
# End Source File
# Begin Source File

SOURCE=.\choose_pool_id.cpp
# End Source File
# Begin Source File

SOURCE=.\choose_sun_color_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\color_static.cpp
# End Source File
# Begin Source File

SOURCE=.\create_file_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\day_night_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\dialog_progress.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_ex.cpp
# End Source File
# Begin Source File

SOURCE=.\fog_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\global_wind_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\graph.cpp
# End Source File
# Begin Source File

SOURCE=.\light_group_factor.cpp
# End Source File
# Begin Source File

SOURCE=.\main_dlg.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\main_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\object_viewer.cpp

!IF  "$(CFG)" == "object_viewer - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "object_viewer - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "object_viewer - Win32 ReleaseDebug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "object_viewer - Win32 DebugFast"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\object_viewer.rc
# End Source File
# Begin Source File

SOURCE=.\save_options_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\scene_rot_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\select_movie_size.cpp
# End Source File
# Begin Source File

SOURCE=.\select_string.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\set_value_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\skeleton_scale_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\skippable_message_box.cpp
# End Source File
# Begin Source File

SOURCE=.\slot_dlg.cpp
# ADD CPP /Yu"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\snapshot_tool_dlg.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\sound_system.cpp
# End Source File
# Begin Source File

SOURCE=.\std_afx.cpp
# ADD CPP /Yc"std_afx.h"
# End Source File
# Begin Source File

SOURCE=.\tune_mrm_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\water_pool_editor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\about_dialog.h
# End Source File
# Begin Source File

SOURCE=.\animation_dlg.h
# End Source File
# Begin Source File

SOURCE=.\animation_set_dlg.h
# End Source File
# Begin Source File

SOURCE=.\blend_wnd.h
# End Source File
# Begin Source File

SOURCE=.\choose_bg_color_dlg.h
# End Source File
# Begin Source File

SOURCE=.\choose_frame_delay.h
# End Source File
# Begin Source File

SOURCE=.\choose_name.h
# End Source File
# Begin Source File

SOURCE=.\choose_pool_id.h
# End Source File
# Begin Source File

SOURCE=.\choose_sun_color_dlg.h
# End Source File
# Begin Source File

SOURCE=.\color_static.h
# End Source File
# Begin Source File

SOURCE=.\create_file_dlg.h
# End Source File
# Begin Source File

SOURCE=.\day_night_dlg.h
# End Source File
# Begin Source File

SOURCE=.\dialog_progress.h
# End Source File
# Begin Source File

SOURCE=.\edit_ex.h
# End Source File
# Begin Source File

SOURCE=.\fog_dlg.h
# End Source File
# Begin Source File

SOURCE=.\global_wind_dlg.h
# End Source File
# Begin Source File

SOURCE=.\graph.h
# End Source File
# Begin Source File

SOURCE=.\light_group_factor.h
# End Source File
# Begin Source File

SOURCE=.\main_dlg.h
# End Source File
# Begin Source File

SOURCE=.\main_frame.h
# End Source File
# Begin Source File

SOURCE=.\object_viewer.h
# End Source File
# Begin Source File

SOURCE=.\object_viewer_interface.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\save_options_dlg.h
# End Source File
# Begin Source File

SOURCE=.\scene_rot_dlg.h
# End Source File
# Begin Source File

SOURCE=.\select_movie_size.h
# End Source File
# Begin Source File

SOURCE=.\select_string.h
# End Source File
# Begin Source File

SOURCE=.\set_value_dlg.h
# End Source File
# Begin Source File

SOURCE=.\skeleton_scale_dlg.h
# End Source File
# Begin Source File

SOURCE=.\skippable_message_box.h
# End Source File
# Begin Source File

SOURCE=.\slot_dlg.h
# End Source File
# Begin Source File

SOURCE=.\snapshot_tool_dlg.h
# End Source File
# Begin Source File

SOURCE=.\sound_system.h
# End Source File
# Begin Source File

SOURCE=.\std_afx.h
# End Source File
# Begin Source File

SOURCE=.\tune_mrm_dlg.h
# End Source File
# Begin Source File

SOURCE=.\water_pool_editor.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00023.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00024.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00025.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00026.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00027.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\light_at.bmp
# End Source File
# Begin Source File

SOURCE=.\nevraxpill.ico
# End Source File
# Begin Source File

SOURCE=.\res\object_viewer.rc2
# End Source File
# Begin Source File

SOURCE=.\particle.bmp
# End Source File
# Begin Source File

SOURCE=.\toolbar1.bmp
# End Source File
# End Group
# Begin Group "particles editor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\attrib_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\attrib_dlg.h
# End Source File
# Begin Source File

SOURCE=.\attrib_list_box.cpp
# End Source File
# Begin Source File

SOURCE=.\attrib_list_box.h
# End Source File
# Begin Source File

SOURCE=.\auto_lod_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\auto_lod_dlg.h
# End Source File
# Begin Source File

SOURCE=.\basis_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\basis_edit.h
# End Source File
# Begin Source File

SOURCE=.\bin_op_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\bin_op_dlg.h
# End Source File
# Begin Source File

SOURCE=.\bound_checker.h
# End Source File
# Begin Source File

SOURCE=.\collision_zone_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\collision_zone_dlg.h
# End Source File
# Begin Source File

SOURCE=.\color_button.cpp
# End Source File
# Begin Source File

SOURCE=.\color_button.h
# End Source File
# Begin Source File

SOURCE=.\color_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\color_edit.h
# End Source File
# Begin Source File

SOURCE=.\constraint_mesh_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\constraint_mesh_dlg.h
# End Source File
# Begin Source File

SOURCE=.\constraint_mesh_global_tex_anim_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\constraint_mesh_global_tex_anim_dlg.h
# End Source File
# Begin Source File

SOURCE=.\constraint_mesh_tex_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\constraint_mesh_tex_dlg.h
# End Source File
# Begin Source File

SOURCE=.\curve_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\curve_edit.h
# End Source File
# Begin Source File

SOURCE=.\dialog_stack.h
# End Source File
# Begin Source File

SOURCE=.\direction_attr.cpp
# End Source File
# Begin Source File

SOURCE=.\direction_attr.h
# End Source File
# Begin Source File

SOURCE=.\direction_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\direction_edit.h
# End Source File
# Begin Source File

SOURCE=.\dup_ps.cpp
# End Source File
# Begin Source File

SOURCE=.\dup_ps.h
# End Source File
# Begin Source File

SOURCE=.\edit_attrib_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_follow_path.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_follow_path.h
# End Source File
# Begin Source File

SOURCE=.\edit_morph_mesh_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_morph_mesh_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_ps_light.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_ps_light.h
# End Source File
# Begin Source File

SOURCE=.\edit_ps_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_ps_sound.h
# End Source File
# Begin Source File

SOURCE=.\edit_spinner.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_spinner.h
# End Source File
# Begin Source File

SOURCE=.\edit_user_param.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_user_param.h
# End Source File
# Begin Source File

SOURCE=.\editable_range.cpp
# End Source File
# Begin Source File

SOURCE=.\editable_range.h
# End Source File
# Begin Source File

SOURCE=.\emitter_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\emitter_dlg.h
# End Source File
# Begin Source File

SOURCE=.\lb_extern_id_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\lb_extern_id_dlg.h
# End Source File
# Begin Source File

SOURCE=.\located_bindable_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\located_bindable_dialog.h
# End Source File
# Begin Source File

SOURCE=.\located_properties.cpp
# End Source File
# Begin Source File

SOURCE=.\located_properties.h
# End Source File
# Begin Source File

SOURCE=.\located_target_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\located_target_dlg.h
# End Source File
# Begin Source File

SOURCE=.\mesh_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mesh_dlg.h
# End Source File
# Begin Source File

SOURCE=.\multi_tex_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\multi_tex_dlg.h
# End Source File
# Begin Source File

SOURCE=.\particle_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\particle_dlg.h
# End Source File
# Begin Source File

SOURCE=.\particle_system_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\particle_system_edit.h
# End Source File
# Begin Source File

SOURCE=.\particle_tree_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\particle_tree_ctrl.h
# End Source File
# Begin Source File

SOURCE=.\particle_workspace.cpp
# End Source File
# Begin Source File

SOURCE=.\particle_workspace.h
# End Source File
# Begin Source File

SOURCE=.\pick_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\pick_sound.h
# End Source File
# Begin Source File

SOURCE=.\popup_notify.h
# End Source File
# Begin Source File

SOURCE=.\precomputed_rotations_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\precomputed_rotations_dlg.h
# End Source File
# Begin Source File

SOURCE=.\ps_global_color_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ps_global_color_dlg.h
# End Source File
# Begin Source File

SOURCE=.\ps_initial_pos.cpp
# End Source File
# Begin Source File

SOURCE=.\ps_initial_pos.h
# End Source File
# Begin Source File

SOURCE=.\ps_mover_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ps_mover_dlg.h
# End Source File
# Begin Source File

SOURCE=.\ps_wrapper.h
# End Source File
# Begin Source File

SOURCE=.\range_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\range_manager.h
# End Source File
# Begin Source File

SOURCE=.\range_selector.cpp
# End Source File
# Begin Source File

SOURCE=.\range_selector.h
# End Source File
# Begin Source File

SOURCE=.\ribbon_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ribbon_dlg.h
# End Source File
# Begin Source File

SOURCE=.\scheme_bank_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\scheme_bank_dlg.h
# End Source File
# Begin Source File

SOURCE=.\scheme_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\scheme_manager.h
# End Source File
# Begin Source File

SOURCE=.\start_stop_particle_system.cpp
# End Source File
# Begin Source File

SOURCE=.\start_stop_particle_system.h
# End Source File
# Begin Source File

SOURCE=.\tail_particle_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\tail_particle_dlg.h
# End Source File
# Begin Source File

SOURCE=.\texture_anim_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\texture_anim_dlg.h
# End Source File
# Begin Source File

SOURCE=.\texture_chooser.cpp
# End Source File
# Begin Source File

SOURCE=.\texture_chooser.h
# End Source File
# Begin Source File

SOURCE=.\value_blender_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\value_blender_dlg.h
# End Source File
# Begin Source File

SOURCE=.\value_from_emitter_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\value_from_emitter_dlg.h
# End Source File
# Begin Source File

SOURCE=.\value_gradient_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\value_gradient_dlg.h
# End Source File
# End Group
# Begin Group "vegetable editor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\vegetable_apperance_page.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_apperance_page.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_copy_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_copy_dlg.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_density_page.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_density_page.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_dlg.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_edit_tools.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_edit_tools.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_list_box.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_list_box.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_list_color.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_list_color.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_noise_value_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_noise_value_dlg.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_refresh.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_refresh.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_rotate_page.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_rotate_page.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_scale_page.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_scale_page.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_select_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_select_dlg.h
# End Source File
# Begin Source File

SOURCE=.\vegetable_wind_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\vegetable_wind_dlg.h
# End Source File
# End Group
# Begin Group "sound editor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound_anim_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sound_anim_dlg.h
# End Source File
# Begin Source File

SOURCE=.\sound_anim_view.cpp
# End Source File
# Begin Source File

SOURCE=.\sound_anim_view.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
