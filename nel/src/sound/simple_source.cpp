/** \file simple_source.cpp
 * CSimpleSource: implementation of USource
 *
 * $Id: simple_source.cpp,v 1.9 2004/11/15 10:25:07 lecroart Exp $
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

#include "stdsound.h"

#include "simple_source.h"
#include "driver/buffer.h"
#include "driver/source.h"
#include "mixing_track.h"
#include "simple_sound.h"
#include "clustered_sound.h"

using namespace NLMISC;


namespace NLSOUND 
{


/*
 * Constructor
 */
CSimpleSource::CSimpleSource( CSimpleSound *simpleSound, bool spawn, TSpawnEndCallback cb, void *cbUserParam, NL3D::CCluster *cluster)
:	CSourceCommon(simpleSound, spawn, cb, cbUserParam, cluster),
	_Track(NULL), _PlayMuted(false)
{
	nlassert(simpleSound != 0);
	_Sound = simpleSound;

	// get a local copy of the simple sound parameter
	_Alpha = _Sound->getAlpha();
}


/*
 * Destructor
 */
CSimpleSource::~CSimpleSource()
{
	if (_Playing)
		stop();
	// Yoyo: security. with prec stop(), should not be needed, but a crash still raise 
	// in "currentEvent->onEvent();" in audio_mixer_user.cpp
	CAudioMixerUser::instance()->removeEvents(this);
}

CSimpleSound	*CSimpleSource::getSimpleSound()
{
	return _Sound;
}

uint32	CSimpleSource::getTime()
{
	if (_Track && _Track->DrvSource)
	{
		return _Track->DrvSource->getTime();
	}
	else
		return 0;
}


IBuffer					*CSimpleSource::getBuffer()
{
	return _Sound->getBuffer();
}




/*
 * Set looping on/off for future playbacks (default: off)
 */
void					CSimpleSource::setLooping( bool l )
{
	CSourceCommon::setLooping(l);
	if ( _Track != NULL )
	{
		_Track->DrvSource->setLooping( l );
	}
}


CVector		CSimpleSource::getVirtualPos() const
{
	if (getCluster() != 0)
	{
		// need to check the cluster status
		const CClusteredSound::CClusterSoundStatus *css = CAudioMixerUser::instance()->getClusteredSound()->getClusterSoundStatus(getCluster());
		if (css != 0)
		{
			// there is some data here, update the virtual position of the sound.
			float dist = (css->Position - getPos()).norm();
			CVector vpos(CAudioMixerUser::instance()->getListenPosVector() + css->Direction * (css->Dist + dist));
			vpos = _Position * (1-css->PosAlpha) + vpos*(css->PosAlpha);
			return vpos;
		}
	}

	return _Position;
}


/*
 * Play
 */
void					CSimpleSource::play()
{
//	nldebug("CSimpleSource %p : play", this);

	CAudioMixerUser *mixer = CAudioMixerUser::instance();

	// -- Some test to scheck if we can play the source
	
	// Check if sample buffer is available and if the sound source is not too far
	if (_Sound->getBuffer() == 0 
		|| !_Sound->getBuffer()->isBufferLoaded()
		|| (mixer->getListenPosVector() - _Position).sqrnorm() > _Sound->getMaxDistance()*_Sound->getMaxDistance())
	{
		// The sample buffer is not available, don't play (we don't know the lenght)
		if (_Spawn)
		{
			if (_SpawnEndCb != 0)
				_SpawnEndCb(this, _CbUserParam);

			delete this;
		}
//		nldebug("CSimpleSource %p : play FAILED !", (CAudioMixerUser::IMixerEvent*)this);
		return;
	}

	// -- Here we can play the source, either in a real track or as a muted source.

	// Try to obtain a track
	if (_Track == 0)
		_Track = mixer->getFreeTrack(this);
	if (_Track != 0)
	{
		// ok, we have a track to realy play, fill the data into the track
		_Track->DrvSource->setStaticBuffer(_Sound->getBuffer());

//		_Track->DrvSource->setPos( _Position, false);
		_Track->DrvSource->setPos( getVirtualPos(), false);
		if ( ! _Sound->getBuffer()->isStereo() )
		{
			_Track->DrvSource->setMinMaxDistances( _Sound->getMinDistance(), _Sound->getMaxDistance(), false );
			setDirection( _Direction ); // because there is a workaround inside
			_Track->DrvSource->setVelocity( _Velocity );
		}
		_Track->DrvSource->setGain( _Gain );
		_Track->DrvSource->setSourceRelativeMode( _RelativeMode );
		_Track->DrvSource->setLooping( _Looping );
		_Track->DrvSource->setPitch( _Pitch );
		_Track->DrvSource->setAlpha( _Alpha );
		
		// and play the sound		
		bool play = _Track->DrvSource->play();

		nlassert(play);
//		nldebug("CSimpleSource %p : REAL play done", (CAudioMixerUser::IMixerEvent*)this);
	}
	else
	{
		if (_Priority == HighestPri)
		{
			// This sound is not discardable, add it in waiting playlist
			mixer->addSourceWaitingForPlay(this);
			return;
		}
		// there is no available track, just do a 'muted' play
		mixer->addEvent(this, CTime::getLocalTime()+_Sound->getDuration());
		_PlayMuted = true;
		mixer->incPlayingSourceMuted();
//		nldebug("CSimpleSource %p : MUTED play done", (CAudioMixerUser::IMixerEvent*)this);
	}

	CSourceCommon::play();

}

