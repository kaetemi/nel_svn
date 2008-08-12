/** \file texture_mem.cpp
 * TODO: File description
 *
 * $Id: texture_mem.cpp,v 1.13 2005/02/22 10:19:12 besson Exp $
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

#include "std3d.h"

#include "nel/3d/texture_mem.h"
#include "nel/misc/mem_stream.h"

#include <memory>


namespace NL3D 
{


/*==================================================================*\
							CTEXTUREMEM
\*==================================================================*/

/*------------------------------------------------------------------*\
							doGenerate()
\*------------------------------------------------------------------*/
void CTextureMem::doGenerate(bool async)
{	
	if (_Data)
	{
		if (_IsFile)
		{
			NLMISC::CMemStream m (true);
			m.fill (_Data, _Length);
			load (m);
		}
		else
		{
			resize(_TexWidth, _TexHeight, _TexType);			
			::memcpy(&getPixels(0)[0], _Data, _Length);
			buildMipMaps();
		}
	}
	else
	{
		makeDummy();
	}
}


static NLMISC::CRGBA WhitePix(255, 255, 255, 255); // the texture datas ... :)

///===========================================================================
ITexture *CTextureMem::Create1x1WhiteTex()
{
	static NLMISC::CSmartPtr<ITexture> tex  = NULL;
	if (!tex)
	{
		tex = new CTextureMem((uint8 *) &WhitePix,
							   sizeof(WhitePix),
							   false, /* dont delete */
							   false, /* not a file */
							   1, 1);
		static_cast<CTextureMem *>((ITexture *)tex)->setShareName("#WhitePix1x1");
	}
	return (ITexture *) tex;
}

///===========================================================================
void	CTextureMem::setAllowDegradation(bool allow)
{
	_AllowDegradation= allow;
}

///===========================================================================
uint32 CTextureMem::getImageWidth() const
{
	return _TexWidth;
}

///===========================================================================
uint32 CTextureMem::getImageHeight() const
{
	return _TexHeight;
}


} // NL3D
