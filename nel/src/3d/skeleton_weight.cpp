/** \file skeleton_weight.cpp
 * TODO: File description
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

#include "std3d.h"

#include "nel/3d/skeleton_weight.h"
#include "nel/misc/stream.h"


namespace NL3D 
{


// ***************************************************************************

uint CSkeletonWeight::getNumNode () const
{
	return _Elements.size();
}

// ***************************************************************************

const std::string& CSkeletonWeight::getNodeName (uint node) const
{
	// Return the name of the n-th node
	return _Elements[node].Name;
}

// ***************************************************************************

float CSkeletonWeight::getNodeWeight (uint node) const
{
	// Return the name of the n-th node
	return _Elements[node].Weight;
}

// ***************************************************************************

void CSkeletonWeight::build (const TNodeArray& array)
{
	// Copy the array
	_Elements=array;
}

// ***************************************************************************

void CSkeletonWeight::serial (NLMISC::IStream& f)
{
	// Serial a header
	f.serialCheck ((uint32)'TWKS');

	// Serial a version number
	(void)f.serialVersion (0);

	// Serial the array
	f.serialCont (_Elements);
}

// ***************************************************************************

void CSkeletonWeight::CNode::serial (NLMISC::IStream& f)
{
	// Serial a version number
	(void)f.serialVersion (0);

	// Serial the name
	f.serial (Name);

	// Serial the weight
	f.serial (Weight);
}

// ***************************************************************************

} // NL3D
