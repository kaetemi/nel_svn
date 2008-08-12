/** \file texture_blank.h
 * TODO: File description
 *
 * $Id: texture_blank.h,v 1.5 2006/12/06 17:21:15 boucher Exp $
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

#ifndef NL_TEXTURE_BLANK_H
#define NL_TEXTURE_BLANK_H

#include "nel/misc/types_nl.h"
#include "texture.h"


namespace NL3D {


/**
 * This texture does generate nothing, and it is releasable. There's no particular reason to use it,
 * unless you want to copy the frame buffer in a texture. You may use that texture so that the device memory
 * will only be allocated once, and the system memory (needed to create the texture, at least with open gl) will be released after that. 
 * A texture_mem could have been used, but it doesn't release memory by itself (added : hmm, well it does since 2/2002 ...). 
 */
class CTextureBlank : public ITexture
{
public:
NLMISC_DECLARE_CLASS(CTextureBlank);
protected:

	/// inherited from ITexture. Does nothing ...
	void doGenerate(bool async) ;	
public:
	virtual ~CTextureBlank() {}
};


} // NL3D


#endif // NL_TEXTURE_BLANK_H

/* End of texture_blank.h */
