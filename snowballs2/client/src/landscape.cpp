/** \file landscape.cpp
 * Landscape interface between the game and NeL
 *
 * $Id: landscape.cpp,v 1.19 2003-04-04 17:00:10 lecroart Exp $
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

#include "nel/misc/types_nl.h"

#include <string>
#include <deque>
#include <vector>

#include "nel/misc/variable.h"
#include "nel/misc/command.h"
#include "nel/misc/variable.h"
#include "nel/misc/debug.h"
#include "nel/misc/path.h"
#include "nel/misc/i18n.h"
#include "nel/misc/config_file.h"

#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/u_material.h>
#include <nel/3d/u_landscape.h>
#include <nel/3d/u_instance_group.h>
#include <nel/3d/u_light.h>

#include <nel/3d/u_visual_collision_entity.h>
#include <nel/3d/u_visual_collision_manager.h>

#include "client.h"
#include "pacs.h"
#include "commands.h"
#include "mouse_listener.h"
#include "physics.h"

//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NL3D;

//
// Variables
//




UVisualCollisionEntity	*AimingEntity = NULL;


vector<UInstanceGroup*>	 InstanceGroups;


ULight					*Sun = NULL;
NLMISC::CVector			 SunDirection;


//
// Functions
//

void cbUpdateLandscape (CConfigFile::CVar &var)
{
	// -- -- split this whole thing up, lol

	if (var.Name == "FogStart") 
		Driver->setupFog (var.asFloat (), 
		ConfigFile->getVar ("FogEnd").asFloat (), 
		CRGBA(ConfigFile->getVar ("FogColor").asInt (0), 
		ConfigFile->getVar ("FogColor").asInt (1),
		ConfigFile->getVar ("FogColor").asInt (2)));
	else if (var.Name == "FogEnd") 
		Driver->setupFog (ConfigFile->getVar ("FogStart").asFloat (), 
		var.asFloat (), 
		CRGBA(ConfigFile->getVar ("FogColor").asInt (0), 
		ConfigFile->getVar ("FogColor").asInt (1),
		ConfigFile->getVar ("FogColor").asInt (2)));
	else if (var.Name == "FogColor")
		Driver->setupFog(
		ConfigFile->getVar ("FogStart").asFloat (), 
		ConfigFile->getVar ("FogEnd").asFloat (), 
		CRGBA(var.asInt (0), var.asInt (1), var.asInt (2)));
	else if (var.Name == "FogEnable")
	{
		Driver->enableFog(var.asBool());
		Driver->setupFog(
			ConfigFile->getVar("FogStart").asFloat(), 
			ConfigFile->getVar("FogEnd").asFloat(),
			CRGBA(ConfigFile->getVar("FogColor").asInt(0), 
			ConfigFile->getVar ("FogColor").asInt(1), 
			ConfigFile->getVar ("FogColor").asInt(2)));
	}
	else if (var.Name == "SunAmbientColor")
	{
		Sun->setAmbiant (CRGBA (var.asInt(0), var.asInt(1), var.asInt(2)));
		Driver->setLight (0, *Sun);
	}
	else if (var.Name == "SunDiffuseColor")
	{
		Sun->setDiffuse (CRGBA (var.asInt(0), var.asInt(1), var.asInt(2)));
		Driver->setLight (0, *Sun);
	}
	else if (var.Name == "SunSpecularColor")
	{
		Sun->setSpecular (CRGBA (var.asInt(0), var.asInt(1), var.asInt(2)));
		Driver->setLight (0, *Sun);
	}
	else if (var.Name == "SunDirection")
	{
		SunDirection.set (var.asFloat(0), var.asFloat(1), var.asFloat(2));
		Sun->setDirection (SunDirection);
		Driver->setLight (0, *Sun);
	}
	else nlwarning ("Unknown variable update %s", var.Name.c_str());
}

void initLight()
{
	// -- -- sun or whatever light, simple use, doesn't need class yet

	Sun = ULight::createLight();
	nlassert(Sun != NULL);
	Sun->setMode(ULight::DirectionalLight);
	Driver->enableLight(0);

	ConfigFile->setCallback("SunAmbientColor", cbUpdateLandscape);
	ConfigFile->setCallback("SunDiffuseColor", cbUpdateLandscape);
	ConfigFile->setCallback("SunSpecularColor", cbUpdateLandscape);
	ConfigFile->setCallback("SunDirection", cbUpdateLandscape);

	cbUpdateLandscape(ConfigFile->getVar("SunAmbientColor"));
	cbUpdateLandscape(ConfigFile->getVar("SunDiffuseColor"));
	cbUpdateLandscape(ConfigFile->getVar("SunSpecularColor"));
	cbUpdateLandscape(ConfigFile->getVar("SunDirection"));
}

void releaseLight()
{
	// -- -- just data

	ConfigFile->setCallback("SunAmbientColor", NULL);
	ConfigFile->setCallback("SunDiffuseColor", NULL);
	ConfigFile->setCallback("SunSpecularColor", NULL);
	ConfigFile->setCallback("SunDirection", NULL);

	delete Sun; Sun = NULL;
}

void	initLandscape()
{



	ConfigFile->setCallback ("FogStart", cbUpdateLandscape);
	ConfigFile->setCallback ("FogEnd", cbUpdateLandscape);
	ConfigFile->setCallback ("FogColor", cbUpdateLandscape);
	ConfigFile->setCallback ("FogEnable", cbUpdateLandscape);

	cbUpdateLandscape (ConfigFile->getVar ("FogStart"));
	cbUpdateLandscape (ConfigFile->getVar ("FogEnd"));
	cbUpdateLandscape (ConfigFile->getVar ("FogColor"));
	cbUpdateLandscape (ConfigFile->getVar ("FogEnable"));





	// -- -- start of init for "instance groups loaded from config"

	CConfigFile::CVar igv = ConfigFile->getVar("InstanceGroups");
	for (uint32 i = 0; i < igv.size (); i++)
	{
		UInstanceGroup *inst = UInstanceGroup::createInstanceGroup (igv.asString (i));
		if (inst == NULL)
		{
			nlwarning ("Instance group '%s' not found", igv.asString (i).c_str ());
		}
		else
		{
			inst->addToScene (*Scene);
			InstanceGroups.push_back (inst);
		}
	}
}

void	releaseLandscape()
{

	ConfigFile->setCallback("FogStart", NULL);
	ConfigFile->setCallback("FogEnd", NULL);
	ConfigFile->setCallback("FogColor", NULL);
	ConfigFile->setCallback("FogEnable", NULL);

}


void	initAiming()
{
	// -- -- belongs in "camera that follows entity and can be used to aim"
	// -- -- random note: is an extension of "camera that follows entity"

	// Create an aiming entity
	AimingEntity = VisualCollisionManager->createEntity();
	AimingEntity->setCeilMode(true);
}

void	releaseAiming()
{
	// -- -- belongs in CAimingEntityCamera

	VisualCollisionManager->deleteEntity(AimingEntity);
}

// -- -- mix with following bit of code for higher accuracy
//NLMISC::CVector CSceneryMouse::getLandscape()
//{
//	if (_LandscapeCached) return _LandscapeCache;
//	CViewport v = _Driver->getViewport();
//	CVector pos, dir; -- -- random note: this code gets the landscape position where the mouse is pointing at
//	v.getRayWithPoint(_X * v.getWidth(), _Y * v.getHeight(), pos, dir, _Camera.getMatrix(), _Camera.getFrustum());
//	dir.normalize();
//	dir *= 50;
// -- -- float rc = _Landscape->getRayCollision(pos, pos + dir);
// -- -- _LandscapeCache = pos + (rc * dir);
//	_LandscapeCached = true;
//	return _LandscapeCache;
//}
// -- -- if higher than 50 or something, use code below
CVector	getTarget(const CVector &start, const CVector &step, uint numSteps)
{
	CVector	testPos = start;

	uint	i;
	for (i=0; i<numSteps; ++i)
	{
		CVector	snapped = testPos, 
				normal;

		// here use normal to check if we have collision
		if (AimingEntity->snapToGround(snapped, normal) && (testPos.z-snapped.z)*normal.z < 0.0f)
		{
			testPos -= step*0.5f;
			break;
		}
		testPos += step;
	}
	return testPos;
}

CVector	getTarget(CTrajectory &trajectory, TTime dtSteps, uint numSteps)
{
	TTime	t = trajectory.getStartTime();
	CVector	testPos;

	uint	i;
	for (i=0; i<numSteps; ++i)
	{
		testPos = trajectory.eval(t);
		CVector	snapped = testPos, 
				normal;

		// here use normal to check if we have collision
		if (AimingEntity->snapToGround(snapped, normal) && (testPos.z-snapped.z)*normal.z < 0.0f)
		{
			t -= (dtSteps/2);
			testPos = trajectory.eval(t);
			break;
		}
		t += dtSteps;
	}
	return testPos;
}

/*
CVector	getTarget(const CVector &start, const CVector &step, uint numSteps)
{
	CVector	testPos = start;

	uint	i;
	for (i=0; i<numSteps; ++i)
	{
		// For each step, check if the snapped position is backward the normal
		CVector	snapped = testPos;
		CVector	normal;
		// here use normal to check if we have collision
		if (AimingEntity->snapToGround(snapped, normal) && (testPos.z-snapped.z)*normal.z < 0.0f)
		{
			testPos -= step*0.5f;
			break;
		}
		testPos += step;
	}

	return testPos;
}
*/

