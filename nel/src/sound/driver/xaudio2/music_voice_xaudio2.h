/**
 * \file music_voice_xaudio2.h
 * \brief CMusicVoiceXAudio2
 * \date 2008-08-30 13:32GMT
 * \author Jan Boon (Kaetemi)
 * CMusicVoiceXAudio2
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

#ifndef NLSOUND_MUSIC_VOICE_XAUDIO2_H
#define NLSOUND_MUSIC_VOICE_XAUDIO2_H
#include "stdxaudio2.h"

// Project includes
#include "music_buffer.h" // ../

// NeL includes

// STL includes

namespace NLMISC {
	class CIFile;
}

namespace NLSOUND {
	class IMusicBuffer;

/**
 * \brief CMusicVoiceXAudio2
 * \date 2008-08-30 13:32GMT
 * \author Jan Boon (Kaetemi)
 * CMusicVoiceXAudio2
 */
class CMusicVoiceXAudio2 : IXAudio2VoiceCallback
{
protected:
	// far pointers
	CSoundDriverXAudio2 *_SoundDriver;
	
	// pointers
	IMusicBuffer *_MusicBuffer;
	IXAudio2SourceVoice *_SourceVoice;
	
	// instances
	uint8 _Buffer[16 * 1024]; // no specific reason, lol
	uint32 _BufferPos; // 0
	float _Gain;
public:
	CMusicVoiceXAudio2();
	virtual ~CMusicVoiceXAudio2();
	void init(CSoundDriverXAudio2 *soundDriver);
	void reset();

	void play(const std::string &streamName, NLMISC::IStream *stream, bool loop);
	void stop();
	void pause();
	void resume();
	inline bool isEnded() { if (_MusicBuffer && _SourceVoice) return _MusicBuffer->isMusicEnded(); else return true; }
	inline float getLength() { if (_MusicBuffer) return _MusicBuffer->getLength(); else return .0f; } // in seconds
	inline void setVolume(float gain) { _Gain = gain; if (_SourceVoice) { _SourceVoice->SetVolume(gain); } } // 1.0 normal

private:
	// XAudio2 Callbacks
    // Called just before this voice's processing pass begins.
    STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired);
    // Called just after this voice's processing pass ends.
    STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS);
    // Called when this voice has just finished playing a buffer stream
    // (as marked with the XAUDIO2_END_OF_STREAM flag on the last buffer).
    STDMETHOD_(void, OnStreamEnd) (THIS);
    // Called when this voice is about to start processing a new buffer.
    STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext);
    // Called when this voice has just finished processing a buffer.
    // The buffer can now be reused or destroyed.
    STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext);
    // Called when this voice has just reached the end position of a loop.
    STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext);
    // Called in the event of a critical error during voice processing,
    // such as a failing XAPO or an error from the hardware XMA decoder.
    // The voice may have to be destroyed and re-created to recover from
    // the error.  The callback arguments report which buffer was being
    // processed when the error occurred, and its HRESULT code.
    STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error);
}; /* class CMusicVoiceXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_MUSIC_VOICE_XAUDIO2_H */

/* end of file */
