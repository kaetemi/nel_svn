/** \file u_visual_collision_mesh.h
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

#ifndef NL_U_VISUAL_COLLISION_MESH_H
#define NL_U_VISUAL_COLLISION_MESH_H

#include "nel/misc/types_nl.h"


namespace NL3D
{


// ***************************************************************************
/**
 * Proxy to a Collision Mesh possibly stored in a UShape
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2003
 */
class UVisualCollisionMesh
{
public:

	/// Proxy interface
	UVisualCollisionMesh();
	/// Attach a IShape to this proxy
	void			attach(class CVisualCollisionMesh	*mesh);
	/// return true if the proxy is empty() (not attached)
	bool			empty() const {return _Mesh==NULL;}
	/// For Advanced usage, get the Collision Mesh ptr
	class CVisualCollisionMesh	*getMeshPtr() const {return _Mesh;}
	// get vertices of the mesh
	const std::vector<NLMISC::CVector> &getVertices() const;
	// get triangles of the mesh
	const std::vector<uint16> &getTriangles() const;
private:
	class CVisualCollisionMesh	*_Mesh;

};


} // NL3D


#endif // NL_U_VISUAL_COLLISION_MESH_H

/* End of u_visual_collision_mesh.h */
