/** \file listener_dsound.cpp
 * DirectSound listener
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

#include "stddsound.h"
#include "../sound_driver.h"

#include "listener_dsound.h"
#include "sound_driver_dsound.h"


using namespace NLMISC;


namespace NLSOUND {


// The instance of the singleton
CListenerDSound	*CListenerDSound::_Instance = NULL;


/*
 * Constructor
 */
CListenerDSound::CListenerDSound(LPDIRECTSOUND3DLISTENER8 dsoundListener) //: IListener()
:	_Pos(CVector::Null)
{
#if EAX_AVAILABLE == 1
	_EAXListener = 0;
#endif
	if ( _Instance == NULL )
	{
		_Instance = this;
        _Listener = dsoundListener;
#if MANUAL_ROLLOFF == 1
		// Manual RollOff => disable API rollOff
		if ( !_Listener || FAILED(_Listener->SetRolloffFactor(DS3D_MINROLLOFFFACTOR, DS3D_DEFERRED)))
		{
			nlwarning("SetRolloffFactor failed");
		}
#endif
	}
	else
	{
		//nlerror( "Listener singleton instanciated twice" );
	}
}


CListenerDSound::~CListenerDSound()
{
	nldebug("Destroying DirectSound listener");

    release();
	_Instance = NULL;
}


/*
 * 	Release all DirectSound resources
 */
void CListenerDSound::release()
{
    if (_Listener != NULL)
    {
        _Listener->Release();
		_Listener = NULL;
    }
#if EAX_AVAILABLE == 1
	if (_EAXListener != NULL)
	{
		_EAXListener->Release();
		_EAXListener = NULL;
	}
#endif
}


/*
 * Set the position vector (default: (0,0,0)) (3D mode only)
 */
void CListenerDSound::setPos( const NLMISC::CVector& pos )
{

	_Pos = pos;
	// Coordinate system: conversion from NeL to OpenAL/GL:
    if (_Listener != NULL)
    {
        if (FAILED(_Listener->SetPosition(pos.x, pos.z, pos.y, DS3D_DEFERRED)))
		{
			nlwarning("SetPosition failed");
		}
		else
		{
			//nlwarning ("set listener NEL(p:%.2f/%.2f/%.2f) DS(p:%.2f/%.2f/%.2f)", pos.x, pos.y, pos.z, pos.x, pos.z, pos.y);
		}
	}
}


/** Get the position vector.
 * See setPos() for details.
 */
const NLMISC::CVector &CListenerDSound::getPos() const
{
	return _Pos;
/*	return;
	// Coordinate system: conversion from NeL to OpenAL/GL:
    if (_Listener != NULL)
	{
		D3DVECTOR v;
        if (FAILED(_Listener->GetPosition(&v)))
		{
			nlwarning("GetPosition failed");
			pos.set(0.0f, 0.0f, 0.0f);
		}
		else
		{
			pos.set(v.x, v.z, v.y);
		}
    }
	else
	{
		pos.set(0, 0, 0);
	}
*/
}


/*
 * Set the velocity vector (3D mode only)
 */
void CListenerDSound::setVelocity( const NLMISC::CVector& vel )
{
    if (_Listener != NULL)
    {
        if (FAILED(_Listener->SetVelocity(vel.x, vel.z, vel.y, DS3D_DEFERRED)))
		{
			nlwarning("SetVelocity failed");
		}
    }
}


/*
 * Get the velocity vector
 */
void CListenerDSound::getVelocity( NLMISC::CVector& vel ) const
{
    if (_Listener != NULL)
	{
		D3DVECTOR v;
        if (FAILED(_Listener->GetVelocity(&v)))
		{
			nlwarning("GetVelocity failed");
			vel.set(0.0f, 0.0f, 0.0f);
		}
		else
		{
			vel.set(v.x, v.z, v.y);
		}
    }
	else
	{
		vel.set(0, 0, 0);
	}
}


/*
 * Set the orientation vectors (3D mode only)
 */
void CListenerDSound::setOrientation( const NLMISC::CVector& front, const NLMISC::CVector& up )
{
    if (_Listener != NULL)
    {
        if (FAILED(_Listener->SetOrientation(front.x, front.z, front.y, up.x, up.z, up.y, DS3D_DEFERRED)))
		{
			nlwarning("SetOrientation failed");
		}
		else
		{
			//nlwarning ("NLSOUND: set listener orientation NEL(f:%.2f/%.2f/%.2f up:%.2f/%.2f/%.2f) DS(f:%.2f/%.2f/%.2f up:%.2f/%.2f/%.2f)", front.x, front.y, front.z, up.x, up.y, up.z, front.x, front.z, front.y, up.x, up.z, up.y);
		}
    }
}


