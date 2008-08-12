/** \file mrm_level_detail.h
 * TODO: File description
 *
 * $Id: mrm_level_detail.h,v 1.3 2004/11/15 10:24:45 lecroart Exp $
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

#ifndef NL_MRM_LEVEL_DETAIL_H
#define NL_MRM_LEVEL_DETAIL_H

#include "nel/misc/types_nl.h"
#include "nel/misc/common.h"


namespace NL3D 
{


// ***************************************************************************
/* This is used to have correct max Polygon count setuped. This suppose that MRM.NumLod==10
	Hence, a mean value of 0.5*1/10 is used
*/
#define	NL3D_MRM_LD_SHIFT_POLY_COUNT	0.05f


// ***************************************************************************
/**
 * Degradation Control for MRM. used by CMeshMRM and CSkeletonModel
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CMRMLevelDetail
{
public:

	/// For Load balancing, the min number of faces this MRM use.
	uint32				MinFaceUsed;
	/// For Load balancing, the max number of faces this MRM use.
	uint32				MaxFaceUsed;

	/// The MRM has its max faces when dist<=DistanceFinest. nlassert if <0.
	float				DistanceFinest;
	/// The MRM has 50% of its faces at dist==DistanceMiddle. nlassert if <= DistanceFinest.
	float				DistanceMiddle;
	/// The MRM has faces/Divisor when dist>=DistanceCoarsest. nlassert if <= DistanceMiddle.
	float				DistanceCoarsest;

	/// compiled info (public for faster serial)
	float				OODistanceDelta;
	float				DistancePow;

public:
	/// Constructor
	CMRMLevelDetail() {}

	/// compile OODistanceDelta and DistancePow
	void				compileDistanceSetup();

	/// return a float [0,1], computed from a distance (should be >0).
	float				getLevelDetailFromDist(float dist);

	/// return number of triangles for a distance
	float				getNumTriangles (float dist)
	{
		// return the lod detail [0,1].
		float	ld= getLevelDetailFromDist(dist);
		// return in nb face.
		if(ld<=0)
			return (float)MinFaceUsed;
		else
		{
			/* over-estimate the number of poly rendered 
				because this is always the higher Lod which is rendered, geomorphing to the coarser one.
				NB: still need to over-estimate if ld==1, because getLevelDetailFromPolyCount() remove the shift...
			*/
			ld+= NL3D_MRM_LD_SHIFT_POLY_COUNT;
			return MinFaceUsed + ld * (MaxFaceUsed - MinFaceUsed);
		}
	}

	/// return a float [0,1], computed from number of poly wanted (should be >0)
	float				getLevelDetailFromPolyCount(float polygonCount)
	{
		float	ld;
		if(MaxFaceUsed > MinFaceUsed)
		{
			// compute the level of detail we want.
			ld= (polygonCount - MinFaceUsed) / (MaxFaceUsed - MinFaceUsed);
			/* remove the value added in getNumTriangles(). For the same reason:
				this is always the higher Lod which is rendered, geomorphing to the coarser one.
				Hence we must degrade a bit.
				NB: if polygonCount==MinFaceUsed, then we have here ld= -NL3D_MRM_LD_SHIFT_POLY_COUNT (ie -0.05f)
				but it is clamped below
			*/
			ld-= NL3D_MRM_LD_SHIFT_POLY_COUNT;
			NLMISC::clamp(ld, 0, 1);
		}
		else
			ld= 1;

		return ld;
	}

};


} // NL3D


#endif // NL_MRM_LEVEL_DETAIL_H

/* End of mrm_level_detail.h */
