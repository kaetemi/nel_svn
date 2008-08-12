# Microsoft Developer Studio Project File - Name="misc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=misc - Win32 Generate config file parser
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak" CFG="misc - Win32 Generate config file parser"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "misc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 DebugInstrument" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 Generate config file parser" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "misc - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/Release/misc"
# PROP Intermediate_Dir "../obj/Release/misc"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../include" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /Yu"stdmisc.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlmisc_r.lib"

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/Debug/misc"
# PROP Intermediate_Dir "../obj/Debug/misc"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "LIBXML_STATIC" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Yu"stdmisc.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlmisc_d.lib"

!ELSEIF  "$(CFG)" == "misc - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/ReleaseDebug/misc"
# PROP Intermediate_Dir "../obj/ReleaseDebug/misc"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../include" /D "NL_RELEASE_DEBUG" /D "_LIB" /D "LIBXML_STATIC" /D "WIN32" /D "NDEBUG" /D "_MBCS" /Yu"stdmisc.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlmisc_rd.lib"

!ELSEIF  "$(CFG)" == "misc - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugFast/misc"
# PROP Intermediate_Dir "../obj/DebugFast/misc"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_LIB" /D "NL_DEBUG_FAST" /D "LIBXML_STATIC" /D "_DEBUG" /D "_MBCS" /D "WIN32" /Yu"stdmisc.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlmisc_df.lib"

!ELSEIF  "$(CFG)" == "misc - Win32 DebugInstrument"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "misc___Win32_DebugInstrument"
# PROP BASE Intermediate_Dir "misc___Win32_DebugInstrument"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugInstrument/misc"
# PROP Intermediate_Dir "../obj/DebugInstrument/misc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_LIB" /D "NL_DEBUG_FAST" /D "LIBXML_STATIC" /D "_DEBUG" /D "_MBCS" /D "WIN32" /Yu"stdmisc.h" /FD /GZ /c
# SUBTRACT BASE CPP /Gf /Gy /Fr
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "NL_DEBUG_FAST" /D "LIBXML_STATIC" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "NL_DEBUG_INSTRUMENT" /Yu"stdmisc.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/nlmisc_df.lib"
# ADD LIB32 /nologo /out:"../lib/nlmisc_di.lib"

!ELSEIF  "$(CFG)" == "misc - Win32 Generate config file parser"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "misc___Win32_Generate_config_file_parser"
# PROP BASE Intermediate_Dir "misc___Win32_Generate_config_file_parser"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/Debug/misc"
# PROP Intermediate_Dir "../obj/Debug/misc"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "LIBXML_STATIC" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Yu"stdmisc.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "LIBXML_STATIC" /D "__STL_DEBUG" /D "WIN32" /D "_DEBUG" /D "_MBCS" /Yu"stdmisc.h" /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/nlmisc_d.lib"
# ADD LIB32 /nologo /out:"../lib/nlmisc_d.lib"

!ENDIF 

# Begin Target

# Name "misc - Win32 Release"
# Name "misc - Win32 Debug"
# Name "misc - Win32 ReleaseDebug"
# Name "misc - Win32 DebugFast"
# Name "misc - Win32 DebugInstrument"
# Name "misc - Win32 Generate config file parser"
# Begin Group "Stream"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\big_file.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\big_file.h
# End Source File
# Begin Source File

SOURCE=.\misc\bit_mem_stream.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\bit_mem_stream.h
# End Source File
# Begin Source File

SOURCE=.\misc\class_registry.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\class_registry.h
# End Source File
# Begin Source File

SOURCE=.\misc\file.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\file.h
# End Source File
# Begin Source File

SOURCE=.\misc\i_xml.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\i_xml.h
# End Source File
# Begin Source File

SOURCE=.\misc\mem_stream.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\mem_stream.h
# End Source File
# Begin Source File

SOURCE=.\misc\o_xml.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\o_xml.h
# End Source File
# Begin Source File

SOURCE=.\misc\stream.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\stream.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\stream_inline.h
# End Source File
# Begin Source File

SOURCE=.\misc\xml_pack.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\xml_pack.h
# End Source File
# End Group
# Begin Group "ConfigFile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\config_file\cf_gramatical.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\misc\config_file\cf_gramatical.h
# End Source File
# Begin Source File

