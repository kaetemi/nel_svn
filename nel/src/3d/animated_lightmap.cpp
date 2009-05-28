/** \file animated_lightmap.cpp
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

#include "nel/3d/animated_lightmap.h"
#include "nel/3d/scene.h"
#include "nel/misc/common.h"

using namespace NLMISC;

namespace NL3D
{


// ***************************************************************************
// ***************************************************************************
// ***************************************************************************
// ***************************************************************************


// ***************************************************************************
CAnimatedLightmap::CAnimatedLightmap (uint lightmapGroup)
{
	// IAnimatable.
	IAnimatable::resize( AnimValueLast );

	_DefaultFactor.setDefaultValue( CRGBA(255,0,255,255) );
	_Factor.Value= _DefaultFactor.getDefaultValue();
	_GroupColor.resize (lightmapGroup, CRGBA::White);
}

// ***************************************************************************
/*void	CAnimatedLightmap::update()
{
	if( isTouched(OwnerBit) )
	{
		// well, just update all...  :)

		// diffuse part.
		CRGBA	diff= _Diffuse.Value;
		sint c= (sint)(_Opacity.Value*255);
		clamp(c, 0, 255);
		diff.A= c;

		// setup material.
		_Lightmap->setLighting(true, _Emissive.Value, _Ambient.Value, diff, _Specular.Value, _Shininess.Value);

		// clear flags.
		clearFlag(AmbientValue);
		clearFlag(DiffuseValue);
		clearFlag(SpecularValue);
		clearFlag(ShininessValue);
		clearFlag(EmissiveValue);
		clearFlag(OpacityValue);


		// Texture Anim.
		if(isTouched(TextureValue))
		{
			nlassert(_LightmapBase);

			uint32	id= _Texture.Value;
			if(_LightmapBase->validAnimatedTexture(id))
			{
				_Lightmap->setTexture(0, _LightmapBase->getAnimatedTexture(id) );
			}
			clearFlag(TextureValue);
		}


		// We are OK!
		IAnimatable::clearFlag(OwnerBit);
	}
}*/


// ***************************************************************************
IAnimatedValue* CAnimatedLightmap::getValue (uint valueId)
{
	switch(valueId)
	{
	case FactorValue: return &_Factor;
	};

	// should not be here!!
	nlstop;
	return NULL;
}
// ***************************************************************************
const char *CAnimatedLightmap::getValueName (uint valueId) const
{
	switch(valueId)
	{
	case FactorValue: nlstop; return "???";
	};

	// should not be here!!
	nlstop;
	return "";
}
// ***************************************************************************
ITrack*	CAnimatedLightmap::getDefaultTrack (uint valueId)
{
	//nlassert(_LightmapBase);

	switch(valueId)
	{
	case FactorValue: return	&_DefaultFactor;
	};

	// should not be here!!
	nlstop;
	return NULL;
}
// ***************************************************************************
void	CAnimatedLightmap::registerToChannelMixer(CChannelMixer *chanMixer, const std::string &prefix)
{
	// For CAnimatedLightmap, channels are detailled (Lightmap rendered after clip)!
	addValue(chanMixer, FactorValue, OwnerBit, prefix, true);

}

// ***************************************************************************

void	CAnimatedLightmap::updateGroupColors (class NL3D::CScene &scene)
{
	// For each colors
	const uint count = scene.getNumLightGroup ();
	_GroupColor.resize (count);
	uint i;
	for (i=0; i<count; i++)
	{
		_GroupColor[i].modulateFromColor (scene.getLightmapGroupColor (i), _Factor.Value);
	}
}

// ***************************************************************************

} // NL3D
