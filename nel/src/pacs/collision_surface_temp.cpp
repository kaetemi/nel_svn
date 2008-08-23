/** \file collision_surface_temp.cpp
 * Temp collision data used during resolution of collision within surfaces.
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

#include "stdpacs.h"

#include "collision_surface_temp.h"


namespace NLPACS
{


// ***************************************************************************
const	uint32	StartEdgeCollideNodeSize= 128;		// mem: 48*128= 6144
const	uint32	StartCollisionChainSize= 128;		// mem: 24*128= 3072
const	uint32	StartEdgeChainEntrySize= 1024;		// mem: 6*1024= 6144
const	uint32	StartCollisionDescSize= 64;			// mem: 36*64= 2304
const	uint32	StartCollisionInstanceSize= 64;		// mem: 4*64= 256
// Total default memory cost by CCollisionSurfaceTemp: 18Ko + 128Ko  (OChainLUT).


// ***************************************************************************
CCollisionSurfaceTemp::CCollisionSurfaceTemp()
{
	memset(OChainLUT, 0xFF, 65536*sizeof(uint16));
	memset(SurfaceLUT, 0x00, 65536*sizeof(CSurfaceLUTEntry));
	_EdgeCollideNodes.reserve(StartEdgeCollideNodeSize);
	CollisionChains.reserve(StartCollisionChainSize);
	EdgeChainEntries.reserve(StartEdgeChainEntrySize);
	CollisionDescs.reserve(StartCollisionDescSize);
	MoveDescs.reserve(StartCollisionDescSize);
	RotDescs.reserve(StartCollisionDescSize);
	CollisionInstances.reserve(StartCollisionInstanceSize);
	PossibleSurfaces.reserve(32);
	PrecValid= false;
	OutCounter = 0;
}


// ***************************************************************************
void				CCollisionSurfaceTemp::resetEdgeCollideNodes()
{
	_EdgeCollideNodes.clear();
}
// ***************************************************************************
uint32				CCollisionSurfaceTemp::allocEdgeCollideNode(uint32 size)
{
	uint32	id= _EdgeCollideNodes.size();
	_EdgeCollideNodes.resize(id+size);
	return id;
}
// ***************************************************************************
CEdgeCollideNode	&CCollisionSurfaceTemp::getEdgeCollideNode(uint32 id)
{
	return _EdgeCollideNodes[id];
}


} // NLPACS
