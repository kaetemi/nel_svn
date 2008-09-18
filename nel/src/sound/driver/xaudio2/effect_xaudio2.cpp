/**
 * \file effect_xaudio2.cpp
 * \brief CReverbEffectXAudio2
 * \date 2008-09-17 17:27GMT
 * \author Jan Boon (Kaetemi)
 * CReverbEffectXAudio2
 */

/* 
 * Copyright (C) 2008  by authors
 * 
 * This file is part of NLSOUND XAudio2 Driver.
 * NLSOUND XAudio2 Driver is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 * 
 * NLSOUND XAudio2 Driver is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NLSOUND XAudio2 Driver; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */

#include "stdxaudio2.h"
#include "effect_xaudio2.h"

// STL includes

// NeL includes
// #include <nel/misc/debug.h>

// Project includes
#include "sound_driver_xaudio2.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CReverbEffectXAudio2::CReverbEffectXAudio2(CSoundDriverXAudio2 *soundDriver) : _SoundDriver(soundDriver), _Effect(NULL), _EffectVoice(NULL)
{
	HRESULT hr;

	uint flags = 0;
#ifdef NL_DEBUG
	flags |= XAUDIO2FX_DEBUG;
#endif		
	if (FAILED(hr = XAudio2CreateReverb(&_Effect, flags)))
		{ release(); nlwarning(NLSOUND_XAUDIO2_PREFIX "Failed to create Reverb APO!"); return; }

	setEnvironment(NLSOUND_ENVIRONMENT_DEFAULT);
}

CReverbEffectXAudio2::~CReverbEffectXAudio2()
{
	release();
}

void CReverbEffectXAudio2::release()
{
	if (_SoundDriver) { _SoundDriver->removeEffect(this); _SoundDriver = NULL; }
	if (_Effect) { _Effect->Release(); _Effect = NULL; }
}

void CReverbEffectXAudio2::setVoice(IXAudio2Voice *effectVoice) 
{ 
	_EffectVoice = effectVoice; 
	if (_EffectVoice) _EffectVoice->SetEffectParameters(0, &_ReverbParams, sizeof(_ReverbParams), 0); 
}

/// Get the type of effect (reverb, etc)
IEffect::TEffectType CReverbEffectXAudio2::getType()
{
	return Reverb;
}

/// Set the environment (you have full control now, have fun)
void CReverbEffectXAudio2::setEnvironment(const CEnvironment &environment)
{
	// unused params
    _ReverbParams.RearDelay = XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY;
    _ReverbParams.PositionLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION;
    _ReverbParams.PositionRight = XAUDIO2FX_REVERB_DEFAULT_POSITION;
    _ReverbParams.PositionMatrixLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
    _ReverbParams.PositionMatrixRight = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
    _ReverbParams.RoomFilterFreq = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_FREQ;
    _ReverbParams.LowEQCutoff = 4;
    _ReverbParams.HighEQCutoff = 6;
    _ReverbParams.WetDryMix = 100.0f;

    // directly mapped
    _ReverbParams.RoomSize = environment.RoomSize;
    _ReverbParams.RoomFilterMain = environment.RoomFilter;
    _ReverbParams.RoomFilterHF = environment.RoomFilterHF;
    _ReverbParams.ReflectionsGain = environment.Reflections;
    _ReverbParams.ReverbGain = environment.LateReverb;
    _ReverbParams.Density = environment.Density;

	// conversions, see ReverbConvertI3DL2ToNative
    _ReverbParams.EarlyDiffusion = (BYTE)(environment.Diffusion * 0.15f);
    _ReverbParams.LateDiffusion = _ReverbParams.EarlyDiffusion;
    if (environment.DecayHFRatio >= 1.0f)
    {
        _ReverbParams.HighEQGain = 8;
        INT32 index = (INT32)(-4.0 * log10(environment.DecayHFRatio));
        if (index < -8)  index = -8;
        _ReverbParams.LowEQGain = BYTE((index < 0) ? index + 8 : 8);
        _ReverbParams.DecayTime = environment.DecayTime * environment.DecayHFRatio;
    }
    else
    {
        _ReverbParams.LowEQGain = 8;
        INT32 index = (INT32)(4.0 * log10(environment.DecayHFRatio));
        if (index < -8) index = -8;
        _ReverbParams.HighEQGain = BYTE((index < 0) ? index + 8 : 8);
        _ReverbParams.DecayTime = environment.DecayTime;
    }
    float reflections_delay = environment.ReflectionsDelay * 1000.0f;
    if (reflections_delay >= XAUDIO2FX_REVERB_MAX_REFLECTIONS_DELAY)
        reflections_delay = (float)(XAUDIO2FX_REVERB_MAX_REFLECTIONS_DELAY - 1);
    else if (reflections_delay <= 1) 
		reflections_delay = 1;
    _ReverbParams.ReflectionsDelay = (UINT32)reflections_delay;
	float reverb_delay = environment.LateReverbDelay * 1000.0f;
    if (reverb_delay >= XAUDIO2FX_REVERB_MAX_REVERB_DELAY)
        reverb_delay = (float)(XAUDIO2FX_REVERB_MAX_REVERB_DELAY - 1);
    _ReverbParams.ReverbDelay = (BYTE)reverb_delay;

	if (_EffectVoice) _EffectVoice->SetEffectParameters(0, &_ReverbParams, sizeof(_ReverbParams), 0);
}

} /* namespace NLSOUND */

/* end of file */
