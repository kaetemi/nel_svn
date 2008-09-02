/**
 * \file music_channel_xaudio2.h
 * \brief CMusicChannelXAudio2
 * \date 2008-08-30 13:31GMT
 * \author Jan Boon (Kaetemi)
 * CMusicChannelXAudio2
 * 
 * $Id$
 */

/* 
 * Copyright (C) 2008  Jan Boon (Kaetemi)
 * 
 * This file is part of NLSOUND XAudio2 Driver.
 * NLSOUND XAudio2 Driver is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 * 
 * NLSOUND XAudio2 Driver is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NLSOUND XAudio2 Driver; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */

#ifndef NLSOUND_MUSIC_CHANNEL_XAUDIO2_H
#define NLSOUND_MUSIC_CHANNEL_XAUDIO2_H
#include "stdxaudio2.h"

// Project includes
#include "music_voice_xaudio2.h"

// NeL includes

// STL includes

namespace NLSOUND {

/**
 * \brief CMusicChannelXAudio2
 * \date 2008-08-30 13:31GMT
 * \author Jan Boon (Kaetemi)
 * CMusicChannelXAudio2
 * channel has 2 voices to fade between
 */
class CMusicChannelXAudio2
{
protected:
	// pointers
	// ...
	
	// instances
	bool _Fading;
	//bool _Playing;
	uint8 _Active; // 0 voice 0, 1 voice 1
	float _Balance; // balance between two voices 0.0 voice 0, 1.0 voice 1
	float _Gain; // 0.0 to 1.0
	float _FadeTime; // total time for fade
	CMusicVoiceXAudio2 _MusicVoices[2]; // two voices to fade between
	NLMISC::IStream *_Streams[2]; // streams to delete
public:
	CMusicChannelXAudio2(CSoundDriverXAudio2 *soundDriver);
	virtual ~CMusicChannelXAudio2();

	void play(NLMISC::CIFile &file, uint xFadeTime, bool loop);
	void play(const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop);
	void stop(uint fadeTimeMs);
	inline void pause() { /*_Playing = false; */_MusicVoices[0].pause(); _MusicVoices[1].pause(); };
	inline void resume() {/* _Playing = true; */_MusicVoices[0].resume(); _MusicVoices[1].resume(); };
	inline bool isEnded() { return _MusicVoices[_Active].isEnded(); }
	inline float getLength() { return _MusicVoices[_Active].getLength(); } // in seconds
	inline void setVolume(float gain) { _Gain = gain; updateVolume(); } // 1.0 normal
	inline void setBalance(float balance) { _Balance = balance; updateVolume(); } // 0.0 0, 1.0 1
	inline uint8 getActive() const { return _Active; }
	inline uint8 getInactive() const { return _Active ? 0 : 1; }

	void update(float dt);

private:
	inline void updateVolume() { _MusicVoices[0].setVolume((1.0f - _Balance) * _Gain); _MusicVoices[1].setVolume(_Balance * _Gain); };
	void switchVoice(uint fadeTime);
}; /* class CMusicChannelXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_MUSIC_CHANNEL_XAUDIO2_H */

/* end of file */
