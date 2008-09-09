/** \file texture_bump.h
 * TODO: File description
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

#ifndef NL_TEXTURE_BUMP_H
#define NL_TEXTURE_BUMP_H

#include "nel/misc/types_nl.h"
#include "nel/3d/texture.h"

namespace NL3D {


/**
 * This texture is a helper to build a DsDt texture from a height map (provided it is supported by hardware)
 * The height map should be convertible to a RGBA bitmap
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class CTextureBump : public ITexture
{
public:
	NLMISC_DECLARE_CLASS(CTextureBump);
	/// ctor
	CTextureBump();
	/// dtor
	~CTextureBump();

	/// set the height map used to generate this bump map
	void				setHeightMap(ITexture *heightMap);
	/// get the height map used to generate this bumpmap
	ITexture			*getHeightMap() { return _HeightMap; };
	/// get the height map used to generate this bumpmap (const version)
	const ITexture		*getHeightMap() const { return _HeightMap; };

	// serial this texture datas
	virtual void	serial(NLMISC::IStream &f) throw(NLMISC::EStream);

	virtual bool			supportSharing() const;

	virtual std::string		getShareName() const;

	void					enableSharing(bool enabled = true) { _DisableSharing = !enabled; }

	bool					isSharingEnabled() const { return !_DisableSharing; }


	/** Force normalization of this texture when it is generated, so that the deltas reach their maximum amplitude.
	  * After the texture generation, the factor needed to normalize can be obtained
	  */
	void					forceNormalize(bool force = true) { _ForceNormalize = force; }

	/// Test wether normalization is forced with that texture
	bool				    isNormalizationForced() const { return _ForceNormalize; }

	/** Get the normalization factor. This is valid only if the texture has been generated
	  * NB : make this virtual because it access static object (_NameToNF) from both DLL and main app, so don't want duplication
	  */
	virtual float					getNormalizationFactor();

	// inherited from ITexture. release this texture, and its datas
	virtual void release();

	// this is a bump texture
	virtual bool isBumpMap() const { return true; }

protected:
	// inherited from ITexture. Generate this bumpmap pixels
	virtual void doGenerate(bool async = false);
	NLMISC::CSmartPtr<ITexture>  _HeightMap;
	float						 *_NormalizationFactor;
	bool						 _DisableSharing;
	bool						 _ForceNormalize;
	// Map that give the normalization factor for each map from its sharename. This avoid to generate several time the maps to get the normalization factor if a bumpmap is shared by severals CTextureBump instances;
	struct CNormalizationInfo
	{
		uint  NumRefs;
		float NormalizationFactor;
	};
	typedef std::map<std::string, CNormalizationInfo> TNameToNI; // sharename to the normalization factor
	static TNameToNI	_NameToNF; // name to normalization factor
private:
	/// we don't allow for mipmap for bump so we redefine this to prevent the user from doing this on the base class Itexture
	virtual         void setFilterMode(TMagFilter magf, TMinFilter minf);
};


} // NL3D


#endif // NL_TEXTURE_BUMP_H

/* End of texture_bump.h */
