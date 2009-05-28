/** \file listener_dsound.h
 * DirectSound sound listener
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

#ifndef NL_LISTENER_DSOUND_H
#define NL_LISTENER_DSOUND_H

#include "../listener.h"
#include "../sound_driver.h"
#include <dsound.h>

namespace NLSOUND {


/**
 * DirectSound listener.
 *
 * For arguments as 3D vectors, use the NeL vector coordinate system
 * (not OpenAL/OpenGL's one).
 *
 * \author Peter Hanappe, Olivier Cado
 * \author Nevrax France
 * \date 2002
 */
class CListenerDSound : public IListener
{
friend class CSoundDriverDSound;

public:

	/// Constructor
	CListenerDSound(LPDIRECTSOUND3DLISTENER8 dsoundListener);

	/// Deconstructor
	virtual ~CListenerDSound();

	/// Return the instance of the singleton
	static CListenerDSound* instance() { return _Instance; }

	/// \name Listener properties
	//@{

    /// Set the position vector (default: (0,0,0)) (3D mode only)
	virtual void			setPos( const NLMISC::CVector& pos );

    /** Get the position vector.
	 * See setPos() for details.
	 */
	virtual const NLMISC::CVector	&getPos() const;

    /// Set the velocity vector (3D mode only) (default: (0,0,0))
	virtual void			setVelocity( const NLMISC::CVector& vel );

    /// Get the velocity vector
	virtual void			getVelocity( NLMISC::CVector& vel ) const;

    /// Set the orientation vectors (3D mode only) (default: (0,1,0), (0,0,1))
	virtual void			setOrientation( const NLMISC::CVector& front, const NLMISC::CVector& up );

    /// Get the orientation vectors
	virtual void			getOrientation( NLMISC::CVector& front, NLMISC::CVector& up ) const;

    /** Set the gain (volume value inside [0 , 1]). (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
    virtual void			setGain( float gain );

    /// Get the gain
	virtual float			getGain() const;
	//@}

	/// \name Global properties
	//@{

    /// Set the doppler factor (default: 1) to exaggerate or not the doppler effect
	virtual void			setDopplerFactor( float f );

    /// Set the rolloff factor (default: 1) to scale the distance attenuation effect
	virtual void			setRolloffFactor( float f );

    /// Return the rolloff factor
	virtual float			getRolloffFactor();

    /// Set DSPROPERTY_EAXLISTENER_ENVIRONMENT and DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE if EAX available (see EAX listener properties)
	virtual void			setEnvironment( uint env, float size=7.5f );

    /// Set any EAX listener property if EAX available
	virtual void			setEAXProperty( uint prop, void *value, uint valuesize );
	//@}

	/// Commit any changes to the 3D environment
	void					commit3DChanges();


private:

	/// Release all DirectSound resources
	void					release();

	/// The instance of the singleton
	static CListenerDSound	*_Instance;

    /// The DirectSound listener interface
    LPDIRECTSOUND3DLISTENER8	 _Listener;

	// TMP : TEST
	NLMISC::CVector			_Pos;

#if EAX_AVAILABLE == 1
	LPKSPROPERTYSET			_EAXListener;
#endif
};


} // NLSOUND


#endif // NL_LISTENER_DSOUND_H