// -- -- snowballs specific commands, not for the landscape class itself, it assumes using 
//       one landscape, and will get actual landscape from CSnowballsClient instance
// -- -- random note: there will only be one instance of CSnowballsClient,
//       which is the class that takes care of what is currently done in client.cpp

//NLMISC_DYNVARIABLE(float,tilenear,"landscape tile near")
//{
//	if (get)
//		*pointer = Landscape->getTileNear();
//	else
//		Landscape->setTileNear(*pointer);
//}
//
//NLMISC_DYNVARIABLE(float,threshold,"landscape threshold")
//{
//	if (get)
//		*pointer = Landscape->getThreshold();
//	else
//		Landscape->setThreshold(*pointer);
//}
//
//// boost to 
//NLMISC_COMMAND(boost,"switch landscape parameters between high speed and high quality","0|1")
//{
//	if (args.size() != 1 ) return false;
//	if ( args[0]=="1" )
//	{
//		ICommand::execute( "tilenear 5", CommandsLog);
//		ICommand::execute( "threshold 1", CommandsLog);
//	}
//	else
//	{
//		ICommand::execute( "tilenear 100", CommandsLog);
//		ICommand::execute( "threshold 0.01", CommandsLog);
//	}
//	return true;
//}


NLMISC_COMMAND(add_ig, "add instance group", "name")
{
	if (args.size() != 1 ) return false;
	UInstanceGroup *inst = UInstanceGroup::createInstanceGroup(args[0]);
	if (inst == NULL) nlwarning("Instance group '%s' not found", args[0].c_str());
	else
	{
		inst->addToScene(*Scene);
		InstanceGroups.push_back(inst);
	}
	return true;
}

