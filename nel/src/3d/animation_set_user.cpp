/** \file animation_set_user.cpp
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

#include "nel/3d/animation_set_user.h"
#include "nel/3d/driver_user.h"


namespace NL3D
{

// ***************************************************************************

UAnimation *CAnimationSetUser::getAnimation (uint animationId)
{

	return _AnimationSet->getAnimation (animationId);
}

// ***************************************************************************

const CAnimationSet* CAnimationSetUser::getAnimationSet () const
{

	return _AnimationSet;
}

// ***************************************************************************
void CAnimationSetUser::setAnimationSampleDivisor(uint sampleDivisor)
{
	_AnimationSet->setAnimationSampleDivisor(sampleDivisor);
}

// ***************************************************************************
uint CAnimationSetUser::getAnimationSampleDivisor() const
{
	return _AnimationSet->getAnimationSampleDivisor();
}

// ***************************************************************************
void CAnimationSetUser::build ()
{

	// build
	_AnimationSet->build ();

	// and preload all SSS shapes that can be spawned during animation
	nlassert(_Owner->getDriver() && _Owner->getShapeBank());
	_AnimationSet->preloadSSSShapes(*_Owner->getDriver(), ((CShapeBankUser*)_Owner->getShapeBank())->_ShapeBank);
}


} // NL3D
