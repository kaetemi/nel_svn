/** \file source_al.cpp
 * OpenAL sound source
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "stdopenal.h"
#include "source_al.h"

#include "sound_driver_al.h"
#include "effect_al.h"
#include "buffer_al.h"

using namespace NLMISC;


namespace NLSOUND {


/*
 * Constructor
 */
CSourceAL::CSourceAL(ALuint sourcename) :
	_Buffer(NULL), _SourceName(sourcename), 
	_IsPlaying(false), _IsPaused(false), 
	_Pos(0.0f, 0.0f, 0.0f)
{
	
}


/*
 * Destructor
 */
CSourceAL::~CSourceAL()
{
	CSoundDriverAL *sdal = CSoundDriverAL::getInstance();
	//if (_Buffer != NULL)
	//	sdal->removeBuffer(_Buffer);
	sdal->removeSource(this);
}

void CSourceAL::setEffect(CEffectAL *effect)
{
	// no filter stuff yet
	// only allow one submix send for now -----------------------------------------------> 0
	if (effect) { /*nldebug("AL: Setting effect");*/ alSource3i(_SourceName, AL_AUXILIARY_SEND_FILTER, effect->getAuxEffectSlot(), 0, AL_FILTER_NULL); }
	else { /*nldebug("AL: Removing effect");*/ alSource3i(_SourceName, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL); }
	alTestError();
}

void CSourceAL::setEffect(IReverbEffect *reverbEffect)
{
	setEffect(reverbEffect ? dynamic_cast<CEffectAL *>(reverbEffect) : NULL);
}

/// Enable or disable streaming mode. Source must be stopped to call this.
void CSourceAL::setStreaming(bool /* streaming */)
{
	nlassert(isStopped());

	// bring the source type to AL_UNDETERMINED
	alSourcei(_SourceName, AL_BUFFER, AL_NONE);
	alTestError();
	_Buffer = NULL;
}

/* Set the buffer that will be played (no streaming)
 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
 * otherwise the source is considered as a 3D source.
 */
void CSourceAL::setStaticBuffer( IBuffer *buffer )
{
	// Stop source
	alSourceStop( _SourceName );
	alTestError();

	// Set buffer
	if ( buffer == NULL )
	{
		alSourcei( _SourceName, AL_BUFFER, AL_NONE );
		alTestError();
		_Buffer = NULL;
	}
	else
	{
		CBufferAL *bufferAL = dynamic_cast<CBufferAL *>(buffer);
		alSourcei( _SourceName, AL_BUFFER, bufferAL->bufferName() );
		alTestError();

		// Set relative mode if the buffer is stereo
		setSourceRelativeMode( bufferAL->isStereo() );

		_Buffer = bufferAL;
	}
}


IBuffer *CSourceAL::getStaticBuffer()
{
	return _Buffer;
}

/// Add a buffer to the streaming queue.  A buffer of 100ms length is optimal for streaming.
/// Should be called by a thread which checks countStreamingBuffers every 100ms.
void CSourceAL::submitStreamingBuffer(IBuffer *buffer)
{
	CBufferAL *bufferAL = static_cast<CBufferAL *>(buffer);
	ALuint bufferName = bufferAL->bufferName();
	nlassert(bufferName);
	alSourceQueueBuffers(_SourceName, 1, &bufferName);
	alTestError();
	_QueuedBuffers.push(bufferAL);
}

/// Return the amount of buffers in the queue (playing and waiting). 3 buffers is optimal.
uint CSourceAL::countStreamingBuffers() const
{
	// a bit ugly here, but makes a much easier/simpler implementation on both drivers
	ALint buffersProcessed;
	alGetSourcei(_SourceName, AL_BUFFERS_PROCESSED, &buffersProcessed);
	while (buffersProcessed)
	{
		ALuint bufferName = _QueuedBuffers.front()->bufferName();
		alSourceUnqueueBuffers(_SourceName, 1, &bufferName);
		alTestError();
		const_cast<std::queue<CBufferAL *> &>(_QueuedBuffers).pop();
		--buffersProcessed;
	}
	// return how many are left in the queue
	//ALint buffersQueued;
	//alGetSourcei(_SourceName, AL_BUFFERS_QUEUED, &buffersQueued);
	//alTestError();
	//return (uint)buffersQueued;
	return (uint)_QueuedBuffers.size();
}

/*
 * Set looping on/off for future playbacks (default: off)
 */
void CSourceAL::setLooping( bool l )
{
	alSourcei( _SourceName, AL_LOOPING, l?AL_TRUE:AL_FALSE );
	alTestError();
}


/*
 * Return the looping state
 */
bool CSourceAL::getLooping() const
{
	ALint b;
	alGetSourcei( _SourceName, AL_LOOPING, &b );
	alTestError();
	return ( b == AL_TRUE );
}


/*
 * Play the static buffer (or stream in and play)
 */
