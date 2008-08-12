/** \file music_channel_fmod.h
 * <File description>
 *
 * $Id: music_channel_fmod.h,v 1.1 2004/12/13 17:52:58 berenguier Exp $
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

#ifndef NL_MUSIC_CHANNEL_FMOD_H
#define NL_MUSIC_CHANNEL_FMOD_H

#include "nel/misc/types_nl.h"

struct FSOUND_STREAM;

namespace NLSOUND {
	
// ***************************************************************************
/**
 * A player of music in sound driver, allowing fade across music
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2004
 */
class CMusicChannelFMod
{
public:

	/// Constructor
	CMusicChannelFMod();

	// playing of a channel, with/wo fading
	bool	playMusicAsync(const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop);
	bool	playMusic(NLMISC::CIFile &fileIn, uint xFadeTime, bool loop);

	// stoping the channel with/wo fading
	void	stopMusic(uint xFadeTime);
	
	// set the music volume
	void	setMusicVolume(float volume);

	// extras
	void	pauseMusic();
	void	resumeMusic();
	bool	isMusicEnded();
	float	getMusicLength();
		
	// update
	void	updateMusic(float dt);

	// From callback
	void	markMusicFaderEnded(void *stream, void *fader);

private:

	/// A music fader fade 2 musics
	class CMusicFader
	{
	public:
		FSOUND_STREAM		*FModMusicStream;	// The FMod stream
		uint8				*FModMusicBuffer;	// the RAM buffer (representation of a MP3 file, only for sync play)
		sint				FModMusicChannel;	// channel played for music. CAN BE -1 while FModMusicStream!=NULL in case of Async Loading
		float				XFadeVolume;		// 0--1
		float				XFadeDVolume;		// dt
		bool				CallBackEnded;		// true if the fmod end callback said the stream is ended
		
	public:
		CMusicFader()
		{
			FModMusicStream= NULL;
			FModMusicBuffer= NULL;
			FModMusicChannel= -1;
			XFadeVolume= 0.f;
			XFadeDVolume= 0.f;
			CallBackEnded= false;
		}
	};

	// 2 musics channels for XFade
	enum	{MaxMusicFader= 2};
	CMusicFader					_MusicFader[MaxMusicFader];
	uint8						_ActiveMusicFader;
	float						_FModMusicVolume;
	std::list<FSOUND_STREAM*>	_FModMusicStreamWaitingForClose;	// see stopMusicFader()
	
	void	playMusicStartCrossFade(uint xFadeTime);
	void	playMusicStartFader(uint musicFader);
	void	stopMusicFader(uint musicFader);
	void	updateMusicVolumeFader(uint musicFader);
	void	updateMusicFModStreamWaitingForClose();
	
};

}

#endif // NL_MUSIC_CHANNEL_FMOD_H

/* End of music_channel_fmod.h */
