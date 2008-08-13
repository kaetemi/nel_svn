/** \file music_channel_fmod.cpp
 * <File description>
 *
 * $Id: music_channel_fmod.cpp,v 1.1 2004/12/13 17:52:58 berenguier Exp $
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

#include "stdfmod.h"

#include "music_channel_fmod.h"
#include "sound_driver_fmod.h"

#include <fmod.h>


using namespace std;
using namespace NLMISC;


namespace NLSOUND 
{


// ***************************************************************************
signed char F_CALLBACKAPI streamEndCallBack(
	FSOUND_STREAM *stream,
	void *buff,
	int len,
	void *userdata
	)
{
	// Avoid any problem, check that the sound driver is still allocated
	if(CSoundDriverFMod::instance()==NULL)
		return false;
	// mark this fader as music ended
	CSoundDriverFMod::instance()->markMusicFaderEnded(stream, userdata);

	return true;
}
	

// ***************************************************************************
CMusicChannelFMod::CMusicChannelFMod()
{
	_ActiveMusicFader= 0;
	_FModMusicVolume= 1.f;
}			

// ***************************************************************************
void	CMusicChannelFMod::playMusicStartCrossFade(uint xFadeTime)
{
	if(xFadeTime==0)
	{
		// stop all channels
		stopMusic(0);
		_ActiveMusicFader= 0;
		// setup no cross fade
		_MusicFader[_ActiveMusicFader].XFadeVolume= 1.f;
		_MusicFader[_ActiveMusicFader].XFadeDVolume= 0.f;
	}
	else
	{
		// setup fade out for old music channel (don't modify previous XFadeVolume, if for instance previous XFade not ended)
		_MusicFader[_ActiveMusicFader].XFadeDVolume= -1000.f/xFadeTime;
		
		// get new active channel
		_ActiveMusicFader++;
		_ActiveMusicFader= _ActiveMusicFader%MaxMusicFader;
		
		// stop this channel if was still played (eg: playMusic() of a third music comes in while old XFade not ended)
		stopMusicFader(_ActiveMusicFader);
		
		// setup fade in for new music channel
		_MusicFader[_ActiveMusicFader].XFadeVolume= 0.f;
		_MusicFader[_ActiveMusicFader].XFadeDVolume= 1000.f/xFadeTime;
	}
	
}

// ***************************************************************************
void	CMusicChannelFMod::playMusicStartFader(uint musicFader)
{
	CMusicFader	&fader= _MusicFader[musicFader];

	// if stopped, abort
	if(!fader.FModMusicStream)
		return;

	// if already start played, no op
	if(fader.FModMusicChannel!=-1)
		return;

	// try to start playing
	fader.FModMusicChannel= FSOUND_Stream_PlayEx(FSOUND_FREE, fader.FModMusicStream, NULL, true);
	// may failed for async case
	if(fader.FModMusicChannel!=-1)
	{
		// stereo pan (as reccomended)
		FSOUND_SetPan(fader.FModMusicChannel, FSOUND_STEREOPAN);
		// update this channel volume (xFaded or not)
		updateMusicVolumeFader(musicFader);
		// unpause
		FSOUND_SetPaused(fader.FModMusicChannel, false);
		// Set a callback to know if stream has ended
		fader.CallBackEnded= false;
		FSOUND_Stream_SetEndCallback(fader.FModMusicStream, streamEndCallBack, &fader);
	}
}

// ***************************************************************************
void	CMusicChannelFMod::stopMusicFader(uint musicFader)
{
	nlassert(musicFader<MaxMusicFader);
	CMusicFader	&fader= _MusicFader[musicFader];

	// if playing some music
	if(fader.FModMusicStream)
	{
		/* just append this channel for closing. We have to maintain such a list because in case of async playing,
			FMod FSOUND_Stream_Stop() and FSOUND_Stream_Close() calls fail if the file is not ready (hapens if music stoped
			in the 50 ms after the play for instance)
		*/
		_FModMusicStreamWaitingForClose.push_back(fader.FModMusicStream);
		// force stop now (succeed in 99% of case, and if not succeed, it means the play has not yet begun, so no problem)
		updateMusicFModStreamWaitingForClose();
		
		// reset
		fader.FModMusicChannel= -1;
		fader.FModMusicStream= NULL;
		// delete the music buffer (only != NULL if !async)
		delete[] fader.FModMusicBuffer;
		fader.FModMusicBuffer= NULL;
		// just to be clean
		fader.XFadeVolume= 0.f;
		fader.XFadeDVolume= 0.f;
	}
}

