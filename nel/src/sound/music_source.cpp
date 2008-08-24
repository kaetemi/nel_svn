/** \file music_source.cpp
 * TODO: File description
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

#include "music_source.h"
#include "music_sound.h"
#include "audio_mixer_user.h"
#include "music_sound_manager.h"


namespace NLSOUND {


// ***************************************************************************
CMusicSource::CMusicSource(CMusicSound *musicSound, bool spawn, TSpawnEndCallback cb, void *cbUserParam, NL3D::CCluster *cluster)
	:	CSourceCommon(musicSound, spawn, cb, cbUserParam, cluster)
{
	_MusicSound= musicSound;
}

// ***************************************************************************
CMusicSource::~CMusicSource()
{
	if(isPlaying())
		stop();

	// avoid any bug, ensure the source is removed
	CAudioMixerUser::instance()->getBackgroundMusicManager()->removeMusicSourcePlaying(this);
}

// ***************************************************************************
TSoundId			CMusicSource::getSound()
{
	return _MusicSound;
}

// ***************************************************************************
void				CMusicSource::play()
{
	// if already playing, no-op (don't restart)
	if(isPlaying())
		return;

	// append and play common
	CAudioMixerUser::instance()->getBackgroundMusicManager()->addMusicSourcePlaying(this);
	CSourceCommon::play();
}

// ***************************************************************************
void				CMusicSource::stop()
{
	// if already non-playing, no-op (don't restop)
	if(!isPlaying())
		return;

	// remove and stop common
	CAudioMixerUser::instance()->getBackgroundMusicManager()->removeMusicSourcePlaying(this);
	CSourceCommon::stop();
}


} // NLSOUND
