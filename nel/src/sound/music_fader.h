/**
 * \file music_fader.h
 * \brief CMusicFader
 * \date 2008-09-04 21:49GMT
 * \author Jan Boon (Kaetemi)
 * CMusicFader roughly based on music_channel_fmod.h
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

#ifndef NLSOUND_MUSIC_FADER_H
#define NLSOUND_MUSIC_FADER_H
#include "stdsound.h"

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {
	class ISoundDriver;
	class IMusicChannel;

/**
 * \brief CMusicFader
 * \date 2004
 * \author Lionel Berenguier
 * \author Nevrax France
 * A player of music in sound driver, allowing fade across music
 * \date 2008-09-04 21:49GMT
 * \author Jan Boon (Kaetemi)
 * Roughly based on stuff in old CMusicChannelFMod
 */
class CMusicFader
{
private:
	struct _CMusicFader
	{
		_CMusicFader::_CMusicFader() : MusicChannel(NULL), XFadeVolume(0.f), XFadeDVolume(0.f), Playing(false), Fade(false) { }
		IMusicChannel *MusicChannel;
		float XFadeVolume; // 0--1
		float XFadeDVolume; // delta
		bool Playing;
		bool Fade;

		inline void fadeIn(uint xFadeTime)
		{
			XFadeVolume = 0.f;
			XFadeDVolume = 1000.f / xFadeTime;
			Fade = true; 
		}

		inline void fadeOut(uint xFadeTime)
		{
			XFadeDVolume = -1000.f / xFadeTime;
			Fade = true;
		}
	};

protected:
	// const
	static const uint _MaxMusicFader = 2;

	// far pointers
	ISoundDriver *_SoundDriver;
	
	// pointers
	_CMusicFader _MusicFader[_MaxMusicFader];
	
	// instances
	uint _ActiveMusicFader;
	float _Gain;
public:
	CMusicFader(ISoundDriver *soundDriver);
	virtual ~CMusicFader();
	inline void update();

private:
	void updateVolume();

public:
	/** Play some music (.ogg etc...)
	 *	NB: if an old music was played, it is first stop with stopMusic()
	 *	\param filepath file path, CPath::lookup is done here
	 *  \param async stream music from hard disk, preload in memory if false
	 *	\param loop must be true to play the music in loop. 
	 */
	bool play(const std::string &filepath, uint xFadeTime = 0, bool async = true, bool loop = true); 

	/// Stop the music previously loaded and played (the Memory is also freed)
	void stop(uint xFadeTime = 0);

	/// Pause the music previously loaded and played (the Memory is not freed)
	void pause();
	
	/// Resume the music previously paused
	void resume();

	/// Return true if all songs are finished.
	bool isEnded();
	
	/// Return the total length (in second) of the music currently played
	float getLength();
	
	/// Set the music volume (if any music played). (volume value inside [0 , 1]) (default: 1)
	/// NB: the volume of music is NOT affected by IListener::setGain()
	void setVolume(float gain);
}; /* class CMusicFader */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_MUSIC_FADER_H */

/* end of file */
