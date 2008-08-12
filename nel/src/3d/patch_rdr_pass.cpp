/** \file patch_rdr_pass.cpp
 * TODO: File description
 *
 * $Id: patch_rdr_pass.cpp,v 1.15 2005/02/22 10:19:11 besson Exp $
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

#include "patch_rdr_pass.h"
#include "index_buffer.h"


namespace NL3D 
{


// ***************************************************************************
CRdrTileId::CRdrTileId()
{
	PatchRdrPass= NULL;
	TileMaterial= NULL;
	_Next= NULL;
}


// ***************************************************************************
CPatchRdrPass::CPatchRdrPass()
{
	RefCount= 0;

	clearAllRenderList();
}


// ***************************************************************************
void	CPatchRdrPass::clearAllRenderList()
{
	_MaxRenderedFaces= 0;
	_Far0ListRoot= NULL;
	_Far1ListRoot= NULL;
	for(uint i=0;i<NL3D_MAX_TILE_PASS; i++)
	{
		_TileListRoot[i]= NULL;
	}
}


} // NL3D
