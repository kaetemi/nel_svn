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

CEffectXAudio2::CEffectXAudio2(CSoundDriverXAudio2 *soundDriver) : _SoundDriver(soundDriver), _Voice(NULL), _Effect(NULL)
{
	HRESULT hr;

	XAUDIO2_VOICE_DETAILS voice_details;
	soundDriver->getMasteringVoice()->GetVoiceDetails(&voice_details);

	if (FAILED(hr = soundDriver->getXAudio2()->CreateSubmixVoice(&_Voice, voice_details.InputChannels, voice_details.InputSampleRate, 0, 4500, NULL, NULL)))
		{ _release(); nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSubmixVoice _Voice!"); return; }
}

CEffectXAudio2::~CEffectXAudio2()
{
	// _release called by inheriting release
}

void CEffectXAudio2::_release()
{
	if (_SoundDriver) { _SoundDriver->removeEffect(this); _SoundDriver = NULL; }
	if (_Voice) { _Voice->DestroyVoice(); _Voice = NULL; }
}

CReverbEffectXAudio2::CReverbEffectXAudio2(CSoundDriverXAudio2 *soundDriver) : CEffectXAudio2(soundDriver)
{
	if (_Voice)
	{
		HRESULT hr;

		uint flags = 0;
	#ifdef NL_DEBUG
		flags |= XAUDIO2FX_DEBUG;
	#endif		
		if (FAILED(hr = XAudio2CreateReverb(&_Effect, flags)))
			{ release(); nlwarning(NLSOUND_XAUDIO2_PREFIX "XAudio2CreateReverb FAILED"); return; }

		XAUDIO2_VOICE_DETAILS voice_details;
		_Voice->GetVoiceDetails(&voice_details);
		XAUDIO2_EFFECT_DESCRIPTOR effect_descriptor;
		effect_descriptor.InitialState = TRUE;
		effect_descriptor.OutputChannels = voice_details.InputChannels;
		effect_descriptor.pEffect = _Effect;
		XAUDIO2_EFFECT_CHAIN effect_chain;
		effect_chain.EffectCount = 1;
		effect_chain.pEffectDescriptors = &effect_descriptor;
		if (FAILED(hr = _Voice->SetEffectChain(&effect_chain)))
			{ release(); nlwarning(NLSOUND_XAUDIO2_PREFIX "SetEffectChain FAILED"); return; }
		
		setEnvironment();
	}
}

CReverbEffectXAudio2::~CReverbEffectXAudio2()
{
	release();
}

void CReverbEffectXAudio2::release()
{
	_release();
	if (_Effect) { _Effect->Release(); _Effect = NULL; }
}
/// Get the type of effect (reverb, etc)
IEffect::TEffectType CReverbEffectXAudio2::getType()
{
	return Reverb;
}

/// Set the gain
void CReverbEffectXAudio2::setGain(float gain)
{
	_Voice->SetVolume(gain);
}

/// Set the environment (you have full control now, have fun)
void CReverbEffectXAudio2::setEnvironment(const CEnvironment &environment, float roomSize)
{
	// unused params
	_ReverbParams.LowEQCutoff = 4;
	_ReverbParams.HighEQCutoff = 6;
	_ReverbParams.RearDelay = XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY;
	_ReverbParams.PositionLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION;
	_ReverbParams.PositionRight = XAUDIO2FX_REVERB_DEFAULT_POSITION;
	_ReverbParams.PositionMatrixLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
	_ReverbParams.PositionMatrixRight = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
	_ReverbParams.RoomFilterFreq = 5000.0f;
	_ReverbParams.WetDryMix = 100.0f;

	// directly mapped
	_ReverbParams.Density = environment.Density;
	_ReverbParams.RoomFilterMain = environment.RoomFilter;
	_ReverbParams.RoomFilterHF = environment.RoomFilterHF;
	_ReverbParams.ReverbGain = environment.LateReverb;
	_ReverbParams.ReflectionsGain = environment.Reflections;
	_ReverbParams.RoomSize = roomSize;

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

	_Voice->SetEffectParameters(0, &_ReverbParams, sizeof(_ReverbParams), 0);
}

} /* namespace NLSOUND */

/* end of file */
