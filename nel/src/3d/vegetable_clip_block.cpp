/** \file vegetable_clip_block.cpp
 * TODO: File description
 */

/* Copyright, 2001 Nevrax Ltd.
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

#include "nel/3d/vegetable_clip_block.h"


namespace NL3D
{


// ***************************************************************************
CVegetableClipBlock::CVegetableClipBlock()
{
	_Empty= true;
	_RenderNext= NULL;
	_NumIgs= 0;
}


// ***************************************************************************
void			CVegetableClipBlock::extendBBoxOnly(const CVector &vec)
{
	if( !_BBox.include(vec) )
	{
		_BBox.extend(vec);
	}
}


// ***************************************************************************
void			CVegetableClipBlock::updateSphere()
{
	_BSphere.Center= _BBox.getCenter();
	_BSphere.Radius= _BBox.getRadius();
}

// ***************************************************************************
void			CVegetableClipBlock::extendSphere(const CVector &vec)
{
	if(_Empty)
	{
		_Empty= false;
		_BBox.setCenter(vec);
		_BBox.setHalfSize(CVector::Null);
		_BSphere.Center= vec;
		_BSphere.Radius= 0;
	}
	else
	{
		extendBBoxOnly(vec);
		updateSphere();
	}

}


// ***************************************************************************
bool			CVegetableClipBlock::clip(const std::vector<CPlane>	&pyramid)
{
	if(_Empty)
		return false;

	for(uint i=0;i<pyramid.size();i++)
	{
		// If entirely out.
		if(!_BSphere.clipBack( pyramid[i] ))
		{
			return false;
		}
	}

	return true;
}



} // NL3D
