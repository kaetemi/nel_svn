/**
 * \file music_fader.cpp
 * \brief CMusicFader
 * \date 2008-09-04 21:49GMT
 * \author Jan Boon (Kaetemi)
 * CMusicFader roughly based on music_channel_fmod.cpp
 * 
 * $Id$
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
#include "music_fader.h"

// STL includes

// NeL includes
// #include <nel/misc/debug.h>

// Project includes
#include "driver/sound_driver.h"
#include "driver/music_channel.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CMusicFader::CMusicFader(ISoundDriver *soundDriver) : _SoundDriver(soundDriver), _ActiveMusicFader(0), _Gain(0.0f)
{
	for (uint i = 0; i < _MaxMusicFader; ++i)
		_MusicFader[i].MusicChannel = soundDriver->createMusicChannel();
}

CMusicFader::~CMusicFader()
{
	for (uint i = 0; i < _MaxMusicFader; ++i)
		_SoundDriver->destroyMusicChannel(_MusicFader[i].MusicChannel);
}

void CMusicFader::update()
{
	for (uint i = 0; i < _MaxMusicFader; ++i)
	{
		_CMusicFader &fader = _MusicFader[i];
		if (fader.Playing)
		{
			if (fader.MusicChannel->isEnded())
			{
				fader.MusicChannel->stop();
				fader.Playing = false;
				fader.Fade = false;
			}
			else if (fader.Fade)
			{
				fader.XFadeVolume += fader.XFadeDVolume;
				if (fader.XFadeVolume <= 0.f)
				{
					// fadeout complete
					fader.MusicChannel->stop();
					fader.Fade = false;
					fader.Playing = false;
				}
				else if (_MusicFader[i].XFadeVolume >= 1.f)
				{
					// fadein complete
					fader.Fade = false;
					fader.XFadeVolume = 1.f;
				}
			}
		}
	}
	updateVolume();
}

void CMusicFader::updateVolume()
{
	for (uint i = 0; i < _MaxMusicFader; ++i)
		if (_MusicFader[i].Playing)
			_MusicFader[i].MusicChannel->setVolume(_MusicFader[i].XFadeVolume * _Gain);
}

/** Play some music (.ogg etc...)
 *	NB: if an old music was played, it is first stop with stopMusic()
 *	\param filepath file path, CPath::lookup is done here
 *  \param async stream music from hard disk, preload in memory if false
 *	\param loop must be true to play the music in loop. 
 */
bool CMusicFader::play(const std::string &filepath, uint xFadeTime, bool async, bool loop)
{
	stop(xFadeTime);

	// Find the next best free music channel
	uint nextFader = _MaxMusicFader;
	for (uint i = 0; i < _MaxMusicFader; ++i) if (!_MusicFader[i].Playing)
		{ nextFader = i; break; }
	if (nextFader == _MaxMusicFader)
	{
		nextFader = (_ActiveMusicFader + 1) % _MaxMusicFader;
		_MusicFader[nextFader].MusicChannel->stop();
		_MusicFader[nextFader].Fade = false;
		_MusicFader[nextFader].Playing = false;
	}
	_ActiveMusicFader = nextFader;

	// Play a song in it :)
	_CMusicFader &fader = _MusicFader[_ActiveMusicFader];
	if (xFadeTime) fader.fadeIn(xFadeTime);
	else fader.XFadeVolume = 1.0f;
	fader.Playing = true;
	updateVolume(); // make sure at ok volume to start :)
	fader.Playing = fader.MusicChannel->play(filepath, async, loop);
	return fader.Playing;
}

/// Stop the music previously loaded and played (the Memory is also freed)
void CMusicFader::stop(uint xFadeTime)
{
	if (xFadeTime)
	{
		for (uint i = 0; i < _MaxMusicFader; ++i) if (_MusicFader[i].Playing)
			_MusicFader[i].fadeOut(xFadeTime);
	}
	else
	{
		for (uint i = 0; i < _MaxMusicFader; ++i) if (_MusicFader[i].Playing)
		{
			_MusicFader[i].MusicChannel->stop();
			_MusicFader[i].Fade = false;
			_MusicFader[i].Playing = false;
		}
	}
}

/// Pause the music previously loaded and played (the Memory is not freed)
void CMusicFader::pause()
{
	for (uint i = 0; i < _MaxMusicFader; ++i) 
		if (_MusicFader[i].Playing)
			_MusicFader[i].MusicChannel->pause();
}

/// Resume the music previously paused
void CMusicFader::resume()
{
	for (uint i = 0; i < _MaxMusicFader; ++i) 
		if (_MusicFader[i].Playing)
			_MusicFader[i].MusicChannel->resume();
}

/// Return true if all songs are finished.
bool CMusicFader::isEnded()
{
	for (uint i = 0; i < _MaxMusicFader; ++i)
	{
		if (_MusicFader[i].Playing) if (!_MusicFader[i].MusicChannel->isEnded())
			return false; // at least one song still playing
	}
	return true; // no song found that is still playing
}

/// Return the total length (in second) of the music currently played
float CMusicFader::getLength()
{
	return _MusicFader[_ActiveMusicFader].MusicChannel->getLength();
}

/// Set the music volume (if any music played). (volume value inside [0 , 1]) (default: 1)
/// NB: the volume of music is NOT affected by IListener::setGain()
void CMusicFader::setVolume(float gain)
{
	_Gain = gain;
	updateVolume();
}

} /* namespace NLSOUND */

/* end of file */
