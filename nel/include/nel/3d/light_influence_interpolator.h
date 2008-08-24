/** \file light_influence_interpolator.h
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

#ifndef NL_LIGHT_INFLUENCE_INTERPOLATOR_H
#define NL_LIGHT_INFLUENCE_INTERPOLATOR_H

#include "nel/misc/types_nl.h"
#include "nel/3d/point_light_influence.h"
#include <vector>


namespace NL3D
{


class	CPointLightNamed;

// ***************************************************************************
/**
 * This class is used by CLandscape and IG/Pacs to compute interpolated influence of lights
 *	(biLinear-like) on a square. It works only with CPointLightNamed.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CLightInfluenceInterpolator
{
public:

	/// We support only 2 light per corner.
	enum	{NumLightPerCorner= 2};

public:

	struct	CCorner
	{
		// List of lights on this corner
		CPointLightNamed		*Lights[NumLightPerCorner];

	private:
		friend class CLightInfluenceInterpolator;
		// biLinear factor
		float					Influence;
	};

	/** The User must setup Lights correctly for each corner (ie set NULL for each light not here).
	 *	Corner order is TL(0,0), TR(1,0), BL(0,1), BR(1,1).
	 */
	CCorner				Corners[4];


public:

	/// Constructor. No-op !!
	CLightInfluenceInterpolator() {}


	/** solve the biLinear (regrouping multiple influence of light at same id),
	 *	and add CPointLightInfluence to the list.
	 *	\param subX E [0, 1] is the x coord for biLinear
	 *	\param subY E [0, 1] is the y coord for biLinear
	 */
	void			interpolate(std::vector<CPointLightInfluence> &pointLightList, float subX, float subY);

};


} // NL3D


#endif // NL_LIGHT_INFLUENCE_INTERPOLATOR_H

/* End of light_influence_interpolator.h */
