/** \file source_fmod.h
 * DirectSound sound source
 *
 * $Id: source_fmod.h,v 1.3 2005/04/07 14:30:40 cado Exp $
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

#ifndef NL_SOURCE_FMOD_H
#define NL_SOURCE_FMOD_H

#include "../source.h"
#include "../sound_driver.h"
#include "../buffer.h"

#ifdef NL_OS_WINDOWS
//#include <windows.h>
#include <dsound.h>
#endif

#undef min
#undef max


namespace NLSOUND {



class CBufferFMod;


/**
 * DirectSound sound source
 *

 * For arguments as 3D vectors, use the NeL vector coordinate system
 * 
 * \author Peter Hanappe
 * \author Nevrax France
 * \date 2002
 */
class CSourceFMod : public ISource
{

friend class CSoundDriverFMod;  

public:

	/// Constructor
	CSourceFMod( uint sourcename = 0 );

    /// Destructor
	virtual ~CSourceFMod();

    /// Initialize the DirectSound buffers. Called by the sound driver only.
	void					init();

	/// \name Initialization
	//@{

    /** Set the buffer that will be played (no streaming)
	 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
	 * otherwise the source is considered as a 3D source.
	 * Set NULL to set "no buffer"
	 */
	virtual void			setStaticBuffer( IBuffer *buffer );

	virtual IBuffer			*getStaticBuffer();

	//@}

	
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

    /// Return the paused state
	virtual bool			isPaused() const;

    /// Update the source (e.g. continue to stream the data in)
	virtual bool			update();

	/// Returns the number of milliseconds the source has been playing
	virtual uint32			getTime();

	//@}


	/// \name Source properties
	//@{

    /** Set the position vector (default: (0,0,0)).
	 * 3D mode -> 3D position
	 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
	 * \param deferred false to apply position immediatly
	 */
	virtual void			setPos( const NLMISC::CVector& pos, bool deferred );

    /** Get the position vector.
	 * See setPos() for details.
	 */
	const NLMISC::CVector	&getPos() const;

    /// Set the velocity vector (3D mode only) (default: (0,0,0))
	virtual void			setVelocity( const NLMISC::CVector& vel, bool deferred);

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
	uint					sourceName() { return _SourceName; }

	// Reset the source before reuse
	void					reset();

	/** Update the source's volume according to its distance and fade out curve. 
	 *  It takes the current position of the listener as argument.
	 *	Called only if MANUAL_ROLLOFF==1
	 */
	void					updateVolume( const NLMISC::CVector& listener );

	/** Set the alpha value for the volume-distance curve
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
	virtual void			setAlpha(double a) { _Alpha = a; }


	bool	needsUpdate();

	void	updateFModPosIfRelative();
	
private:

	void copySampleTo16BitsTrack(void *dst, void *src, uint nbSample, TSampleFormat sourceFormat);

	enum TSourceState
	{
		source_stoped,
		source_playing,
		source_silencing,
		source_swap_pending
	};

	/// Release all DirectSound resources
	void					release();

	// Source name
	uint					_SourceName;

	TSourceState			_State;

	IBuffer					*_Sample;
	IBuffer					*_NextSample;
	sint					_FModChannel;
	
    // States
	bool					_PosRelative;
    bool					_Loop;
	float					_Gain;
	float					_Pitch;
	double					_Alpha;
	NLMISC::CVector			_Pos;
	NLMISC::CVector			_Vel;
	NLMISC::CVector			_Front;
	float					_MinDist, _MaxDist;

	void	updateFModPos();
	
};


} // NLSOUND


#endif // NL_SOURCE_FMOD_H

/* End of source_al.h */
