/** \file music_channel_fmod.cpp
 * <File description>
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

// STL includes

// 3rd Party includes
#include <fmod.h>

// NeL includes

// Project includes
#include "sound_driver_fmod.h"

using namespace std;
using namespace NLMISC;

namespace  NLSOUND
{

signed char F_CALLBACKAPI streamEndCallBack(
	FSOUND_STREAM *stream,
	void *buff,
	int len,
	void *userdata
	)
{
	// Avoid any problem, check that the sound driver is still allocated
	if (!CSoundDriverFMod::instance()) return false;

	// mark this fader as music ended
	CSoundDriverFMod::instance()->markMusicFaderEnded(stream, userdata);
	
	return true;
}

CMusicChannelFMod::CMusicChannelFMod(CSoundDriverFMod *soundDriver) 
: _Gain(1.0f), FModMusicStream(NULL), FModMusicBuffer(NULL), 
FModMusicChannel(-1), CallBackEnded(false), _SoundDriver(soundDriver)
{
	
}

CMusicChannelFMod::~CMusicChannelFMod()
{
	
}

/** Play some music (.ogg etc...)
 *	NB: if an old music was played, it is first stop with stopMusic()
 *	\param filepath file path, CPath::lookup is done here
 *  \param async stream music from hard disk, preload in memory if false
 *	\param loop must be true to play the music in loop. 
 */
bool CMusicChannelFMod::play(const std::string &filepath, bool async, bool loop)
{
	// dont forget set volume
	return false;
}

/// Stop the music previously loaded and played (the Memory is also freed)
void CMusicChannelFMod::stop()
{
	
}

/** Pause the music previously loaded and played (the Memory is not freed)
 */
void CMusicChannelFMod::pause()
{
	
}

/// Resume the music previously paused
void CMusicChannelFMod::resume()
{
	
}

/// Return true if a song is finished.
bool CMusicChannelFMod::isEnded()
{
	return true;
}

/// Return true if the song is still loading asynchronously and hasn't started playing yet (false if not async), used to delay fading
bool CMusicChannelFMod::isLoadingAsync()
{
	return false;
}

/// Return the total length (in second) of the music currently played
float CMusicChannelFMod::getLength()
{
	return .0f;
}

/** Set the music volume (if any music played). (volume value inside [0 , 1]) (default: 1)
 *	NB: the volume of music is NOT affected by IListener::setGain()
 */
void CMusicChannelFMod::setVolume(float gain)
{
	_Gain = gain;
	// set stream volume too
}

