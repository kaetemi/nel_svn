/** \file async_texture_block.h
 * TODO: File description
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

#ifndef NL_ASYNC_TEXTURE_BLOCK_H
#define NL_ASYNC_TEXTURE_BLOCK_H

#include "nel/misc/types_nl.h"
#include "nel/3d/material.h"


namespace NL3D 
{


class CMeshBaseInstance;


// ***************************************************************************
/**
 * Descriptor of TextureFile Names.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CAsyncTextureBlock
{
public:
	// List of texture file name for a material
	std::string			TextureNames[IDRV_MAT_MAXTEXTURES];

	CAsyncTextureBlock()
	{
		for(uint i=0;i<IDRV_MAT_MAXTEXTURES;i++)
		{
			TextIds[i]= UINT_MAX; //-1;
			IsTextureFile[i]= false;
		}
	}
	bool				isTextureFile(uint stage) const {return IsTextureFile[stage];}

private:
	friend	class CMeshBaseInstance;
	// Ids in the CAsyncTextureManager
	uint				TextIds[IDRV_MAT_MAXTEXTURES];
	// true if the texture in the stage is really a texture file.
	bool				IsTextureFile[IDRV_MAT_MAXTEXTURES];

};


} // NL3D


#endif // NL_ASYNC_TEXTURE_BLOCK_H

/* End of async_texture_block.h */
