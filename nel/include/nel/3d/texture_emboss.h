/** \file texture_emboss.h
 *
 * $Id: texture_emboss.h,v 1.4 2005/02/22 10:19:12 besson Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
 *
 * This file is part of NEVRAX RYZOM.
 * NEVRAX RYZOM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX RYZOM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX RYZOM; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_TEXTURE_EMBOSS_H
#define NL_TEXTURE_EMBOSS_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
//
#include "texture.h"

namespace NL3D {


/**
 * This texture is a helper to build a embossed texture from a height map. 
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2003
 */
class CTextureEmboss : public ITexture
{
public:
	NLMISC_DECLARE_CLASS(CTextureEmboss);
	/// ctor
	CTextureEmboss();

	/// set the height map used to generate this bump map
	void				setHeightMap(ITexture *heightMap);
	/// get the height map used to generate this bumpmap
	ITexture			*getHeightMap() { return _HeightMap; };
	/// get the height map used to generate this bumpmap (const version)
	const ITexture		*getHeightMap() const { return _HeightMap; };

	// serial this texture datas
	virtual void			serial(NLMISC::IStream &f) throw(NLMISC::EStream);	
	virtual bool			supportSharing() const;	
	virtual std::string		getShareName() const;
	//
	void					enableSharing(bool enabled = true) { _DisableSharing = !enabled; }
	bool					isSharingEnabled() const { return !_DisableSharing; }

	// set the ambiant/ diffuse color to be added to the embossed texture
	void					setAmbient(CRGBA ambient) { _Ambient = ambient; touch(); }
	void					setDiffuse(CRGBA diffuse) { _Diffuse = diffuse; touch(); }
	// Set the direction of light (usually should be normalized). The bitmap is in the x,y plane
	void					setLightDir(const NLMISC::CVector &lightDir) { _LightDir = lightDir; touch(); }
	// set a factor for the slope
	void                    setSlopeFactor(float factor) { _SlopeFactor = factor; touch(); }	
	// 
	CRGBA					getAmbient() const { return _Ambient; }	
	CRGBA					getDiffuse() const { return _Diffuse; }	
	const CVector		   &getLightDir() const { return _LightDir; }	
	float					getSlopeFactor() const { return _SlopeFactor; }
	
	
	// inherited from ITexture. release this texture, and its datas
	virtual void release();	
	
	
protected:
	// inherited from ITexture. Generate this bumpmap pixels
	virtual void doGenerate(bool async = false);	
	NLMISC::CSmartPtr<ITexture> _HeightMap;	
	CRGBA						_Ambient;
	CRGBA						_Diffuse;
	NLMISC::CVector				_LightDir;
	bool						_DisableSharing;
	float						_SlopeFactor;
};


} // NL3D

#endif
