/**
 * \file source_xaudio2.cpp
 * \brief CSourceXAudio2
 * \date 2008-08-20 15:53GMT
 * \author Jan Boon (Kaetemi)
 * CSourceXAudio2
 * 
 * $Id$
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
 *  - Curve
 *    - _MaxDistance (silence sound after max distance, not required really)
 *  - EAX
 *    - setEAXProperty
 *  - Time
 *    - getTime
 */

// curve cone eax time

#include "stdxaudio2.h"
#include "source_xaudio2.h"

// STL includes
#include <cfloat>
#include <algorithm>
#include <limits>

// NeL includes
#include <nel/misc/hierarchical_timer.h>
#include <nel/misc/debug.h>
#include <nel/misc/variable.h>

// Project includes
#include "sound_driver_xaudio2.h"
#include "buffer_xaudio2.h"
#include "listener_xaudio2.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CSourceXAudio2::CSourceXAudio2(CSoundDriverXAudio2 *soundDriver) 
: _SoundDriver(soundDriver), _SourceVoice(NULL), _StaticBuffer(NULL), 
_Format(Mono16), _FreqVoice(44100.0f), _FreqRatio(1.0f), _PlayStart(0), 
_Doppler(1.0f), _Pos(0.0f, 0.0f, 0.0f), _Relative(false), _Alpha(1.0), 
_IsPlaying(false), _IsPaused(false), _IsLooping(false), _Pitch(1.0f), 
_Gain(1.0f), _MinDistance(1.0f), _MaxDistance(numeric_limits<float>::max())
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Inititializing CSourceXAudio2");

	memset(&_Emitter, 0, sizeof(_Emitter));
	memset(&_Cone, 0, sizeof(_Cone));

	_Cone.InnerAngle = X3DAUDIO_2PI;
    _Cone.OuterAngle = X3DAUDIO_2PI;
	_Cone.InnerVolume = 1.0f;
    _Cone.OuterVolume = 0.0f;
    _Cone.InnerLPF = 1.0f;
    _Cone.OuterLPF = 0.0f;
    _Cone.InnerReverb = 1.0f;
    _Cone.OuterReverb = 0.0f;

	_Emitter.OrientFront.x = 0.0f;
	_Emitter.OrientFront.y = 0.0f;
	_Emitter.OrientFront.z = 1.0f;
	_Emitter.OrientTop.x = 0.0f;
	_Emitter.OrientTop.y = 1.0f;
	_Emitter.OrientTop.z = 0.0f;
	_Emitter.Position.x = 0.0f;
	_Emitter.Position.y = 0.0f;
	_Emitter.Position.z = 0.0f;
	_Emitter.Velocity.x = 0.0f;
	_Emitter.Velocity.y = 0.0f;
	_Emitter.Velocity.z = 0.0f;
	_Emitter.ChannelCount = 1;
	_Emitter.InnerRadius = 0.0f;
	_Emitter.InnerRadiusAngle = 0.0f;
	_Emitter.ChannelRadius = 0.0f;
	_Emitter.CurveDistanceScaler = 1.0f;
	_Emitter.DopplerScaler = 1.0f;
}

CSourceXAudio2::~CSourceXAudio2()
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Destroying CSourceXAudio2");

	release();
}

void CSourceXAudio2::release() // called by driver :)
{
	_SoundDriver->removeSource(this);
	destroySourceVoice(_SourceVoice);
	_SourceVoice = NULL;
	stop();
}

