/** \file component.cpp
 * IComponent
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
 * $Id: component.cpp 418 2007-12-31 02:17:28Z Kaetemi $
 */

#include <nel/misc/types_nl.h>
#include "component.h"

#include "component_manager.h"

#include <nel/misc/app_context.h>

using namespace std;
using namespace NLMISC;

namespace SBCLIENT {

IComponent::IComponent(CComponentManager *manager, const string &instanceId)
: _Manager(manager), _Config(), _InstanceId(instanceId)
{
	// register this with the app context
	// this ensures that the same component configuration isn't init twice
	CApplicationContext::getInstance().setSingletonPointer(
		string("SBCLIENT::IComponent|") + _InstanceId, this);
	// initialize the config file manager
	_Config.setConfigFile(&manager->ConfigFile, instanceId);
}

IComponent::~IComponent()
{
	// remove this from the app context
	CApplicationContext::getInstance().releaseSingletonPointer(
		string("SBCLIENT::IComponent|") + _InstanceId, this);
}

IComponent &IComponent::getInstance(const string &instanceId)
{
	IComponent *instance = getInstancePtr(instanceId);
	if (instance == NULL) 
		nlerror("IComponent %s does not exist", instanceId.c_str());
	return *instance;
}

IComponent *IComponent::getInstancePtr(const string &instanceId)
{
	// make use of the nlmisc application context
	IComponent *instance = 
		(IComponent *)CApplicationContext::getInstance()
		.getSingletonPointer(string("SBCLIENT::IComponent|") + instanceId);
	// don't allow null result for now
	nlassert(instance); return instance;
}

void IComponent::registerConfigCallback(const string &varName)
{
	_Config.setCallback(varName, _config);
}

void IComponent::registerAndCallConfigCallback(const string &varName)
{
	registerConfigCallback(varName);
	config(varName);
}

void IComponent::unregisterConfigCallback(const string &varName)
{
	_Config.setCallback(varName, NULL);
}

void IComponent::config(const std::string &varName)
{
	config(varName, _Config.getVar(varName));
}

void IComponent::_config(NLMISC::CConfigFile::CVar &var)
{
	vector<string> nameVector;
	std::string instanceId = nameVector[0];
	explode(var.Name, string("_"), nameVector, false);
	IComponent *instance = getInstancePtr(instanceId);
	uint i = 1;
	while (!instance)
	{
		if (i > nameVector.size() - 2) // need extra for var name
		{
			nlwarning("Config var callback %s not linked to any IComponent", var.Name.c_str());
			return;
		}
		instanceId = instanceId + string("_") + nameVector[i];
		++i;
	}
	std::string varName = nameVector[i]; ++i;
	while (i < nameVector.size());
	{
		varName = varName + string("_") + nameVector[i];
		++i;
	}
	instance->config(varName, var);
}

}
