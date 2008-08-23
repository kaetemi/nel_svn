/** \file animated_morph.cpp
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

#include "nel/3d/animated_morph.h"
#include "nel/misc/common.h"

using namespace NLMISC;

namespace NL3D
{

// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************

CMorphBase::CMorphBase()
{
	DefaultFactor.setDefaultValue (0.0f);
}

// ***************************************************************************
void CMorphBase::serial(NLMISC::IStream &f)
{
	f.serial (Name);
}

// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************


// ***************************************************************************
CAnimatedMorph::CAnimatedMorph (CMorphBase*mb)
{
	nlassert(mb);

	// IAnimatable.
	IAnimatable::resize (AnimValueLast);

	_MorphBase = mb;
	
	_Factor.Value= mb->DefaultFactor.getDefaultValue();
}

// ***************************************************************************
IAnimatedValue* CAnimatedMorph::getValue (uint valueId)
{
	switch(valueId)
	{
		case FactorValue: return &_Factor;
	};

	return NULL;
}
// ***************************************************************************
const char *CAnimatedMorph::getValueName (uint valueId) const
{
	switch(valueId)
	{
		case FactorValue: return "MorphFactor";
	};

	return "";
}
// ***************************************************************************
ITrack*	CAnimatedMorph::getDefaultTrack (uint valueId)
{
	nlassert(_MorphBase);

	switch(valueId)
	{
		case FactorValue: return &_MorphBase->DefaultFactor;
	};

	return NULL;
}
// ***************************************************************************
void	CAnimatedMorph::registerToChannelMixer(CChannelMixer *chanMixer, const std::string &prefix)
{
	// For CAnimatedMorph, channels are detailled (morph evaluated after clip)!
	addValue(chanMixer, FactorValue, OwnerBit, prefix, true);

}


} // NL3D