/*
 * Get the orientation vectors
 */
void CListenerDSound::getOrientation( NLMISC::CVector& front, NLMISC::CVector& up ) const
{
    if (_Listener != NULL)
	{
		D3DVECTOR vfront, vtop;
        if (FAILED(_Listener->GetOrientation(&vfront, &vtop)))
		{
			nlwarning("GetOrientation failed");
			front.set(0.0f, 0.0f, 1.0f);
			up.set(0.0f, 1.0f, 0.0f);
		}
		else
		{
			front.set(vfront.x, vfront.z, vfront.y);
			up.set(vtop.x, vtop.z, vtop.y);
		}
    }
	else
	{
		front.set(0, 0, 1);
		up.set(0, 1, 0);
	}
}


/* Set the gain (volume value inside [0 , 1]). (default: 1)
 * 0.0 -> silence
 * 0.5 -> -6dB
 * 1.0 -> no attenuation
 * values > 1 (amplification) not supported by most drivers
 */
void CListenerDSound::setGain( float gain )
{
	CSoundDriverDSound::instance()->setGain(gain);
}


/*
 * Get the gain
 */
float CListenerDSound::getGain() const
{
    return CSoundDriverDSound::instance()->getGain();
}


/*
 * Set the doppler factor (default: 1) to exaggerate or not the doppler effect
 */
void CListenerDSound::setDopplerFactor( float f )
{
    if (_Listener != NULL)
    {
		if (f > DS3D_MAXDOPPLERFACTOR)
		{
			f = DS3D_MAXDOPPLERFACTOR;
		}
		else if (f < DS3D_MINDOPPLERFACTOR)
		{
			f = DS3D_MINDOPPLERFACTOR;
		}

        if (FAILED(_Listener->SetDopplerFactor(f, DS3D_DEFERRED)))
		{
			nlwarning("SetDopplerFactor failed");
		}
    }
}


/*
 * Set the rolloff factor (default: 1) to scale the distance attenuation effect
 */
void CListenerDSound::setRolloffFactor( float f )
{
	// Works only in API rolloff mode
#if MANUAL_ROLLOFF == 0
    if (_Listener != NULL)
    {
		clamp(f, DS3D_MINROLLOFFFACTOR, DS3D_MAXROLLOFFFACTOR);
		if (FAILED(_Listener->SetRolloffFactor(f, DS3D_DEFERRED)))
		{
			nlwarning("SetRolloffFactor failed");
		}
    }
#endif
}


float CListenerDSound::getRolloffFactor()
{
	// Works only in API rolloff mode
#if MANUAL_ROLLOFF == 0
	if (_Listener != NULL)
    {
		float f;
		_Listener->GetRolloffFactor(&f);
		return f;
    }
#endif

	return 1.f;
}


void CListenerDSound::commit3DChanges()
{
    if (_Listener != NULL)
    {
		_Listener->CommitDeferredSettings();
	}
}


/*
 * Set DSPROPERTY_EAXLISTENER_ENVIRONMENT and DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE if EAX available (see EAX listener properties)
 */
void CListenerDSound::setEnvironment( uint env, float size )
{
#if EAX_AVAILABLE == 1
	if (_EAXListener == NULL)
	{
		_EAXListener = CSoundDriverDSound::instance()->createPropertySet(NULL);
	}
	if ( _EAXListener != NULL )
	{
		HRESULT res = _EAXListener->Set( DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, NULL, 0, &env, sizeof(unsigned long) );
		if (res != S_OK)
			nlwarning("Setting EAX environment #%u fail : %x", env, res);
		res = _EAXListener->Set( DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE, NULL, 0, &size, sizeof(float) );
		if (res != S_OK)
			nlwarning("Setting EAX environment size %f fail : %x", size, res);
	}
#endif
}


/*
 * Set any EAX listener property if EAX available
 */
void CListenerDSound::setEAXProperty( uint prop, void *value, uint valuesize )
{
#if EAX_AVAILABLE
	if (_EAXListener == NULL)
	{
		_EAXListener = CSoundDriverDSound::instance()->createPropertySet(NULL);
	}
	if ( _EAXListener != NULL )
	{
		HRESULT res = _EAXListener->Set(DSPROPSETID_EAX_ListenerProperties, prop, NULL, 0, value, valuesize );
		if (res != S_OK)
			nlwarning("Setting EAX listener prop #%d fail : %x", prop, res);
	}
#endif
}


} // NLSOUND
