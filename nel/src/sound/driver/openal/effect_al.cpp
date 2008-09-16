/**
 * \file effect_al.cpp
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

#include "stdopenal.h"
#include "effect_al.h"

#include "sound_driver_al.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CReverbAl::CReverbAl(ALuint alEfxObject) : _AlEffect(alEfxObject), _RoomSize(ENVFX_DEFAULT_SIZE)
#if EFX_CREATIVE_AVAILABLE
, _Creative(false)
#endif
{
	setEnvironment(CEnvironment(NLSOUND_I3DL2_ENVIRONMENT_PRESET_ROOM));
}

#if EFX_CREATIVE_AVAILABLE
CReverbAl::CReverbAl(ALuint alEfxObject, bool creative) : _AlEffect(alEfxObject), _RoomSize(ENVFX_DEFAULT_SIZE), _Creative(creative)
{
	setEnvironment(CEnvironment(NLSOUND_I3DL2_ENVIRONMENT_PRESET_ROOM));
}
#endif

CReverbAl::~CReverbAl()
{
	
}

IEffect::TEffectType CReverbAl::getType()
{
	return Reverb;
}

void CReverbAl::setEnvironment(const CEnvironment &environment)
{
	_Environment = environment;
#if EFX_CREATIVE_AVAILABLE
	if (_Creative)
	{
		EAXREVERBPROPERTIES eaxreverb;
		eaxreverb.ulEnvironment = 26;
		eaxreverb.flEnvironmentSize = _RoomSize;
		eaxreverb.flEnvironmentDiffusion = environment.Diffusion;
		eaxreverb.lRoom = environment.Room;
		eaxreverb.lRoomHF = environment.RoomHF;
		eaxreverb.lRoomLF = 0;
		eaxreverb.flDecayTime = environment.DecayTime;
		eaxreverb.flDecayHFRatio = environment.DecayHFRatio;
		eaxreverb.flDecayLFRatio = 1.0f;
		eaxreverb.lReflections = environment.Reflections;
		eaxreverb.flReflectionsDelay = environment.ReflectionsDelay;
		eaxreverb.vReflectionsPan.x = 0.0f;
		eaxreverb.vReflectionsPan.y = 0.0f;
		eaxreverb.vReflectionsPan.z = 0.0f;
		eaxreverb.lReverb = environment.Reverb;
		eaxreverb.flReverbDelay = environment.ReverbDelay;
		eaxreverb.vReverbPan.x = 0.0f;
		eaxreverb.vReverbPan.y = 0.0f;
		eaxreverb.vReverbPan.z = 0.0f;
		eaxreverb.flEchoTime = 0.250f;
		eaxreverb.flEchoDepth = 0.000f;
		eaxreverb.flModulationTime = 0.250f;
		eaxreverb.flModulationDepth = 0.000f;
		eaxreverb.flAirAbsorptionHF = -5.0f;
		eaxreverb.flHFReference = environment.HFReference;
		eaxreverb.flLFReference = 250.0f;
		eaxreverb.flRoomRolloffFactor = environment.RoomRolloffFactor;
		eaxreverb.ulFlags = 0x3f;
		EFXEAXREVERBPROPERTIES efxcreativereverb;
		ConvertReverbParameters(&eaxreverb, &efxcreativereverb);
		efxcreativereverb.flDensity = environment.Density / 100.0f;
		ALenum gaintest14 = alGetEnumValue("AL_EAXREVERB_GAIN");
		ALenum gaintes42t = alGetEnumValue("AL_REVERB_GAIN");
		ALenum gaintes4t23 = alGetEnumValue("AL_EAXREVERB_DENSITY");
		ALenum gaintest = alcGetEnumValue(CSoundDriverAL::getInstance()->getAlDevice(), "AL_EAXREVERB_GAIN");
		ALenum gaintes2t = alcGetEnumValue(CSoundDriverAL::getInstance()->getAlDevice(), "AL_REVERB_GAIN");
		ALenum gaintest23 = alcGetEnumValue(CSoundDriverAL::getInstance()->getAlDevice(), "AL_EAXREVERB_DENSITY");
		alEffectf(_AlEffect, AL_EAXREVERB_DENSITY, efxcreativereverb.flDensity); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_DIFFUSION, efxcreativereverb.flDiffusion); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_GAIN, efxcreativereverb.flGain); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_GAINHF, efxcreativereverb.flGainHF); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_GAINLF, efxcreativereverb.flGainLF); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_DECAY_TIME, efxcreativereverb.flDecayTime); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_DECAY_HFRATIO, efxcreativereverb.flDecayHFRatio); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_DECAY_LFRATIO, efxcreativereverb.flDecayLFRatio); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_REFLECTIONS_GAIN, efxcreativereverb.flReflectionsGain); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_REFLECTIONS_DELAY, efxcreativereverb.flReflectionsDelay); alTestWarning();
		alEffectfv(_AlEffect, AL_EAXREVERB_REFLECTIONS_PAN, efxcreativereverb.flReflectionsPan); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_LATE_REVERB_GAIN, efxcreativereverb.flLateReverbGain); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_LATE_REVERB_DELAY, efxcreativereverb.flLateReverbDelay); alTestWarning();
		alEffectfv(_AlEffect, AL_EAXREVERB_LATE_REVERB_PAN, efxcreativereverb.flLateReverbPan); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_ECHO_TIME, efxcreativereverb.flEchoTime); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_ECHO_DEPTH, efxcreativereverb.flEchoDepth); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_MODULATION_TIME, efxcreativereverb.flModulationTime); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_MODULATION_DEPTH, efxcreativereverb.flModulationDepth); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, efxcreativereverb.flAirAbsorptionGainHF); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_HFREFERENCE, efxcreativereverb.flHFReference); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_LFREFERENCE, efxcreativereverb.flLFReference); alTestWarning();
		alEffectf(_AlEffect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, efxcreativereverb.flRoomRolloffFactor); alTestWarning();
		alEffecti(_AlEffect, AL_EAXREVERB_DECAY_HFLIMIT, efxcreativereverb.iDecayHFLimit); alTestWarning(); // note: spec says AL_EAXREVERB_DECAYHF_LIMIT
	}
	else
#endif
	{
		ALenum gaintest14 = alGetEnumValue("AL_EAXREVERB_GAIN");
		ALenum gaintes42t = alGetEnumValue("AL_REVERB_GAIN");
		ALenum gaintes4t23 = alGetEnumValue("AL_EAXREVERB_DENSITY");
		ALenum gaintest = alcGetEnumValue(CSoundDriverAL::getInstance()->getAlDevice(), "AL_EAXREVERB_GAIN");
		ALenum gaintes2t = alcGetEnumValue(CSoundDriverAL::getInstance()->getAlDevice(), "AL_REVERB_GAIN");
		ALenum gaintest23 = alcGetEnumValue(CSoundDriverAL::getInstance()->getAlDevice(), "AL_EAXREVERB_DENSITY");
		nlwarning("setEnvironment not implemented");
	}
}

void CReverbAl::setRoomSize(float roomSize)
{
#if EFX_CREATIVE_AVAILABLE
	if (_Creative)
	{
		nlwarning("setRoomSize not implemented");
	}
	else
#endif
	{
		nlwarning("setRoomSize not implemented");
	}
}

} /* namespace NLSOUND */

/* end of file */