void CSimpleSource::onEvent()
{
//	nldebug("CSimpleSource %p : stop EVENT", (CAudioMixerUser::IMixerEvent*)this);
	// A muted play is terminated.
	if (!_Playing)
		return;
//	nlassert(_Playing);
//	nlassert(_Track == 0);
	_PlayMuted = false;
	CAudioMixerUser::instance()->decPlayingSourceMuted();

	stop();
}

/*
 * Stop playing
 */
void					CSimpleSource::stop()
{
//	nldebug("CSimpleSource %p : stop", (CAudioMixerUser::IMixerEvent*)this);
//	nlassert(_Playing);
	if (!_Playing)
		return;

	if (_Track != 0)
	{
		// free the track
		_Track->DrvSource->stop();
		_Track->DrvSource->setStaticBuffer(0);
		CAudioMixerUser::instance()->freeTrack(_Track);
		_Track = 0;
	}
	else if (_PlayMuted)
	{
		// clear the registered event because of a stop before normal end of play
		CAudioMixerUser::instance()->decPlayingSourceMuted();
		CAudioMixerUser::instance()->removeEvents(this);
	}

//	CAudioMixerUser::instance()->decPlayingSource();
	CSourceCommon::stop();

	if (_Spawn)
	{
		if ( _SpawnEndCb != 0 )
		{
			_SpawnEndCb( this, _CbUserParam);
		}

		delete this;
	}
}


/* Set the position vector (default: (0,0,0)).
 * 3D mode -> 3D position
 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
 */
void					CSimpleSource::setPos( const NLMISC::CVector& pos )
{
	CSourceCommon::setPos(pos);

	// Set the position
	if ( _Track != NULL )
	{
//		_Track->DrvSource->setPos( pos );
		_Track->DrvSource->setPos( getVirtualPos() );
	}
}


/*
 * Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
 */
void					CSimpleSource::setVelocity( const NLMISC::CVector& vel )
{
	CSourceCommon::setVelocity(vel);

	// Set the velocity
	if ( _Track != NULL )
	{
		// TODO : uncoment, test only	
		_Track->DrvSource->setVelocity( vel );
	}
}


/*
 * Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
 */
void					CSimpleSource::setDirection( const NLMISC::CVector& dir )
{
	CSourceCommon::setDirection(dir);

	// Set the direction
	if ( _Track != NULL )
	{
		if ( ! _Sound->getBuffer()->isStereo() )
		{
			static bool coneset = false;
			if ( dir.isNull() ) // workaround
			{
				_Track->DrvSource->setCone( float(Pi*2), float(Pi*2), 1.0f ); // because the direction with 0 is not enough for a non-directional source!
				_Track->DrvSource->setDirection( CVector::I );  // Don't send a 0 vector, DSound will complain. Send (1,0,0), it's omnidirectional anyway.
				coneset = false;
			}
			else
			{
//				if ( ! coneset )
				{
					_Track->DrvSource->setCone( _Sound->getConeInnerAngle(), _Sound->getConeOuterAngle(), _Sound->getConeOuterGain() );
					coneset = true;
				}
				_Track->DrvSource->setDirection( dir );
			}
		}
	}
}


/* Set the gain (volume value inside [0 , 1]). (default: 1)
 * 0.0 -> silence
 * 0.5 -> -6dB
 * 1.0 -> no attenuation
 * values > 1 (amplification) not supported by most drivers
 */
void					CSimpleSource::setGain( float gain )
{
	CSourceCommon::setGain(gain);

	// Set the gain
	if ( _Track != NULL )
	{
		_Track->DrvSource->setGain( gain );
	}
}

void CSimpleSource::setRelativeGain( float gain )
{
	CSourceCommon::setRelativeGain(gain);

	// Set the gain
	if ( _Track != NULL )
	{
		_Track->DrvSource->setGain( _Gain );
	}
}


/* Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
 * of one octave. 0 is not a legal value.
 */
void					CSimpleSource::setPitch( float pitch )
{
	CSourceCommon::setPitch(pitch);

	// Set the pitch
	if ( _Track != NULL )
	{
		_Track->DrvSource->setPitch( pitch );
	}
}


/*
 * Set the source relative mode. If true, positions are interpreted relative to the listener position (default: false)
 */
void					CSimpleSource::setSourceRelativeMode( bool mode )
{
	CSourceCommon::setSourceRelativeMode(mode);

	// Set the relative mode
	if ( _Track != NULL )
	{
		_Track->DrvSource->setSourceRelativeMode( mode );
	}
}

/*
 * Get playing state. Return false if the source has stopped on its own.
 */
bool					CSimpleSource::isPlaying()
{
	return _Playing;
}


} // NLSOUND
