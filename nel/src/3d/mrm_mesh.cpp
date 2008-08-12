/** \file mrm_mesh.cpp
 * Internal mesh for CMRMBuilder.
 *
 * $Id: mrm_mesh.cpp,v 1.8 2005/02/22 10:19:10 besson Exp $
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

#include "std3d.h"

#include "mrm_mesh.h"
#include <algorithm>

using namespace std;

namespace NL3D
{


// ***************************************************************************
uint CMRMMeshFinal::CWedge::NumAttributesToCompare= 0;
bool CMRMMeshFinal::CWedge::CompareSkinning= false;


// ***************************************************************************
CMRMMesh::CMRMMesh()
{
	NumAttributes= 0;
}



// ***************************************************************************
sint	CMRMMeshFinal::findInsertWedge(const CWedge &w)
{
	sint	ret;
	TWedgeMap::iterator		it;
	it= _WedgeMap.find(w);

	// if not found, must add it.
	if(it==_WedgeMap.end())
	{
		ret= Wedges.size();
		// insert into the map, with good id.
		_WedgeMap.insert(make_pair(w, ret));
		// add it to the array.
		Wedges.push_back(w);
	}
	else
	{
		ret= it->second;
	}

	return ret;
}

// ***************************************************************************
CMRMMeshFinal::CWedge::CWedge()
{
	Vertex = NLMISC::CVector::Null;
	NSkinMatUsed = 0;
	for (uint k = 0; k < NL3D_MRM_MAX_ATTRIB; ++k)
	{
		Attributes[k].set(0, 0, 0, 0);
	}
}

} // NL3D
