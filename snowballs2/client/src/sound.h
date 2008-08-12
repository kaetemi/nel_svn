/** \file sound.h
 * Sound interface between the game and NeL
 *
 * $Id: sound.h,v 1.4 2003/02/24 13:04:53 lecroart Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef SOUND_H
#define SOUND_H

//
// Includes
//

#include <nel/sound/u_audio_mixer.h>
#include <nel/sound/u_listener.h>
#include <nel/sound/u_source.h>


#include "entities.h"

//
// External variables
//

extern NLSOUND::UAudioMixer *AudioMixer;

extern NLSOUND::TSoundId SoundId;

//
// External functions
//

void	initSound ();
void	updateSound ();
void	releaseSound ();

// Set and play a sound on an entity
void	playSound (CEntity &entity, NLSOUND::TSoundId id);

// Remove the sound system link to the entity
void	deleteSound (CEntity &entity);

#endif // SOUND_H

/* End of sound.h */
