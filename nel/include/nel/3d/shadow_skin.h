/** \file shadow_skin.h
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

#ifndef NL_SHADOW_SKIN_H
#define NL_SHADOW_SKIN_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/vector.h"
#include "nel/3d/matrix_3x4.h"

namespace NL3D
{


// ***************************************************************************
/**
 * Vertex for CShadowSkin
 */
class		CShadowVertex
{
public:
	CVector		Vertex;
	uint32		MatrixId;
	void		serial(NLMISC::IStream &f)
	{
		(void)f.serialVersion(0);

		f.serial(Vertex);
		f.serial(MatrixId);
	}

	// operator for sort
	bool		operator==(const CShadowVertex &v) const
	{
		return MatrixId==v.MatrixId && Vertex==v.Vertex;
	}
	bool		operator<(const CShadowVertex &v) const
	{
		if(MatrixId!=v.MatrixId)
			return MatrixId<v.MatrixId;
		else
			return Vertex<v.Vertex;
	}
};


// ***************************************************************************
/**
 * Simple Skinning for shadow map rendering
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2004
 */
class CShadowSkin
{
public:
	std::vector<CShadowVertex>		Vertices;
	std::vector<uint32>				Triangles;

public:

	// skinning
	void		applySkin(NLMISC::CVector *dst, std::vector<CMatrix3x4> &boneMat3x4);

	/** return ray intersection.
 	 *	\return false if no triangles, true if can do the test (even if don't intersect!)
	 *	if intersect, dist2D=0, and distZ= Depth Distance
	 *	if don't intersect, dist2D="nearest distance to the ray", and distZ=0
	 *	\param computeDist2D if false and don't intersect, then return dist2D=FLT_MAX, and distZ=0
	 */
	bool		getRayIntersection(const CMatrix &toRaySpace, class CSkeletonModel &skeleton,
		const std::vector<uint32> &matrixInfluences, float &dist2D, float &distZ, bool computeDist2D);

private:
	static  uint	NumCacheVertexShadow;

};


} // NL3D


#endif // NL_SHADOW_SKIN_H

/* End of shadow_skin.h */
