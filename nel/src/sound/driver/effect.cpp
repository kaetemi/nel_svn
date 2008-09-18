/**
 * \file effect.cpp
 * \brief IEffect
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IEffect
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

#include <nel/misc/types_nl.h>
#include "effect.h"

// STL includes

// NeL includes
// #include <nel/misc/debug.h>

// Project includes

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

IEffect::IEffect()
{
	
}

IEffect::~IEffect()
{
	
}

IReverbEffect::IReverbEffect()
{
	
}

IReverbEffect::~IReverbEffect()
{
	
}

IReverbEffect::CEnvironment EnvironmentPresets[] = 
{
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_GENERIC), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_PADDEDCELL), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_ROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_BATHROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_LIVINGROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_STONEROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_AUDITORIUM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_CONCERTHALL), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_CAVE), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_ARENA), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_HANGAR), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_CARPETEDHALLWAY), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_HALLWAY), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_STONECORRIDOR), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_ALLEY), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_FOREST), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_CITY), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_MOUNTAINS), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_QUARRY), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_PLAIN), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_PARKINGLOT), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_SEWERPIPE), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_UNDERWATER), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_SMALLROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_MEDIUMROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_LARGEROOM), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_MEDIUMHALL), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_LARGEHALL), 
	IReverbEffect::CEnvironment(NLSOUND_ENVIRONMENT_PRESET_PLATE), 
};

} /* namespace NLSOUND */

/* end of file */
