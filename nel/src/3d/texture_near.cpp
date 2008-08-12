/** \file texture_near.cpp
 * TODO: File description
 *
 * $Id: texture_near.cpp,v 1.8 2005/02/22 10:19:12 besson Exp $
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


#include "texture_near.h"
using namespace NLMISC;

namespace NL3D 
{


// ***************************************************************************
CTextureNear::CTextureNear(sint size)
{
	nlassert(size>=NL_TILE_LIGHTMAP_SIZE);
	nlassert(NLMISC::isPowerOf2(size));

	// The near texture always reside in memory...
	// NB: this is simplier like that, and this is not a problem, since only 1 or 2 Mo are allocated :o)
	setReleasable(false);
	// create the bitmap.
	CBitmap::resize(size, size, CBitmap::RGBA);
	// Format of texture, 32 bits and no mipmaps.
	setUploadFormat(ITexture::RGBA8888);
	setFilterMode(ITexture::Linear, ITexture::LinearMipMapOff);

	// Fill the array of free tiles.
	uint	nbTilesByLine= size/NL_TILE_LIGHTMAP_SIZE;
	_FreeTiles.resize(nbTilesByLine*nbTilesByLine);
	_AvailableTiles.resize(nbTilesByLine*nbTilesByLine);
	for(sint i=0;i<(sint)_FreeTiles.size();i++)
	{
		// This tile is free!!
		_FreeTiles[i]=i;
		_AvailableTiles[i]= true;
	}

}

// ***************************************************************************
sint			CTextureNear::getNbAvailableTiles()
{
	return _FreeTiles.size();
}
// ***************************************************************************
uint			CTextureNear::getTileAndFillRect(CRGBA  map[NL_TILE_LIGHTMAP_SIZE*NL_TILE_LIGHTMAP_SIZE])
{
	nlassert(getNbAvailableTiles()>0);
	uint	id= _FreeTiles.back();
	// This tile is now more free.
	_AvailableTiles[id]= false;
	_FreeTiles.pop_back();

	// Fill the texture
	refillRect(id, map);

	return id;
}

// ***************************************************************************
void			CTextureNear::refillRect(uint id, CRGBA  map[NL_TILE_LIGHTMAP_SIZE*NL_TILE_LIGHTMAP_SIZE])
{
	uint	dstWidth= getWidth();
	// Copy the map into the texture
	uint	nbTilesByLine= dstWidth/NL_TILE_LIGHTMAP_SIZE;
	uint	s= id% nbTilesByLine;
	uint	t= id/ nbTilesByLine;
	s*= NL_TILE_LIGHTMAP_SIZE;
	t*= NL_TILE_LIGHTMAP_SIZE;
	CRGBA	*src= map;
	CRGBA	*dst= (CRGBA*)getPixels().getPtr();
	dst+= t*dstWidth+s;
	for(sint n= NL_TILE_LIGHTMAP_SIZE;n>0;n--, src+= NL_TILE_LIGHTMAP_SIZE, dst+= dstWidth)
	{
		memcpy(dst, src, NL_TILE_LIGHTMAP_SIZE*sizeof(CRGBA));
	}

	// Invalidate the rectangle.
	ITexture::touchRect(CRect(s, t, NL_TILE_LIGHTMAP_SIZE, NL_TILE_LIGHTMAP_SIZE));
}

// ***************************************************************************
void			CTextureNear::releaseTile(uint id)
{
	nlassert(!_AvailableTiles[id]);
	// This tile is now free.
	_AvailableTiles[id]= true;
	// insert this tile at the end of the free list.
	_FreeTiles.push_back(id);
}


} // NL3D
