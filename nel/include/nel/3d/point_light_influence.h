/** \file point_light_influence.h
 * TODO: File description
 *
 * $Id: point_light_influence.h,v 1.4 2004/11/15 10:24:17 lecroart Exp $
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

#ifndef NL_POINT_LIGHT_INFLUENCE_H
#define NL_POINT_LIGHT_INFLUENCE_H

#include "nel/misc/types_nl.h"

namespace NL3D {


class CPointLight;


/**
 * A pointLight Influence. Filled by Static Lighting system (landscape / Igs).
 *	The influence may be lower than 1, because landscape/Igs look into a grid (on patchs or on pacs surfaces)
 *	and do biLinear to avoid lighting poping.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CPointLightInfluence
{
public:
	// The light of interest
	CPointLight		*PointLight;
	// The factor of influence (0..1) of this light, computed by the static light setup.
	float			Influence;
	// Internal Use only. Used by CLightingManager
	float			BkupInfluence;
	// Internal Use only. Used by CLightingManager
	float			DistanceToModel;

	// To sort by influence.
	bool	operator<(const CPointLightInfluence &sl) const
	{
		// sort in growing order
		return Influence>sl.Influence;
	}

};



} // NL3D


#endif // NL_POINT_LIGHT_INFLUENCE_H

/* End of point_light_influence.h */
