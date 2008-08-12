# Microsoft Developer Studio Project File - Name="logic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=logic - Win32 DebugFast
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "logic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "logic.mak" CFG="logic - Win32 DebugFast"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "logic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "logic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "logic - Win32 DebugFast" (based on "Win32 (x86) Static Library")
!MESSAGE "logic - Win32 ReleaseDebug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "logic - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/Release/logic"
# PROP Intermediate_Dir "../obj/Release/logic"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../include" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nllogic_r.lib"

!ELSEIF  "$(CFG)" == "logic - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/Debug/logic"
# PROP Intermediate_Dir "../obj/Debug/logic"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "../include" /D "_LIB" /D "__STL_DEBUG" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "LIBXML_STATIC" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nllogic_d.lib"

!ELSEIF  "$(CFG)" == "logic - Win32 DebugFast"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj/DebugFast/logic"
# PROP Intermediate_Dir "../obj/DebugFast/logic"
# PROP Target_Dir ""
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /Ob1 /I "../include" /D "_LIB" /D "_DEBUG" /D "NL_DEBUG_FAST" /D "_MBCS" /D "LIBXML_STATIC" /D "WIN32" /FD /GZ /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nllogic_df.lib"

!ELSEIF  "$(CFG)" == "logic - Win32 ReleaseDebug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj/ReleaseDebug/logic"
# PROP Intermediate_Dir "../obj/ReleaseDebug/logic"
# PROP Target_Dir ""
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "../include" /D "_LIB" /D "LIBXML_STATIC" /D "_MBCS" /D "NL_RELEASE_DEBUG" /D "WIN32" /D "NDEBUG" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x40c
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo /out:"../lib/nllogic_rd.lib"

!ENDIF 

# Begin Target

# Name "logic - Win32 Release"
# Name "logic - Win32 Debug"
# Name "logic - Win32 DebugFast"
# Name "logic - Win32 ReleaseDebug"
# Begin Group "State"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\logic\logic_state.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\logic\logic_state.h
# End Source File
# End Group
# Begin Group "Variable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\logic\logic_variable.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\logic\logic_variable.h
# End Source File
# End Group
# Begin Group "Event"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\logic\logic_event.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\logic\logic_event.h
# End Source File
# End Group
# Begin Group "Condition"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\logic\logic_condition.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\logic\logic_condition.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\logic\logic_state_machine.cpp
# End Source File
# Begin Source File

SOURCE=..\include\nel\logic\logic_state_machine.h
# End Source File
# End Target
# End Project