SOURCE=.\misc\config_file\cf_gramatical.yxx

!IF  "$(CFG)" == "misc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 DebugInstrument"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 Generate config file parser"

# PROP Intermediate_Dir "../obj/Debug/misc"
# Begin Custom Build - Building config file parser grammar from $(InputPath)
InputDir=.\misc\config_file
InputPath=.\misc\config_file\cf_gramatical.yxx
InputName=cf_gramatical

BuildCmds= \
	"c:\program files\GnuWin32\bin\bison" -o$(InputDir)/$(InputName).cpp --defines=$(InputDir)/$(InputName).h -pcf $(InputPath)

"$(InputDir)/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)/$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\misc\config_file\cf_lexical.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\misc\config_file\cf_lexical.lxx

!IF  "$(CFG)" == "misc - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 DebugInstrument"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "misc - Win32 Generate config file parser"

# Begin Custom Build - Building config file lexer from $(InputPath)
InputDir=.\misc\config_file
InputPath=.\misc\config_file\cf_lexical.lxx
InputName=cf_lexical

"$(InputDir)/$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -BL -o$(InputDir)/$(InputName).cpp $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\misc\config_file\config_file.cpp
# SUBTRACT CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\config_file.h
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ""
# Begin Group "direct input"

# PROP Default_Filter ""
# Begin Group "direct input devices"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\di_game_device.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\di_game_device.h
# End Source File
# Begin Source File

SOURCE=.\misc\di_keyboard_device.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\di_keyboard_device.h
# End Source File
# Begin Source File

SOURCE=.\misc\di_mouse_device.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\di_mouse_device.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\misc\di_event_emitter.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\di_event_emitter.h
# End Source File
# End Group
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\win_event_emitter.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\win_event_emitter.h
# End Source File
# End Group
# Begin Group "devices"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\nel\misc\game_device.h
# End Source File
# Begin Source File

SOURCE=.\misc\input_device.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\input_device.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\input_device_manager.h
# End Source File
# Begin Source File

SOURCE=.\misc\input_device_server.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\input_device_server.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\keyboard_device.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\mouse_device.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\misc\event_emitter.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\event_emitter.h
# End Source File
# Begin Source File

SOURCE=.\misc\event_emitter_multi.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\event_emitter_multi.h
# End Source File
# Begin Source File

SOURCE=.\misc\event_listener.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\event_listener.h
# End Source File
# Begin Source File

SOURCE=.\misc\event_server.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\event_server.h
# End Source File
# Begin Source File

SOURCE=.\misc\events.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\events.h
# End Source File
# Begin Source File

SOURCE=.\misc\game_device_events.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\game_device_events.h
# End Source File
# Begin Source File

SOURCE=.\misc\mouse_smoother.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\mouse_smoother.h
# End Source File
# End Group
# Begin Group "Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\nel\misc\array_2d.h
# End Source File
# Begin Source File

SOURCE=.\misc\block_memory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\block_memory.h
# End Source File
# Begin Source File

SOURCE=.\misc\buf_fifo.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\buf_fifo.h
# End Source File
# Begin Source File

SOURCE=.\misc\contiguous_block_allocator.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\contiguous_block_allocator.h
# End Source File
# Begin Source File

SOURCE=.\misc\fast_mem.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\fast_mem.h
# End Source File
# Begin Source File

SOURCE=.\misc\fixed_size_allocator.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\fixed_size_allocator.h
# End Source File
# Begin Source File

SOURCE=.\misc\heap_memory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\heap_memory.h
# End Source File
# Begin Source File

SOURCE=.\misc\object_arena_allocator.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\object_arena_allocator.h
# End Source File
# Begin Source File

SOURCE=.\misc\object_vector.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\object_vector.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\pool_memory.h
# End Source File
# Begin Source File

SOURCE=.\misc\shared_memory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\shared_memory.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\static_map.h
# End Source File
# Begin Source File

SOURCE=.\misc\stl_block_allocator.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\stl_block_allocator.h
# End Source File
# Begin Source File

SOURCE=.\misc\stl_block_list.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\stl_block_list.h
# End Source File
# Begin Source File

