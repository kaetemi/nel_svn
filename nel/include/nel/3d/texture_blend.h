/** \file texture_blend.h
 * A helper texture class to blend between 2 others textures.
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_TEXTURE_BLEND_H
#define NL_TEXTURE_BLEND_H

#include "nel/misc/types_nl.h"
#include "nel/3d/texture.h"


namespace NL3D {


/**
 * This is a helper texture that helps to blend between 2 others textures. It may help where sharing is needed.
 * (for example, with a texture that blend between day / night, and that is shared by several object). The default is
 * to have sharing enabled. 
 * NB : sharing is only supported if the 2 blending textures support sharing
 * IMPORTANT: you should setup all your blend texture after changing the blend factor to avoid previous texture
 * to be left in VRAM
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class CTextureBlend : public ITexture
{
public:	
	NLMISC_DECLARE_CLASS(CTextureBlend);
	/// ctor
	CTextureBlend();

	/// Set one of the textures between which to blend. If set to NULL, the result texture will be a dummy texture
	void			setBlendTexture(uint index, ITexture *tex);

	/// Get a blend texture
	ITexture		*getBlendtexture(uint index)	   { nlassert(index < 2); return (ITexture *) _BlendTex[index]; }
	const ITexture	*getBlendtexture(uint index) const { nlassert(index < 2); return (ITexture *) _BlendTex[index]; }

	/** Set the blend factor between textures. It must range from 0 to 256.
	  * \return true if the texture has been touched
	  */
	bool		setBlendFactor(uint16 factor);

	/// Get the blend factor between the textures (from 0 to 255)
	uint16	        getBlendFactor() const { return _BlendFactor; }

	///\name Texture sharing
	// @{
	virtual bool			supportSharing() const;	
	virtual std::string		getShareName() const;
	/// enable / disable sharing support
	void					enableSharing(bool enabled = false);
	/// test whether texture sharing is enabled
	bool					isSharingEnabled() const { return _SharingEnabled; }
	// @}

	/// Generate this texture data's.
	virtual void doGenerate(bool async);

	/// release this texture datas
	virtual void release();

	// serial this texture datas
	virtual void	serial(NLMISC::IStream &f) throw(NLMISC::EStream);

private:
	uint16						_BlendFactor;
	NLMISC::CSmartPtr<ITexture> _BlendTex[2];
	bool						_SharingEnabled;
};


} // NL3D


#endif // NL_TEXTURE_BLEND_H

/* End of texture_blend.h */