bool CSourceAL::play()
{
	if ( _Buffer != NULL )
	{
		// Static playing mode
		_IsPlaying = true;
		_IsPaused = false;
		alSourcePlay(_SourceName);
		return alGetError() == AL_NO_ERROR;
	}
	else
	{
		// TODO: Verify streaming mode?
		_IsPlaying = true;
		_IsPaused = false;
		alSourcePlay(_SourceName);
		return alGetError() == AL_NO_ERROR;
		// Streaming mode
		//nlwarning("AL: Cannot play null buffer; streaming not implemented" );
		//nlstop;
	}
}


/*
 * Stop playing
 */
void CSourceAL::stop()
{
	if ( _Buffer != NULL )
	{
		// Static playing mode
		_IsPlaying = false;
		_IsPaused = false;
		alSourceStop(_SourceName);
		alTestError();
	}
	else
	{
		// TODO: Verify streaming mode?
		_IsPlaying = false;
		_IsPaused = false;
		alSourceStop(_SourceName);
		alTestError();
		// unqueue buffers
		while (_QueuedBuffers.size())
		{
			ALuint bufferName = _QueuedBuffers.front()->bufferName();
			alSourceUnqueueBuffers(_SourceName, 1, &bufferName);
			_QueuedBuffers.pop();
			alTestError();
		}
		// Streaming mode
		//nlwarning("AL: Cannot stop null buffer; streaming not implemented" );
		//nlstop;
	}
}


/*
 * Pause. Call play() to resume.
 */
void CSourceAL::pause()
{
	if ( _Buffer != NULL )
	{
		if (_IsPaused) nlwarning("AL: Called pause() while _IsPaused == true!");

		// Static playing mode
		if (!isStopped())
		{
			_IsPaused = true;
			alSourcePause( _SourceName );
			alTestError();
		}
	}
	else
	{
		// TODO: Verify streaming mode?
		_IsPaused = true;
		alSourcePause( _SourceName );
		alTestError();
		// Streaming mode
		//nlwarning("AL: Cannot pause null buffer; streaming not implemented" );
		//nlstop;
	}
}

/// Return true if play() or pause(), false if stop().
bool CSourceAL::isPlaying() const
{
	//return !isStopped() && !_IsPaused;
	ALint srcstate;
	alGetSourcei(_SourceName, AL_SOURCE_STATE, &srcstate);
	alTestError();
	return (srcstate == AL_PLAYING || srcstate == AL_PAUSED);
}

/// Return true if playing is finished or stop() has been called.
bool CSourceAL::isStopped() const
{
	//if (_IsPlaying)
	//{
	//	if (!_IsPaused)
	//	{
	ALint srcstate;
	alGetSourcei(_SourceName, AL_SOURCE_STATE, &srcstate);
	alTestError();
	return (srcstate == AL_STOPPED || srcstate == AL_INITIAL);
	//	}
	//	return false;
	//}
	//return true;
}

/// Return true if the playing source is paused
bool CSourceAL::isPaused() const
{
	ALint srcstate;
	alGetSourcei(_SourceName, AL_SOURCE_STATE, &srcstate);
	alTestError();
	return (srcstate == AL_PAUSED);
}

/// Returns the number of milliseconds the source has been playing
uint32 CSourceAL::getTime()
{
	// TODO
	return 0;
}

/* Set the position vector.
 * 3D mode -> 3D position
 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
 */
void CSourceAL::setPos(const NLMISC::CVector& pos, bool /* deffered */)
{
	_Pos = pos;
	// Coordinate system: conversion from NeL to OpenAL/GL:
	alSource3f( _SourceName, AL_POSITION, pos.x, pos.z, -pos.y );
	alTestError();
}


/* Get the position vector.
 * See setPos() for details.
 */
const NLMISC::CVector &CSourceAL::getPos() const
{
	return _Pos;
}


/*
 * Set the velocity vector (3D mode only)
 */
void CSourceAL::setVelocity( const NLMISC::CVector& vel, bool /* deferred */)
{
	// Coordsys conversion
	alSource3f( _SourceName, AL_VELOCITY, vel.x, vel.z, -vel.y );
	alTestError();
}


/*
 * Get the velocity vector
 */
void CSourceAL::getVelocity( NLMISC::CVector& vel ) const
{
	ALfloat v[3];
	alGetSourcefv( _SourceName, AL_VELOCITY, v );
	alTestError();
	// Coordsys conversion
	vel.set( v[0], -v[2], v[1] );
}


/*
 * Set the direction vector (3D mode only)
 */
void CSourceAL::setDirection( const NLMISC::CVector& dir )
{
	// Coordsys conversion
	alSource3f( _SourceName, AL_DIRECTION, dir.x, dir.z, -dir.y );
	alTestError();
}


/*
 * Get the direction vector
 */
void CSourceAL::getDirection( NLMISC::CVector& dir ) const
{
	ALfloat v[3];
	alGetSourcefv( _SourceName, AL_DIRECTION, v );
	alTestError();
	// Coordsys conversion
	dir.set( v[0], -v[2], v[1] );
}