//// ***************************************************************************
//bool	CMusicChannelFMod::playMusic(NLMISC::CIFile &fileIn, uint xFadeTime, bool loop)
//{
//	// Stop old channels, according to cross fade or not
//	playMusicStartCrossFade(xFadeTime);
//
//	// start trying to play the corresponding channel
//	nlassert(_ActiveMusicFader<MaxMusicFader);
//	CMusicFader	&fader= _MusicFader[_ActiveMusicFader];
//	// should be stoped in playMusicStartCrossFade()
//	nlassert(fader.FModMusicStream==NULL);
//
//	// try to load the new one in memory
//	uint32	fs= fileIn.getFileSize();
//	if(fs==0)
//		return false;
//
//	// read Buffer
//	fader.FModMusicBuffer= new uint8 [fs];
//	try
//	{
//		fileIn.serialBuffer(fader.FModMusicBuffer, fs);
//	}
//	catch(...)
//	{
//		nlwarning("Sound FMOD: Error While reading music file");
//		delete[] fader.FModMusicBuffer;
//		fader.FModMusicBuffer= NULL;
//		return false;
//	}
//
//	// Load to a stream FMOD sample
//	fader.FModMusicStream= FSOUND_Stream_Open((const char*)fader.FModMusicBuffer,
//		FSOUND_2D|FSOUND_LOADMEMORY|(loop?FSOUND_LOOP_NORMAL:FSOUND_LOOP_OFF), 0, fs);
//	// not succeed?
//	if(!fader.FModMusicStream)
//	{
//		nlwarning("Sound FMOD: Error While creating the FMOD stream for music file");
//		delete[] fader.FModMusicBuffer;
//		fader.FModMusicBuffer= NULL;
//		return false;
//	}
//
//	// start to play this stream (if ok)
//	playMusicStartFader(_ActiveMusicFader);
//
//	return true;
//}
//
//// ***************************************************************************
//bool	CMusicChannelFMod::playMusicAsync(const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop)
//{
//	// Stop old channels, according to cross fade or not
//	playMusicStartCrossFade(xFadeTime);
//
//	// start trying to play the corresponding channel
//	nlassert(_ActiveMusicFader<MaxMusicFader);
//	CMusicFader	&fader= _MusicFader[_ActiveMusicFader];
//	// should be stoped in playMusicStartCrossFade()
//	nlassert(fader.FModMusicStream==NULL);
//
//	// Start FMod
//	fader.FModMusicStream= FSOUND_Stream_Open((const char*)path.c_str(),
//		FSOUND_2D|(loop?FSOUND_LOOP_NORMAL:FSOUND_LOOP_OFF)|FSOUND_NONBLOCKING, fileOffset, fileSize);
//	// with FSOUND_NONBLOCKING, should always succeed
//	nlassert(fader.FModMusicStream);
//
//	// with FSOUND_NONBLOCKING, the file is surely not ready, but still try now (will retry to replay at each updateMusic())
//	playMusicStartFader(_ActiveMusicFader);
//
//	return true;
//}
//
//// ***************************************************************************
//void	CMusicChannelFMod::stopMusic(uint xFadeTime)
//{
//	// if no cross fade
//	if(xFadeTime==0)
//	{
//		// stop Music on all channels
//		for(uint i=0;i<MaxMusicFader;i++)
//			stopMusicFader(i);
//	}
//	// else don't stop now, but fade out
//	else
//	{
//		// setup all playing channels to fade out
//		for(uint i=0;i<MaxMusicFader;i++)
//		{
//			CMusicFader	&fader= _MusicFader[i];
//
//			// if playing, setup fade out (don't modify previous XFadeVolume, if for instance previous XFade not ended)
//			if(fader.FModMusicStream)
//				fader.XFadeDVolume= -1000.f/xFadeTime;
//		}
//	}
//}
//
//// ***************************************************************************
//void	CMusicChannelFMod::pauseMusic()
//{
//	// setup all playing channels to fade out
//	for(uint i=0;i<MaxMusicFader;i++)
//	{
//		CMusicFader	&fader= _MusicFader[i];
//
//		// If playing and not fading out
//		if(fader.FModMusicChannel != -1 && fader.XFadeDVolume >= 0.f)
//			FSOUND_SetPaused(fader.FModMusicChannel, true);
//	}
//}
//
//// ***************************************************************************
//void	CMusicChannelFMod::resumeMusic()
//{
//	// setup all playing channels to fade out
//	for(uint i=0;i<MaxMusicFader;i++)
//	{
//		CMusicFader	&fader= _MusicFader[i];
//
//		// If paused, resume
//		if(fader.FModMusicChannel != -1 && FSOUND_GetPaused(fader.FModMusicChannel))
//			FSOUND_SetPaused(fader.FModMusicChannel, false);
//	}
//}
//
//// ***************************************************************************
//bool	CMusicChannelFMod::isMusicEnded()
//{
//	bool	channelEnded= true;
//
//	// test all playing channels
//	for(uint i=0;i<MaxMusicFader;i++)
//	{
//		CMusicFader	&fader= _MusicFader[i];
//
//		// If playing and not fading out
//		if(fader.FModMusicStream && fader.FModMusicChannel != -1)
//		{
//			bool	faderEnded= false;
//			// test with file position
//			if ((int)FSOUND_Stream_GetPosition(fader.FModMusicStream) == FSOUND_Stream_GetLength(fader.FModMusicStream))
//				faderEnded= true;
//			// NB: the preceding code don't work with .ogg vorbis encoded mp3. Thus test also the end with a callback
//			if(fader.CallBackEnded)
//				faderEnded= true;
//
//			// channel is considered ended if all fader have ended
//			channelEnded &= faderEnded;
//		}
//		// if playing, but not starting because of async, not ended (because not even really started)
//		else if(fader.FModMusicStream)
//			channelEnded= false;
//	}
//
//	return channelEnded;
//}
//
//// ***************************************************************************
//float	CMusicChannelFMod::getMusicLength()
//{
//	// return the active music channel length
//	CMusicFader	&fader= _MusicFader[_ActiveMusicFader];
//
//	// If playing
//	if(fader.FModMusicStream && fader.FModMusicChannel != -1)
//	{
//		return FSOUND_Stream_GetLengthMs(fader.FModMusicStream)*0.001f;
//	}
//
//	return 0.f;
//}
//
//// ***************************************************************************
//void	CMusicChannelFMod::setMusicVolume(float gain)
//{
//	// bkup the volume
//	clamp(gain, 0.f, 1.f);
//	_FModMusicVolume= gain;
//
//	// update volume of all music channels
//	for(uint i=0;i<MaxMusicFader;i++)
//		updateMusicVolumeFader(i);
//}
//
//// ***************************************************************************
//void	CMusicChannelFMod::updateMusic(float dt)
//{
//	for(uint i=0;i<MaxMusicFader;i++)
//	{
//		CMusicFader	&fader= _MusicFader[i];
//
//		// **** may start now the play (async playing)
//		// if this channel is playing an async music, may retry to start the music each frame
//		if(fader.FModMusicStream && fader.FModMusicBuffer==NULL)
//		{
//			if(fader.FModMusicChannel==-1)
//			{
//				playMusicStartFader(i);
//			}
//		}
//
//		// **** update fading
//		// if playing and some fadein/fadeout
//		if(fader.FModMusicStream && fader.XFadeDVolume)
//		{
//			// update volume
//			fader.XFadeVolume+= fader.XFadeDVolume*dt;
//
//			// if fade in and max reached, stop fade in
//			if(fader.XFadeDVolume>0 && fader.XFadeVolume>1.f)
//			{
//				fader.XFadeVolume= 1.f;
//				fader.XFadeDVolume= 0;
//			}
//			// if fade out and min reached, stop music and fade out!
//			else if(fader.XFadeDVolume<0 && fader.XFadeVolume<0.f)
//			{
//				fader.XFadeVolume= 0.f;
//				fader.XFadeDVolume= 0;
//				stopMusicFader(i);
//			}
//
//			// update the actual volume (NB: if just stoped, will work, see updateMusicVolumeFader)
//			updateMusicVolumeFader(i);
//		}
//	}
//
//	// flush the FMod stream waiting for close
//	updateMusicFModStreamWaitingForClose();
//}
//
//// ***************************************************************************
//void	CMusicChannelFMod::updateMusicFModStreamWaitingForClose()
//{
//	std::list<FSOUND_STREAM*>::iterator	it= _FModMusicStreamWaitingForClose.begin();
//	while(it!=_FModMusicStreamWaitingForClose.end())
//	{
//		bool	ok= FSOUND_Stream_Stop(*it)!=0;
//		if(ok)
//			ok= FSOUND_Stream_Close(*it)!=0;
//		// erase from list, or next
//		if(ok)
//			it= _FModMusicStreamWaitingForClose.erase(it);
//		else
//			it++;
//	}
//}
//
//// ***************************************************************************
void	CMusicChannelFMod::markMusicFaderEnded(void *stream, void *fader)
{
	//for(uint i=0;i<MaxMusicFader;i++)
	//{
	//	if(fader==&(_MusicFader[i]) && stream==_MusicFader[i].FModMusicStream)
	//	{
	//		_MusicFader[i].CallBackEnded= true;
	//		return;
	//	}
	//}
}


}