SOURCE=.\misc\tds.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\tds.h
# End Source File
# End Group
# Begin Group "Makefile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\Makefile.am
# End Source File
# End Group
# Begin Group "Displayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\displayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\displayer.h
# End Source File
# Begin Source File

SOURCE=.\misc\gtk_displayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\gtk_displayer.h
# End Source File
# Begin Source File

SOURCE=.\misc\log.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\log.h
# End Source File
# Begin Source File

SOURCE=.\misc\mem_displayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\mem_displayer.h
# End Source File
# Begin Source File

SOURCE=.\misc\win_displayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\win_displayer.h
# End Source File
# Begin Source File

SOURCE=.\misc\window_displayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\window_displayer.h
# End Source File
# End Group
# Begin Group "Strings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\diff_tool.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\diff_tool.h
# End Source File
# Begin Source File

SOURCE=.\misc\i18n.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\i18n.h
# End Source File
# Begin Source File

SOURCE=.\misc\sstring.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\sstring.h
# End Source File
# Begin Source File

SOURCE=.\misc\string_common.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\string_common.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\string_conversion.h
# End Source File
# Begin Source File

SOURCE=.\misc\string_id_array.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\string_id_array.h
# End Source File
# Begin Source File

SOURCE=.\misc\string_mapper.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\string_mapper.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\ucstring.h
# End Source File
# Begin Source File

SOURCE=.\misc\unicode.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\words_dictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\words_dictionary.h
# End Source File
# End Group
# Begin Group "Threads"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\co_task.cpp

!IF  "$(CFG)" == "misc - Win32 Release"

# ADD CPP /D _WIN32_WINNT=0x0400

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

!ELSEIF  "$(CFG)" == "misc - Win32 ReleaseDebug"

# ADD CPP /D _WIN32_WINNT=0x0400

!ELSEIF  "$(CFG)" == "misc - Win32 DebugFast"

# ADD CPP /D _WIN32_WINNT=0x0400

!ELSEIF  "$(CFG)" == "misc - Win32 DebugInstrument"

# ADD CPP /D _WIN32_WINNT=0x0400

!ELSEIF  "$(CFG)" == "misc - Win32 Generate config file parser"

# ADD CPP /D _WIN32_WINNT=0x0400

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\co_task.h
# End Source File
# Begin Source File

SOURCE=.\misc\inter_window_msg_queue.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\inter_window_msg_queue.h
# End Source File
# Begin Source File

SOURCE=.\misc\mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\mutex.h
# End Source File
# Begin Source File

SOURCE=.\misc\p_thread.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\p_thread.h
# End Source File
# Begin Source File

SOURCE=.\misc\reader_writer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\reader_writer.h
# End Source File
# Begin Source File

SOURCE=.\misc\task_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\task_manager.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\thread.h
# End Source File
# Begin Source File

SOURCE=.\misc\win_thread.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\win_thread.h
# End Source File
# End Group
# Begin Group "Time"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\hierarchical_timer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\hierarchical_timer.h
# End Source File
# Begin Source File

SOURCE=.\misc\stop_watch.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\stop_watch.h
# End Source File
# Begin Source File

SOURCE=.\misc\time_nl.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\time_nl.h
# End Source File
# End Group
# Begin Group "Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\async_file_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\async_file_manager.h
# End Source File
# Begin Source File

SOURCE=.\misc\md5.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\md5.h
# End Source File
# Begin Source File

SOURCE=.\misc\path.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\path.h
# End Source File
# Begin Source File

SOURCE=.\misc\sha1.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\sha1.h
# End Source File
# End Group
# Begin Group "Identifiers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\eid_translator.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\eid_translator.h
# End Source File
# Begin Source File

SOURCE=.\misc\entity_id.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\entity_id.h
# End Source File
# Begin Source File

SOURCE=.\misc\sheet_id.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\sheet_id.h
# End Source File
# End Group
# Begin Group "Math and 3d"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\aabbox.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\aabbox.h
# End Source File
# Begin Source File

SOURCE=.\misc\bitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\bitmap.h
# End Source File
# Begin Source File

SOURCE=.\misc\bitmap_png.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\bsphere.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\bsphere.h
# End Source File
# Begin Source File

