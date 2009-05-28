/** \file visual_collision_manager_user.cpp
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

#include "nel/3d/visual_collision_manager_user.h"
#include "nel/3d/u_visual_collision_mesh.h"


namespace NL3D {


// ***************************************************************************
uint		CVisualCollisionManagerUser::addMeshInstanceCollision(const UVisualCollisionMesh &mesh, const NLMISC::CMatrix &instanceMatrix, bool avoidCollisionWhenInside, bool avoidCollisionWhenOutside)
{
	// if empty proxy abort
	if(mesh.empty())
		return 0;
	return _Manager.addMeshInstanceCollision(mesh.getMeshPtr(), instanceMatrix, avoidCollisionWhenInside, avoidCollisionWhenOutside);
}

// ***************************************************************************
void CVisualCollisionManagerUser::getMeshs(const NLMISC::CAABBox &aabbox, std::vector<CMeshInstanceColInfo> &dest)
{
	static std::vector<CVisualCollisionManager::CMeshInstanceColInfo> colInfos;
	_Manager.getMeshs(aabbox, colInfos);
	dest.resize(colInfos.size());
	for(uint k = 0; k < colInfos.size(); ++k)
	{
		dest[k].Mesh.attach(colInfos[k].Mesh);
		dest[k].WorldMatrix = colInfos[k].WorldMatrix;
		dest[k].ID = colInfos[k].ID;
		dest[k].WorldBBox = colInfos[k].WorldBBox;
	}
}


} // NL3D





















