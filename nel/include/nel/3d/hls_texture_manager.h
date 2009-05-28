/** \file hls_texture_manager.h
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

#ifndef NL_HLS_TEXTURE_MANAGER_H
#define NL_HLS_TEXTURE_MANAGER_H

#include "nel/misc/types_nl.h"
#include "nel/3d/hls_texture_bank.h"


namespace NL3D
{


// ***************************************************************************
/**
 * This is a list of banks of colorisable textures.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CHLSTextureManager
{
public:

	/// Constructor
	CHLSTextureManager();
	~CHLSTextureManager();

	void			reset();

	/// Add a compiled bank. Ptr is owned and deleted by the manager.
	void			addBank(CHLSTextureBank *bank);

	/** search a texture name in the banks (case insensitive), and return its id.
	 *	\param name a texture file name. NB: name is case-lowered first. (case-insensitive)
	 *	\return -1 if not found, else return the id.
	 */
	sint			findTexture(const std::string &name) const;

	/** build the colored version bitmap of a texture
	 *	\param textId a texture id returned by findTexture()
	 *	\return false if not found
	 */
	bool			buildTexture(sint textId, NLMISC::CBitmap &out) const;

	/// Texture name access
	uint			getNumTextures() const {return _Instances.size();}
	const char		*getTextureName(uint i) const;

private:

	// List of banks
	std::vector<CHLSTextureBank *>		_Banks;

	// Sorted Array of texture instances.
	std::vector<CHLSTextureBank::CTextureInstanceHandle>		_Instances;

};


} // NL3D


#endif // NL_HLS_TEXTURE_MANAGER_H

/* End of hls_texture_manager.h */
