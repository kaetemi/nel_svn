/** \file source_fmod.cpp
 * DirectSound sound source
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


#include "stdfmod.h"
#include "nel/misc/hierarchical_timer.h"
#include "source_fmod.h"
#include "sound_driver_fmod.h"
#include "buffer_fmod.h"
#include "listener_fmod.h"
#include "../sound_driver.h"
#include <cfloat>


#include <algorithm>


using namespace NLMISC;
using namespace std;


namespace NLSOUND 
{


// ******************************************************************

CSourceFMod::CSourceFMod( uint sourcename ) 
:	ISource(), 
	_SourceName(sourcename)
{
	_Sample = NULL;
	_NextSample = NULL;
	_State = source_stoped;

	_PosRelative= false;
	_Loop = false;
	_Gain = 1.0f;
	_Alpha = 0.0;
	_Pos= _Vel= CVector::Null;
	_Front= CVector::J;
	_MinDist= 1.f;
	_MaxDist= FLT_MAX;
	_Pitch= 1.0f;
					

	_FModChannel= -1;
}


// ******************************************************************

CSourceFMod::~CSourceFMod()
{
	nldebug("Destroying FMod source");

	CSoundDriverFMod::instance()->removeSource(this);

	release();
}


// ******************************************************************

void CSourceFMod::release()
{
	// stop any pending play
	stop();
}


uint32	CSourceFMod::getTime() 
{ 
	if (_Sample == 0 || _FModChannel==-1)
		return 0;

	TSampleFormat format;
	uint freq;
	_Sample->getFormat(format, freq);

	return uint32(1000.0f * FSOUND_GetCurrentPosition(_FModChannel) / (float)freq);
}

// ******************************************************************

void CSourceFMod::init()
{
}

// ******************************************************************

void CSourceFMod::reset()
{
	setPitch(1.0f);
	setLooping(false);
	setGain(1.0f);
}


// ******************************************************************
void CSourceFMod::setStaticBuffer( IBuffer *buffer )
{
	if (_State == source_playing)
	{
		_State = source_swap_pending;
		_Sample = 0;
		_NextSample = buffer;
	}
	else
	{
		_Sample = buffer;
		_NextSample = NULL;
	}
}

// ***************************************************************************
IBuffer *CSourceFMod::getStaticBuffer()
{
	if (_State == source_swap_pending)
		return _NextSample;
	else
		return _Sample;

}


// ***************************************************************************
bool CSourceFMod::play()
{
	// stop any current sound
	stop();

	// play the new one
	if(_Sample)
	{
		CBufferFMod	*bufFMod= static_cast<CBufferFMod*>(_Sample);
		_State= source_playing;
		// start paused, for Loop behaviour to work properly
		if(bufFMod->_FModSample)
			_FModChannel= FSOUND_PlaySoundEx(FSOUND_FREE, bufFMod->_FModSample, NULL, true);

		// Update all setup for this channel
		if(_FModChannel!=-1)
		{
			FSOUND_SetLoopMode(_FModChannel, _Loop?FSOUND_LOOP_NORMAL:FSOUND_LOOP_OFF);
			FSOUND_3D_SetMinMaxDistance(_FModChannel, _MinDist, _MaxDist);
			updateFModPos();
			// reset pitch
			setPitch(_Pitch);

			// Set the correct volume now
#if MANUAL_ROLLOFF == 0
			FSOUND_SetVolume(_FModChannel, uint32(255*_Gain));
#else
			// manual rolloff => recompute according to position
			CListenerFMod	*listener= CListenerFMod::instance();
			if(listener)
				updateVolume(listener->getPos());
#endif
			
			// unpause
			FSOUND_SetPaused(_FModChannel, false);
		}
	}

	return true;
}

// ***************************************************************************
void CSourceFMod::stop()
{
	if(_State == source_swap_pending)
	{
		_State= source_playing;
		_Sample= _NextSample;
		_NextSample= NULL;
	}
	
	_State= source_stoped;

	// Stop the FMod channel
	if(_FModChannel!=-1)
	{
		FSOUND_StopSound(_FModChannel);
		_FModChannel= -1;
	}
}


// ******************************************************************

void CSourceFMod::setLooping( bool l )
{
	if(_Loop!=l)
	{
		_Loop = l;
		if(_FModChannel!=-1)
		{
			// Must pause/unpause (Hardware limitation)
			FSOUND_SetPaused(_FModChannel, true);
			FSOUND_SetLoopMode(_FModChannel, _Loop?FSOUND_LOOP_NORMAL:FSOUND_LOOP_OFF);
			FSOUND_SetPaused(_FModChannel, false);
		}
	}
}


// ******************************************************************

bool CSourceFMod::getLooping() const
{
	return _Loop;
}

// ******************************************************************
void CSourceFMod::pause()
{
	// TODO : recode this !
	nlassert(false);
}

// ******************************************************************

bool CSourceFMod::isPlaying() const
{
	return _State == source_playing || _State == source_swap_pending;
}


// ******************************************************************

bool CSourceFMod::isPaused() const
{
	// TODO
	nlassert(false);
	return false;
}


// ******************************************************************

bool CSourceFMod::isStopped() const
{
	return _State == source_silencing || _State == source_stoped;
}


// ******************************************************************
bool CSourceFMod::needsUpdate()
{
	return _State == source_silencing || _State == source_playing || _State == source_swap_pending;
}



// ******************************************************************

bool CSourceFMod::update()
{
	// don't stop if loop
	if(_FModChannel!=-1 && isPlaying())
	{
		// If FMod ended
		if(!FSOUND_IsPlaying(_FModChannel))
			_State= source_silencing;
	}

	return true;
}


// ******************************************************************

void CSourceFMod::setPos( const NLMISC::CVector& pos, bool deferred )
{
	_Pos = pos;
	updateFModPos();
}


// ******************************************************************

const NLMISC::CVector &CSourceFMod::getPos() const
{
	return _Pos;
}


// ******************************************************************

void CSourceFMod::setVelocity( const NLMISC::CVector& vel, bool deferred )
{
	_Vel= vel;
	updateFModPos();
}


// ******************************************************************

void CSourceFMod::getVelocity( NLMISC::CVector& vel ) const
{
	vel= _Vel;
}


// ******************************************************************

void CSourceFMod::setDirection( const NLMISC::CVector& dir )
{
	_Front= dir;
	updateFModPos();
}


// ******************************************************************

void CSourceFMod::getDirection( NLMISC::CVector& dir ) const
{
	dir= _Front;
}


// ******************************************************************

void CSourceFMod::setGain( float gain )
{
	clamp(gain, 0.00001f, 1.0f);
	_Gain = gain;

#if MANUAL_ROLLOFF == 0
	if(_FModChannel!=-1)
		FSOUND_SetVolume(_FModChannel, uint32(255*gain));
#endif
	// set the volume later in updateVolume() in case of MANUAL_ROLLOFF==1
}


// ***************************************************************************
float CSourceFMod::getGain() const
{
	return _Gain;
}


// ******************************************************************
void CSourceFMod::setPitch( float coeff )
{
	_Pitch= coeff;

	if (_Sample != NULL && _FModChannel!=-1)
	{
		TSampleFormat format;
		uint freq;

		_Sample->getFormat(format, freq);

		uint32 newFreq = (uint32) (coeff * (float) freq);

		FSOUND_SetFrequency(_FModChannel, newFreq);
	}
}


// ******************************************************************
float CSourceFMod::getPitch() const
{
	return _Pitch;
}


// ******************************************************************
void CSourceFMod::setSourceRelativeMode( bool mode )
{
	_PosRelative= mode;
	updateFModPos();
}


// ******************************************************************

bool CSourceFMod::getSourceRelativeMode() const
{
	return _PosRelative;
}


// ******************************************************************
void CSourceFMod::setMinMaxDistances( float mindist, float maxdist, bool deferred )
{
	_MinDist= mindist;
	_MaxDist= maxdist;
	if(_FModChannel!=-1)
	{
		FSOUND_3D_SetMinMaxDistance(_FModChannel, _MinDist, _MaxDist);
	}
}


// ******************************************************************
void CSourceFMod::getMinMaxDistances( float& mindist, float& maxdist ) const
{
	mindist= _MinDist;
	maxdist= _MaxDist;
}

// ******************************************************************
void CSourceFMod::updateVolume( const NLMISC::CVector& listener )
{
#if MANUAL_ROLLOFF == 0
	nlstopex("no updateVolume() if MANUAL_ROLLOFF==0");
#else
	
	// only if channel active
	if(_FModChannel==-1)
		return;

	CVector pos = getPos();
	// make relative to listener (if not already!)
	if(!_PosRelative)
		pos -= listener;
	float sqrdist = pos.sqrnorm();

	// compute volume in DB, according to current gain
	sint32 volumeDB= sint32(floor(2000.0 * log10(_Gain))); // convert to 1/100th decibels
	const	sint32	dbMin= -10000;
	const	sint32	dbMax= 0;
	clamp(volumeDB, dbMin, dbMax);

	// attenuate the volume according to distance and alpha
	volumeDB= ISource::computeManualRollOff(volumeDB, dbMin, dbMax, _Alpha, sqrdist);
	
	// retransform to linear form
	double	attGain= pow((double)10.0, double(volumeDB)/2000.0);
	clamp(attGain, 0.f, 1.f);

	// set the attenuated volume
	FSOUND_SetVolume(_FModChannel, uint32(attGain*255));
#endif
}

// ******************************************************************

void CSourceFMod::setCone( float innerAngle, float outerAngle, float outerGain )
{
	// TODO_SOURCE_DIR
}

// ******************************************************************

void CSourceFMod::getCone( float& innerAngle, float& outerAngle, float& outerGain ) const
{
	// TODO_SOURCE_DIR
}

// ******************************************************************
void CSourceFMod::setEAXProperty( uint prop, void *value, uint valuesize )
{
}


// ***************************************************************************
void CSourceFMod::updateFModPos()
{
	// TODO_SOURCE_DIR
	if(_FModChannel!=-1)
	{
		CVector		wpos, wvel;
		wpos= _Pos;
		wvel= _Vel;

		// If relative, must transform to absolute
		if(_PosRelative)
		{
			CListenerFMod	*lsr= CListenerFMod::instance();
			if(lsr)
			{
				wpos= lsr->getPosMatrix() * wpos;
				wvel= lsr->getPosMatrix() * wvel;
			}
		}

		// set World Pos/Vel to FMod
		float		fmodPos[3];
		float		fmodVel[3];
		CSoundDriverFMod::toFModCoord(wpos, fmodPos);
		CSoundDriverFMod::toFModCoord(wvel, fmodVel);
		FSOUND_3D_SetAttributes(_FModChannel, fmodPos, fmodVel);
	}
}


// ***************************************************************************
void CSourceFMod::updateFModPosIfRelative()
{
	// Not supported by FMod, emulate each frame (before FSOUND_update())
	if(_PosRelative)
		updateFModPos();
}


} // NLSOUND
