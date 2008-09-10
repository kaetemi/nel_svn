/** \file landscape_component.cpp
 * CLandscapeComponent
 * 
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * $Id: landscape_component.cpp 418 2007-12-31 02:17:28Z Kaetemi $
 */

#include <nel/misc/types_nl.h>
#include "landscape_component.h"

#include <nel/misc/path.h>

#include <nel/3d/u_landscape.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/u_camera.h>

using namespace std;
using namespace NL3D;
using namespace NLMISC;

extern ULandscape *Landscape; // temp

namespace SBCLIENT {

CLandscapeComponent::CLandscapeComponent(
	CComponentManager *manager, const string &instanceId,
	UScene *scene)
: IComponent(manager, instanceId), _Landscape(NULL), _Scene(scene)
{
	// -- -- start of init for "landscape around camera that gets data from config"

	// create the landscape
	_Landscape = _Scene->createLandscape();
	Landscape = _Landscape;

	// load the bank files
	_Landscape->loadBankFiles(
		CPath::lookup(_Config.getVar("BankName").asString()), 
		CPath::lookup(_Config.getVar("FarBankName").asString()));
	_Landscape->invalidateAllTiles();

	// _Landscape->postfixTileFilename("_au");
	// _Landscape->postfixTileVegetableDesc("_au");

	// -- -- this doesn't do anything useful
	//////// setup the zone path
	//////Landscape->setZonePath(ConfigFile->getVar("DataPath").asString() + "zones/");

	// -- -- do this when character appears or does far teleport
	//////// and eventually, load the zones around the starting point.
	//////Landscape->loadAllZonesAround (CVector(ConfigFile->getVar("StartPoint").asFloat(0),
	//////									   ConfigFile->getVar("StartPoint").asFloat(1),
	//////									   ConfigFile->getVar("StartPoint").asFloat(2)), 
	//////							   1000.0f);

	// color of the landscape shadow
	CRGBA diffuse(
		_Config.getVar("DiffuseColor").asInt(0), 
		_Config.getVar("DiffuseColor").asInt(1), 
		_Config.getVar("DiffuseColor").asInt(2));
	CRGBA ambient(
		_Config.getVar("AmbiantColor").asInt(0), 
		_Config.getVar("AmbiantColor").asInt(1), 
		_Config.getVar("AmbiantColor").asInt(2));
	
	_Landscape->setupStaticLight(
		diffuse, ambient,
		_Config.getVar("MultiplyFactor").asFloat());

	registerAndCallConfigCallback("ReceiveShadowMap");
	registerAndCallConfigCallback("TileNear");
	registerAndCallConfigCallback("Threshold");
	registerAndCallConfigCallback("Vision");
	registerAndCallConfigCallback("VisionInitial");
}

CLandscapeComponent::~CLandscapeComponent()
{
	unregisterConfigCallback("TileNear");
	unregisterConfigCallback("Threshold");

	// -- -- release for cameralandscape
	_Scene->deleteLandscape(_Landscape);
}

void CLandscapeComponent::update()
{
	// -- -- update for CCameraLandscape
	// -- -- no need to go to snowballs mouse listener, can probly get this 
	//       from a NL3D::UCamera, NLPACS::UMovePrimitive or NL3D::UInstance too.
	// -- -- random note: make a CControllableMovePrimitiveEntityInstance or something
	// -- -- should get the player position and not the camera position,
	//       most optimal for camera rotating around player.

	// load the zones around the viewpoint
	_Landscape->refreshZonesAround(
		_Scene->getCam().getMatrix().getPos(), _cfgVision);
	//_Landscape->refreshZonesAround(MouseListener->getViewMatrix().getPos(), 1000.0f);
}

void CLandscapeComponent::render()
{
	
}

void CLandscapeComponent::config(const string &varName, CConfigFile::CVar &var)
{
	if (varName == "TileNear") 
		_Landscape->setTileNear(var.asFloat());

	else if (varName == "Threshold") 
		_Landscape->setThreshold(var.asFloat());

	else if (varName == "Vision") 
		_cfgVision = var.asFloat();

	else if (varName == "VisionInitial") 
		_cfgVisionInitial = var.asFloat();

	else if (varName == "ReceiveShadowMap")
		_Landscape->enableReceiveShadowMap(var.asBool());

	else nlwarning("Unknown variable update %s", var.Name.c_str());
}

void CLandscapeComponent::loadAllZonesAround()
{
	_Landscape->loadAllZonesAround(
		_Scene->getCam().getMatrix().getPos(), _cfgVisionInitial);
}

}
