/** \file listener_user.h
 * UListenerUser: implementation of UListener
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

#ifndef NL_LISTENER_USER_H
#define NL_LISTENER_USER_H

#include "nel/misc/types_nl.h"
#include "nel/sound/u_listener.h"
#include "driver/sound_driver.h"
#include "driver/listener.h"


// This namespace contains the sound classes
namespace NLSOUND {


/**
 * Implementation of UListener
 *
 * This implementation does not check if the properties have changed or not.
 * Therefore it is suggested to test them and not to call the set methods if there is no change.
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CListenerUser : public UListener
{
public:

	/// Constructor
	CListenerUser()	: _DrvListener (NULL) {}
	/// Init
	void			init( ISoundDriver *sd )					{  nlassert( sd ); _DrvListener = sd->createListener(); }
	/// Destructor
	virtual			~CListenerUser()							{ if ( _DrvListener!=NULL ) delete _DrvListener; }


	/// \name Listener properties
	//@{
	/// Set the position vector (default: (0,0,0)) (3D mode only)
	virtual void	setPos( const NLMISC::CVector& pos );
	/** Get the position vector.
	 * See setPos() for details.
	 */
	virtual const NLMISC::CVector &getPos() const		{ return _DrvListener->getPos(); }
	/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
	virtual void	setVelocity( const NLMISC::CVector& vel )	{ _DrvListener->setVelocity( vel ); }
	/// Get the velocity vector
	virtual void	getVelocity( NLMISC::CVector& vel ) const	{ _DrvListener->getVelocity( vel ); }
	/// Set the orientation vectors (3D mode only, ignored in stereo mode) (default: (0,1,0), (0,0,1) )
	virtual void	setOrientation( const NLMISC::CVector& front,
									const NLMISC::CVector& up )	{ _DrvListener->setOrientation( front, up ); }
	/// Get the orientation vectors
	virtual void	getOrientation( NLMISC::CVector& front,
									NLMISC::CVector& up ) const	{ _DrvListener->getOrientation( front, up ); }
	/** Set the gain (volume value inside [0 , 1]). (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
	virtual void	setGain( float gain )						{ _DrvListener->setGain( gain ); }
	/// Get the gain
	virtual float	getGain() const								{ return _DrvListener->getGain(); }
	//@}


	/// Direct access granted to the audio mixer
	IListener		*getListener()								{ return _DrvListener; }

private:

	/// Listener property
	IListener		*_DrvListener;
};


} // NLSOUND


#endif // NL_LISTENER_USER_H

/* End of listener_user.h */
