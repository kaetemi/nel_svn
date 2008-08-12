/** \file texture_bloom.h
 * 
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

#ifndef NL_TEXTURE_BLOOM_H
#define NL_TEXTURE_BLOOM_H

#include "nel/misc/types_nl.h"
#include "texture_blank.h"


namespace NL3D {


/**
 * This texture does generate nothing, and it is releasable. It is used for bloom effect.
 */
class CTextureBloom : public CTextureBlank
{
public:
NLMISC_DECLARE_CLASS(CTextureBloom);
	
	CTextureBloom() {Mode2D=false;}
	virtual ~CTextureBloom() {}

	virtual bool isBloomTexture() const { return true; }

	void mode2D(bool isMode2D) {Mode2D=isMode2D;}
	bool isMode2D() {return Mode2D;}

private:

	bool	Mode2D;
};


} // NL3D


#endif // NL_TEXTURE_BLOOM_H

/* End of texture_bloom.h */
