/**
 * \file effect_al.h
 * \brief CReverbAl
 * \date 2008-09-15 23:09GMT
 * \author Jan Boon (Kaetemi)
 * CReverbAl
 */

/* 
 * Copyright (C) 2008  by authors
 * 
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 * 
 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#ifndef NLSOUND_EFFECT_AL_H
#define NLSOUND_EFFECT_AL_H
#include <nel/misc/types_nl.h>

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {

/**
 * \brief CReverbAl
 * \date 2008-09-15 23:09GMT
 * \author Jan Boon (Kaetemi)
 * CReverbAl
 */
class CReverbAl : public IReverb
{
protected:
	// pointers
	
	// instances
	ALuint _AlEffect;
	CEnvironment _Environment;
	float _RoomSize;

#if EFX_CREATIVE_AVAILABLE
	bool _Creative;
#endif
public:
	CReverbAl(ALuint alEfxObject);
#if EFX_CREATIVE_AVAILABLE
	CReverbAl(ALuint alEfxObject, bool creative);
#endif
	virtual ~CReverbAl();

	inline ALuint getAlEfxObject() { return _AlEffect; }
#if EFX_CREATIVE_AVAILABLE
	inline void setCreative(bool creative) { _Creative = creative; }
#endif

	// IEffect
	virtual TEffectType getType();

	// IReverb
	virtual void setEnvironment(const CEnvironment &environment);
	virtual void setRoomSize(float roomSize);
}; /* class CReverbAl */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EFFECT_AL_H */

/* end of file */