/// Commit all the changes made to 3D settings of listener and sources
void CSourceXAudio2::commit3DChanges()
{
	if (_IsPlaying)
	{
		nlassert(_SourceVoice);
		
		// Only mono buffers get 3d sound, stereo buffers go directly to the speakers.
		// Todo: stereo buffers calculate distance
		if (_Format == Stereo16 || _Format == Stereo8)
		{
			_SoundDriver->getDSPSettings()->DstChannelCount = 1;
			// calculate without doppler
			// 1 result in matrix, use with setvolume
			// todo: some more stuff...
			_SourceVoice->SetFrequencyRatio(_FreqRatio * _Pitch);
		}
		else
		{
			// nldebug(NLSOUND_XAUDIO2_PREFIX "_SampleVoice->getBuffer() %u", (uint32)_SampleVoice->getBuffer());

			_Emitter.DopplerScaler = _SoundDriver->getListener()->getDopplerScaler();
			_Emitter.CurveDistanceScaler = _MinDistance * _SoundDriver->getListener()->getDistanceScaler(); // might be just _MinDistance, not sure, compare with fmod driver
			// _MaxDistance not implemented (basically should cut off sound beyond maxdistance)

			_SoundDriver->getDSPSettings()->DstChannelCount = 2;

			X3DAudioCalculate(_SoundDriver->getX3DAudio(), 
				_Relative 
					? _SoundDriver->getEmptyListener() // position is relative to listener (we use 0pos listener)
					: _SoundDriver->getListener()->getListener(), // position is absolute
				&_Emitter, 
				X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER, 
				_SoundDriver->getDSPSettings());

			_SourceVoice->SetOutputMatrix(
				// _SoundDriver->getMasteringVoice(),
				_SoundDriver->getListener()->getVoiceSends()->pOutputVoices[0], 
				_SoundDriver->getDSPSettings()->SrcChannelCount, 
				_SoundDriver->getDSPSettings()->DstChannelCount, 
				_SoundDriver->getDSPSettings()->pMatrixCoefficients);
			// nldebug(NLSOUND_XAUDIO2_PREFIX "left: %f, right %f", _SoundDriver->getDSPSettings()->pMatrixCoefficients[0], _SoundDriver->getDSPSettings()->pMatrixCoefficients[1]);
			_Doppler = _SoundDriver->getDSPSettings()->DopplerFactor;
			_SourceVoice->SetFrequencyRatio(_FreqRatio * _Pitch * _Doppler);
		}
	}

	// todo: reverb & delay? ^^
}

