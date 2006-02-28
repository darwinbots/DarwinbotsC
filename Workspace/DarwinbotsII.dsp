# Microsoft Developer Studio Project File - Name="DarwinbotsII" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DarwinbotsII - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DarwinbotsII.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DarwinbotsII.mak" CFG="DarwinbotsII - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DarwinbotsII - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "DarwinbotsII - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DarwinbotsII - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib FOXD-1.4.lib glut32.lib opengl32.lib glu32.lib wsock32.lib stlport_vc6.lib /nologo /map /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "DarwinbotsII - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib FOXD-1.4.lib glut32.lib opengl32.lib glu32.lib wsock32.lib stlport_vc6.lib /nologo /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "DarwinbotsII - Win32 Release"
# Name "DarwinbotsII - Win32 Debug"
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Group "Robot"

# PROP Default_Filter ""
# Begin Group "DNA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\Engine\Block.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Block.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\DNA_Execution.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\DNA_Execution.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\DNA_Parse.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\DNAClass.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\DNAClass.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Mutations.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\Darwinbots\Engine\ObjectPrimitive.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\ObjectPrimitive.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Robot.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\RobotPhysics.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Robots.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\RobotSysvars.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Senses.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Vegs.cpp
# End Source File
# End Group
# Begin Group "Master Engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\Engine\Engine.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Engine.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\EngineThread.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\EngineThread.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\HardDriveRoutines.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\HardDriveRoutines.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\SimOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\SimOptions.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Specie.h
# End Source File
# End Group
# Begin Group "Globals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\Engine\Globals.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Globals.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Common\Math2D.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Common\Math3D.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Common\Random.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Common\Random.h
# End Source File
# End Group
# Begin Group "Shots"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\Engine\Shot.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Shots.h
# End Source File
# End Group
# Begin Group "Ties"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\Engine\Tie.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Ties.cpp
# End Source File
# End Group
# End Group
# Begin Group "GUI"

# PROP Default_Filter ""
# Begin Group "Options Form"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIfunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIInternetOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIMutations.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIPhysicsOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIRecording.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIRestartLeague.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUISpecies.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIVeggy.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIBotDebug.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIBotDebug.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIGeneral.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUIGLWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUImain.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\GUImain.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GUI\ViewerControls.cpp
# End Source File
# End Group
# Begin Group "GFX"

# PROP Default_Filter ""
# Begin Group "Icons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Darwinbots\GFX\Icons\icons.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GFX\Icons\icons.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Darwinbots\GFX\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GFX\Camera.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GFX\DrawWorld.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GFX\DrawWorld.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GFX\Primitives.cpp
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\GFX\Primitives.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Darwinbots\GFX\DisplayList.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\Engine\Mutations.h
# End Source File
# Begin Source File

SOURCE=..\Darwinbots\TempMain.cpp
# End Source File
# End Target
# End Project
