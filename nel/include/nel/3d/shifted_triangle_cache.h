/** \file shifted_triangle_cache.h
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

#ifndef NL_SHIFTED_TRIANGLE_CACHE_H
#define NL_SHIFTED_TRIANGLE_CACHE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/object_vector.h"
#include "nel/3d/index_buffer.h"


namespace NL3D
{


// ***************************************************************************
/**
 * This is a cache of indices which are the copy of CMesh/CMeshMRM indices, but shifted according to a value.
 *	This is useful for skinning.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CShiftedTriangleCache
{
public:
	struct	CRdrPass
	{
		/// Point to CShiftedTriangleCache::Triangles
		uint32				Triangles;
		uint32				NumTriangles;
	};

public:
	/// The Raw triangles array
	CIndexBuffer								RawIndices;
	/// List of triangles, per rdrPass
	NLMISC::CObjectVector<CRdrPass, false>		RdrPass;

	/// What MRM lod this cache represent. -1 if NULL
	sint					LodId;
	/// To see if same Data than in the CMeshMRMGeom
	uint					MeshDataId;
	/// the shift value used to compute this indices.
	uint					BaseVertex;

	// free up the memory
	void				clearArrays();

	// ctor
	CShiftedTriangleCache()
	{
		NL_SET_IB_NAME(RawIndices, "CShiftedTriangleCache");
	}

};


} // NL3D


#endif // NL_SHIFTED_TRIANGLE_CACHE_H

/* End of shifted_triangle_cache.h */
