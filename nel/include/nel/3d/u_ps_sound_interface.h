/** \file u_ps_sound_interface.h
 * TODO: File description
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_PS_SOUND_INTERFACE_H
#define NL_PS_SOUND_INTERFACE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/string_mapper.h"
#include <string>

namespace NLMISC
{
	class CVector;
}

namespace NL3D
{

struct UPSSoundInstance;


/**
 * This class is an interface which allow the particle system to create a sound. When a sound is created,
 * the system get an interface on a sound instance. The interface must be registered to the particle system.
 * when it has been created.
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
struct UPSSoundServer
{
	virtual ~UPSSoundServer() {}

	/** Querry the implementer to create a sound instance, and retrieve an interface to it.
	  * NULL means that the server can't create the sound, so it is ignored
	  * \param soundName the name of the sound in the sound bank
	  * \param spawn     true if the sound must be spawned e.g it continues after this interface is removed
	  * \param cb		 useful only for spawned sound, it tells when a spawned sound has been removed
	  */
	virtual UPSSoundInstance *createSound(const NLMISC::TStringId &soundName, bool spawn = false) = 0;
};


/**
  * This is an interface between the particle system and a sound instance. When the system call 'release' on this interface
  * , the sound must be detroyed. If a sound stop before relese is called, this interface must remains valid, however.
  */

struct UPSSoundInstance
{
	virtual ~UPSSoundInstance() {}

	/** The system will call this method to set the parameters of the sound
	  * Values are clamped
	  */
	virtual void setSoundParams(float gain,
								const NLMISC::CVector &pos,
								const NLMISC::CVector &velocity,
								float frequency
							   ) = 0;

	/// start to play the sound
	virtual void play(void) = 0;

	/// tells whether the sound is playing
	virtual bool isPlaying(void) const = 0;

	/// stop the sound
	virtual void stop(void) = 0;

	/// when this method is called, the sound is not needed anymore by the system
	virtual void release(void) = 0;

	/// get pitch
	virtual float getPitch() const = 0;

	// set sound looping
	virtual void setLooping(bool looping) = 0;

	// test if sound is looping
	virtual bool isLooping() const = 0;
};



} // NL3D


#endif // NL_PS_SOUND_INTERFACE_H

/* End of ps_sound_interface.h */
