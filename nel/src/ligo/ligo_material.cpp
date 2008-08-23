/** \file ligo_material.cpp
 * A ligoscape material
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

#include "ligo_material.h"

// Ligo include
#include "ligo_error.h"

//using namespace NL3D;

namespace NLLIGO
{

// ***************************************************************************

bool CMaterial::build (const CZoneTemplate &tplt, const CLigoConfig &config, CLigoError &errors)
{
	// Clear errors
	errors.clear ();

	// Edge vector
	const std::vector<CZoneEdge> &edges = tplt.getEdges ();

	// This template should have 4 edges
	if (edges.size() != 4)
	{
		errors.MainError = CLigoError::MustHave4Edges;
		return false;
	}

	// The 1st edge must be symetrical
	if (!edges[0].isSymetrical (config, errors))
		return false;

	// Error code
	bool ok = true;

	// The others must be the same edges
	uint edge;
	for (edge=1; edge<edges.size(); edge++)
	{
		// The same edge ?
		if (!edges[0].isTheSame (edges[edge], config, errors))
		{
			// Error
			ok = false;
		}
	}

	// Build ?
	if (ok)
	{
		// Ok, build the material
		_ZoneEdge = edges[0];
	}

	// Return error code
	return ok;
}

// ***************************************************************************

void CMaterial::serial (NLMISC::IStream &s)
{
	// Serial the main node
	s.xmlPush ("LIGO_MATERIAL");

		// Serial the header
		s.serialCheck ((uint32)'TMOL');

		// Serial the version
		/*sint ver =*/ s.serialVersion (0);

		// Serial the zoneedge
		s.xmlSerial (_ZoneEdge, "ZONE_EDGE");

	// Close the main node
	s.xmlPop ();
}

// ***************************************************************************

}