// ***************************************************************************
void	CMusicChannelFMod::updateMusicVolumeFader(uint musicFader)
{
	nlassert(musicFader<MaxMusicFader);
	CMusicFader	&fader= _MusicFader[musicFader];
	
	// the channel must be really playing (may not be the case for async play)
	if(fader.FModMusicStream && fader.FModMusicChannel!=-1)
	{
		float	realVol= fader.XFadeVolume*_FModMusicVolume;
		clamp(realVol, 0.f, 1.f);
		uint8	vol255= uint(realVol*255);
		FSOUND_SetVolumeAbsolute(fader.FModMusicChannel, vol255);
	}
}

// ***************************************************************************
bool	CMusicChannelFMod::playMusic(NLMISC::CIFile &fileIn, uint xFadeTime, bool loop)
{
	// Stop old channels, according to cross fade or not
	playMusicStartCrossFade(xFadeTime);
	
	// start trying to play the corresponding channel
	nlassert(_ActiveMusicFader<MaxMusicFader);
	CMusicFader	&fader= _MusicFader[_ActiveMusicFader];
	// should be stoped in playMusicStartCrossFade()
	nlassert(fader.FModMusicStream==NULL);
	
	// try to load the new one in memory
	uint32	fs= fileIn.getFileSize();
	if(fs==0)
		return false;
	
	// read Buffer
	fader.FModMusicBuffer= new uint8 [fs];
	try
	{
		fileIn.serialBuffer(fader.FModMusicBuffer, fs);
	}
	catch(...)
	{
		nlwarning("Sound FMOD: Error While reading music file");
		delete[] fader.FModMusicBuffer;
		fader.FModMusicBuffer= NULL;
		return false;
	}
	
	// Load to a stream FMOD sample
	fader.FModMusicStream= FSOUND_Stream_Open((const char*)fader.FModMusicBuffer, 
		FSOUND_2D|FSOUND_LOADMEMORY|(loop?FSOUND_LOOP_NORMAL:FSOUND_LOOP_OFF), 0, fs);
	// not succeed?
	if(!fader.FModMusicStream)
	{
		nlwarning("Sound FMOD: Error While creating the FMOD stream for music file");
		delete[] fader.FModMusicBuffer;
		fader.FModMusicBuffer= NULL;
		return false;
	}
	
	// start to play this stream (if ok)
	playMusicStartFader(_ActiveMusicFader);
	
	return true;
}
	
// ***************************************************************************
bool	CMusicChannelFMod::playMusicAsync(const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop)
{
	// Stop old channels, according to cross fade or not
	playMusicStartCrossFade(xFadeTime);
	
	// start trying to play the corresponding channel
	nlassert(_ActiveMusicFader<MaxMusicFader);
	CMusicFader	&fader= _MusicFader[_ActiveMusicFader];
	// should be stoped in playMusicStartCrossFade()
	nlassert(fader.FModMusicStream==NULL);
	
	// Start FMod
	fader.FModMusicStream= FSOUND_Stream_Open((const char*)path.c_str(), 
		FSOUND_2D|(loop?FSOUND_LOOP_NORMAL:FSOUND_LOOP_OFF)|FSOUND_NONBLOCKING, fileOffset, fileSize);
	// with FSOUND_NONBLOCKING, should always succeed
	nlassert(fader.FModMusicStream);
	
	// with FSOUND_NONBLOCKING, the file is surely not ready, but still try now (will retry to replay at each updateMusic())
	playMusicStartFader(_ActiveMusicFader);
	
	return true;
}
	
// ***************************************************************************
void	CMusicChannelFMod::stopMusic(uint xFadeTime)
{
	// if no cross fade
	if(xFadeTime==0)
	{
		// stop Music on all channels
		for(uint i=0;i<MaxMusicFader;i++)
			stopMusicFader(i);
	}
	// else don't stop now, but fade out
	else
	{
		// setup all playing channels to fade out
		for(uint i=0;i<MaxMusicFader;i++)
		{
			CMusicFader	&fader= _MusicFader[i];
			
			// if playing, setup fade out (don't modify previous XFadeVolume, if for instance previous XFade not ended)
			if(fader.FModMusicStream)
				fader.XFadeDVolume= -1000.f/xFadeTime;
		}	
	}
}

// ***************************************************************************
void	CMusicChannelFMod::pauseMusic()
{
	// setup all playing channels to fade out
	for(uint i=0;i<MaxMusicFader;i++)
	{
		CMusicFader	&fader= _MusicFader[i];
		
		// If playing and not fading out
		if(fader.FModMusicChannel != -1 && fader.XFadeDVolume >= 0.f)
			FSOUND_SetPaused(fader.FModMusicChannel, true);
	}	
}