IXAudio2SourceVoice *CSourceXAudio2::createSourceVoice(TSampleFormat format)
{
	nlassert(_SoundDriver->getListener());

	HRESULT hr;

	WAVEFORMATEX wfe; // todo: ADPCMWAVEFORMAT // wSamplesPerBlock // wNumCoef // aCoef
	wfe.cbSize = 0;

	nlassert(format == Mono16 || format == Mono16ADPCM || format == Mono16 || format == Stereo16 || format == Stereo8);

	wfe.wFormatTag = (format == Mono16ADPCM) 
		? WAVE_FORMAT_ADPCM
		: WAVE_FORMAT_PCM;
	wfe.nChannels = (format == Mono16 || format == Mono16ADPCM || format == Mono8)
		? 1
		: 2;
	wfe.wBitsPerSample = (format == Mono8 || format == Stereo8)
		? 8
		: 16;

	XAUDIO2_VOICE_DETAILS voice_details;
	_SoundDriver->getListener()->getVoiceSends()->pOutputVoices[0]->GetVoiceDetails(&voice_details);
	wfe.nSamplesPerSec = voice_details.InputSampleRate;

	wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
	wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

	// note: 32.0f allows at lowest 1378.125hz audio samples, increase if you need even lower bitrate (or higher pitch)
	// todo: callback for when error happens on voice, so we can restart it!
	IXAudio2SourceVoice *source_voice = NULL;

	if (FAILED(hr = _SoundDriver->getXAudio2()->CreateSourceVoice(&source_voice, &wfe, 0, 32.0f, NULL/*this*/, _SoundDriver->getListener()->getVoiceSends(), NULL)))
	{ if (source_voice) source_voice->DestroyVoice(); nlerror(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSourceVoice"); return NULL; }

	return source_voice;
}

void CSourceXAudio2::destroySourceVoice(IXAudio2SourceVoice *sourceVoice)
{
	if (sourceVoice) sourceVoice->DestroyVoice();
}

void CSourceXAudio2::submitStaticBuffer()
{
	nlassert(_SourceVoice);
	nlassert(_Format == _StaticBuffer->getFormat());
	
	XAUDIO2_BUFFER buffer;
	buffer.AudioBytes = _StaticBuffer->getSize();
	buffer.Flags = 0;
	buffer.LoopBegin = 0;
	buffer.LoopCount = _IsLooping ? XAUDIO2_LOOP_INFINITE : 0;
	buffer.LoopLength = 0;
	buffer.pAudioData = _StaticBuffer->getData();
	buffer.pContext = _StaticBuffer;
	buffer.PlayBegin = 0;
	buffer.PlayLength = 0;
	
	_SourceVoice->SubmitSourceBuffer(&buffer);
}

/// \name Initialization
//@{
/** Set the buffer that will be played (no streaming)
 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
 * otherwise the source is considered as a 3D source.
 */
void CSourceXAudio2::setStaticBuffer(IBuffer *buffer)
{
	// if (buffer) nldebug(NLSOUND_XAUDIO2_PREFIX "setStaticBuffer %s", _SoundDriver->getStringMapper()->unmap(buffer->getName()).c_str());
	// else nldebug(NLSOUND_XAUDIO2_PREFIX "setStaticBuffer NULL");

	if (_IsPlaying) nlwarning(NLSOUND_XAUDIO2_PREFIX "Called setStaticBuffer(IBuffer *buffer) while _IsPlaying == true!");
	
	_StaticBuffer = static_cast<CBufferXAudio2 *>(buffer);
}

/// Return the buffer, or NULL if streaming is used.
IBuffer *CSourceXAudio2::getStaticBuffer()
{
	return _StaticBuffer;
}

///** Set the sound loader that will be used to stream in the data to play
// * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
// * otherwise the source is considered as a 3D source.
// */
//void CSourceXAudio2::setStreamLoader(ILoader *loader) { _Loader = loader; }
//@}


/// \name Playback control
//@{
/// Set looping on/off for future playbacks (default: off)
void CSourceXAudio2::setLooping(bool l)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setLooping %u", (uint32)l);
	
	_IsLooping = l;
}

/// Return the looping state
bool CSourceXAudio2::getLooping() const
{
	return _IsLooping;
}

/** Play the static buffer (or stream in and play).
 *	This method can return false if the sample for this sound is unloaded.
 */
bool CSourceXAudio2::play()
{	
	// nldebug(NLSOUND_XAUDIO2_PREFIX "play");

	if (_IsPaused)
	{
		if (SUCCEEDED(_SourceVoice->Start(0))) _IsPaused = false;
			else nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Play");
		return !_IsPaused;
	}
	else
	{
		if (_IsPlaying)
		{
			nlwarning(NLSOUND_XAUDIO2_PREFIX "Called play() while _IsPlaying == true!");
			if (_StaticBuffer->getFormat() == _Format) // cannot call stop directly before destroy voice, ms bug in xaudio2
				stop(); // sets _IsPlaying = false;
		}
		if (_StaticBuffer)
		{
			if (_SourceVoice && _StaticBuffer->getFormat() != _Format)
			{
				nlwarning(NLSOUND_XAUDIO2_PREFIX "Switching format %u to %u!", (uint32)_Format, (uint32)_StaticBuffer->getFormat());
				destroySourceVoice(_SourceVoice);
				_SourceVoice = NULL;
			}
			if (!_SourceVoice) 
			{
				// nlwarning(NLSOUND_XAUDIO2_PREFIX "New voice with format %u!", (uint32)_StaticBuffer->getFormat());
				_SourceVoice = createSourceVoice(_StaticBuffer->getFormat());
				if (!_SourceVoice) return false; // fail
				_Format = _StaticBuffer->getFormat();
				XAUDIO2_VOICE_DETAILS voice_details;
				_SourceVoice->GetVoiceDetails(&voice_details);
				_FreqVoice = (float)voice_details.InputSampleRate;
				_SourceVoice->SetVolume(_Gain);
			}
			_FreqRatio = (float)_StaticBuffer->getFreq() / _FreqVoice;
			commit3DChanges(); // sets pitch etc
			submitStaticBuffer();
			_PlayStart = CTime::getLocalTime();
			if (SUCCEEDED(_SourceVoice->Start(0))) _IsPlaying = true;
			else nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Play");
		}
		return _IsPlaying;
	}
}

/// Stop playing
void CSourceXAudio2::stop()
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "stop");

	_IsPlaying = false;
	_IsPaused = false;
	if (_SourceVoice)
	{
		if (FAILED(_SourceVoice->Stop(0))) 
			nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Stop");
		if (FAILED(_SourceVoice->FlushSourceBuffers())) 
			nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED FlushSourceBuffers");
	}
}

