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
#include <nel/misc/common.h>

// Project includes
#include "sound_driver_xaudio2.h"

using namespace std;
using namespace NLMISC;

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

	// conversions, see ReverbConvertI3DL2ToNative in case of errors
	if (environment.DecayHFRatio >= 1.0f)
	{
		_ReverbParams.HighEQGain = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_GAIN;
		sint32 index = (sint32)(log10(environment.DecayHFRatio) * -4.0f) + 8;
		clamp(index, XAUDIO2FX_REVERB_MIN_LOW_EQ_GAIN, XAUDIO2FX_REVERB_MAX_LOW_EQ_GAIN);
		_ReverbParams.LowEQGain = (BYTE)index;
		_ReverbParams.DecayTime = environment.DecayTime * environment.DecayHFRatio;
	}
	else
	{
		_ReverbParams.LowEQGain = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_GAIN;
		sint32 index = (sint32)(log10(environment.DecayHFRatio) * 4.0f) + 8;
		clamp(index, XAUDIO2FX_REVERB_MIN_HIGH_EQ_GAIN, XAUDIO2FX_REVERB_MAX_HIGH_EQ_GAIN);
		_ReverbParams.HighEQGain = (BYTE)index;
		_ReverbParams.DecayTime = environment.DecayTime;
	}

	sint32 reflections_delay = (sint32)(environment.ReflectionsDelay * 1000.0f);
	clamp(reflections_delay, XAUDIO2FX_REVERB_MIN_REFLECTIONS_DELAY, XAUDIO2FX_REVERB_MAX_REFLECTIONS_DELAY);
	_ReverbParams.ReflectionsDelay = (UINT32)reflections_delay;
	
	sint32 reverb_delay = (sint32)(environment.LateReverbDelay * 1000.0f);
	clamp(reverb_delay, XAUDIO2FX_REVERB_MIN_REVERB_DELAY, XAUDIO2FX_REVERB_MAX_REVERB_DELAY);
	_ReverbParams.ReverbDelay = (BYTE)reverb_delay;

	_ReverbParams.EarlyDiffusion = (BYTE)(environment.Diffusion * 0.15f);
	_ReverbParams.LateDiffusion = _ReverbParams.EarlyDiffusion;

	if (_EffectVoice) _EffectVoice->SetEffectParameters(0, &_ReverbParams, sizeof(_ReverbParams), 0);
}

} /* namespace NLSOUND */

/* end of file */
