/** \file listener_al.cpp
 * OpenAL sound listener
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
#include "listener_al.h"

#include "sound_driver_al.h"

using namespace NLMISC;

namespace NLSOUND {


// The instance of the singleton
CListenerAL	*CListenerAL::_Instance = NULL;


/*
 * Constructor
 */
CListenerAL::CListenerAL() : IListener()
{
	if ( _Instance == NULL )
	{
		_Instance = this;
	}
	else
	{
		nlerror( "Listener singleton instanciated twice" );
	}
	_Pos.set(0.0f, 0.0f, 0.0f);
}


/*
 * Set the position vector (default: (0,0,0)) (3D mode only)
 */
void					CListenerAL::setPos( const NLMISC::CVector& pos )
{
	_Pos = pos;
	// Coordinate system: conversion from NeL to OpenAL/GL:
	alListener3f( AL_POSITION, pos.x, pos.z, -pos.y );
	TestALError();
}


/** Get the position vector.
 * See setPos() for details.
 */
const NLMISC::CVector &CListenerAL::getPos() const
{
	return _Pos;

// Currently, the OpenAL headers are different between Windows and Linux versions !
// alGetListener3f() is part of the spec, though.
/*
#ifdef NL_OS_WINDOWS
	// Coordsys conversion
	float glposz;
	alGetListener3f( AL_POSITION, &pos.x, &pos.z, &glposz );
	pos.y = -glposz;
#else
	float posarray [3];
	alGetListenerfv( AL_POSITION, posarray );
	// Coordsys conversion
	pos.set( posarray[0], -posarray[2], posarray[1] );
#endif
	TestALError();
*/
}


/*
 * Set the velocity vector (3D mode only)
 */
void					CListenerAL::setVelocity( const NLMISC::CVector& vel )
{
	// Coordsys conversion
	alListener3f( AL_VELOCITY, vel.x, vel.z, -vel.y );
	TestALError();
}


/*
 * Get the velocity vector
 */
void				 	CListenerAL::getVelocity( NLMISC::CVector& vel ) const
{
#ifdef NL_OS_WINDOWS
	// Coordsys conversion
	float glposz;
	alGetListener3f( AL_VELOCITY, &vel.x, &vel.z, &glposz );
	vel.y = - glposz;
#else
	float velarray [3];
	alGetListenerfv( AL_VELOCITY, velarray );
	// Coordsys conversion
	vel.set( velarray[0], -velarray[2], velarray[1] );
#endif
	TestALError();
}


/*
 * Set the orientation vectors (3D mode only)
 */
void					CListenerAL::setOrientation( const NLMISC::CVector& front, const NLMISC::CVector& up )
{
	// Forward then up
	ALfloat v[6];
	// Coordsys conversion
	v[0] = front.x;
	v[1] = front.z;
	v[2] = -front.y;
	v[3] = up.x;
	v[4] = up.z;
	v[5] = -up.y;
	alListenerfv( AL_ORIENTATION, v );
	TestALError();
}


/*
 * Get the orientation vectors
 */
void					CListenerAL::getOrientation( NLMISC::CVector& front, NLMISC::CVector& up ) const
{
	// Forward then up
	ALfloat v[6];
	alGetListenerfv( AL_ORIENTATION, v );
	TestALError();
	// Coordsys conversion
	front.set( v[0], -v[2], v[1] );
	up.set( v[3], -v[5], v[4] );
}


/* Set the gain (volume value inside [0 , 1]). (default: 1)
 * 0.0 -> silence
 * 0.5 -> -6dB
 * 1.0 -> no attenuation
 * values > 1 (amplification) not supported by most drivers
 */
void					CListenerAL::setGain( float gain )
{
	alListenerf( AL_GAIN, gain );
	TestALError();
}


/*
 * Get the gain
 */
float					CListenerAL::getGain() const
{
	ALfloat gain;
#ifdef NL_OS_WINDOWS
	alGetListenerf( AL_GAIN, &gain );
#else
	alGetListenerfv( AL_GAIN, &gain );
#endif
	TestALError();
	return gain;
}


/*
 * Set the doppler factor (default: 1) to exaggerate or not the doppler effect
 */
void					CListenerAL::setDopplerFactor( float f )
{
	alDopplerFactor( f );
	TestALError();
}


/*
 * Set the rolloff factor (default: 1) to scale the distance attenuation effect
 */
void					CListenerAL::setRolloffFactor( float f )
{
	nlassert(CSoundDriverAL::getInstance() != NULL);
	CSoundDriverAL::getInstance()->applyRolloffFactor(f);
}


/*
 * Set DSPROPERTY_EAXLISTENER_ENVIRONMENT and DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE if EAX available (see EAX listener properties)
 */
void					CListenerAL::setEnvironment( uint env, float size )
{
#if EAX_AVAILABLE == 1
	if (AlExtEax)
	{
		eaxSet( &DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, 0, &env, sizeof(unsigned long) );
		eaxSet( &DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE, 0, &size, sizeof(float) );
	}
#endif
}


/*
 * Set any EAX listener property if EAX available
 */
void					CListenerAL::setEAXProperty( uint prop, void *value, uint valuesize )
{
#if EAX_AVAILABLE == 1
	if (AlExtEax)
	{
		eaxSet( &DSPROPSETID_EAX_ListenerProperties, prop, 0, value, valuesize );
	}
#endif
}


} // NLSOUND
