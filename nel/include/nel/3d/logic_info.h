/** \file logic_info.h
 * TODO: File description
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_LOGIC_INFO_H
#define NL_LOGIC_INFO_H

#include "nel/misc/types_nl.h"
#include "nel/misc/rgba.h"
#include "nel/3d/point_light_influence.h"
#include <vector>


namespace NL3D
{


/**
 * An interface for UScene to retrieve client information for a specified UTransform
 *	( see UTransfrom::setLogicInfo() ).
 *
 *	implemented by user. typically, methods are called during UScene::render() and are called
 *	only if necessary (typically after clip).
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class ILogicInfo
{
public:

	/// Constructor
	ILogicInfo();
	virtual	~ILogicInfo();


	/**
	 *	This method must return the static light setup which influence the object attached with this ILogicInfo
	 *	pointLightList.size() may not be 0. Deriver should just append his light and do not clear this list.
	 *
	 *	NB: called by CLightingManager::computeModelLightContributions() when needed
	 *
	 *	\param pointLightList append to this list static pointLights which may influence this object.
	 *	\param sunContribution contribution factor of the sun to apply to the transform.
	 *	\param localAmbient ig or landscape may replace sunAmbient with their special ambient.
	 *	localAmbient.A tells the fraction of this color to take (255 => full contribution of the localAmbient, and
	 *	no contribution of the ambient of the sun)
	 */
	virtual	void		getStaticLightSetup(NLMISC::CRGBA sunAmbient, std::vector<CPointLightInfluence> &pointLightList,
		uint8 &sunContribution, NLMISC::CRGBA &localAmbient) =0;


};


} // NL3D


#endif // NL_LOGIC_INFO_H

/* End of logic_info.h */
