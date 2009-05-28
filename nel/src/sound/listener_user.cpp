/** \file listener_user.cpp
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

#include "stdsound.h"

#include "listener_user.h"
#include "audio_mixer_user.h"


namespace NLSOUND {


/*
 * Set the position vector (default: (0,0,0)) (3D mode only)
 */
void	CListenerUser::setPos( const NLMISC::CVector& pos )
{
	// Change position
	_DrvListener->setPos( pos );

	// Select environment effect
	CAudioMixerUser::instance()->applyListenerMove( pos );
}


} // NLSOUND
