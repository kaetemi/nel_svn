/** \file client.cpp
 * Snowballs main file
 *
 * $Id$
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
#	define NOMINMAX
#	include <windows.h>
#endif

#include <ctime>
#include <string>
#include <vector>

#include <nel/misc/md5.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/vectord.h>
#include <nel/misc/time_nl.h>
#include <nel/misc/command.h>
#include <nel/misc/config_file.h>

#include <nel/net/login_client.h>

#include <nel/3d/u_scene.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_texture.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_material.h>
#include <nel/3d/u_text_context.h>

#include "pacs.h"
#include "radar.h"
#include "graph.h"
#include "camera.h"
#include "compass.h"
#include "commands.h"
#include "entities.h"
#include "network.h"
#include "landscape.h"
#include "animation.h"
#include "interface.h"
#include "lens_flare.h"
#include "mouse_listener.h"

#ifdef NL_OS_WINDOWS
// Sound currently disabled under Linux
#	include "sound.h"
#endif


#include "component_manager.h"
#include "landscape_component.h"

//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NL3D;
using namespace NLNET;
using namespace SBCLIENT;

// 
// Constants
// 

static const uint8 GameStateLoad = 0, GameStateUnload = 1, GameStateReset = 2, GameStateExit = 3, 
GameStateLogin = 4, GameStateOnline = 5, GameStateOffline = 6;


// Temp
ULandscape *Landscape;

// Component temp test
CComponentManager *ComponentManager;
CLandscapeComponent *LandscapeComponent;

//
// Globals
//

// This class contains all variables that are in the client.cfg
CConfigFile *ConfigFile; // core
// The 3d driver
UDriver *Driver = NULL; // core
// This variable is used to display text on the screen
UTextContext *TextContext = NULL; // core
// This is the main scene
UScene *Scene = NULL; // ingame
// This class is used to handle mouse/keyboard input for camera movement
C3dMouseListener *MouseListener = NULL; // ingame
// Log file
CFileDisplayer FileDisplayer; // main
// The previous and current frame dates
TTime  LastTime, NewTime, DiffTime; // ingame
// true if the commands(chat) interface must be display. This variable is set automatically with the config file
static bool ShowCommands; // ingame
// if true, the mouse can't go out the client window(work only on Windows)
static bool CaptureState = false; // ingame
// Set NextGameState to switch the current game state
static uint8 CurrentGameState = -1, NextGameState = 0; // state
// To know which data has been loaded
static bool LoadedCore = false, LoadedIngame = false, LoadedLogin = false,
LoadedOnline = false, LoadedOffline = false; // state
// Stuff for connection
ucstring Login;
static string FSAddr, Cookie;

//
// Prototypes
//

void initLoadingState();
void releaseLoadingState();
void renderLoadingState(const char *state, bool logo3d);
void updateLoadingState(const char *state, bool network, bool information);
void displayLoadingState(const char *state);
void renderLoadingState(ucstring state, bool logo3d);
void updateLoadingState(ucstring state, bool network, bool information);
void displayLoadingState(ucstring state);
void update3dLogo();
void renderInformation();
void switchGameState();
void loopLogin();
void loopIngame();
void initCore();
void initLogin();
void initIngame();
void initOnline();
void initOffline();
void releaseCore();
void releaseLogin();
void releaseIngame();
void releaseOnline();
void releaseOffline();
void cbGraphicsDriver(CConfigFile::CVar &var);

//
// Functions
//

void switchGameState()
{
SwitchNextGameState:
	nlinfo("Switching to the next game state");
	if (CurrentGameState == NextGameState)
	{
		nlwarning("NextGameState wasn't changed");
	}
	else
	{
		switch(CurrentGameState)
		{
		case GameStateOnline:
			releaseOnline(); // always release online after switch
			break;
		case GameStateOffline:
			releaseOffline(); // always releaes offline after switch
			break;
		}
		switch(NextGameState)
		{
		case GameStateLoad:
			try
			{
				initCore(); // core is required
			}
			catch (NLMISC::Exception e)
			{
#ifdef NL_OS_WINDOWS
				MessageBox(NULL, e.what(), "NeL Exception", MB_OK | MB_ICONSTOP);
#else
				printf(e.what());
#endif
				return; // exit if driver loading failed
			}
			break;
		case GameStateUnload:
			displayLoadingState("Unloading");
			releaseLogin(); // release all
			releaseIngame();
			break;
		case GameStateReset:
			displayLoadingState("Reset");
			releaseLogin(); // release all
			releaseIngame();
			releaseCore();
			break;
		case GameStateExit:
			displayLoadingState("See you later!");
			releaseLogin(); // release all
			releaseIngame();
			releaseCore();
			break;
		case GameStateLogin:
			initCore(); // core is required
			initLogin(); // login is required
			break;
		case GameStateOnline:
			initCore(); // core is required
			releaseLogin(); //login can be released
			initIngame(); // ingame is required
			initOnline(); // connection is required
			break;
		case GameStateOffline:
			initCore(); // core is required
			releaseLogin(); //login can be released
			initIngame(); // ingame is required
			initOffline(); // offline entity required
			break;
		}
	}
	CurrentGameState = NextGameState;
	switch(CurrentGameState)
	{
	case GameStateLoad: // switch to the default state
		NextGameState = GameStateLogin;
		break;
	case GameStateUnload: // test state, switch back to load for default
		NextGameState = GameStateLoad;
		break;
	case GameStateReset: // used to reset everything
		NextGameState = GameStateLoad;
		break;
	case GameStateExit: // exit the loop
		return;
	case GameStateLogin: // loop the login screen
		loopLogin(); // must loop by itself
		break;
	case GameStateOnline: // start offline if not online
		if (!LoadedOnline)
		{
			NextGameState = GameStateOffline;
			break;
		}
	case GameStateOffline: // loop ingame
		loopIngame(); // must loop by itself
		break;
	}	
	goto SwitchNextGameState;
}

void initCore()
{
	if (!LoadedCore)
	{
		LoadedCore = true;
		// Seed the randomizer
		srand(uint(time(0)));
		// Set the ShowCommands with the value set in the client config file
		ShowCommands = ConfigFile->getVar("ShowCommands").asInt() == 1;
		// Add different path for automatic file lookup
		CPath::addSearchPath(ConfigFile->getVar("DataPath").asString(), true, false);
		CPath::remapExtension("dds", "tga", true);
		// Create a driver	
		Driver = UDriver::createDriver(0, ConfigFile->getVar("OpenGL").asInt() == 0);
		// Create the window with config file values
		Driver->setDisplay(UDriver::CMode(ConfigFile->getVar("ScreenWidth").asInt(), 
			ConfigFile->getVar("ScreenHeight").asInt(),
			ConfigFile->getVar("ScreenDepth").asInt(),
			ConfigFile->getVar("ScreenFull").asInt()==0));
		// Set the cache size for the font manager(in bytes)
		Driver->setFontManagerMaxMemory(2097152);
		// Create a Text context for later text rendering
		displayLoadingState("Initialize Text"); 
		TextContext = Driver->createTextContext(CPath::lookup(ConfigFile->getVar("FontName").asString()));
		TextContext->setShaded(true);
		TextContext->setKeep800x600Ratio(false);
		// You can't call displayLoadingState() before init the loading state system
		displayLoadingState("Initialize Loading");
		initLoadingState();
		// Initialize sound for loading screens etc
#ifdef NL_OS_WINDOWS
		displayLoadingState("Initialize Sound");
		initSound();
		playMusic(SBCLIENT_MUSIC_WAIT);
#endif
		// Required for 3d rendering (3d nel logo etc)
		displayLoadingState("Initialize Light");
		initLight();

		ConfigFile->setCallback("OpenGL", cbGraphicsDriver);
	}
}

void initLogin()
{
	if (!LoadedLogin)
	{
		LoadedLogin = true;
	}
}

void initIngame()
{
	if (!LoadedIngame)
	{
		LoadedIngame = true;
#ifdef NL_OS_WINDOWS
		playMusic(SBCLIENT_MUSIC_WAIT);
#endif

		// Create a scene
		Scene = Driver->createScene(false);
		// Init the landscape using the previously created UScene
		displayLoadingState("Initialize Landscape");
		LandscapeComponent = new CLandscapeComponent(
			ComponentManager, std::string("Landscape"), Scene);
		initLandscape();
		// Init the pacs
		displayLoadingState("Initialize PACS ");
		initPACS();
		// Init the aiming system
		displayLoadingState("Initialize Aiming ");
		initAiming();
		// Init the user camera
		displayLoadingState("Initialize Camera ");
		initCamera();
		// Create a 3D mouse listener
		displayLoadingState("Initialize MouseListener ");
		MouseListener = new C3dMouseListener();
		MouseListener->addToServer(Driver->EventServer);
		MouseListener->setCamera(Camera);
		MouseListener->setHotSpot(CVectorD(0,0,0));
		MouseListener->setFrustrum(Camera.getFrustum());
		MouseListener->setMatrix(Camera.getMatrix());
		MouseListener->setSpeed(PlayerSpeed);
		initMouseListenerConfig();
		// Init interface
		displayLoadingState("Initialize Interface ");
		initInterface();
		// Init radar
		displayLoadingState("Initialize Radar ");
		initRadar();
		// Init compass
		displayLoadingState("Initialize Compass ");
		initCompass();
		// Init graph
		displayLoadingState("Initialize Graph ");
		initGraph();
		// Init the command control
		displayLoadingState("Initialize Commands ");
		initCommands();
		// Init the entities prefs
		displayLoadingState("Initialize Entities ");
		initEntities();
		// Init animation system
		displayLoadingState("Initialize Animation ");
		initAnimation();
		// Init the lens flare
		displayLoadingState("Initialize LensFlare ");
		initLensFlare();
		// Init the sky
		displayLoadingState("Initialize Sky ");
		initSky();

		// Init the mouse so it's trapped by the main window.
		Driver->showCursor(false);
		Driver->setCapture(true);
		Driver->setMousePos(0.5f, 0.5f);
	}
}

void initOnline()
{
	if (LoadedOnline) return;
#ifdef NL_OS_WINDOWS
	playMusic(SBCLIENT_MUSIC_WAIT);
#endif
	
	displayLoadingState("Connecting");
	
	// connect to the server
	nlinfo("Try to connect to FS addr '%s' and identify with the cookie '%s'", FSAddr.c_str(), Cookie.c_str());
	initNetwork(Cookie, FSAddr);

	while (Self == NULL) // wait for position etc from server
		updateLoadingState(ucstring("Connecting"), true, true);

	displayLoadingState("Load Landscape");
	LandscapeComponent->loadAllZonesAround();

	displayLoadingState("Ready!");

#ifdef NL_OS_WINDOWS
	playMusic(SBCLIENT_MUSIC_BACKGROUND);
#endif
	LoadedOnline = true;
}

void initOffline()
{
	if (!LoadedOffline)
	{
		LoadedOffline = true;
#ifdef NL_OS_WINDOWS
		playMusic(SBCLIENT_MUSIC_WAIT);
#endif

		uint32 id = NextEID++;
		Login = ucstring("Entity" + toString(id));

		// Creates the self entity
		displayLoadingState("Creating offline entity");
		addEntity(id, Login.toUtf8(), CEntity::Self, CVector(ConfigFile->getVar("StartPoint").asFloat(0),
													 ConfigFile->getVar("StartPoint").asFloat(1),
													 ConfigFile->getVar("StartPoint").asFloat(2)),
											 CVector(ConfigFile->getVar("StartPoint").asFloat(0),
													 ConfigFile->getVar("StartPoint").asFloat(1),
													 ConfigFile->getVar("StartPoint").asFloat(2)));

		displayLoadingState("Load Landscape");
		LandscapeComponent->loadAllZonesAround();

		// Display a local welcome message
		addLine(">>>>> Welcome to Snowballs!");
		addLine(">>>>> Press SHIFT-ESC to exit the game.");

		displayLoadingState("Ready!");
	
#ifdef NL_OS_WINDOWS
		playMusic(SBCLIENT_MUSIC_BACKGROUND);
#endif
	}
}

void releaseCore()
{
	if (LoadedCore)
	{
		LoadedCore = false;
		// Release configuration callbacks
		ConfigFile->setCallback("OpenGL", NULL);

		// Release the sun
		releaseLight();
		// Release the loading state textures
		releaseLoadingState();
		// Release the sound
#ifdef NL_OS_WINDOWS
		releaseSound();
#endif
		// Release the text context
		Driver->deleteTextContext(TextContext);
		TextContext = NULL;
		// Release the 3d driver
		Driver->release();
		delete Driver;
		Driver = NULL;
	}
}

void releaseLogin()
{
	if (LoadedLogin)
	{
		LoadedLogin = false;
	}
}

void releaseIngame()
{
	if (LoadedIngame)
	{
		LoadedIngame = false;

		// Release the mouse cursor
		if (CaptureState)
		{
			Driver->setCapture(false);
			Driver->showCursor(true);
		}

		// Release all before quit

		releaseSky();
		releaseLensFlare();
		releaseRadar();
		releaseCommands();
		releaseEntities();
		releaseGraph();
		releaseCompass();
		releaseInterface();
		releaseNetwork();
		releaseAnimation();
		releaseMouseListenerConfig();
		releaseCamera();
		releaseAiming();
		releasePACS();
		releaseLandscape();
		delete LandscapeComponent;
		// Release the mouse listener
		MouseListener->removeFromServer(Driver->EventServer);
		delete MouseListener;
		Driver->deleteScene(Scene);
	}
}

void releaseOnline()
{
	if (LoadedOnline)
	{
		LoadedOnline = false;
		releaseNetwork();
		deleteAllEntities();
	}
}

void releaseOffline()
{
	if (LoadedOffline)
	{
		LoadedOffline = false;
		deleteAllEntities();
	}
}

void loopLogin()
{
#ifdef NL_OS_WINDOWS
	playMusic(SBCLIENT_MUSIC_LOGIN);
#endif
	// todo: login screen, move this stuff to a button or something
	displayLoadingState("Login");
	if (ConfigFile->getVar("Local").asInt() == 0)
	{
		if (ConfigFile->getVar("UseDirectClient").asInt() == 1)
		{
			string result;
			string LSHost(ConfigFile->getVar("LSHost").asString());
			Login = ConfigFile->getVar("Login").asString();
			ucstring Password = ConfigFile->getVar("Password").asString();
			CHashKeyMD5 hk = getMD5((uint8*)Password.c_str(), Password.size());
			string CPassword = hk.toString();
			nlinfo("The crypted password is %s", CPassword.c_str());
			string Application = ConfigFile->getVar("ClientApplication").asString();
			sint32 sid = ConfigFile->getVar("ShardId").asInt();

			// 1/ Authenticate
			updateLoadingState(ucstring("Authenticate"), false, false);
			result = CLoginClient::authenticateBegin(LSHost, Login, CPassword, Application);
			if (!result.empty()) goto AuthenticateFail;
			while (CLoginClient::authenticateUpdate(result))
				updateLoadingState(ucstring("Authenticate"), false, false);
			if (!result.empty()) goto AuthenticateFail;

			goto AuthenticateSuccess;
AuthenticateFail:
			nlinfo("*** Authenticate failed '%s' ***", result.c_str());
			for (TTime t = 0; t < 5000; t += DiffTime)
				updateLoadingState(ucstring("Authenticate failed: ") + ucstring(result), false, false);
			NextGameState = GameStateOffline;
			return;
AuthenticateSuccess:

			nlinfo("%d Shards are available:", CLoginClient::ShardList.size());
			for (uint i = 0; i < CLoginClient::ShardList.size(); i++)
			{
				nlinfo("    ShardId %3d: %s(%d online players)", CLoginClient::ShardList[i].Id, CLoginClient::ShardList[i].Name.toUtf8().c_str(), CLoginClient::ShardList[i].NbPlayers);
			}

			// 2/ Select shard
			updateLoadingState(ucstring("Select shard"), false, false);
			result = CLoginClient::selectShardBegin(sid);
			if (!result.empty()) goto SelectFail;
			while (CLoginClient::selectShardUpdate(result, FSAddr, Cookie))
				updateLoadingState(ucstring("Select shard"), false, false);
			if (!result.empty()) goto SelectFail;
			goto SelectSuccess;
SelectFail:
			nlinfo("*** Connection to the shard failed '%s' ***", result.c_str());
			for (TTime t = 0; t < 5000; t += DiffTime)
				updateLoadingState(ucstring("Select shard failed: ") + ucstring(result), false, false);
			NextGameState = GameStateOffline;
			return;
SelectSuccess:;
		}
		NextGameState = GameStateOnline;
		return;
	}
	NextGameState = GameStateOffline;
	return;
}

void loopIngame()
{
	while (CurrentGameState == NextGameState)
	{
		if (!Driver->isActive()) { NextGameState = GameStateExit; return; }

		animateSky(NewTime-LastTime);

		// Clear all buffers
		Driver->clearBuffers(CRGBA(0, 0, 0));

		// Update the time counters
		LastTime = NewTime;
		NewTime = CTime::getLocalTime();
		//nldebug("NewTime = %lld", NewTime);
		DiffTime = NewTime - LastTime;

		// Update all entities positions
		MouseListener->update();
		updateEntities();

		// setup the camera
		// -> first update camera position directly from the mouselistener
		// -> then update stuffs linked to the camera(snow, sky, lens flare etc.)
		MouseListener->updateCamera();
		updateCamera();		
		LandscapeComponent->update(); // Update the landscape
#ifdef NL_OS_WINDOWS
		updateSound(); // Update the sound
#endif
		Scene->animate(float(NewTime)/1000); // Set new animation date
		updateSky(); // Render the sky scene before the main scene

		Scene->render(); // Render		
		updateLensFlare(); // Render the lens flare
		updateCompass(); // Update the compass		
		updateRadar(); // Update the radar
		updateGraph(); // Update the radar		
		if (ShowCommands) updateCommands(); // Update the commands panel
		updateAnimation();		
		renderEntitiesNames(); // Render the name on top of the other players		
		updateInterface(); // Update interface
		renderInformation();
		update3dLogo();

		// Update network messages
		updateNetwork();
		// Swap 3d buffers
		Driver->swapBuffers();
		// Pump user input messages
		Driver->EventServer.pump();

		// Manage the keyboard

		if (Driver->AsyncListener.isKeyDown(KeySHIFT) && Driver->AsyncListener.isKeyDown(KeyESCAPE))
		{
			// Shift Escape -> quit
			NextGameState = GameStateExit;
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF3))
		{
			// F3 -> toggle wireframe/solid
			UDriver::TPolygonMode p = Driver->getPolygonMode();
			p = UDriver::TPolygonMode(((int)p+1)%3);
			Driver->setPolygonMode(p);
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF4))
		{
			// F4 -> clear the command(chat) output
			clearCommands();
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF5))
		{
			// F5 -> display/hide the commands(chat) interface
			ShowCommands = !ShowCommands;
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF6))
		{
			// F6 -> display/hide the radar interface
			RadarState =(RadarState + 1) % 3;
		}
		else if (Driver->AsyncListener.isKeyDown(KeyF7))
		{
			// F7 -> radar zoom out
			RadarDistance += 50;
		}
		else if (Driver->AsyncListener.isKeyDown(KeyF8))
		{
			// F8 -> radar zoom in
			RadarDistance -= 50;
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF9))
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
		else if (Driver->AsyncListener.isKeyPushed(KeyF10))
		{
			// F10 -> switch beteen online and offline
			if (isOnline()) NextGameState = GameStateOffline;
			else NextGameState = GameStateLogin;
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF11))
		{
			// F11 -> reset the PACS global position of the self entity(in case of a pacs failure :-\)
			if (Self != NULL)
				resetEntityPosition(Self->Id);
		}
		else if (Driver->AsyncListener.isKeyPushed(KeyF12))
		{
			// F12 -> take a screenshot
			CBitmap btm;
			Driver->getBuffer(btm);
			string filename = CFile::findNewFile("screenshot.tga");
			COFile fs(filename);
			btm.writeTGA(fs,24,false);
			nlinfo("Screenshot '%s' saved", filename.c_str());
		}
		// Check if the config file was modified by another program
		CConfigFile::checkConfigFiles();
	}
}

void renderInformation()
{
	// Display if we are online or offline
	TextContext->setHotSpot(UTextContext::TopRight);
	TextContext->setColor(isOnline()?CRGBA(0, 255, 0):CRGBA(255, 0, 0));
	TextContext->setFontSize(18);
	TextContext->printfAt(0.99f, 0.99f, isOnline() ? "Online" : "Offline");

	// Display the frame rate
	float fps = 1000.0f /(float)DiffTime;
	TextContext->setHotSpot(UTextContext::TopLeft);
	TextContext->setColor(CRGBA(255, 255, 255, 255));
	TextContext->setFontSize(14);
	TextContext->printfAt(0.01f, 0.99f, "%.2ffps %ums", fps,(uint32)DiffTime);

	// one more frame
	FpsGraph.addValue(1.0f);
	SpfGraph.addOneValue((float)DiffTime);
}

// 
// Configuration callbacks
// 

void cbGraphicsDriver(CConfigFile::CVar &var)
{
	// -- give ingame warning or something instead =)
	NextGameState = GameStateReset;
}

//
// Loading state procedure
//

static UTextureFile *NelLogo = NULL;
static UTextureFile *NevraxLogo = NULL;
static float ScreenWidth, ScreenHeight;
// The logo 3D objects
static UScene				*LogoScene = NULL;
static UInstance			Logo = NULL;

void initLoadingState()
{
	NelLogo = Driver->createTextureFile("nel128.tga");
	NevraxLogo = Driver->createTextureFile("nevrax.tga");
	uint32 width, height;
	Driver->getWindowSize(width, height);
	ScreenWidth =(float)width;
	ScreenHeight =(float)height;

	//
	// Setup the logo scene
	//

	LogoScene = Driver->createScene(false);

	CViewport v;
	v.init(0.0f, 0.80f, 0.2f, 0.2f);
	LogoScene->setViewport(v);

	Logo = LogoScene->createInstance("nel_logo.shape");
	Logo.setPos(0.0f, 3.0f, 0.0f);
	Logo.setTransformMode(UTransformable::RotEuler);
}

void releaseLoadingState()
{
	LogoScene->deleteInstance(Logo); Logo = NULL;
	Driver->deleteScene(LogoScene); LogoScene = NULL;
	Driver->deleteTextureFile(NelLogo); NelLogo = NULL;
	Driver->deleteTextureFile(NevraxLogo); NevraxLogo = NULL;
}

void renderLoadingState(const char *state, bool logo3d)
{
	renderLoadingState(ucstring(state), logo3d);
}
void renderLoadingState(ucstring state, bool logo3d)
{
	if (!Driver) return;

	Driver->clearBuffers(CRGBA(0,0,0));

	Driver->setMatrixMode2D(CFrustum(0.0f, ScreenWidth, 0.0f, ScreenHeight, 0.0f, 1.0f, false));
	if (logo3d) update3dLogo();
	else if (NelLogo != NULL) Driver->drawBitmap(10, ScreenHeight-128-10, 128, 128, *NelLogo);
	if (NevraxLogo != NULL) Driver->drawBitmap(ScreenWidth-128-10, ScreenHeight-16-10, 128, 16, *NevraxLogo);

	if (!TextContext) return;

	TextContext->setColor(CRGBA(255, 255, 255));
	TextContext->setHotSpot(UTextContext::MiddleMiddle);

	TextContext->setFontSize(40);
	TextContext->printAt(0.5f, 0.5f, ucstring("Welcome to Snowballs!"));
	
	TextContext->setFontSize(30);
	TextContext->printAt(0.5f, 0.2f, state);
	
	TextContext->setHotSpot(UTextContext::BottomRight);
	TextContext->setFontSize(15);
#if (FINAL_VERSION == 1)
	TextContext->printAt(0.99f, 0.01f, ucstring("Final Version"));
#else
	TextContext->printAt(0.99f, 0.01f, ucstring("(compiled " __DATE__ " " __TIME__ ")"));
#endif

	TextContext->setHotSpot(UTextContext::BottomLeft);
	TextContext->setFontSize(15);
#if defined(NL_DEBUG_FAST)
	ucstring version = ucstring("DebugFast Version");
#elif defined(NL_DEBUG)
	ucstring version = ucstring("Debug Version");
#elif defined(NL_RELEASE)
	ucstring version = ucstring("Release Version");
#elif defined(NL_RELEASE_DEBUG)
	ucstring version = ucstring("ReleaseDebug Version");
#else
	ucstring version = ucstring("Unknown Version");
#endif
}

void displayLoadingState(const char *state)
{
	displayLoadingState(ucstring(state));
}
void displayLoadingState(ucstring state)
{
	LastTime = NewTime;
	NewTime = CTime::getLocalTime();
	DiffTime = NewTime - LastTime;
	renderLoadingState(state, false);
	Driver->swapBuffers();
	//Driver->EventServer.pump();
}

void updateLoadingState(const char *state, bool network, bool information)
{
	updateLoadingState(ucstring(state), network, information);
}
void updateLoadingState(ucstring state, bool network, bool information)
{
	LastTime = NewTime;
	NewTime = CTime::getLocalTime();
	DiffTime = NewTime - LastTime;
#ifdef NL_OS_WINDOWS
	updateSound();
#endif
	renderLoadingState(state, true);
	if (information) renderInformation();
	if (network) updateNetwork();
	Driver->swapBuffers();
	Driver->EventServer.pump();
}

void update3dLogo()
{
	Driver->clearZBuffer();
	static float angle=0.0;
	angle+=0.002f * DiffTime;
	Logo.setRotEuler(0.0f,0.0f,angle);
	LogoScene->animate(float(NewTime)/1000);
	LogoScene->render();
}




// Command to quit the client
NLMISC_COMMAND(sb_quit,"quit the client","")
{
	// check args, if there s not the right number of parameter, return bad
	if (args.size() != 0) return false;

	log.displayNL("Exit requested");

	NextGameState = GameStateExit;

	return true;
}

NLMISC_COMMAND(sb_offline, "go offline", "")
{
	if (args.size() != 0) return false;
	NextGameState = GameStateOffline;
	return true;
}

NLMISC_COMMAND(sb_unload, "unload game", "")
{
	if (args.size() != 0) return false;
	NextGameState = GameStateUnload;
	return true;
}

NLMISC_COMMAND(sb_reset, "reset game", "")
{
	if (args.size() != 0) return false;
	NextGameState = GameStateReset;
	return true;
}

NLMISC_COMMAND(sb_login, "go to the login screen", "")
{
	if (args.size() != 0) return false;
	NextGameState = GameStateLogin;
	return true;
}
