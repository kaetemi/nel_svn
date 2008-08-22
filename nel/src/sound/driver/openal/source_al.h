/** \file source_al.h
 * OpenAL sound source
 *
 * $Id: source_al.h,v 1.12 2004/02/23 14:38:45 lecroart Exp $
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

#ifndef NL_SOURCE_AL_H
#define NL_SOURCE_AL_H

#include "nel/misc/types_nl.h"
#include "../source.h"
#include "AL/al.h"


namespace NLSOUND {


/**
 * OpenAL sound source
 *
 * Note: the creation/deletion of sources and the setting of their rolloff factor
 * are done in CSoundDriverAL.
 *
 * The EAX extensions are not available on all sound cards, and currently not at
 * all on Linux.
 *
 * For arguments as 3D vectors, use the NeL vector coordinate system
 * (not OpenAL/OpenGL's one).
 * 
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CSourceAL : public ISource
{
public:

	/// Constructor
	CSourceAL( ALuint sourcename=AL_NONE );
	/// Destructor
	virtual					~CSourceAL();

	
	/// \name Initialization
	//@{
	/** Set the buffer that will be played (no streaming)
	 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
	 * otherwise the source is considered as a 3D source.
	 * Set NULL to set "no buffer"
	 */
	virtual void			setStaticBuffer( IBuffer *buffer );
	/// Set the next source that is to be played immediately after the present source
	//virtual void					setNext( ISource *next );
	//@}

	virtual IBuffer			*getStaticBuffer();

	/// \name Playback control
	//@{
	/// Set looping on/off for future playbacks (default: off)
	virtual void			setLooping( bool l );
	/// Return the looping state
	virtual bool			getLooping() const;
	/// Play the static buffer (or stream in and play)
	virtual bool			play();
	/// Stop playing
	virtual void			stop();
	/// Pause. Call play() to resume.
	virtual void			pause();
	/// Return the playing state
	virtual bool			isPlaying() const;
	/// Return true if playing is finished or stop() has been called.
	virtual bool			isStopped() const;
	/// Update the source (e.g. continue to stream the data in)
	virtual bool			update();
	//@}


	/// \name Source properties
	//@{
	/** Set the position vector (default: (0,0,0)).
	 * 3D mode -> 3D position
	 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
	 */
	virtual void			setPos( const NLMISC::CVector& pos, bool deffered = true );
	/** Get the position vector.
	 * See setPos() for details.
	 */
	virtual const NLMISC::CVector	&getPos() const;
	/// Set the velocity vector (3D mode only) (default: (0,0,0))
	virtual void			setVelocity( const NLMISC::CVector& vel, bool deferred );
	/// Get the velocity vector
	virtual void			getVelocity( NLMISC::CVector& vel ) const;
	/// Set the direction vector (3D mode only) (default: (0,0,0) as non-directional)
	virtual void			setDirection( const NLMISC::CVector& dir );
	/// Get the direction vector
	virtual void			getDirection( NLMISC::CVector& dir ) const;
	/** Set the gain (volume value inside [0 , 1]) (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
	virtual void			setGain( float gain );
	/// Get the gain
	virtual float			getGain() const;
	/** Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
	 * of one octave. 0 is not a legal value.
	 */
	virtual void			setPitch( float pitch );
	/// Get the pitch
	virtual float			getPitch() const;
	/// Set the source relative mode. If true, positions are interpreted relative to the listener position (default: false)
	virtual void			setSourceRelativeMode( bool mode );
	/// Get the source relative mode
	virtual bool			getSourceRelativeMode() const;
	/// Set the min and max distances (default: 1, MAX_FLOAT) (3D mode only)
	virtual void			setMinMaxDistances( float mindist, float maxdist, bool deferred );
	/// Get the min and max distances
	virtual void			getMinMaxDistances( float& mindist, float& maxdist ) const;
	/// Set the cone angles (in radian) and gain (in [0 , 1]) (default: 2PI, 2PI, 0) (3D mode only)
	virtual void			setCone( float innerAngle, float outerAngle, float outerGain );
	/// Get the cone angles (in radian)
	virtual void			getCone( float& innerAngle, float& outerAngle, float& outerGain ) const;
	/// Set any EAX source property if EAX available
	virtual void			setEAXProperty( uint prop, void *value, uint valuesize );
	//@}


	/// Return the OpenAL source name
	ALuint					sourceName()							{ return _SourceName; }

private:
	// assigned buffer object
	IBuffer*				_Buffer;

	// Source name
	ALuint					_SourceName;

	NLMISC::CVector			_Pos;
};


} // NLSOUND


#endif // NL_SOURCE_AL_H

/* End of source_al.h */
