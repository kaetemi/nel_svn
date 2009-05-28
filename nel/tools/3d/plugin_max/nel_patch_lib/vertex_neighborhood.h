/** \file vertex_neighborhood.h
 * Container to get neigborhood information.
 *
 * $Id: vertex_neighborhood.h,v 1.2 2004/11/15 10:25:11 lecroart Exp $
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

#ifndef NL_VERTEX_NEIGHBORHOOD_H
#define NL_VERTEX_NEIGHBORHOOD_H

#include "nel/misc/types_nl.h"

#include <vector>

class PatchMesh;

/**
 * TODO Class description
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CVertexNeighborhood
{
public:
	// Default constructor reserve a good array.
	CVertexNeighborhood ();

	// build it 
	void build (const PatchMesh& patch);

	// Get neighbor index
	uint getNeighborCount (uint neighborId) const
	{
		return _VectorIndex[2*neighborId];
	}

	// Get neighbor index
	uint& getNeighborCountRef (uint neighborId)
	{
		return _VectorIndex[2*neighborId];
	}

	// Get neighbor list
	const uint* getNeighborList (uint neighborId) const
	{
		// Const iterator
		std::vector<uint>::const_iterator ite=_VectorIndex.begin();
		return (&*ite) + getNeighborIndex (neighborId);
	}

	// Get neighbor list
	uint* getNeighborList (uint neighborId)
	{
		return &_VectorIndex[getNeighborIndex (neighborId)];
	}

	// Get neighbor count
	uint getNeighborIndex (uint neighborId) const
	{
		return _VectorIndex[2*neighborId+1];
	}

	// Get neighbor count
	uint& getNeighborIndexRef (uint neighborId)
	{
		return _VectorIndex[2*neighborId+1];
	}
private:
	std::vector<uint>	_VectorIndex;
};

extern CVertexNeighborhood vertexNeighborhoodGlobal;

#endif // NL_VERTEX_NEIGHBORHOOD_H

/* End of vertex_neighborhood.h */
