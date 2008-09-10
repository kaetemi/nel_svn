/** \file landscape_component.h
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
 * $Id: landscape_component.h 418 2007-12-31 02:17:28Z Kaetemi $
 */

#ifndef SBCLIENT_LANDSCAPE_COMPONENT_H
#define SBCLIENT_LANDSCAPE_COMPONENT_H
#include <nel/misc/types_nl.h>
#include "component.h"

namespace NL3D {
	class ULandscape;
	class UScene;
}

namespace SBCLIENT {

class CComponentManager;

/**
 * A landscape component.
 * \author Name
 * \date Year
 */
class CLandscapeComponent : public IComponent
{
protected:
	// pointers
	NL3D::ULandscape *_Landscape; // deleted here
	NL3D::UScene *_Scene; // get in constructor
	
	// instances
	float _cfgVision;
	float _cfgVisionInitial;
public:	
	/// Basic constructor of a component.
	/// Requires a pointer to the componentmanager and a unique name.
	CLandscapeComponent(
		CComponentManager *manager, const std::string &instanceId, 
		NL3D::UScene *scene);
	~CLandscapeComponent();

	void update();
	void render();
	void config(const std::string &varName, NLMISC::CConfigFile::CVar &var);

	void loadAllZonesAround();
};

}

#endif /* #ifndef SBCLIENT_LANDSCAPE_COMPONENT_H */
