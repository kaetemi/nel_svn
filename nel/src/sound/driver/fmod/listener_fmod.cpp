/** \file listener_fmod.cpp
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

#include "stdfmod.h"
#include "../sound_driver.h"

#include "listener_fmod.h"
#include "sound_driver_fmod.h"

#include <fmod.h>


using namespace NLMISC;


namespace NLSOUND
{


// ***************************************************************************
// The instance of the singleton
CListenerFMod	*CListenerFMod::_Instance = NULL;


// ***************************************************************************
CListenerFMod::CListenerFMod() //: IListener()
:	_Pos(CVector::Null), _Vel(CVector::Null), _Front(CVector::J), _Up(CVector::K)
{
	if ( _Instance == NULL )
	{
		_Instance = this;
		_RolloffFactor= 1.f;
		_Pos= CVector::Null;
		_Vel= CVector::Null;
		_Front= CVector::J;
		_Up= CVector::K;
#if MANUAL_ROLLOFF == 1
		// Manual RollOff => disable API rollOff
		if( CSoundDriverFMod::instance()->fmodOk() )
		{
			FSOUND_3D_SetRolloffFactor(0);
		}
#endif
	}
	else
	{
		//nlerror( "Listener singleton instanciated twice" );
	}
}


// ***************************************************************************
CListenerFMod::~CListenerFMod()
{
	//nldebug("Destroying FMod listener");

    release();
	_Instance = NULL;
}


// ***************************************************************************
void CListenerFMod::release()
{
}


// ***************************************************************************
void CListenerFMod::setPos( const NLMISC::CVector& pos )
{
	_Pos = pos;
	updateFModPos();
}


// ***************************************************************************
const NLMISC::CVector &CListenerFMod::getPos() const
{
	return _Pos;
}


// ***************************************************************************
void CListenerFMod::setVelocity( const NLMISC::CVector& vel )
{
	_Vel= vel;
	updateFModPos();
}


// ***************************************************************************
void CListenerFMod::getVelocity( NLMISC::CVector& vel ) const
{
	vel= _Vel;
}


// ***************************************************************************
void CListenerFMod::setOrientation( const NLMISC::CVector& front, const NLMISC::CVector& up )
{
	_Front= front;
	_Up= up;
	updateFModPos();
}


// ***************************************************************************
void CListenerFMod::getOrientation( NLMISC::CVector& front, NLMISC::CVector& up ) const
{
	front= _Front;
	up= _Up;
}


// ***************************************************************************
void CListenerFMod::setGain( float gain )
{
	CSoundDriverFMod::instance()->setGain(gain);
}


// ***************************************************************************
float CListenerFMod::getGain() const
{
    return CSoundDriverFMod::instance()->getGain();
}


// ***************************************************************************
void CListenerFMod::setDopplerFactor( float f )
{
	if( !CSoundDriverFMod::instance()->fmodOk() )
		return;

	// clamp as in DSound.
	clamp(f, 0.f, 10.f);

	// set
	FSOUND_3D_SetDopplerFactor(f);
}


// ***************************************************************************
void CListenerFMod::setRolloffFactor( float f )
{
	// Works only in API rolloff mode
#if MANUAL_ROLLOFF == 0
	if( !CSoundDriverFMod::instance()->fmodOk() )
		return;

	// clamp as in DSound (FMod requirement)
	clamp(f, 0.f, 10.f);

	_RolloffFactor= f;

	// set
	FSOUND_3D_SetRolloffFactor(f);
#endif
}


// ***************************************************************************
float CListenerFMod::getRolloffFactor()
{
	return _RolloffFactor;
}


// ***************************************************************************
void CListenerFMod::setEnvironment( uint env, float size )
{
	// TODO_EAX
}


// ***************************************************************************
void CListenerFMod::setEAXProperty( uint prop, void *value, uint valuesize )
{
	// TODO_EAX
}


// ***************************************************************************
void CListenerFMod::updateFModPos()
{
	// recompute matrix (for Source relative mode)
	// same orientation
	_PosMatrix.identity();
	_PosMatrix.setRot(CVector::I, _Front, _Up);
	_PosMatrix.normalize(CMatrix::YZX);
	_VelMatrix= _PosMatrix;
	// special position
	_PosMatrix.setPos(_Pos);
	_VelMatrix.setPos(_Vel);

	// set up FMod attributes
	float		pos[3];
	float		vel[3];
	float		front[3];
	float		up[3];
	CVector		ful= _Front.normed(), tul= _Up.normed();
	CSoundDriverFMod::toFModCoord(_Pos, pos);
	CSoundDriverFMod::toFModCoord(_Vel, vel);
	CSoundDriverFMod::toFModCoord(ful, front);
	CSoundDriverFMod::toFModCoord(tul, up);
	FSOUND_3D_Listener_SetAttributes(pos, vel, front[0], front[1], front[2], up[0], up[1], up[2]);
}


} // NLSOUND
