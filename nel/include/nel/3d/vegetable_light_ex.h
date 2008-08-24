/** \file vegetable_light_ex.h
 * TODO: File description
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_VEGETABLE_LIGHT_EX_H
#define NL_VEGETABLE_LIGHT_EX_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "nel/misc/rgba.h"


namespace NL3D
{


class	CPointLightNamed;


/**
 * Additional information to light Vegetables. 2 "precomputed" pointLights can
 *	additionally light the vegetables.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CVegetableLightEx
{
public:

	/// Must not change (hardcoded)
	enum	{MaxNumLight= 2};

	/// Number Of light currently really enabled.
	uint				NumLights;
	/// PointLights. Used at CVegetableManager::updateLighting() to get current colors of pointLights.
	CPointLightNamed	*PointLight[MaxNumLight];
	/// Direction of the light. the direction to the instance should be precomputed.
	CVector				Direction[MaxNumLight];
	/// Factor to be multiplied by color of the light. Actually it is the attenuation factor.
	uint				PointLightFactor[MaxNumLight];

	/// Current Color of the light.
	NLMISC::CRGBA		Color[MaxNumLight];

public:
	CVegetableLightEx()
	{
		NumLights= 0;
	}

	/// Fill Color array according to PointLight[] and PointLightFactor[].
	void				computeCurrentColors();
};


} // NL3D


#endif // NL_VEGETABLE_LIGHT_EX_H

/* End of vegetable_light_ex.h */
