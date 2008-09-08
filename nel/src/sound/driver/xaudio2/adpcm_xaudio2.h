/**
 * \file adpcm_xaudio2.h
 * \brief CAdpcmXAudio2
 * \date 2008-09-07 03:53GMT
 * \author Jan Boon (Kaetemi)
 * CAdpcmXAudio2
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

#ifndef NLSOUND_ADPCM_XAUDIO2_H
#define NLSOUND_ADPCM_XAUDIO2_H
#include "stdxaudio2.h"

// STL includes

// NeL includes
#include "../buffer.h"

// Project includes
// #include "sound_driver_xaudio2.h"

namespace NLSOUND {
	class CBufferXAudio2;

/**
 * \brief CAdpcmXAudio2
 * \date 2008-09-07 03:53GMT
 * \author Jan Boon (Kaetemi)
 * CAdpcmXAudio2 (TODO! IGNORE THIS CLASS!)
 */
class CAdpcmXAudio2
{
protected:
	// stuff
	// IBuffer *_SourceBuffer;
	IXAudio2SourceVoice *_SourceVoice;
	uint8 *_SourceData;
	uint32 _SourceSize;
	
	// other stuff
	IBuffer::TADPCMState _State;
	bool _InfiniteLoop;
	uint16 _Buffer[16 * 1024]; // no specific reason, lol
	uint32 _BufferPos; // 0
	uint _InvalidCounter;
public:
	CAdpcmXAudio2();
	virtual ~CAdpcmXAudio2();
	
	/// Submit the next ADPCM buffer, only 1 buffer can be submitted at a time!
	void submitSourceBuffer(CBufferXAudio2 *buffer, bool infiniteLoop);

	/// Reset the decoder, clear the queued buffer
	void flushSourceBuffers();

	/// Returns NULL if the buffer has ended playing, never NULL for loops!
	inline uint8 *getSourceData() { return _SourceData; }

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
}; /* class CAdpcmXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_ADPCM_XAUDIO2_H */

/* end of file */
