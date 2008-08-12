# Microsoft Developer Studio Project File - Name="sound" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sound - Win32 DebugInstrument
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sound.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sound.mak" CFG="sound - Win32 DebugInstrument"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sound - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sound - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "sound - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "sound - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE "sound - Win32 DebugInstrument" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/Release/sound"
# PROP Intermediate_Dir "../obj/Release/sound"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../include" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /Yu"stdsound.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlsound_r.lib"

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/Debug/sound"
# PROP Intermediate_Dir "../obj/Debug/sound"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Z7 /Od /I "../include" /D "__STL_DEBUG" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /YX"stdsound.h" /FD /GZ /Zm400 /c
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlsound_d.lib"

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/ReleaseDebug/sound"
# PROP Intermediate_Dir "../obj/ReleaseDebug/sound"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../include" /D "NL_RELEASE_DEBUG" /D "_LIB" /D "LIBXML_STATIC" /D "WIN32" /D "NDEBUG" /D "_MBCS" /Yu"stdsound.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlsound_rd.lib"

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugFast/sound"
# PROP Intermediate_Dir "../obj/DebugFast/sound"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_LIB" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /Yu"stdsound.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nlsound_df.lib"

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sound___Win32_DebugInstrument"
# PROP BASE Intermediate_Dir "sound___Win32_DebugInstrument"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugInstrument/sound"
# PROP Intermediate_Dir "../obj/DebugInstrument/sound"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_LIB" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /Yu"stdsound.h" /FD /GZ /c
# SUBTRACT BASE CPP /Gf /Gy /Fr
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_LIB" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /D "NL_DEBUG_INSTRUMENT" /Yu"stdsound.h" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../lib/nlsound_df.lib"
# ADD LIB32 /nologo /out:"../lib/nlsound_di.lib"

!ENDIF 

# Begin Target

# Name "sound - Win32 Release"
# Name "sound - Win32 Debug"
# Name "sound - Win32 ReleaseDebug"
# Name "sound - Win32 DebugFast"
# Name "sound - Win32 DebugInstrument"
# Begin Group "User"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\nel\sound\u_audio_mixer.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\sound\u_env_sound.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\sound\u_listener.h
# End Source File
# Begin Source File

SOURCE=..\include\nel\sound\u_source.h
# End Source File
# End Group
# Begin Group "UserImp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\audio_mixer_user.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\audio_mixer_user.h
# End Source File
# Begin Source File

SOURCE=.\sound\env_sound_user.cpp

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sound\env_sound_user.h

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sound\listener_user.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\listener_user.h
# End Source File
# End Group
# Begin Group "Makefile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\Makefile.am
# End Source File
# End Group
# Begin Group "SoundClass"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\background_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\background_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\complex_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\complex_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\context_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\context_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\music_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\music_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\simple_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\simple_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\sound.h
# End Source File
# End Group
# Begin Group "Animation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\sound_anim_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\sound\sound_anim_manager.h
# End Source File
# Begin Source File

SOURCE=.\sound\sound_anim_marker.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\sound\sound_anim_marker.h
# End Source File
# Begin Source File

SOURCE=.\sound\sound_animation.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\sound\sound_animation.h
# End Source File
# End Group
# Begin Group "source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\background_source.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\background_source.h
# End Source File
# Begin Source File

SOURCE=.\sound\complex_source.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\complex_source.h
# End Source File
# Begin Source File

SOURCE=.\sound\music_source.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\music_source.h
# End Source File
# Begin Source File

SOURCE=.\sound\simple_source.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\simple_source.h
# End Source File
# Begin Source File

SOURCE=.\sound\source_common.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\source_common.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sound\ambiant_source.cpp

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sound\ambiant_source.h

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sound\async_file_manager_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\async_file_manager_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\background_sound_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\background_sound_manager.h
# End Source File
# Begin Source File

SOURCE=.\sound\clustered_sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\clustered_sound.h
# End Source File
# Begin Source File

SOURCE=.\sound\env_effect.cpp

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sound\env_effect.h

!IF  "$(CFG)" == "sound - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 ReleaseDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugFast"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "sound - Win32 DebugInstrument"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sound\mixing_track.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\mixing_track.h
# End Source File
# Begin Source File

SOURCE=.\sound\music_sound_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\music_sound_manager.h
# End Source File
# Begin Source File

SOURCE=.\sound\sample_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\sample_bank.h
# End Source File
# Begin Source File

SOURCE=.\sound\sound_bank.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\sound_bank.h
# End Source File
# Begin Source File

SOURCE=.\sound\sound_controller.h
# End Source File
# Begin Source File

SOURCE=.\sound\stdsound.cpp
# ADD CPP /Yc"stdsound.h"
# End Source File
# Begin Source File

SOURCE=.\sound\stdsound.h
# End Source File
# End Target
# End Project
