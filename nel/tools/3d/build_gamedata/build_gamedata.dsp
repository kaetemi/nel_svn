# Microsoft Developer Studio Project File - Name="build_gamedata" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=build_gamedata - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "build_gamedata.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "build_gamedata.mak" CFG="build_gamedata - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "build_gamedata - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "build_gamedata - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "build_gamedata - Win32 Release"

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

!ELSEIF  "$(CFG)" == "build_gamedata - Win32 Debug"

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

!ENDIF 

# Begin Target

# Name "build_gamedata - Win32 Release"
# Name "build_gamedata - Win32 Debug"
# Begin Group "Doc Files"

# PROP Default_Filter "*.txt"
# Begin Source File

SOURCE=".\Howto export.txt"
# End Source File
# End Group
# Begin Group "Config Files"

# PROP Default_Filter "*.cfg"
# Begin Source File

SOURCE=.\cfg\config.cfg
# End Source File
# Begin Source File

SOURCE=.\cfg\directories.cfg
# End Source File
# Begin Source File

SOURCE=.\cfg\panoply.cfg
# End Source File
# Begin Source File

SOURCE=.\cfg\properties_draft.cfg
# End Source File
# Begin Source File

SOURCE=.\cfg\properties_final.cfg
# End Source File
# Begin Source File

SOURCE=.\cfg\site.cfg
# End Source File
# End Group
# Begin Group "Skel Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\skel\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\skel\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\skel\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\skel\log.log
# End Source File
# Begin Source File

SOURCE=.\processes\skel\maxscript\skel_export.ms
# End Source File
# End Group
# Begin Group "Swt Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\swt\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\swt\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\swt\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\swt\log.log
# End Source File
# Begin Source File

SOURCE=.\processes\swt\maxscript\swt_export.ms
# End Source File
# End Group
# Begin Group "Shape Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\shape\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\shape\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\shape\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\shape\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\shape\maxscript\shape_export.ms
# End Source File
# End Group
# Begin Group "Map Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\map\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\map\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\map\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\map\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\map\log.log
# End Source File
# End Group
# Begin Group "Zone Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\zone\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\zone\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\zone\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone\log.log
# End Source File
# Begin Source File

SOURCE=.\processes\zone\maxscript\zone_export.ms
# End Source File
# End Group
# Begin Group "Smallbank Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\smallbank\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\smallbank\log.log
# End Source File
# End Group
# Begin Group "Farbank Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\farbank\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\farbank\log.log
# End Source File
# End Group
# Begin Group "Anim Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\anim\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\maxscript\anim_export.ms
# End Source File
# Begin Source File

SOURCE=.\processes\anim\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\anim\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\anim\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\anim\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\anim\log.log
# End Source File
# End Group
# Begin Group "Ps Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\ps\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ps\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ps\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ps\log.log
# End Source File
# End Group
# Begin Group "Ig Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\ig\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ig\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ig\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig\maxscript\ig_export.ms
# End Source File
# Begin Source File

SOURCE=.\processes\ig\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ig\log.log
# End Source File
# End Group
# Begin Group "Tiles Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\tiles\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\tiles\log.log
# End Source File
# End Group
# Begin Group "Displace Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\displace\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\displace\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\displace\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\displace\log.log
# End Source File
# End Group
# Begin Group "Interface Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\interface\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\interface\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\interface\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\interface\log.log
# End Source File
# End Group
# Begin Group "Command Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\_idle.bat
# End Source File
# Begin Source File

SOURCE=.\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\sh\clean.sh
# End Source File
# Begin Source File

SOURCE=.\client_clean.bat
# End Source File
# Begin Source File

SOURCE=.\sh\client_clean.sh
# End Source File
# Begin Source File

SOURCE=.\client_setup.bat
# End Source File
# Begin Source File

SOURCE=.\sh\client_setup.sh
# End Source File
# Begin Source File

SOURCE=.\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\log.log
# End Source File
# Begin Source File

SOURCE=.\set_title.bat
# End Source File
# Begin Source File

SOURCE=.\sh\setup.sh
# End Source File
# Begin Source File

SOURCE=.\update_local_tools.bat
# End Source File
# Begin Source File

SOURCE=.\update_tools.bat
# End Source File
# End Group
# Begin Group "VegetSet Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\vegetset\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\vegetset\sh\install.sh
# End Source File
# End Group
# Begin Group "Rbank Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\rbank\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\sh\clean.sh
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\cfg\config.cfg
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\maxscript\rbank_export.ms
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\cfg\template_draft.cfg
# End Source File
# Begin Source File

SOURCE=.\processes\rbank\cfg\template_final.cfg
# End Source File
# End Group
# Begin Group "Veget Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\veget\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\veget\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\veget\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\veget\maxscript\veget_export.ms
# End Source File
# End Group
# Begin Group "Ig_light"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\ig_light\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ig_light\sh\install.sh
# End Source File
# End Group
# Begin Group "Ligo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\ligo\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\ligo\maxscript\nel_ligo_export.ms
# End Source File
# End Group
# Begin Group "Pacs_prim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\pacs_prim\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\pacs_prim\maxscript\pacs_prim_export.ms
# End Source File
# End Group
# Begin Group "CLodBank Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\clodbank\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\maxscript\clod_export.ms
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\sh\install.sh
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\cfg\local_path.cfg
# End Source File
# Begin Source File

SOURCE=.\processes\clodbank\process_doc.txt
# End Source File
# End Group
# Begin Group "Zone_light"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\zone_light\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\sh\build.sh
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\zone_light\sh\install.sh
# End Source File
# End Group
# Begin Group "Font"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\processes\font\0_setup.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\1_clean.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\2_export.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\3_build.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\4_install.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\sh\export.sh
# End Source File
# Begin Source File

SOURCE=.\processes\font\export_build_all_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\export_build_data.bat
# End Source File
# Begin Source File

SOURCE=.\processes\font\sh\install.sh
# End Source File
# End Group
# End Target
# End Project
