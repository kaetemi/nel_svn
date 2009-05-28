/** \file tile_light_influence.cpp
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

#include "nel/3d/tile_light_influence.h"
#include "nel/misc/debug.h"


namespace NL3D
{


void			CTileLightInfluence::setDiffuseLightFactor(uint i, uint8 factor)
{
	nlassert(CTileLightInfluence::NumLightPerCorner == 2);
	nlassert(i == 0 || i == 1);

	// Divide by 16.
	factor>>=4;

	// set to the ith light.
	uint8	mask= 0x0F << (4*i);
	// clear.
	PackedLightFactor&= ~mask;
	// set.
	PackedLightFactor|= factor << (4*i);
}


uint8			CTileLightInfluence::getDiffuseLightFactor(uint i) const
{
	nlassert(CTileLightInfluence::NumLightPerCorner == 2);
	nlassert(i == 0 || i == 1);

	// Choose what factor
	uint8	ret= PackedLightFactor >> (4*i);
	ret&= 0x0F;

	// expand to 0..255
	return ret + (ret<<4);
}


void			CTileLightInfluence::serial(NLMISC::IStream &f)
{
	nlassert(CTileLightInfluence::NumLightPerCorner == 2);
	// No version for smaller size on disk !!

	f.serial(Light[0], Light[1], PackedLightFactor);
}



} // NL3D
