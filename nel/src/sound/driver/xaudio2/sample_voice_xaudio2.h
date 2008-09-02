/**
 * \file sample_voice_xaudio2.h
 * \brief CSampleVoiceXAudio2
 * \date 2008-08-21 09:55GMT
 * \author Jan Boon (Kaetemi)
 * CSampleVoiceXAudio2
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

#ifndef NLSOUND_SAMPLE_VOICE_XAUDIO2_H
#define NLSOUND_SAMPLE_VOICE_XAUDIO2_H
#include "stdxaudio2.h"

// Project includes

// NeL includes
#include <nel/misc/mutex.h>

// STL includes

namespace NLSOUND {
	class CSourceXAudio2;
	class CBufferXAudio2;

/**
 * \brief CSampleVoiceXAudio2
 * \date 2008-08-21 09:55GMT
 * \author Jan Boon (Kaetemi)
 * CSampleVoiceXAudio2
 * Contains an allocated voice of a specified format.
 */
class CSampleVoiceXAudio2 : IXAudio2VoiceCallback
{
	friend class CSoundDriverXAudio2;
	friend class CSourceXAudio2;

protected:
	// far pointers
	CBufferXAudio2 *_Buffer; // MT // set from OnBufferStart :)
	CSourceXAudio2 *_Owner; // MT  // 'owner' of this sample voice

	// pointers
	IXAudio2SourceVoice *_SourceVoice; // doesn't change at runtime
	
	// instances
	TSampleFormat _Format; // doesn't change at runtime

	// user vars
	float _Pitch; // MT // changed by user
public:
	inline TSampleFormat getFormat() { return _Format; }
	inline IXAudio2SourceVoice *getSourceVoice() { return _SourceVoice; }

	inline void setPitch(float pitch) { _Pitch = pitch; updatePitch(); } // applied immediately
	inline float getPitch() { return _Pitch; }

	inline CSourceXAudio2 *getOwner() { return _Owner; }
	inline CBufferXAudio2 *getBuffer() { return _Buffer; }

private:
	CSampleVoiceXAudio2(CSourceXAudio2 *owner, TSampleFormat format);
	virtual ~CSampleVoiceXAudio2();
	inline void setOwner(CSourceXAudio2 *owner) { _Owner = owner; }
	
	void updatePitch();

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
}; /* class CSampleVoiceXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SAMPLE_VOICE_XAUDIO2_H */

/* end of file */
