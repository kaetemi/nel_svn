/** \file zone_edge.h
 * A ZoneEdge descriptor
 *
 * $Id: zone_edge.h,v 1.1 2002/02/14 11:16:43 besson Exp $
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_ZONE_EDGE_H
#define NL_ZONE_EDGE_H

// NeL include
#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"

// STL include
#include <vector>

namespace NLMISC
{
	class IStream;
	class CMatrix;
}

namespace NLLIGO
{

class CLigoError;
class CLigoConfig;

/**
 * A ZoneEdge descriptor
 * 
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CZoneEdge
{
public:

	/// Build a edge zone
	bool build (const std::vector<NLMISC::CVector> &theEdge, const std::vector<uint32> &theId, uint rotation, 
				sint32 offsetX, sint32 offsetY, const CLigoConfig &config, CLigoError &errors);

	/// Serial
	void serial (NLMISC::IStream& s);

	/// Is symetrical ?
	bool isSymetrical (const CLigoConfig &config, CLigoError &errors) const;

	/// Is the same edge ?
	bool isTheSame (const CZoneEdge &other, const CLigoConfig &config, CLigoError &errors) const;

	/// Invert the edge
	void invert (const CLigoConfig &config);

	/// Return the vertex count
	uint getNumVertex () const { return _TheEdge.size(); }

	/// Return the vertex
	const NLMISC::CVector& getVertex (uint id) const { return _TheEdge[id]; }

	/// Return the matrix
	void buildMatrix (NLMISC::CMatrix& mat, const CLigoConfig &config) const;

	/// Get values
	uint32 getRotation () const { return _Rotation; }
	sint32 getOffsetX () const { return _OffsetX; }
	sint32 getOffsetY () const { return _OffsetY; }

private:

	/// The vector of position for this edge
	std::vector<NLMISC::CVector>	_TheEdge;

	/// Id of the vertices
	std::vector<uint32>				_Id;

	/// Rotation of the edge. Must be 0, 1, 2, 3. The rotation angle is Pi/2 * (double)_Rotation in CCW.
	uint32							_Rotation;

	/// X an Y offset of the edge. the position of the i-th vertex is rotate (_Rotation) * (theEdge[i], 0, 0) + (_OffsetX, _OffsetY, 0)
	sint32							_OffsetX;
	sint32							_OffsetY;
};

}

#endif // NL_ZONE_EDGE_H

/* End of zone_edge.h */
