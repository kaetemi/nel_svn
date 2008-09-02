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

// Project includes
//#include "buffer_xaudio2.h"
#include "listener_xaudio2.h"

// NeL includes
#include <nel/misc/hierarchical_timer.h>
#include <nel/misc/debug.h>

// STL includes
#include <cfloat>
#include <algorithm>
#include <limits>

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CSourceXAudio2::CSourceXAudio2(CSoundDriverXAudio2 *soundDriver) 
: _SoundDriver(soundDriver), _SampleVoice(NULL), _NextBuffer(NULL), _HasBuffer(NULL), 
_Doppler(1.0f), _Pitch(1.0f), _IsPlaying(false), _IsLooping(false), _Relative(false), _Gain(1.0f), 
_MinDistance(1.0f), _MaxDistance(numeric_limits<float>::max())
{
	nlwarning("Inititializing CSourceXAudio2");

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
	nlwarning("Destroying CSourceXAudio2");

	release();
}

void CSourceXAudio2::release() // called by driver :)
{
	if (_SampleVoice)
	{
		_SampleVoice->setOwner(NULL); // make sure no more callbacks arrive here while releasing
		delete _SampleVoice; _SampleVoice = NULL; // delete instead of putting back into pool
	}
	_SoundDriver->removeSource(this);
}

/// Commit all the changes made to 3D settings of listener and sources
void CSourceXAudio2::commit3DChanges()
{
	if (_HasBuffer && _IsPlaying/* && _SampleVoice->getBuffer()*/)
	{
		nlassert(_SampleVoice);
		
		// Only mono buffers get 3d sound, stereo buffers go directly to the speakers.
		if (_SampleVoice->getFormat() != Stereo16 && _SampleVoice->getFormat() != Stereo8)
		{
			_Emitter.DopplerScaler = _SoundDriver->getListener()->getDopplerScaler();
			_Emitter.CurveDistanceScaler = _MinDistance * _SoundDriver->getListener()->getDistanceScaler(); // might be just _MinDistance, not sure, compare with fmod driver
			// _MaxDistance not implemented (basically cuts off sound beyond maxdistance)

			X3DAudioCalculate(_SoundDriver->getX3DAudio(), 
				_Relative 
					? _SoundDriver->getEmptyListener() // position is relative to listener (we use 0pos listener)
					: _SoundDriver->getListener()->getListener(), // position is absolute
				&_Emitter, 
				X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER, 
				_SoundDriver->getDSPSettings());
			_SampleVoice->getSourceVoice()->SetOutputMatrix(
				// _SoundDriver->getMasteringVoice(),
				_SoundDriver->getListener()->getSubmixVoice(), 
				_SoundDriver->getDSPSettings()->SrcChannelCount, 
				_SoundDriver->getDSPSettings()->DstChannelCount, 
				_SoundDriver->getDSPSettings()->pMatrixCoefficients);
			// nldebug("left: %f, right %f", _SoundDriver->getDSPSettings()->pMatrixCoefficients[0], _SoundDriver->getDSPSettings()->pMatrixCoefficients[1]);
			_Doppler = _SoundDriver->getDSPSettings()->DopplerFactor;
			_SampleVoice->setPitch(_Doppler * _Pitch);
		}
	}

	// todo: reverb & delay? ^^
}

void CSourceXAudio2::cbVoiceProcessingPassStart(uint32 BytesRequired)
{    
	
}

void CSourceXAudio2::cbVoiceProcessingPassEnd()
{ 
	
}

void CSourceXAudio2::cbStreamEnd()
{ 
	
}

void CSourceXAudio2::cbBufferStart(CBufferXAudio2 *pBufferContext)
{    
	////// update buffer frequency :) todo: take into account other frequency modifiers!!
	// done in sample voice class :)
	////IBuffer *buffer = (IBuffer *)pBufferContext; // loool
	////_SourceVoice->SetFrequencyRatio((double)((CBufferXAudio2 *)buffer)->getFreq() 
	////	/ (double)NLSOUND_XAUDIO2_SOURCE_SAMPLES_PER_SEC);
	////// check how SetFrequencyRatio can be used to change the pitch vs changing bitrate/speed!!!!
	////// note: nel change pitch does change speed in other drivers too, so SetFreq is ok. :)
}

void CSourceXAudio2::cbBufferEnd(CBufferXAudio2 *pBufferContext)
{ 
	// if need to change format, call destroy with stop set to false !!!
	_Mutex.enter(); // _NextBuffer, startNextBuffer, _HasBuffer
	if (_NextBuffer) startNextBuffer();
	else if (_IsLooping && pBufferContext == _HasBuffer) // loop was called after setting buffer without looping, resume buffer
	{
		XAUDIO2_BUFFER xbuffer;
		xbuffer.AudioBytes = _HasBuffer->getSize();
		xbuffer.Flags = 0;
		xbuffer.LoopBegin = 0;
		xbuffer.LoopCount =  XAUDIO2_LOOP_INFINITE;
		xbuffer.LoopLength = 0;
		xbuffer.pAudioData = _HasBuffer->getData();
		xbuffer.pContext = _HasBuffer;
		xbuffer.PlayBegin = 0;
		xbuffer.PlayLength = 0;

		if (_SampleVoice) _SampleVoice->getSourceVoice()->SubmitSourceBuffer(&xbuffer);
	}
	else _HasBuffer = NULL;
	_Mutex.leave();
}

