/** \file u_particle_system_sound.h
 * TODO: File description
 *
 * $Id: u_particle_system_sound.h,v 1.6 2004/11/15 10:24:18 lecroart Exp $
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

#ifndef NL_U_PARTICLE_SYSTEM_SOUND_H
#define NL_U_PARTICLE_SYSTEM_SOUND_H

#include "nel/misc/types_nl.h"

#include "u_ps_sound_interface.h"
#include "u_ps_sound_impl.h"





namespace NL3D {

// if you include this, you must also have the NLSOUND library








/// for private use only..
void assignSoundServerToPS(UPSSoundServer *soundServer);


/**
 * This init the sound for particle systems
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class UParticleSystemSound
{
public:
	/// init the particle system sound with the given AudioMixer
	static void setPSSound(NLSOUND::UAudioMixer *audioMixer);
};


} // NL3D


#endif // NL_U_PARTICLE_SYSTEM_SOUND_H

/* End of u_particle_system_sound.h */
