/** \file sound.cpp
 * Sound interface between the game and NeL
 *
 * $Id: sound.cpp,v 1.3 2003/02/24 13:04:53 lecroart Exp $
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

//
// Includes
//

#include <math.h>
#include <vector>

#include <nel/misc/vector.h>

#include <nel/sound/u_audio_mixer.h>
#include <nel/sound/u_listener.h>
#include <nel/sound/u_source.h>

#include "client.h"
#include "entities.h"

//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NLSOUND;

//
// Variables
//

UAudioMixer *AudioMixer = NULL;

TSoundId SoundId;

const vector<TSoundId> *SoundIdArray;

//
// Functions
//

void	initSound()
{
/*	AudioMixer = UAudioMixer::createAudioMixer ();
	AudioMixer->init ();

	AudioMixer->loadSoundBuffers ("sounds.nss", &SoundIdArray);
	nlassert( SoundIdArray->size() == 2 );
	SoundId = (*SoundIdArray)[0];
//	StSoundId = (*SoundIdArray)[1];
*/}


void	playSound (CEntity &entity, TSoundId id)
{
/*	entity.Source = AudioMixer->createSource (id);
	entity.Source->setLooping (true);
	entity.Source->play ();
*/}

void	deleteSound (CEntity &entity)
{
/*	if (entity.Source != NULL)
	{
		if (entity.Source->isPlaying ())
			entity.Source->stop ();

		AudioMixer->removeSource (entity.Source);
		entity.Source = NULL;
	}
*/}

void	updateSound()
{
	/// \todo 
}

void	releaseSound()
{
	/// \todo 
}
