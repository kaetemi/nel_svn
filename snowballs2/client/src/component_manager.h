/** \file component_manager.h
 * CComponentManager
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
 * $Id: component_manager.h 417 2007-12-29 19:37:37Z Kaetemi $
 */

#ifndef SBCLIENT_COMPONENT_MANAGER_H
#define SBCLIENT_COMPONENT_MANAGER_H
#include <nel/misc/types_nl.h>
#include <nel/misc/config_file.h>

namespace SBCLIENT {

// todo: implement the component manager
class CComponentManager
{
public:	
	// pointers
	// ...
	
	// instances
	NLMISC::CConfigFile ConfigFile;
public:
	CComponentManager(const std::string &configFile);
	virtual ~CComponentManager();
};

}

#endif /* #ifndef SBCLIENT_COMPONENT_MANAGER_H */
