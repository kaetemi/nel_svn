/** \file texture_cube.h
 * Cube mapping (6 maps around the object)
 *
 * $Id: texture_cube.h,v 1.9 2006/09/14 16:56:08 cado Exp $
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

#ifndef NL_TEXTURE_CUBE_H
#define NL_TEXTURE_CUBE_H

#include "nel/misc/types_nl.h"
#include "nel/3d/texture.h"


namespace NL3D
{


//****************************************************************************
/**
 * CTextureCube
 * \author Matthieu Besson
 * \author Nevrax France
 * \date 2000
 */
class CTextureCube : public ITexture
{
public:

	enum TFace { positive_x=0, negative_x, positive_y, negative_y, positive_z, negative_z };

public:

	/** 
	 * Default constructor
	 */	
	CTextureCube();


	/** 
	 * Accessors
	 */	
	void setTexture(TFace f, ITexture *t);
	ITexture* getTexture(TFace f) { return _Textures[f]; }


	/** 
	 * Set the name of the file containing the texture
	 * \param name of the file
	 */	
	//void setFileName(std::string s);


	/** 
	 * sharing system.
	 */	
	virtual bool			supportSharing() const {return true;}
	virtual std::string		getShareName() const;


	/** 
	 * Generate the texture, looking in CPath if necessary.
	 */	
	void doGenerate(bool async = false);

	virtual void release();
	/// Does this texture is a cube texture
	virtual bool isTextureCube() const { return true; }

	/// Save the texture file name.
	virtual void	serial(NLMISC::IStream &f) throw(NLMISC::EStream);
	NLMISC_DECLARE_CLASS(CTextureCube);

	/// If the face support multiple texture (such has CTextureMultiFile), this allow to select the active set
	virtual void selectTexture(uint index);
	// from ITexture
	virtual bool isSelectable() const;
	// from ITexture
	virtual ITexture		*buildNonSelectableVersion(uint index);


private:
	NLMISC::CSmartPtr<ITexture> _Textures[6];
};


} // NL3D


#endif // NL_TEXTURE_CUBE_H

/* End of texture_cube.h */
