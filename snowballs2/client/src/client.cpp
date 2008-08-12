/** \file client.cpp
 * Snowballs main file
 *
 * $Id: client.cpp,v 1.61 2004/07/29 09:06:07 lecroart Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

//
// Includes
// 

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#ifndef SNOWBALLS_CONFIG
#define SNOWBALLS_CONFIG ""
#endif // SNOWBALLS_CONFIG

#include <nel/misc/types_nl.h>

#ifdef NL_OS_WINDOWS
#	include <windows.h>
#	undef min
#	undef max
#endif

#include <time.h>
#include <string>
#include <vector>

#include <nel/misc/config_file.h>
#include <nel/misc/path.h>
#include <nel/misc/vectord.h>
#include <nel/misc/time_nl.h>
#include <nel/misc/command.h>
#include <nel/misc/file.h>

#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_text_context.h>
#include <nel/3d/u_material.h>
#include <nel/3d/u_texture.h>

#include <nel/net/login_client.h>

#include "commands.h"
#include "landscape.h"
#include "entities.h"
#include "camera.h"
#include "pacs.h"
#include "animation.h"
#include "network.h"
#ifdef NL_OS_WINDOWS
// Sound currently disabled under Linux
#include "sound.h"
#endif
#include "interface.h"
#include "lens_flare.h"
#include "mouse_listener.h"
#include "radar.h"
#include "compass.h"
#include "graph.h"

//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NL3D;
using namespace NLNET;

//
// Globals
//

// This class contains all variables that are in the client.cfg
CConfigFile			 ConfigFile;

// The 3d driver
UDriver				*Driver = NULL;

// This is the main scene
UScene				*Scene = NULL;

// This class is used to handle mouse/keyboard input for camera movement
C3dMouseListener	*MouseListener = NULL;

// This variable is used to display text on the screen
UTextContext		*TextContext = NULL;

// The previous and current frame dates
TTime				 LastTime, NewTime;

// true if you want to exit the main loop
static bool			 NeedExit = false;

// true if the commands (chat) interface must be display. This variable is set automatically with the config file
static bool			 ShowCommands;

// if true, the mouse can't go out the client window (work only on Windows)
static bool			 CaptureState = false;

//
// Prototypes
//

//void startLoginInterface ();
//void updateLoginInterface ();

void initLoadingState ();
void displayLoadingState (char *state);

//
// Functions
//

//
// Main
//

#ifdef NL_OS_WINDOWS
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdline, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{
	nlinfo ("Starting Snowballs !");

	// Look the command line to see if we have a cookie and a addr
	
	string cookie, fsaddr;

#ifdef NL_OS_WINDOWS

	// extract the 2 first param (argv[1] and argv[2]) it must be cookie and addr

	string cmd = cmdline;
	int pos1 = cmd.find_first_not_of (' ');
	int pos2;
	if (pos1 != string::npos)
	{
		pos2 = cmd.find (' ', pos1);
		if(pos2 != string::npos)
		{
			cookie = cmd.substr (pos1, pos2-pos1);

			pos1 = cmd.find_first_not_of (' ', pos2);
			if (pos1 != string::npos)
			{
				pos2 = cmd.find (' ', pos1);
				if(pos2 == string::npos)
				{
					fsaddr = cmd.substr (pos1);
				}
				else if (pos1 != pos2)
				{
					fsaddr = cmd.substr (pos1, pos2-pos1);
				}
			}
		}
	}

#else

	if (argc>=3)
	{
		cookie = argv[1];
		fsaddr = argv[2];
	}

#endif

	nlinfo ("cookie '%s' addr '%s'", cookie.c_str (), fsaddr.c_str());

	// Load config file
	ConfigFile.load (SNOWBALLS_CONFIG "client.cfg");

	// Set the ShowCommands with the value set in the client config file
	ShowCommands = ConfigFile.getVar("ShowCommands").asInt () == 1;

	// Add different path for automatic file lookup
	CPath::addSearchPath (ConfigFile.getVar("DataPath").asString (), true, false);

	// Create a driver
	Driver = UDriver::createDriver();

	// Create the window with config file values
	Driver->setDisplay (UDriver::CMode(ConfigFile.getVar("ScreenWidth").asInt(), 
									   ConfigFile.getVar("ScreenHeight").asInt(),
									   ConfigFile.getVar("ScreenDepth").asInt(),
									   ConfigFile.getVar("ScreenFull").asInt()==0));

	// Set the cache size for the font manager (in bytes)
	Driver->setFontManagerMaxMemory (2000000);

	// Create a Text context for later text rendering
	TextContext = Driver->createTextContext (CPath::lookup(ConfigFile.getVar("FontName").asString ()));

	// You can't call displayLoadingState() before init the loading state system
	initLoadingState ();

	// Create a scene
	Scene = Driver->createScene(false);

	// Init the landscape using the previously created UScene
	displayLoadingState ("Initialize Landscape");
	initLandscape();

	// Init the pacs
	displayLoadingState ("Initialize PACS");
	initPACS();

	// Init the aiming system
	displayLoadingState ("Initialize Aiming");
	initAiming();

	// Init the user camera
	displayLoadingState ("Initialize Camera");
	initCamera();

	// Create a 3D mouse listener
	displayLoadingState ("Initialize MouseListener");
	MouseListener = new C3dMouseListener();
	MouseListener->addToServer(Driver->EventServer);
	MouseListener->setCamera(Camera);
	MouseListener->setHotSpot (CVectorD (0,0,0));
	MouseListener->setFrustrum (Camera.getFrustum());
	MouseListener->setMatrix (Camera.getMatrix());
	MouseListener->setSpeed(PlayerSpeed);
	initMouseListenerConfig();

	// Init interface
	displayLoadingState ("Initialize Interface");
	initInterface();

	// Init radar
	displayLoadingState ("Initialize Radar");
	initRadar();

	// Init compass
	displayLoadingState ("Initialize Compass");
	initCompass();

	// Init graph
	displayLoadingState ("Initialize Graph");
	initGraph();

#ifdef NL_OS_WINDOWS
	// Init sound control
	displayLoadingState ("Initialize Sound");
	initSound();
#endif

	// Init the command control
	displayLoadingState ("Initialize Commands");
	initCommands ();

	// Init the entities prefs
	displayLoadingState ("Initialize Entities");
	initEntities();

	// Init animation system
	displayLoadingState ("Initialize Animation");
	initAnimation ();

	// Init the lens flare
	displayLoadingState ("Initialize LensFlare");
	initLensFlare ();

	// Init the sky
	displayLoadingState ("Initialize Sky");
	initSky ();

	// Creates the self entity
	displayLoadingState ("Adding your entity");
	srand (time(NULL));
	uint32 id = rand();
	addEntity(id, "Entity"+toString(id), CEntity::Self, CVector(ConfigFile.getVar("StartPoint").asFloat(0),
												 ConfigFile.getVar("StartPoint").asFloat(1),
												 ConfigFile.getVar("StartPoint").asFloat(2)),
										 CVector(ConfigFile.getVar("StartPoint").asFloat(0),
												 ConfigFile.getVar("StartPoint").asFloat(1),
												 ConfigFile.getVar("StartPoint").asFloat(2)));

	if (ConfigFile.getVar("Local").asInt() == 0 && !cookie.empty (), !fsaddr.empty ())
	{
		// Init the network structure
		displayLoadingState ("Initialize Network");
		initNetwork(cookie, fsaddr);
	}

	displayLoadingState ("Ready !!!");

	// Init the mouse so it's trapped by the main window.
	Driver->showCursor(false);
	Driver->setCapture(true);
	Driver->setMousePos(0.5f, 0.5f);

	// Display the first line
	nlinfo ("Welcome to Snowballs !");
	nlinfo ("");
	nlinfo ("Press SHIFT-ESC to exit the game");

	// Get the current time
	NewTime = CTime::getLocalTime();

	while ((!NeedExit) && Driver->isActive())
	{
		animateSky (NewTime-LastTime);

		// Clear all buffers
		Driver->clearBuffers (CRGBA (0, 0, 0));

		// Update the time counters
		LastTime = NewTime;
		NewTime = CTime::getLocalTime();

		// Update all entities positions
		MouseListener->update();
		updateEntities();

		// setup the camera
		// -> first update camera position directly from the mouselistener
		// -> then update stuffs linked to the camera (snow, sky, lens flare etc.)
		MouseListener->updateCamera();
		updateCamera();

		// Update the landscape
		updateLandscape ();

#ifdef NL_OS_WINDOWS
		// Update the sound
		updateSound ();
#endif

		// Set new animation date
		Scene->animate (float(NewTime)/1000);

		// Render the sky scene before the main scene
		updateSky ();

		// Render
		Scene->render ();

		// Render the lens flare
		updateLensFlare ();

		// Update the compass
		updateCompass ();

		// Update the radar
		updateRadar ();

		// Update the radar
		updateGraph ();

		// Update the commands panel
		if (ShowCommands) updateCommands ();

		updateAnimation ();

		// Render the name on top of the other players
		renderEntitiesNames();

		// Update interface
		updateInterface ();

		// Display if we are online or offline
		TextContext->setHotSpot (UTextContext::TopRight);
		TextContext->setColor (isOnline()?CRGBA(0, 255, 0):CRGBA(255, 0, 0));
		TextContext->setFontSize (18);
		TextContext->printfAt (0.99f, 0.99f, isOnline()?"Online":"Offline");

		// Display the frame rate
		uint32 dt = (uint32)(NewTime-LastTime);
		float fps = 1000.0f/(float)dt;
		TextContext->setHotSpot (UTextContext::TopLeft);
		TextContext->setColor (CRGBA(255, 255, 255, 255));
		TextContext->setFontSize (14);
		TextContext->printfAt (0.01f, 0.99f, "%.2ffps %ums", fps, dt);

		// one more frame
		FpsGraph.addValue (1.0f);
		SpfGraph.addOneValue ((float)dt);

		update3dLogo ();

		// Update network messages
		updateNetwork ();

		// Swap 3d buffers
		Driver->swapBuffers ();

		// Pump user input messages
		Driver->EventServer.pump();

		// Manage the keyboard

		if (Driver->AsyncListener.isKeyDown (KeySHIFT) && Driver->AsyncListener.isKeyDown (KeyESCAPE))
		{
			// Shift Escape -> quit
			NeedExit = true;
		}
		else if(Driver->AsyncListener.isKeyPushed (KeyF3))
		{
			// F3 -> toggle wireframe/solid
			UDriver::TPolygonMode p = Driver->getPolygonMode ();
			p = UDriver::TPolygonMode(((int)p+1)%3);
			Driver->setPolygonMode (p);
		}
		else if (Driver->AsyncListener.isKeyPushed (KeyF4))
		{
			// F4 -> clear the command (chat) output
			clearCommands ();
		}
		else if (Driver->AsyncListener.isKeyPushed (KeyF5))
		{
			// F5 -> display/hide the commands (chat) interface
			ShowCommands = !ShowCommands;
		}
		else if (Driver->AsyncListener.isKeyPushed (KeyF6))
		{
			// F6 -> display/hide the radar interface
			RadarState = (RadarState+1)%3;
		}
		else if(Driver->AsyncListener.isKeyDown (KeyF7))
		{
			// F7 -> radar zoom out
			RadarDistance += 50;
		}
		else if(Driver->AsyncListener.isKeyDown(KeyF8))
		{
			// F8 -> radar zoom in
			RadarDistance -= 50;
		}
		else if (Driver->AsyncListener.isKeyPushed (KeyF9))
		{
			// F9 -> release/capture the mouse cursor
			if (!CaptureState)
			{
				Driver->setCapture(false);
				Driver->showCursor(true);
				MouseListener->removeFromServer(Driver->EventServer);
			}
			else
			{
				Driver->setCapture(true);
				Driver->showCursor(false);
				MouseListener->addToServer(Driver->EventServer);
			}
			CaptureState = !CaptureState;
		}
		else if (Driver->AsyncListener.isKeyPushed (KeyF11))
		{
			// F11 -> reset the PACS global position of the self entity (in case of a pacs failure :-\)
			if (Self != NULL)
				resetEntityPosition(Self->Id);
		}
		else if (Driver->AsyncListener.isKeyPushed (KeyF12))
		{
			// F12 -> take a screenshot
			CBitmap btm;
			Driver->getBuffer (btm);
			string filename = CFile::findNewFile ("screenshot.tga");
			COFile fs (filename);
			btm.writeTGA (fs,24,true);
			nlinfo("Screenshot '%s' saved", filename.c_str());
		}
		// Check if the config file was modified by another program
		CConfigFile::checkConfigFiles ();
	}

	// Release the mouse cursor
	if (CaptureState)
	{
		Driver->setCapture(false);
		Driver->showCursor(true);
	}

	// Release all before quit

	releaseLensFlare ();
	releaseRadar ();
	releaseGraph ();
	releaseCompass ();
	releaseInterface ();
	releaseNetwork ();
	releaseAnimation ();
	releaseAiming();
	releasePACS();
	releaseLandscape();
#ifdef NL_OS_WINDOWS	
	releaseSound ();
#endif

	// Release the mouse listener
	MouseListener->removeFromServer(Driver->EventServer);
	delete MouseListener;

	// Release the 3d driver
	delete Driver;

	// Exit
	return EXIT_SUCCESS;
}

//
// Loading state procedure
//

static UTexture *NelLogo = NULL;
static UTexture *NevraxLogo = NULL;
static float	 ScreenWidth, ScreenHeight;

void initLoadingState ()
{
	NelLogo = Driver->createTextureFile ("nel128.tga");
	NevraxLogo = Driver->createTextureFile ("nevrax.tga");
	uint32 width, height;
	Driver->getWindowSize (width, height);
	ScreenWidth = (float) width;
	ScreenHeight = (float) height;
}


void displayLoadingState (char *state)
{
	Driver->clearBuffers (CRGBA(0,0,0));

	Driver->setMatrixMode2D (CFrustum (0.0f, ScreenWidth, 0.0f, ScreenHeight, 0.0f, 1.0f, false));
	Driver->drawBitmap (10, ScreenHeight-128-10, 128, 128, *NelLogo);
	Driver->drawBitmap (ScreenWidth-128-10, ScreenHeight-16-10, 128, 16, *NevraxLogo);

	TextContext->setColor (CRGBA (255, 255, 255));
	TextContext->setHotSpot (UTextContext::MiddleMiddle);

	TextContext->setFontSize (40);
	TextContext->printAt (0.5f, 0.5f, ucstring("Welcome to Snowballs !"));
	
	TextContext->setFontSize (30);
	TextContext->printAt (0.5f, 0.2f, ucstring(state));
	
	TextContext->setHotSpot (UTextContext::BottomRight);
	TextContext->setFontSize (15);
	TextContext->printAt (0.99f, 0.01f, ucstring("(compiled " __DATE__ " " __TIME__ ")"));

	TextContext->setHotSpot (UTextContext::BottomLeft);
	TextContext->setFontSize (15);
#ifdef NL_DEBUG
	string version = "Debug Version";
#elif defined (NL_RELEASE)
	string version = "Release Version";
#else
	string version = "Unknown Version";
#endif
	TextContext->printAt (0.01f, 0.01f, ucstring(version));

	Driver->swapBuffers ();
}



// Command to quit the client
NLMISC_COMMAND(sb_quit,"quit the client","")
{
	// check args, if there s not the right number of parameter, return bad
	if(args.size() != 0) return false;

	log.displayNL("Exit requested");

	NeedExit = true;

	return true;
}