void CSourceXAudio2::cbLoopEnd(CBufferXAudio2 *pBufferContext)
{    
	
}

void CSourceXAudio2::cbVoiceError(CBufferXAudio2 *pBufferContext, HRESULT Error)
{ 
	////nlwarning(NLSOUND_XAUDIO2_PREFIX "CSourceXAudio2::OnVoiceError");
	////nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	////release();
	////init();
	////// todo: put everything back in as it should!
}

/// \name Initialization
//@{
/** Set the buffer that will be played (no streaming)
 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
 * otherwise the source is considered as a 3D source.
 */
void CSourceXAudio2::setStaticBuffer(IBuffer *buffer)
{
	nlinfo("setStaticBuffer %s", buffer->getName());

	_Mutex.enter(); // _NextBuffer, startNextBuffer, _HasBuffer
	_NextBuffer = (CBufferXAudio2 *)buffer;
	if (!_HasBuffer) 
	{
		_HasBuffer = _NextBuffer;
		startNextBuffer();
	}
	_Mutex.leave();

	
	/*nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return;*/
}

void CSourceXAudio2::startNextBuffer() // note: called from callback !!! -- don't flush buffer & must call from mutexed!
{
	if (!_NextBuffer) return;

	bool change = false;
	if (_SampleVoice)
	{
		if (_SampleVoice->getFormat() != _NextBuffer->getFormat())
		{
			// remove this debug info, or glitches may happen on sound
			nlwarning(NLSOUND_XAUDIO2_PREFIX "_SampleVoice->getFormat() != _NextBuffer->getFormat()");
			_SoundDriver->destroySampleVoice(_SampleVoice, false); // don't set to null!
			change = true;
		}
	}
	else { change = true; }
	if (change)
	{
		// update values to new voice
		_SampleVoice = _SoundDriver->createSampleVoice(this, _NextBuffer->getFormat());
		_SampleVoice->getSourceVoice()->SetVolume(_Gain);
		if (_SampleVoice->getFormat() != Stereo16 && _SampleVoice->getFormat() != Stereo8)
			_SampleVoice->setPitch(_Pitch * _Doppler);
		else _SampleVoice->setPitch(_Pitch);
		if (_IsPlaying) _SampleVoice->getSourceVoice()->Start(0);
	}

	XAUDIO2_BUFFER xbuffer;
	xbuffer.AudioBytes = _NextBuffer->getSize();
	xbuffer.Flags = 0;
	xbuffer.LoopBegin = 0;
	xbuffer.LoopCount = _IsLooping ? XAUDIO2_LOOP_INFINITE : 0;
	xbuffer.LoopLength = 0;
	xbuffer.pAudioData = _NextBuffer->getData();
	xbuffer.pContext = _NextBuffer; // neat :)
	xbuffer.PlayBegin = 0;
	xbuffer.PlayLength = 0;

	_SampleVoice->getSourceVoice()->SubmitSourceBuffer(&xbuffer);

	_NextBuffer = NULL;
	// _HasBuffer = true; // is called from setStaticBuffer :)
}

/// Return the buffer, or NULL if streaming is used.
IBuffer *CSourceXAudio2::getStaticBuffer()
{
	return _HasBuffer;
}

///** Set the sound loader that will be used to stream in the data to play
// * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
// * otherwise the source is considered as a 3D source.
// */
//void CSourceXAudio2::setStreamLoader(ILoader *loader) { _Loader = loader; }
//@}


/// \name Playback control
//@{
/// Set looping on/off for future playbacks (default: off) // doesn't seem to be future playbacks though >_>
void CSourceXAudio2::setLooping(bool l)
{
	nlinfo("setLooping %u", (uint32)l);
	
	if (_IsLooping != l)
	{
		if (l)
		{
			_Mutex.enter();
			_IsLooping = true;
			_Mutex.leave();
		}
		else
		{
			_Mutex.enter();
			_IsLooping = false;
			_Mutex.leave();
			_SampleVoice->getSourceVoice()->ExitLoop();
		}
	}
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
	nlinfo("play");

	if (_SampleVoice)
	{
		_IsPlaying = true;
		commit3DChanges(); // ensure awesomeness :)
		return SUCCEEDED(_SampleVoice->getSourceVoice()->Start(0));
	}
	return false;
}

/// Stop playing
void CSourceXAudio2::stop()
{
	nlinfo("stop");

	_IsPlaying = false;
	if (_SampleVoice)
	{
		_Mutex.enter();
		_HasBuffer = NULL;
		_NextBuffer = NULL;
		_Mutex.leave();
		if (FAILED(_SampleVoice->getSourceVoice()->Stop(0))) 
			nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Stop");
		if (FAILED(_SampleVoice->getSourceVoice()->FlushSourceBuffers())) 
			nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED FlushSourceBuffers");
	}
}

