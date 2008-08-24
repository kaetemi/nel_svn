/** \file u_visual_collision_mesh.cpp
 * TODO: File description
 */

/* Copyright, 2000-2003 Nevrax Ltd.
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

#include "nel/3d/u_visual_collision_mesh.h"
#include "nel/3d/visual_collision_mesh.h"


namespace NL3D
{


// ***************************************************************************
UVisualCollisionMesh::UVisualCollisionMesh() : _Mesh(NULL)
{
}

// ***************************************************************************
void			UVisualCollisionMesh::attach(class CVisualCollisionMesh	*mesh)
{
	_Mesh= mesh;
}

// ***************************************************************************
const std::vector<NLMISC::CVector> &UVisualCollisionMesh::getVertices() const
{
	return _Mesh->getVertices();
}

// ***************************************************************************
const std::vector<uint16> &UVisualCollisionMesh::getTriangles() const
{
	return _Mesh->getTriangles();
}


} // NL3D