/// Pause. Call play() to resume.
void CSourceXAudio2::pause()
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "pause");

	if (_IsPaused) nlwarning(NLSOUND_XAUDIO2_PREFIX "Called pause() while _IsPaused == true!");

	if (_IsPlaying)
	{
		_IsPaused = true;
		if (FAILED(_SourceVoice->Stop(0))) 
			nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Stop");
	}
	else nlwarning(NLSOUND_XAUDIO2_PREFIX "Called pause() while _IsPlaying == false!");
}

/// Return the playing state
bool CSourceXAudio2::isPlaying() const
{
	// nlinfo(NLSOUND_XAUDIO2_PREFIX "isPlaying?");

	return _IsPlaying && !_IsPaused;
}

/// Return true if playing is finished or stop() has been called.
bool CSourceXAudio2::isStopped() const
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "isStopped?");
	
	return !_IsPlaying;
}

/// Return the paused state
bool CSourceXAudio2::isPaused() const
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "isStopped?");

	return _IsPaused;
}

/// Update the source (e.g. continue to stream the data in)
bool CSourceXAudio2::update()
{
	if (_IsPlaying)
	{
		XAUDIO2_VOICE_STATE voice_state;
		_SourceVoice->GetState(&voice_state);
		if (!voice_state.BuffersQueued)
		{
			if (FAILED(_SourceVoice->Stop(0))) 
				nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Stop");
			_IsPlaying = false;
		}
	}
	return true;
}

/// Returns the number of milliseconds the source has been playing
uint32 CSourceXAudio2::getTime()
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "getTime");

	// ----------------------------- todo

	return _IsPlaying ? (uint32)(CTime::getLocalTime() - _PlayStart) : 0;
}
//@}

/// \name Source properties
//@{
/** Set the position vector (default: (0,0,0)).
 * 3D mode -> 3D position
 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
 */
void CSourceXAudio2::setPos(const NLMISC::CVector& pos, bool deffered) // note: deferred with a different spelling
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setPos %f %f %f", pos.x, pos.y, pos.z);

	_Pos = pos; // getPos() sucks
	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Emitter.Position, pos);

	// !! todo if threaded: if (!deffered) { /* nlwarning(NLSOUND_XAUDIO2_PREFIX "!deffered"); */ commit3DChanges(); }
}

/** Get the position vector.
 * See setPos() for details.
 */
const NLMISC::CVector &CSourceXAudio2::getPos() const
{
	return _Pos;
}

/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
void CSourceXAudio2::setVelocity(const NLMISC::CVector& vel, bool deferred)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setVelocity %f %f %f", vel.x, vel.y, vel.z);

	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Emitter.Velocity, vel);

	// !! todo if threaded: if (!deferred) { /* nlwarning(NLSOUND_XAUDIO2_PREFIX "!deferred"); */ commit3DChanges(); }
}

/// Get the velocity vector
void CSourceXAudio2::getVelocity(NLMISC::CVector& vel) const
{
	NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(vel, _Emitter.Velocity);
}

/// Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
void CSourceXAudio2::setDirection(const NLMISC::CVector& dir)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setDirection %f %f %f", dir.x, dir.y, dir.z);

	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Emitter.OrientFront, dir);
}

/// Get the direction vector
void CSourceXAudio2::getDirection(NLMISC::CVector& dir) const
{
	NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(dir, _Emitter.OrientFront);
}

/** Set the gain (volume value inside [0 , 1]). (default: 1)
 * 0.0 -> silence
 * 0.5 -> -6dB
 * 1.0 -> no attenuation
 * values > 1 (amplification) not supported by most drivers
 */
void CSourceXAudio2::setGain(float gain)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setGain %f", gain);

	_Gain = gain;
	if (_SourceVoice) _SourceVoice->SetVolume(gain);
}

/// Get the gain
float CSourceXAudio2::getGain() const
{
	return _Gain;
}

/** Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
 * of one octave. 0 is not a legal value.
 */
