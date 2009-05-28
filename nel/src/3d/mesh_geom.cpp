/** \file mesh_geom.cpp
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

#include "nel/3d/mesh_geom.h"
#include "nel/3d/mesh_block_manager.h"


namespace NL3D
{


// ***************************************************************************
IMeshGeom::IMeshGeom()
{
	_RootInstanceId= -1;
	_MeshBlockManager= NULL;
	_MeshVBHeapId= 0;
	_MeshVBHeapNumVertices= 0;
}

// ***************************************************************************
IMeshGeom::~IMeshGeom()
{
	// If still have a VBHeap data in the manager, must free it.
	if(_MeshVBHeapId)
	{
		nlassert(_MeshBlockManager);
		_MeshBlockManager->freeMeshVBHeap(this);
	}
}


} // NL3D
