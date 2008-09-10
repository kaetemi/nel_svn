/** \file component.h
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
 * $Id: component.h 418 2007-12-31 02:17:28Z Kaetemi $
 */

#ifndef SBCLIENT_COMPONENT_H
#define SBCLIENT_COMPONENT_H
#include <nel/misc/types_nl.h>
#include "sub_configuration.h"

namespace SBCLIENT {

class CComponentManager;

/**
 * Base class for components that can be identified uniquely by name,
 * and make use of a configuration file to initialize themselves.
 * \author Jan Boon
 * \date 2007
 */
class IComponent
{
protected:
	// pointers
	CComponentManager *_Manager; // not deleted here
	
	// instances
	CSubConfiguration _Config;
	std::string _InstanceId;
public:	
	/// Basic constructor of a component.
	/// Requires a pointer to the componentmanager and a unique name.
	IComponent(CComponentManager *manager, const std::string &instanceId);
	virtual ~IComponent();

	virtual void update() { }
	virtual void render() { }

	/// Force update of config value.
	/// Calls the virtual config callback of the component.
	void config(const std::string &varName);

	/// Get the instance id of this component.
	std::string getInstanceId() { return _InstanceId; }

	/// Gets a component instance by name. 
	/// A component that uses this to get another component it depends on,
	/// should get the InstanceId from it's configuration, and optimally
	/// only call this once for every component instance it depends on.
	static IComponent &getInstance(const std::string &instanceId);
	static IComponent *getInstancePtr(const std::string &instanceId);
protected:
	void registerConfigCallback(const std::string &varName);
	void registerAndCallConfigCallback(const std::string &varName);
	void unregisterConfigCallback(const std::string &varName);
	virtual void config(const std::string &varName, NLMISC::CConfigFile::CVar &var) { }
	static void _config(NLMISC::CConfigFile::CVar &var);
};

}

#endif /* #ifndef SBCLIENT_COMPONENT_H */
