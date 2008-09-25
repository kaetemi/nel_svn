/**
 * \file effect_al.cpp
 * \brief CReverbEffectAL
 * \date 2008-09-15 23:09GMT
 * \author Jan Boon (Kaetemi)
 * CReverbEffectAL
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

// ******************************************************************

CEffectAL::CEffectAL(CSoundDriverAL *soundDriver, ALuint alEffect, ALuint alAuxEffectSlot) : _SoundDriver(soundDriver), _AlEffect(alEffect), _AlAuxEffectSlot(alAuxEffectSlot)
{

}

CEffectAL::~CEffectAL()
{
	if (_SoundDriver)
	{
		_SoundDriver->removeEffect(this);
		_SoundDriver = NULL;
		_AlEffect = AL_NONE;
		_AlAuxEffectSlot = AL_NONE;
	}
}

// ******************************************************************

CStandardReverbEffectAL::CStandardReverbEffectAL(CSoundDriverAL *soundDriver, ALuint alEffect, ALuint alAuxEffectSlot) : CEffectAL(soundDriver, alEffect, alAuxEffectSlot)
{
	// unused params, set default values
	alEffectf(_AlEffect, AL_REVERB_AIR_ABSORPTION_GAINHF, 0.994f);
	alEffectf(_AlEffect, AL_REVERB_ROOM_ROLLOFF_FACTOR, 0.0f);
	alEffectf(_AlEffect, AL_REVERB_DECAY_HFLIMIT, AL_TRUE);

	// set default environment
	setEnvironment(NLSOUND_ENVIRONMENT_DEFAULT);
}

CStandardReverbEffectAL::~CStandardReverbEffectAL()
{

}

void CStandardReverbEffectAL::setEnvironment(const CEnvironment &environment)
{
	nldebug("AL: CStandardReverbEffectAL::setEnvironment, size: %f", environment.RoomSize);

	// *** TODO *** environment.RoomSize
	alEffectf(_AlEffect, AL_REVERB_DENSITY, environment.Density / 100.0f); alTestWarning("AL_REVERB_DENSITY");
	alEffectf(_AlEffect, AL_REVERB_DIFFUSION, environment.Diffusion / 100.0f); alTestWarning("AL_REVERB_DIFFUSION");
	alEffectf(_AlEffect, AL_REVERB_GAIN, decibelsToAmplitudeRatio(environment.RoomFilter)); alTestWarning("AL_REVERB_GAIN");
	alEffectf(_AlEffect, AL_REVERB_GAINHF, decibelsToAmplitudeRatio(environment.RoomFilterHF)); alTestWarning("AL_REVERB_GAINHF");
	alEffectf(_AlEffect, AL_REVERB_DECAY_TIME, environment.DecayTime); alTestWarning("AL_REVERB_DECAY_TIME");
	alEffectf(_AlEffect, AL_REVERB_DECAY_HFRATIO, environment.DecayHFRatio); alTestWarning("AL_REVERB_DECAY_HFRATIO");
	alEffectf(_AlEffect, AL_REVERB_REFLECTIONS_GAIN, decibelsToAmplitudeRatio(environment.Reflections)); alTestWarning("AL_REVERB_REFLECTIONS_GAIN");
	alEffectf(_AlEffect, AL_REVERB_REFLECTIONS_DELAY, environment.ReflectionsDelay); alTestWarning("AL_REVERB_REFLECTIONS_DELAY");
	alEffectf(_AlEffect, AL_REVERB_LATE_REVERB_GAIN, decibelsToAmplitudeRatio(environment.LateReverb)); alTestWarning("AL_REVERB_LATE_REVERB_GAIN");
	alEffectf(_AlEffect, AL_REVERB_LATE_REVERB_DELAY, environment.LateReverbDelay); alTestWarning("AL_REVERB_LATE_REVERB_DELAY");
}

void CStandardReverbEffectAL::setGain(float gain)
{
	alAuxiliaryEffectSlotf(_AlAuxEffectSlot, AL_EFFECTSLOT_GAIN, gain);
}

/// Get the type of effect (reverb, etc)
IEffect::TEffectType CStandardReverbEffectAL::getType()
{
	return Reverb;
}

// ******************************************************************

#if EFX_CREATIVE_AVAILABLE

CCreativeReverbEffectAL::CCreativeReverbEffectAL(CSoundDriverAL *soundDriver, ALuint alEffect, ALuint alAuxEffectSlot) : CEffectAL(soundDriver, alEffect, alAuxEffectSlot)
{
	// set default environment
	setEnvironment(NLSOUND_ENVIRONMENT_DEFAULT);
}

CCreativeReverbEffectAL::~CCreativeReverbEffectAL()
{

}

void CCreativeReverbEffectAL::setGain(float gain)
{
	alAuxiliaryEffectSlotf(_AlAuxEffectSlot, AL_EFFECTSLOT_GAIN, gain);
}

/// Get the type of effect (reverb, etc)
IEffect::TEffectType CCreativeReverbEffectAL::getType()
{
	return Reverb;
}

void CCreativeReverbEffectAL::setEnvironment(const CEnvironment &environment)
{
	nldebug("AL: CCreativeReverbEffectAL::setEnvironment, size: %f", environment.RoomSize);

	EAXREVERBPROPERTIES eaxreverb;
	eaxreverb.ulEnvironment = 26;
	eaxreverb.flEnvironmentSize = environment.RoomSize;
	eaxreverb.flEnvironmentDiffusion = environment.Diffusion / 100.0f;
	eaxreverb.lRoom = (long)(environment.RoomFilter * 100.0f);
	eaxreverb.lRoomHF = (long)(environment.RoomFilterHF * 100.0f);
	eaxreverb.lRoomLF = 0;
	eaxreverb.flDecayTime = environment.DecayTime;
	eaxreverb.flDecayHFRatio = environment.DecayHFRatio;
	eaxreverb.flDecayLFRatio = 1.0f;
	eaxreverb.lReflections = (long)(environment.Reflections * 100.0f);
	eaxreverb.flReflectionsDelay = environment.ReflectionsDelay;
	eaxreverb.vReflectionsPan.x = 0.0f;
	eaxreverb.vReflectionsPan.y = 0.0f;
	eaxreverb.vReflectionsPan.z = 0.0f;
	eaxreverb.lReverb = (long)(environment.LateReverb * 100.0f);
	eaxreverb.flReverbDelay = environment.LateReverbDelay;
	eaxreverb.vReverbPan.x = 0.0f;
	eaxreverb.vReverbPan.y = 0.0f;
	eaxreverb.vReverbPan.z = 0.0f;
	eaxreverb.flEchoTime = 0.250f;
	eaxreverb.flEchoDepth = 0.000f;
	eaxreverb.flModulationTime = 0.250f;
	eaxreverb.flModulationDepth = 0.000f;
	eaxreverb.flAirAbsorptionHF = -5.0f;
	eaxreverb.flHFReference = 5000.0f;
	eaxreverb.flLFReference = 250.0f;
	eaxreverb.flRoomRolloffFactor = 0.0f;
	eaxreverb.ulFlags = 0x3f;
	EFXEAXREVERBPROPERTIES efxcreativereverb;
	ConvertReverbParameters(&eaxreverb, &efxcreativereverb);
	efxcreativereverb.flDensity = environment.Density / 100.0f;
	alEffectf(_AlEffect, AL_EAXREVERB_DENSITY, efxcreativereverb.flDensity); alTestWarning("AL_EAXREVERB_DENSITY");
	alEffectf(_AlEffect, AL_EAXREVERB_DIFFUSION, efxcreativereverb.flDiffusion); alTestWarning("AL_EAXREVERB_DIFFUSION");
	alEffectf(_AlEffect, AL_EAXREVERB_GAIN, efxcreativereverb.flGain); alTestWarning("AL_EAXREVERB_GAIN");
	alEffectf(_AlEffect, AL_EAXREVERB_GAINHF, efxcreativereverb.flGainHF); alTestWarning("AL_EAXREVERB_GAINHF");
	alEffectf(_AlEffect, AL_EAXREVERB_GAINLF, efxcreativereverb.flGainLF); alTestWarning("AL_EAXREVERB_GAINLF");
	alEffectf(_AlEffect, AL_EAXREVERB_DECAY_TIME, efxcreativereverb.flDecayTime); alTestWarning("AL_EAXREVERB_DECAY_TIME");
	alEffectf(_AlEffect, AL_EAXREVERB_DECAY_HFRATIO, efxcreativereverb.flDecayHFRatio); alTestWarning("AL_EAXREVERB_DECAY_HFRATIO");
	alEffectf(_AlEffect, AL_EAXREVERB_DECAY_LFRATIO, efxcreativereverb.flDecayLFRatio); alTestWarning("AL_EAXREVERB_DECAY_LFRATIO");
	alEffectf(_AlEffect, AL_EAXREVERB_REFLECTIONS_GAIN, efxcreativereverb.flReflectionsGain); alTestWarning("AL_EAXREVERB_REFLECTIONS_GAIN");
	alEffectf(_AlEffect, AL_EAXREVERB_REFLECTIONS_DELAY, efxcreativereverb.flReflectionsDelay); alTestWarning("AL_EAXREVERB_REFLECTIONS_DELAY");
	alEffectfv(_AlEffect, AL_EAXREVERB_REFLECTIONS_PAN, efxcreativereverb.flReflectionsPan); alTestWarning("AL_EAXREVERB_REFLECTIONS_PAN");
	alEffectf(_AlEffect, AL_EAXREVERB_LATE_REVERB_GAIN, efxcreativereverb.flLateReverbGain); alTestWarning("AL_EAXREVERB_LATE_REVERB_GAIN");
	alEffectf(_AlEffect, AL_EAXREVERB_LATE_REVERB_DELAY, efxcreativereverb.flLateReverbDelay); alTestWarning("AL_EAXREVERB_LATE_REVERB_DELAY");
	alEffectfv(_AlEffect, AL_EAXREVERB_LATE_REVERB_PAN, efxcreativereverb.flLateReverbPan); alTestWarning("AL_EAXREVERB_LATE_REVERB_PAN");
	alEffectf(_AlEffect, AL_EAXREVERB_ECHO_TIME, efxcreativereverb.flEchoTime); alTestWarning("AL_EAXREVERB_ECHO_TIME");
	alEffectf(_AlEffect, AL_EAXREVERB_ECHO_DEPTH, efxcreativereverb.flEchoDepth); alTestWarning("AL_EAXREVERB_ECHO_DEPTH");
	alEffectf(_AlEffect, AL_EAXREVERB_MODULATION_TIME, efxcreativereverb.flModulationTime); alTestWarning("AL_EAXREVERB_MODULATION_TIME");
	alEffectf(_AlEffect, AL_EAXREVERB_MODULATION_DEPTH, efxcreativereverb.flModulationDepth); alTestWarning("AL_EAXREVERB_MODULATION_DEPTH");
	alEffectf(_AlEffect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, efxcreativereverb.flAirAbsorptionGainHF); alTestWarning("AL_EAXREVERB_AIR_ABSORPTION_GAINHF");
	alEffectf(_AlEffect, AL_EAXREVERB_HFREFERENCE, efxcreativereverb.flHFReference); alTestWarning("AL_EAXREVERB_HFREFERENCE");
	alEffectf(_AlEffect, AL_EAXREVERB_LFREFERENCE, efxcreativereverb.flLFReference); alTestWarning("AL_EAXREVERB_LFREFERENCE");
	alEffectf(_AlEffect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, efxcreativereverb.flRoomRolloffFactor); alTestWarning("AL_EAXREVERB_ROOM_ROLLOFF_FACTOR");
	alEffecti(_AlEffect, AL_EAXREVERB_DECAY_HFLIMIT, efxcreativereverb.iDecayHFLimit); alTestWarning("AL_EAXREVERB_DECAY_HFLIMIT"); // note: spec says AL_EAXREVERB_DECAYHF_LIMIT
}

#endif /* #if EFX_CREATIVE_AVAILABLE */

// ******************************************************************

} /* namespace NLSOUND */

/* end of file */
