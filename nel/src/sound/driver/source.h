/** \file source.h
 * ISource: sound source interface
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

#ifndef NL_SOURCE_H
#define NL_SOURCE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "sound_driver.h"

namespace NLSOUND {


class IBuffer;
class ILoader;


/**
 * Sound source interface (implemented in sound driver dynamic library)
 *
 * - If the buffer is mono, the source is played in 3D mode. For arguments
 * as 3D vectors, use the NeL vector coordinate system:
 * \verbatim
 *     (top)
 *       z
 *       |  y (front)
 *       | /
 *       -----x (right)
 * \endverbatim
 *
 * - If the buffer is stereo, the source is played in stereo mode.
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class ISource
{
public:

	/// \name Initialization
	//@{
	/** Set the buffer that will be played (no streaming)
	 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
	 * otherwise the source is considered as a 3D source.
	 */
	virtual void					setStaticBuffer( IBuffer *buffer )	= 0; //{ _Buffer = buffer; }
	/// Return the buffer, or NULL if streaming is used.
	virtual IBuffer					*getStaticBuffer() = 0; //					{ return _Buffer; }
	/** Set the sound loader that will be used to stream in the data to play
	 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
	 * otherwise the source is considered as a 3D source.
	 */
	virtual void					setStreamLoader( ILoader *loader )	{ _Loader = loader; }
	//@}


	/// \name Playback control
	//@{
	/// Set looping on/off for future playbacks (default: off)
	virtual void					setLooping( bool l ) = 0;
	/// Return the looping state
	virtual bool					getLooping() const = 0;
	/** Play the static buffer (or stream in and play).
	 *	This method can return false if the sample for this sound is unloaded.
	 */
	virtual bool					play() = 0;
	/// Stop playing
	virtual void					stop() = 0;
	/// Pause. Call play() to resume.
	virtual void					pause() = 0;
	/// Return the playing state
	virtual bool					isPlaying() const = 0;
	/// Return true if playing is finished or stop() has been called.
	virtual bool					isStopped() const = 0;
	/// Update the source (e.g. continue to stream the data in)
	virtual bool					update() = 0;
	/// Returns the number of milliseconds the source has been playing
	virtual uint32					getTime() { return 0; }
	//@}


	/// \name Source properties
	//@{
	/** Set the position vector (default: (0,0,0)).
	 * 3D mode -> 3D position
	 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
	 */
	virtual void					setPos( const NLMISC::CVector& pos, bool deffered = true ) = 0;
	/** Get the position vector.
	 * See setPos() for details.
	 */
	virtual const NLMISC::CVector	&getPos() const =0;
	/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
	virtual void					setVelocity( const NLMISC::CVector& vel, bool deferred = true ) = 0;
	/// Get the velocity vector
	virtual void					getVelocity( NLMISC::CVector& vel ) const = 0;
	/// Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
	virtual void					setDirection( const NLMISC::CVector& dir ) = 0;
	/// Get the direction vector
	virtual void					getDirection( NLMISC::CVector& dir ) const = 0;
	/** Set the gain (volume value inside [0 , 1]). (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
	virtual void					setGain( float gain ) = 0;
	/// Get the gain
	virtual float					getGain() const = 0;
	/** Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
	 * of one octave. 0 is not a legal value.
	 */
	virtual void					setPitch( float pitch ) = 0;
	/// Get the pitch
	virtual float					getPitch() const = 0;
	/// Set the source relative mode. If true, positions are interpreted relative to the listener position
	virtual void					setSourceRelativeMode( bool mode ) = 0;
	/// Get the source relative mode
	virtual bool					getSourceRelativeMode() const = 0;
	/// Set the min and max distances (default: 1, MAX_FLOAT) (3D mode only)
	virtual void					setMinMaxDistances( float mindist, float maxdist, bool deferred = true ) = 0;
	/// Get the min and max distances
	virtual void					getMinMaxDistances( float& mindist, float& maxdist ) const = 0;
	/// Set the cone angles (in radian) and gain (in [0 , 1]) (default: 2PI, 2PI, 0)
	virtual void					setCone( float innerAngle, float outerAngle, float outerGain ) = 0;
	/// Get the cone angles (in radian)
	virtual void					getCone( float& innerAngle, float& outerAngle, float& outerGain ) const = 0;
	/// Set any EAX source property if EAX available
	virtual void					setEAXProperty( uint prop, void *value, uint valuesize ) = 0;
	/** Set the alpha value for the volume-distance curve
	 *
	 *	Usefull only if MANUAL_ROLLOFF==1. value from -1 to 1 (default 0)
	 *
	 *  alpha = 0.0: the volume will decrease linearly between 0dB and -100 dB
	 *  alpha = 1.0: the volume will decrease linearly between 1.0 and 0.0 (linear scale)
	 *  alpha = -1.0: the volume will decrease inversely with the distance (1/dist). This
	 *                is the default used by DirectSound/OpenAL
	 *
	 *  For any other value of alpha, an interpolation is be done between the two
	 *  adjacent curves. For example, if alpha equals 0.5, the volume will be halfway between
	 *  the linear dB curve and the linear amplitude curve.
	 */
	///
	virtual void					setAlpha(double a) {  }
	//@}


	/// Constructor
	ISource() : /*_Buffer(NULL),*/ _Loader(NULL) {}

	/// Destructor
	virtual							~ISource() { /*_Buffer=NULL;*/ _Loader=NULL; }

protected:

	// Buffer (static mode)
//	IBuffer							*_Buffer;

	// Sound loader (streaming mode, if _Buffer==NULL)
	ILoader							*_Loader;

	// common method used only if MANUAL_ROLLOFF==1. return the volume in 1/100th DB modified
	sint32		computeManualRollOff(sint32 volumeDB, sint32 dbMin, sint32 dbMax, double alpha, float sqrdist) const;

};


} // NLSOUND


#endif // NL_SOURCE_H

/* End of source.h */