void CSourceXAudio2::setPitch(float pitch)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setPitch %f", pitch);

	_Pitch = pitch;
	if (_SourceVoice)
	{
		if (_Format == Stereo16 || _Format == Stereo8) _SourceVoice->SetFrequencyRatio(_FreqRatio * _Pitch);
		else _SourceVoice->SetFrequencyRatio(_FreqRatio * _Pitch * _Doppler);
	}
}

/// Get the pitch
float CSourceXAudio2::getPitch() const
{
	return _Pitch;
}

/// Set the source relative mode. If true, positions are interpreted relative to the listener position
void CSourceXAudio2::setSourceRelativeMode(bool mode)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setSourceRelativeMode %u", (uint32)mode);

	_Relative = mode;
}

/// Get the source relative mode
bool CSourceXAudio2::getSourceRelativeMode() const
{
	return _Relative;
}

//nd_sources_df.exe : ----- setMinMaxDistances 1.200000, 1000.000000 ----
//df.exe :            ------- setCone 6.283185, 6.283185 ,0.000010 ----
//nd_sources_df.exe : ----- setMinMaxDistances 5.000000, 50.000000 -----
//df.exe :             ----- setCone 6.283185, 6.283185 ,0.000010 ------

/// Set the min and max distances (default: 1, MAX_FLOAT) (3D mode only)
void CSourceXAudio2::setMinMaxDistances(float mindist, float maxdist, bool deferred)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setMinMaxDistances %f, %f", mindist, maxdist);

	_MinDistance = mindist;
	_MaxDistance = maxdist;

	// !! todo if threaded: if (!deferred) { /* nlwarning(NLSOUND_XAUDIO2_PREFIX "!deferred"); */ commit3DChanges(); }
}

/// Get the min and max distances
void CSourceXAudio2::getMinMaxDistances(float& mindist, float& maxdist) const
{
	mindist = _MinDistance;
	maxdist = _MaxDistance;
}

/// Set the cone angles (in radian) and gain (in [0 , 1]) (default: 2PI, 2PI, 0)
void CSourceXAudio2::setCone(float innerAngle, float outerAngle, float outerGain)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setCone %f, %f ,%f", innerAngle, outerAngle, outerGain);
	
	if (innerAngle >= 6.283185f && outerAngle >= 6.283185f)
		_Emitter.pCone = NULL;
	else _Emitter.pCone = &_Cone;
	if (innerAngle > outerAngle)
	{
		nlwarning(NLSOUND_XAUDIO2_PREFIX "innerAngle > outerAngle");
		innerAngle = outerAngle;
	}
	_Cone.InnerAngle = innerAngle;
	_Cone.OuterAngle = outerAngle;
	_Cone.OuterVolume = outerGain;
}

/// Get the cone angles (in radian)
void CSourceXAudio2::getCone(float& innerAngle, float& outerAngle, float& outerGain) const
{
	innerAngle = _Cone.InnerAngle;
	outerAngle = _Cone.OuterAngle;
	outerGain = _Cone.OuterVolume;
}

/// Set any EAX source property if EAX available
void CSourceXAudio2::setEAXProperty(uint prop, void *value, uint valuesize)
{
	// nldebug(NLSOUND_XAUDIO2_PREFIX "setEAXProperty %u, %u, %u", (uint32)prop, (uint32)value, (uint32)valuesize);
}

///** Set the alpha value for the volume-distance curve
// *
// *	Usefull only if MANUAL_ROLLOFF==1. value from -1 to 1 (default 0)
// * 
// *  alpha.0: the volume will decrease linearly between 0dB and -100 dB
// *  alpha = 1.0: the volume will decrease linearly between 1.0 and 0.0 (linear scale)
// *  alpha = -1.0: the volume will decrease inversely with the distance (1/dist). This
// *                is the default used by DirectSound/OpenAL
// * 
// *  For any other value of alpha, an interpolation is be done between the two
// *  adjacent curves. For example, if alpha equals 0.5, the volume will be halfway between
// *  the linear dB curve and the linear amplitude curve.
// */
///// 
void CSourceXAudio2::setAlpha(double a) 
{  
	// if (a != 1.0) nldebug(NLSOUND_XAUDIO2_PREFIX "setAlpha %f", (float)a);

	_Alpha = a;
}

} /* namespace NLSOUND */

/* end of file */
