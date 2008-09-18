/**
 * \file listener_xaudio2.cpp
 * \brief CListenerXAudio2
 * \date 2008-08-20 12:32GMT
 * \author Jan Boon (Kaetemi)
 * CListenerXAudio2
 */

/* 
 * Copyright (C) 2008  Jan Boon (Kaetemi)
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

/*
 * TODO:
 *  - EAX
 *    - setEAXProperty
 */

#include "stdxaudio2.h"
#include "listener_xaudio2.h"

// STL includes

// NeL includes
#include "../sound_driver.h"
#include <nel/misc/debug.h>

// Project includes
#include "sound_driver_xaudio2.h"
#include "eax_xaudio2.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CListenerXAudio2::CListenerXAudio2(CSoundDriverXAudio2 *soundDriver)
: _OutputVoice(NULL), _ListenerOk(false), _SoundDriver(soundDriver), 
_DopplerScaler(1.0f), _ReverbApo(NULL), 
_EaxEnvironment(CEaxXAudio2::getInvalidEnvironmentId()), 
_ReverbVoice(NULL), _SampleVoice(NULL), _Pos(0.0f, 0.0f, 0.0f)
#if MANUAL_ROLLOFF == 0
, _RolloffScaler(1.0f)
#endif
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Initializing CListenerXAudio2");

	HRESULT hr;
	memset(&_Listener, 0, sizeof(_Listener));
	memset(&_VoiceSends, 0, sizeof(_VoiceSends));

	_Listener.OrientFront.x = 0.0f;
	_Listener.OrientFront.y = 0.0f;
	_Listener.OrientFront.z = 1.0f;
	_Listener.OrientTop.x = 0.0f;
	_Listener.OrientTop.y = 1.0f;
	_Listener.OrientTop.z = 0.0f;
	_Listener.Position.x = 0.0f;
	_Listener.Position.y = 0.0f;
	_Listener.Position.z = 0.0f;
	_Listener.Velocity.x = 0.0f;
	_Listener.Velocity.y = 0.0f;
	_Listener.Velocity.z = 0.0f;

	XAUDIO2_VOICE_DETAILS voice_details;
	soundDriver->getMasteringVoice()->GetVoiceDetails(&voice_details);

	if (FAILED(hr = soundDriver->getXAudio2()->CreateSubmixVoice(&_OutputVoice, voice_details.InputChannels, voice_details.InputSampleRate, 0, 9000, NULL, NULL)))
		{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSubmixVoice _OutputVoice!"); return; }
	XAUDIO2_VOICE_SENDS output_voice_sends;
	output_voice_sends.OutputCount = 1;
	output_voice_sends.pOutputVoices = (IXAudio2Voice **)(&_OutputVoice); // pointer to the pointer (pointer to array of pointers actually)
	
	if (_SoundDriver->useEax())
	{
		uint32 flags = 0;
#ifdef NL_DEBUG
		flags |= XAUDIO2FX_DEBUG;
#endif
		if (FAILED(hr = XAudio2CreateReverb(&_ReverbApo, flags)))
			{ release(); throw ESoundDriver("Failed to create Reverb APO!"); return; }

		XAUDIO2_EFFECT_DESCRIPTOR effect_desc;
		effect_desc.InitialState = TRUE;
		effect_desc.OutputChannels = voice_details.InputChannels;
		effect_desc.pEffect = _ReverbApo;
		XAUDIO2_EFFECT_CHAIN effect_chain;
		effect_chain.EffectCount = 1;
		effect_chain.pEffectDescriptors = &effect_desc; // "array"
		
		if (FAILED(hr = soundDriver->getXAudio2()->CreateSubmixVoice(&_ReverbVoice, voice_details.InputChannels, voice_details.InputSampleRate,	0, 7000, &output_voice_sends, &effect_chain)))
			{ release();  throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSubmixVoice _ReverbVoice!");  return; }

		IXAudio2Voice *reverb_output_array[2];
		reverb_output_array[0] = _OutputVoice;
		reverb_output_array[1] = _ReverbVoice;

		XAUDIO2_VOICE_SENDS reverb_output_voice_sends;
		reverb_output_voice_sends.OutputCount = 2;
		reverb_output_voice_sends.pOutputVoices = (IXAudio2Voice **)reverb_output_array;

		if (FAILED(hr = soundDriver->getXAudio2()->CreateSubmixVoice(&_SampleVoice, voice_details.InputChannels, voice_details.InputSampleRate,	0, 5000, &reverb_output_voice_sends, NULL)))
			{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSubmixVoice _SampleVoice!"); return; }

		_VoiceSends.OutputCount = 1;
		_VoiceSends.pOutputVoices = (IXAudio2Voice **)(&_SampleVoice);

		setEnvironment(ENVFX_DEFAULT_NUM, ENVFX_DEFAULT_SIZE); // something default-ish here
	}
	else
	{
		_VoiceSends = output_voice_sends;
	}
	
	_ListenerOk = true;
}

CListenerXAudio2::~CListenerXAudio2()
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Destroying CListenerXAudio2");
	
	release();	
}

#define NLSOUND_XAUDIO2_RELEASE(pointer) if (_ListenerOk) nlassert(pointer) \
	/*if (pointer) {*/ delete pointer; pointer = NULL; /*}*/
#define NLSOUND_XAUDIO2_RELEASE_AR(pointer) if (_ListenerOk) nlassert(pointer) \
	/*if (pointer) {*/ delete[] pointer; pointer = NULL; /*}*/
#define NLSOUND_XAUDIO2_RELEASE_EX(pointer, command) if (_ListenerOk) nlassert(pointer) \
	if (pointer) { command; pointer = NULL; }
void CListenerXAudio2::release()
{
	if (_SampleVoice) { _SampleVoice->DestroyVoice(); _SampleVoice = NULL; }
	if (_ReverbVoice) { _ReverbVoice->DestroyVoice(); _ReverbVoice = NULL; }
	NLSOUND_XAUDIO2_RELEASE_EX(_OutputVoice, _OutputVoice->DestroyVoice())
	if (_ReverbApo) { _ReverbApo->Release(); _ReverbApo = NULL; }
	if (_SoundDriver) { _SoundDriver->removeListener(this); _SoundDriver = NULL; }

	_ListenerOk = false;
}

/// \name Listener properties
//@{
/// Set the position vector (default: (0,0,0)) (3D mode only)
void CListenerXAudio2::setPos(const NLMISC::CVector& pos)
{
	_Pos = pos;
	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Listener.Position, pos);
}

