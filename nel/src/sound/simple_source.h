/** \file simple_source.h
 * CSimpleSource: implementation of USource
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

#ifndef NL_SIMPLE_SOURCE_H
#define NL_SIMPLE_SOURCE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "nel/misc/time_nl.h"
#include "audio_mixer_user.h"
//#include "playable.h"
#include "source_common.h"
#include "simple_sound.h"


namespace NLSOUND {


class ISource;
class CTrack;
class CSimpleSound;


/**
 * Implementation of USource
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CSimpleSource : public CSourceCommon, public CAudioMixerUser::IMixerEvent //, public IPlayable
{
public:

	/// Constructor
	CSimpleSource( CSimpleSound *simpleSound=NULL, bool spawn=false, TSpawnEndCallback cb=0, void *cbUserParam = 0, NL3D::CCluster *cluster = 0);
	/// Destructor
	virtual ~CSimpleSource();

/*	/// Static init (call at the very beginning)
	static void						init()
	{
		//NLMISC_REGISTER_CLASS(CSimpleSource);
	}
*/

	/// Return the sound binded to the source (or NULL if there is no sound)
	virtual TSoundId				getSound()									{ return _Sound; }
	/// Return the simple sound bound to the source (or NULL).
	CSimpleSound					*getSimpleSound();

	/// \name Playback control
	//@{
	/// Set looping on/off for future playbacks (default: off)
	virtual void					setLooping( bool l );
	/// Play
	virtual void					play();
	/// Stop playing
	virtual void					stop();
	/// Get playing state. Return false even if the source has stopped on its own.
	virtual bool					isPlaying();
	///
	virtual NLMISC::TTicks			getPlayTime()								{ return getTime(); }
	/// Returns the number of milliseconds the source has been playing
	virtual uint32					getTime();
	//@}


	/// \name Source properties
	//@{
	/** Set the position vector (default: (0,0,0)).
	 * 3D mode -> 3D position
	 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
	 */
	virtual void					setPos( const NLMISC::CVector& pos );
	/** Get the position vector.
	 * If the source is stereo, return the position vector which reference was passed to set3DPositionVector()
	 */
//	virtual void					getPos( NLMISC::CVector& pos ) const;
	/** Get the virtual source position.
	 *	This method compute the virtual source position with cluster system.
	 */
	NLMISC::CVector					getVirtualPos() const;
	/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
	virtual void					setVelocity( const NLMISC::CVector& vel );
	/// Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
	virtual void					setDirection( const NLMISC::CVector& dir );
	/** Set the gain (volume value inside [0 , 1]). (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
	virtual void					setGain( float gain );
	/** Set the gain amount (value inside [0, 1]) to map between 0 and the nominal gain
	 * (which is getSource()->getGain()). Does nothing if getSource() is null.
	 */
	virtual void					setRelativeGain( float gain );
	/** Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
	 * of one octave. 0 is not a legal value.
	 */
	virtual void					setPitch( float pitch );
	/// Set the source relative mode. If true, positions are interpreted relative to the listener position (default: false)
	virtual void					setSourceRelativeMode( bool mode );


	/// Return the track
	CTrack							*getTrack()									{ return _Track; }
	/// Return the spawn end callback
	TSpawnEndCallback				getSpawnEndCallback() const					{ return _SpawnEndCb; }

	//NLMISC_DECLARE_CLASS(CSimpleSource);

	virtual IBuffer					*getBuffer();

private:
	// Mixer event call when doing muted play
	virtual void onEvent();

	TSOURCE_TYPE					getType() const								{return SOURCE_SIMPLE;}

	// The simple sound of this source.
	CSimpleSound					*_Sound;

	// The volume falloff factor.
	float							_Alpha;

	// Corresponding track (if selected for playing)
	CTrack							*_Track;
	// True when the sound is played muted and until the mixer event notifying the end.
	bool							_PlayMuted;

};


} // NLSOUND


#endif // NL_SIMPLE_SOURCE_H

/* End of simple_source.h */