/// Pause. Call play() to resume.
void CSourceXAudio2::pause()
{
	nlinfo("pause");

	if (FAILED(_SampleVoice->getSourceVoice()->Stop(0))) 
		nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED Stop");
}

/// Return the playing state
bool CSourceXAudio2::isPlaying() const
{
	nlinfo("isPlaying?");

	return _IsPlaying && _HasBuffer;// && !_IsPaused;
}

/// Return true if playing is finished or stop() has been called.
bool CSourceXAudio2::isStopped() const
{
	nlinfo("isStopped?");

	return !_IsPlaying || !_HasBuffer;
}

/// Update the source (e.g. continue to stream the data in)
bool CSourceXAudio2::update()
{
	return true; // nothing to do here :)
}

/// Returns the number of milliseconds the source has been playing
uint32 CSourceXAudio2::getTime()
{
	nlinfo("getTime");

	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return 0;
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
	nlinfo("setPos %f %f %f", pos.x, pos.y, pos.z);

	_Pos = pos; // getPos() sucks
	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Emitter.Position, pos);
	if (!deffered) { /* nlwarning("!deffered"); */ commit3DChanges(); }
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
	nlinfo("setVelocity %f %f %f", vel.x, vel.y, vel.z);

	NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(_Emitter.Velocity, vel);
	if (!deferred) { /* nlwarning("!deferred"); */ commit3DChanges(); }
}

/// Get the velocity vector
void CSourceXAudio2::getVelocity(NLMISC::CVector& vel) const
{
	NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(vel, _Emitter.Velocity);
}

/// Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
void CSourceXAudio2::setDirection(const NLMISC::CVector& dir)
{
	nlinfo("setDirection %f %f %f", dir.x, dir.y, dir.z);

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
	nlinfo("setGain %f", gain);

	_Gain = gain;
	if (_SampleVoice) _SampleVoice->getSourceVoice()->SetVolume(gain);
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
	nlinfo("setPitch %f", pitch);

	_Pitch = pitch;
	if (_SampleVoice)
	{
		if (_SampleVoice->getFormat() != Stereo16 && _SampleVoice->getFormat() != Stereo8)
			_SampleVoice->setPitch(_Pitch * _Doppler);
		else _SampleVoice->setPitch(_Pitch);
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
	nlinfo("setSourceRelativeMode %u", (uint32)mode);

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
	nlinfo("setMinMaxDistances %f, %f", mindist, maxdist);
	_MinDistance = mindist;
	_MaxDistance = maxdist;
	if (!deferred) { /* nlwarning("!deferred"); */ commit3DChanges(); }
}

/// Get the min and max distances
void CSourceXAudio2::getMinMaxDistances(float& mindist, float& maxdist) const
{
	mindist = _MinDistance;
	maxdist = _MaxDistance;
}

//.\source_xaudio2.cpp(498) : NLSOUND::CSourceXAudio2::setMinMaxDistances INF  938: setMinMaxDistances 4.000000, 25.000000
//.\source_xaudio2.cpp(514) : NLSOUND::CSourceXAudio2::setCone INF  938: setCone 6.283185, 6.283185 ,0.000010
//******************************************************************************
//*** XAPO ASSERT: iSrcOffset == (NWORD)uSrcSampleCount || iSrcOffset == (NWORD)uSrcSampleCount-1 || iSrcOffset == (NWORD)uSrcSampleCount-1*2, {ResampleLinearFromInt16MonoSse2, Line 1029}
//******************************************************************************
//XAUDIO2: WARNING: Spent 56970.19ms in audio thread; XAudio2 possibly overloaded
//################################################################################
//### XAUDIO2: src_fast.cpp:554: 
//### ASSERT FAILED: m_SRCParameters.iSrcOffset == -m_SRCParameters.iChannelCount || m_SRCParameters.iSrcOffset == 0
//################################################################################
//******************************************************************************
//*** XAPO ASSERT: pSRCParameters->iSrcOffset == -1 || pSRCParameters->iSrcOffset == 0, {ResampleLinearFromInt16MonoSse2, Line 917}
//******************************************************************************

/// Set the cone angles (in radian) and gain (in [0 , 1]) (default: 2PI, 2PI, 0)
void CSourceXAudio2::setCone(float innerAngle, float outerAngle, float outerGain)
{
	nlinfo("setCone %f, %f ,%f", innerAngle, outerAngle, outerGain);
	// X3DAUDIO_2PI 6.283185307f
	//      setCone 6.283185, 6.283185 ,0.000010
	//NLMISC_2
	if (innerAngle >= 6.283185 && outerAngle >= 6.283185)
		_Emitter.pCone = NULL;
	else _Emitter.pCone = &_Cone;
	if (innerAngle > outerAngle)
	{
		nlwarning("innerAngle > outerAngle");
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
	nlinfo("setEAXProperty %u, %u, %u", (uint32)prop, (uint32)value, (uint32)valuesize);
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
//void setAlpha(double a) {  }

} /* namespace NLSOUND */

/* end of file */
