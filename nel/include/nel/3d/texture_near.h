/** \file texture_near.h
 * TODO: File description
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

#ifndef NL_TEXTURE_NEAR_H
#define NL_TEXTURE_NEAR_H

#include "nel/misc/types_nl.h"
#include "nel/misc/common.h"
#include "nel/3d/texture.h"


// Size of a TileLightmap. Must be 10 now, because we have 2x2 tiles per Tilelightmap.
#define NL_TILE_LIGHTMAP_SIZE	10


namespace NL3D
{


using NLMISC::CRGBA;

// ***************************************************************************
/**
 * A texture container for lot of little lightmap.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CTextureNear : public ITexture
{
public:

	/// Constructor
	CTextureNear(sint size);

	/// Since texture is always in memory...
	void			doGenerate(bool /* async */)
	{
		// Do nothing. texture still in memory... :o)
	}

	/// \name Tile Lightmap mgt.
	// @{
	sint			getNbAvailableTiles();
	/** return the id of the tile, locally in the texture.
	 * nlassert() if no free tiles (use getNbAvailableTiles()).
	 * Tile coordinate in the texture can be get with:
	 * s= id% nbTilesByLine;
	 * t= id/ nbTilesByLine;
	 * where nbTilesByLine== sizeOfTextureNear/NL_TILE_LIGHTMAP_SIZE.
	 * The texture is invalidate (on this part only...)
	 */
	uint			getTileAndFillRect(CRGBA  map[NL_TILE_LIGHTMAP_SIZE*NL_TILE_LIGHTMAP_SIZE]);

	/** given id of the tile, refill the texture.
	 * The texture is invalidate (on this part only...)
	 */
	void			refillRect(uint id, CRGBA  map[NL_TILE_LIGHTMAP_SIZE*NL_TILE_LIGHTMAP_SIZE]);

	/// Set a tile lightmap as free for use. It is an error to free a not allocated tile. (nlassert!!)
	void			releaseTile(uint id);
	// @}

	/// TextureNear are system. Do not need to serialize them...
	// default ctor is required for compilation with NLMISC_DECLARE_CLASS, but never called...
	CTextureNear() {nlstop;}
	virtual void	serial(NLMISC::IStream &/* f */) throw(NLMISC::EStream) {nlstop;}
	NLMISC_DECLARE_CLASS(CTextureNear);

private:
	/// The list of available tiles.
	std::vector<uint>	_FreeTiles;
	/// For check, Availability of tiles.
	std::vector<bool>	_AvailableTiles;
};


} // NL3D


#endif // NL_TEXTURE_NEAR_H

/* End of texture_near.h */