// ***************************************************************************
void	CMusicChannelFMod::resumeMusic()
{
	// setup all playing channels to fade out
	for(uint i=0;i<MaxMusicFader;i++)
	{
		CMusicFader	&fader= _MusicFader[i];
		
		// If paused, resume
		if(fader.FModMusicChannel != -1 && FSOUND_GetPaused(fader.FModMusicChannel))
			FSOUND_SetPaused(fader.FModMusicChannel, false);
	}	
}

// ***************************************************************************
bool	CMusicChannelFMod::isMusicEnded()
{
	bool	channelEnded= true;

	// test all playing channels
	for(uint i=0;i<MaxMusicFader;i++)
	{
		CMusicFader	&fader= _MusicFader[i];
		
		// If playing and not fading out
		if(fader.FModMusicStream && fader.FModMusicChannel != -1)
		{
			bool	faderEnded= false;
			// test with file position
			if ((int)FSOUND_Stream_GetPosition(fader.FModMusicStream) == FSOUND_Stream_GetLength(fader.FModMusicStream))
				faderEnded= true;
			// NB: the preceding code don't work with .ogg vorbis encoded mp3. Thus test also the end with a callback
			if(fader.CallBackEnded)
				faderEnded= true;

			// channel is considered ended if all fader have ended
			channelEnded &= faderEnded;
		}
		// if playing, but not starting because of async, not ended (because not even really started)
		else if(fader.FModMusicStream)
			channelEnded= false;
	}	

	return channelEnded;
}

// ***************************************************************************
float	CMusicChannelFMod::getMusicLength()
{
	// return the active music channel length
	CMusicFader	&fader= _MusicFader[_ActiveMusicFader];

	// If playing
	if(fader.FModMusicStream && fader.FModMusicChannel != -1)
	{
		return FSOUND_Stream_GetLengthMs(fader.FModMusicStream)*0.001f;
	}

	return 0.f;
}

// ***************************************************************************
void	CMusicChannelFMod::setMusicVolume(float gain)
{
	// bkup the volume
	clamp(gain, 0.f, 1.f);
	_FModMusicVolume= gain;
	
	// update volume of all music channels
	for(uint i=0;i<MaxMusicFader;i++)
		updateMusicVolumeFader(i);
}

// ***************************************************************************
void	CMusicChannelFMod::updateMusic(float dt)
{
	for(uint i=0;i<MaxMusicFader;i++)
	{
		CMusicFader	&fader= _MusicFader[i];
		
		// **** may start now the play (async playing)
		// if this channel is playing an async music, may retry to start the music each frame
		if(fader.FModMusicStream && fader.FModMusicBuffer==NULL)
		{
			if(fader.FModMusicChannel==-1)
			{
				playMusicStartFader(i);
			}
		}
		
		// **** update fading
		// if playing and some fadein/fadeout
		if(fader.FModMusicStream && fader.XFadeDVolume)
		{
			// update volume
			fader.XFadeVolume+= fader.XFadeDVolume*dt;
			
			// if fade in and max reached, stop fade in
			if(fader.XFadeDVolume>0 && fader.XFadeVolume>1.f)
			{
				fader.XFadeVolume= 1.f;
				fader.XFadeDVolume= 0;
			}
			// if fade out and min reached, stop music and fade out!
			else if(fader.XFadeDVolume<0 && fader.XFadeVolume<0.f)
			{
				fader.XFadeVolume= 0.f;
				fader.XFadeDVolume= 0;
				stopMusicFader(i);
			}
			
			// update the actual volume (NB: if just stoped, will work, see updateMusicVolumeFader)
			updateMusicVolumeFader(i);
		}
	}

	// flush the FMod stream waiting for close
	updateMusicFModStreamWaitingForClose();
}

// ***************************************************************************
void	CMusicChannelFMod::updateMusicFModStreamWaitingForClose()
{
	std::list<FSOUND_STREAM*>::iterator	it= _FModMusicStreamWaitingForClose.begin();
	while(it!=_FModMusicStreamWaitingForClose.end())
	{
		bool	ok= FSOUND_Stream_Stop(*it)!=0;
		if(ok)
			ok= FSOUND_Stream_Close(*it)!=0;
		// erase from list, or next
		if(ok)
			it= _FModMusicStreamWaitingForClose.erase(it);
		else
			it++;
	}
}

// ***************************************************************************
void	CMusicChannelFMod::markMusicFaderEnded(void *stream, void *fader)
{
	for(uint i=0;i<MaxMusicFader;i++)
	{
		if(fader==&(_MusicFader[i]) && stream==_MusicFader[i].FModMusicStream)
		{
			_MusicFader[i].CallBackEnded= true;
			return;
		}
	}
}


}