/* Set the gain (volume value inside [0 , 1]).
 * 0.0 -> silence
 * 0.5 -> -6dB
 * 1.0 -> no attenuation
 * values > 1 (amplification) not supported by most drivers
 */
void CSourceAL::setGain( float gain )
{
	clamp(gain, 0.0f, 1.0f);
	alSourcef( _SourceName, AL_GAIN, gain );
	alTestError();
}


/*
 * Get the gain
 */
float CSourceAL::getGain() const
{
	ALfloat gain;
	alGetSourcef( _SourceName, AL_GAIN, &gain );
	alTestError();
	return gain;
}


/* Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
 * of one octave. 0 is not a legal value.
 */
void CSourceAL::setPitch( float pitch )
{
	nlassert(pitch > 0);
	alSourcef(_SourceName, AL_PITCH, pitch);
	alTestError();
}


/*
 * Get the pitch
 */
float CSourceAL::getPitch() const
{
	ALfloat pitch;
	alGetSourcef( _SourceName, AL_PITCH, &pitch );
	alTestError();
	return pitch;
}


/*
 * Set the source relative mode. If true, positions are interpreted relative to the listener position.
 */
void CSourceAL::setSourceRelativeMode( bool mode )
{
	alSourcei( _SourceName, AL_SOURCE_RELATIVE, mode?AL_TRUE:AL_FALSE );
	alTestError();
}


/*
 * Get the source relative mode (3D mode only)
 */
bool CSourceAL::getSourceRelativeMode() const
{
	ALint b;
	alGetSourcei( _SourceName, AL_SOURCE_RELATIVE, &b );
	alTestError();
	return (b==AL_TRUE);
}


/*
 * Set the min and max distances (3D mode only)
 */
void CSourceAL::setMinMaxDistances( float mindist, float maxdist, bool /* deferred */)
{
	nlassert( (mindist >= 0.0f) && (maxdist >= 0.0f) );
	alSourcef( _SourceName, AL_REFERENCE_DISTANCE, mindist );
	alSourcef( _SourceName, AL_MAX_DISTANCE, maxdist );
	alTestError();
}


/*
 * Get the min and max distances
 */
void CSourceAL::getMinMaxDistances( float& mindist, float& maxdist ) const
{
	alGetSourcef( _SourceName, AL_REFERENCE_DISTANCE, &mindist );
	alGetSourcef( _SourceName, AL_MAX_DISTANCE, &maxdist );
	alTestError();
}


/*
 * Set the cone angles (in radian) and gain (in [0 , 1]) (3D mode only)
 */
void CSourceAL::setCone( float innerAngle, float outerAngle, float outerGain )
{
	nlassert( (outerGain >= 0.0f) && (outerGain <= 1.0f ) );
	alSourcef( _SourceName, AL_CONE_INNER_ANGLE, radToDeg(innerAngle) );
	alSourcef( _SourceName, AL_CONE_OUTER_ANGLE, radToDeg(outerAngle) );
	alSourcef( _SourceName, AL_CONE_OUTER_GAIN, outerGain );
	alTestError();
}


/*
 * Get the cone angles (in radian)
 */
void CSourceAL::getCone( float& innerAngle, float& outerAngle, float& outerGain ) const
{
	float ina, outa;
	alGetSourcef( _SourceName, AL_CONE_INNER_ANGLE, &ina );
	innerAngle = degToRad(ina);
	alGetSourcef( _SourceName, AL_CONE_OUTER_ANGLE, &outa );
	outerAngle = degToRad(outa);
	alGetSourcef( _SourceName, AL_CONE_OUTER_GAIN, &outerGain );
	alTestError();
}

/** Set the alpha value for the volume-distance curve
 *
 *	Useful only with OptionManualRolloff. value from -1 to 1 (default 0)
 *
 *  alpha.0: the volume will decrease linearly between 0dB and -100 dB
 *  alpha = 1.0: the volume will decrease linearly between 1.0 and 0.0 (linear scale)
 *  alpha = -1.0: the volume will decrease inversely with the distance (1/dist). This
 *                is the default used by DirectSound/OpenAL
 *
 *  For any other value of alpha, an interpolation is be done between the two
 *  adjacent curves. For example, if alpha equals 0.5, the volume will be halfway between
 *  the linear dB curve and the linear amplitude curve.
 */
void CSourceAL::setAlpha(double /* a */)
{
	// throw ESoundDriverNoManualRolloff();
}


///*
// * Set any EAX source property if EAX available
// */
//void CSourceAL::setEAXProperty( uint prop, void *value, uint valuesize )
//{
//#if EAX_AVAILABLE == 1
//	if (AlExtEax)
//	{
//		eaxSet( &DSPROPSETID_EAX_SourceProperties, prop, _SourceName, value, valuesize );
//	}
//#endif
//}


} // NLSOUND
