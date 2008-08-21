/** \file patchuv_locator.h
 * TODO: File description
 *
 * $Id: patchuv_locator.h,v 1.6 2005/02/22 10:19:11 besson Exp $
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

#ifndef NL_PATCHUV_LOCATOR_H
#define NL_PATCHUV_LOCATOR_H

#include "nel/misc/types_nl.h"
#include "nel/3d/patch.h"
#include "nel/misc/vector_2f.h"


namespace NL3D 
{


// ***************************************************************************
/**
 * From a patch and UV coordinate in [0,OrderS], [0,OrderT], retrieve the appropriate coordinate in neighborhood.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CPatchUVLocator
{
public:

	// build information for a patch and his 1 to 4 neigbhor on a edge.
	void	build(const CPatch *patchCenter, sint edgeCenter, CPatch::CBindInfo	&bindInfo);


	// for an uv given in src patch basis, find the associate patch.
	uint	selectPatch(const NLMISC::CVector2f &uvIn);


	// for an uv given in src patch basis, and the number of patch we want (for bind 1/X, see selectPatch),
	// find the neighbor UV, and the neighbor patch.
	void	locateUV(const NLMISC::CVector2f &uvIn, uint patch, CPatch *&patchOut, NLMISC::CVector2f &uvOut);


	/** return true only if the 2 edges have same number of tiles.
	 *	bind 1/X case: return true only if ALL the adjacents patchs respect this rule. So you are sure that
	 *	for all the src patch, one tile has exaclty one neighbor tile near him.
	 */
	bool	sameEdgeOrder() const {return _SameEdgeOrder;}


private:

	struct	CUVBasis
	{
		NLMISC::CVector2f	UvI, UvJ, UvP;

		void	mulPoint(const NLMISC::CVector2f &uvIn, NLMISC::CVector2f &uvOut)
		{
			uvOut= UvP + uvIn.x * UvI + uvIn.y * UvJ;
		}
	};

private:
	CPatch				*_CenterPatch;
	sint				_CenterPatchEdge;
	sint				_NPatchs;
	CPatch				*_NeighborPatch[4];
	CUVBasis			_NeighborBasis[4];
	bool				_SameEdgeOrder;


};


} // NL3D


#endif // NL_PATCHUV_LOCATOR_H

/* End of patchuv_locator.h */
