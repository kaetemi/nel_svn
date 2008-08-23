/** \file zone_template.h
 * Ligo zone template definition
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

#ifndef NL_ZONE_TEMPLATE_H
#define NL_ZONE_TEMPLATE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"

#include "zone_edge.h"

#include <map>

namespace NLLIGO
{

class CLigoConfig;
class CLigoError;

/**
 * Ligo zone template
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CZoneTemplate
{
public:

	/**
	  * Build method. Build the zone template with a vertex list and an edge list.
	  *
	  * \param vertices is the vertex array
	  * \param indexes is the edge array
	  * \param config is the current lingo config file
	  * \param errors is the error structure
	  * \return true if the build success, else return false
	  */
	bool build (const std::vector<NLMISC::CVector> &vertices, const std::vector< std::pair<uint, uint> > &indexes, const CLigoConfig &config, CLigoError &errors);

	/// Serialisation
	void serial (NLMISC::IStream& s);

	/// Get the vertex array of the template
	const std::vector<CZoneEdge>	&getEdges () const { return _Edges; }

	/// Get the mask of the template
	void getMask (std::vector<bool> &mask, uint &width, uint &height);

private:

	/// Round a value on the snap resolution
	static inline void snap (float& value, float snap);
	
	/// Snap a value on the grid
	static inline bool snapOnGrid (float& value, float resolution, float snap);

	/// Return true if this value is snapped
	static inline bool isSnapedOnGrid (float value, float resolution, float snap);

	/// Return the interger index of a snappable value
	static inline sint32 getSnappedIndex (float value, float resolution, float snap);

	/// Vertex array
	std::vector<CZoneEdge>	_Edges;

};

}

#endif // NL_ZONE_TEMPLATE_H

/* End of zone_template.h */
