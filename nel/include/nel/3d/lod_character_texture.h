/** \file lod_character_texture.h
 * Lod Texture Descriptor
 *
 * $Id: lod_character_texture.h,v 1.1 2002/11/08 18:41:58 berenguier Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_LOD_CHARACTER_TEXTURE_H
#define NL_LOD_CHARACTER_TEXTURE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"


namespace NL3D
{


// ***************************************************************************
// A lod texture is 32*32 pixels. => 256 lods takes 500Ko in VRAM (16 bits)
#define	NL3D_CLOD_TEXT_WIDTH	32
#define	NL3D_CLOD_TEXT_HEIGHT	32
#define	NL3D_CLOD_TEXT_SIZE		NL3D_CLOD_TEXT_WIDTH*NL3D_CLOD_TEXT_HEIGHT


// ***************************************************************************
/**
 * This describe Texturing information for CLods. It is stored in .shape.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CLodCharacterTexture
{
public:

	/// The Texture UV Quality info per pixel.
	struct	CTUVQ
	{
		// This is an index on the material in the Mesh. The stage0 texture is taken from this material.
		uint8	T;
		// This is the compressed UV which index the pixel in the texture. NB: Ignored if the material is not textured.
		uint8	U,V;
		// The lower, the better. This said how near this pixel is from the shape vertex.
		uint8	Q;

		void		serial(NLMISC::IStream &f)
		{
			f.serial(T,U,V,Q);
		}
	};

public:
	// Lookup information.
	std::vector<CTUVQ>		Texture;


public:
	/// Constructor
	CLodCharacterTexture();
	uint		getWidth() const {return _Width;}
	uint		getHeight() const {return _Height;}

	void		serial(NLMISC::IStream &f);

// ****************
private:
	// Serialized width / Height. This must be equal to NL3D_CLOD_TEXT_WIDTH/NL3D_CLOD_TEXT_HEIGHT
	uint32					_Width, _Height;

};


} // NL3D


#endif // NL_LOD_CHARACTER_TEXTURE_H

/* End of lod_character_texture.h */
