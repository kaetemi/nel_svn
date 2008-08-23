/** \file zone_smoother.h
 * TODO: File description
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef NL_ZONE_SMOOTHER_H
#define NL_ZONE_SMOOTHER_H

#include "nel/misc/types_nl.h"
#include "nel/3d/zone.h"
#include "nel/misc/common.h"
#include <map>


namespace NL3D 
{


// ***************************************************************************
/**
 * A class used to make Bezier patch of zones G1.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CZoneSmoother
{
public:
	struct	CZoneInfo
	{
		/// Id of the zone.
		uint16 ZoneId;

		/// A ptr on the array of patchs of the zone.
		std::vector<CPatchInfo>		*Patchs;

		CZoneInfo()
		{
			ZoneId= 0;
			Patchs= NULL;
		}
	};

public:
	/// Constructor
	CZoneSmoother() {}


	/**
	 * Smooth the tangents of those zones. Zones must be correclty welded. 
	 * Only all patchs of zones[0] are parsed. But other zones may be modified on their edge (so you must save them).
	 *
	 * NB: tangent smoothing is only done on bind 1/1.
	 *
	 * \param zones The 0 is the center zone to be computed. Other are the 4 zones around (no special order needed).
	 *	Doesn't matter if zones[i].Patchs is NULL. Also, if a neighbor patch is not found on a edge, then no error is 
	 *  generated: this patch edge is not modified.
	 *	nlstop if zones[0]==NULL.
	 * \param angleThreshold if angle beetween (patch_interior - tangent) and (neighbor_patch_interior - tangent) is 
	 *	above angleThreshold, no smooth is done on this tangent. Default: 30deg.
	 * \param continuityC1. when a smooth is done on a tangent, tangent is forced such that the 2 interiors and the 
	 *	tangent are colinear, so continuity G1 is assured. if continuityC1 is true, then tangent is set to the middle of 
	 *	the interiors (continuity C1). If false, tangent is setup so that previous distance ratio are kept.
	 *
	 */
	void			smoothTangents(CZoneInfo zones[5], float angleThreshold= NLMISC::Pi/6, bool continuityC1= false);


private:
	typedef std::map<sint, CZoneInfo>	TZoneInfoMap;
	TZoneInfoMap		_Zones;
	float				_CosThreshold;
	bool				_ContinuityC1;

	// smoothTangent according to _CosThreshold and _ContinuityC1.
	bool		smoothTangent(const CVector &tgt, const CVector &int0, const CVector &int1, CVector &tgtres);

};


} // NL3D


#endif // NL_ZONE_SMOOTHER_H

/* End of zone_smoother.h */