/** Get the position vector.
 * See setPos() for details.
 */
const NLMISC::CVector &CListenerXAudio2::getPos() const
{
	return _Pos;
}

/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
void CListenerXAudio2::setVelocity(const NLMISC::CVector& vel)
{
	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Listener.Velocity, vel);
}

/// Get the velocity vector
void CListenerXAudio2::getVelocity(NLMISC::CVector& vel) const
{
	NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(vel, _Listener.Velocity);
}

/// Set the orientation vectors (3D mode only, ignored in stereo mode) (default: (0,1,0), (0,0,-1))
void CListenerXAudio2::setOrientation(const NLMISC::CVector& front, const NLMISC::CVector& up)
{
	// nldebug("--- orientation --- %s --- %s ---", front.toString().c_str(), up.toString().c_str());

	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Listener.OrientFront, front);
	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Listener.OrientTop, up);
}

/// Get the orientation vectors
void CListenerXAudio2::getOrientation(NLMISC::CVector& front, NLMISC::CVector& up) const
{
	NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(front, _Listener.OrientFront);
	NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(up, _Listener.OrientTop);
}

/** Set the gain (volume value inside [0 , 1]). (default: 1)
 * 0.0 -> silence
 * 0.5 -> -6dB
 * 1.0 -> no attenuation
 * values > 1 (amplification) not supported by most drivers
 */
void CListenerXAudio2::setGain(float gain)
{
	_OutputVoice->SetVolume(gain);
}

/// Get the gain
float CListenerXAudio2::getGain() const
{
	float gain;
	_OutputVoice->GetVolume(&gain);
	return gain;
}

//@}

/// \name Global properties
//@{
/// Set the doppler factor (default: 1) to exaggerate or not the doppler effect
void CListenerXAudio2::setDopplerFactor(float f)
{
	// nlinfo(NLSOUND_XAUDIO2_PREFIX "setDopplerFactor %f", f);
	_DopplerScaler = f;
}

/// Set the rolloff factor (default: 1) to scale the distance attenuation effect
void CListenerXAudio2::setRolloffFactor(float f)
{
#if MANUAL_ROLLOFF == 1
	nlerror("MANUAL_ROLLOFF == 1");
#else

	// nlinfo(NLSOUND_XAUDIO2_PREFIX "setRolloffFactor %f", f);
	_RolloffScaler = f;
#endif
}

/// Set DSPROPERTY_EAXLISTENER_ENVIRONMENT and DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE if EAX available (see EAX listener properties)
void CListenerXAudio2::setEnvironment(uint env, float size)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setEnvironment %u, %f", (uint32)env, (float)size);

	if (_ReverbApo)
	{
		if (_EaxEnvironment != env)
		{
			CEaxXAudio2::getEnvironment(env, &_ReverbParams);
			_EaxEnvironment = env;
		}
		_ReverbParams.RoomSize = size; // 0 to 100
		_ReverbVoice->SetEffectParameters(0, &_ReverbParams, sizeof(_ReverbParams), 0);
	}
}

/// Set any EAX listener property if EAX available
void CListenerXAudio2::setEAXProperty(uint prop, void *value, uint valuesize)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setEAXProperty %u, %u, %u", (uint32)prop, (uint32)value, (uint32)valuesize);
	nlerror("this isn't used");
}

//@}

} /* namespace NLSOUND */

/* end of file */