SOURCE=.\misc\check_fpu.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\check_fpu.h
# End Source File
# Begin Source File

SOURCE=.\misc\eval_num_expr.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\eval_num_expr.h
# End Source File
# Begin Source File

SOURCE=.\misc\fast_floor.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\fast_floor.h
# End Source File
# Begin Source File

SOURCE=.\misc\geom_ext.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\geom_ext.h
# End Source File
# Begin Source File

SOURCE=.\misc\grid_traversal.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\grid_traversal.h
# End Source File
# Begin Source File

SOURCE=.\misc\line.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\line.h
# End Source File
# Begin Source File

SOURCE=.\misc\matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\matrix.h
# End Source File
# Begin Source File

SOURCE=.\misc\noise_value.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\noise_value.h
# End Source File
# Begin Source File

SOURCE=.\misc\plane.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\plane.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\plane_inline.h
# End Source File
# Begin Source File

SOURCE=.\misc\polygon.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\polygon.h
# End Source File
# Begin Source File

SOURCE=.\misc\quad.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\quad.h
# End Source File
# Begin Source File

SOURCE=.\misc\quat.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\quat.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\random.h
# End Source File
# Begin Source File

SOURCE=.\misc\rect.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\rect.h
# End Source File
# Begin Source File

SOURCE=.\misc\rgba.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\rgba.h
# End Source File
# Begin Source File

SOURCE=.\misc\triangle.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\triangle.h
# End Source File
# Begin Source File

SOURCE=.\misc\uv.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\uv.h
# End Source File
# Begin Source File

SOURCE=.\misc\value_smoother.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\value_smoother.h
# End Source File
# Begin Source File

SOURCE=.\misc\vector.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vector.h
# End Source File
# Begin Source File

SOURCE=.\misc\vector_2d.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vector_2d.h
# End Source File
# Begin Source File

SOURCE=.\misc\vector_2f.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vector_2f.h
# End Source File
# Begin Source File

SOURCE=.\misc\vector_h.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vector_h.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vector_inline.h
# End Source File
# Begin Source File

SOURCE=.\misc\vectord.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vectord.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\vectord_inline.h
# End Source File
# End Group
# Begin Group "Admin and info"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\app_context.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\app_context.h
# End Source File
# Begin Source File

SOURCE=.\misc\command.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\command.h
# End Source File
# Begin Source File

SOURCE=.\misc\cpu_time_stat.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\cpu_time_stat.h
# End Source File
# Begin Source File

SOURCE=.\misc\progress_callback.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\progress_callback.h
# End Source File
# Begin Source File

SOURCE=.\misc\report.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\report.h
# End Source File
# Begin Source File

SOURCE=.\misc\system_info.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\system_info.h
# End Source File
# Begin Source File

SOURCE=.\misc\variable.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\variable.h
# End Source File
# End Group
# Begin Group "C++ extensions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\bit_set.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\bit_set.h
# End Source File
# Begin Source File

SOURCE=.\misc\class_id.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\class_id.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\enum_bitset.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\historic.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\mutable_container.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\resource_ptr.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\resource_ptr_inline.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\singleton.h
# End Source File
# Begin Source File

SOURCE=.\misc\smart_ptr.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\smart_ptr.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\smart_ptr_inline.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\speaker_listener.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\twin_map.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\algo.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\algo.h
# End Source File
# Begin Source File

SOURCE=.\misc\common.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\common.h
# End Source File
# Begin Source File

SOURCE=.\misc\debug.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\debug.h
# End Source File
# Begin Source File

SOURCE=.\misc\dynloadlib.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\dynloadlib.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\factory.h
# End Source File
# Begin Source File

SOURCE=.\misc\stdmisc.cpp
# ADD CPP /Yc"stdmisc.h"
# End Source File
# Begin Source File

SOURCE=.\misc\stdmisc.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\timeout_assertion_thread.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\traits_nl.h
# End Source File
# End Group
# Begin Group "win32 util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\dummy_window.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\dummy_window.h
# End Source File
# Begin Source File

SOURCE=.\misc\win32_util.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\misc\win32_util.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\nel\misc\types_nl.h
# End Source File
# End Target
# End Project
