/**
 * \file adpcm_xaudio2.cpp
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

#include "stdxaudio2.h"
#include "adpcm_xaudio2.h"

// STL includes

// NeL includes
#include <nel/misc/debug.h>

// Project includes
#include "buffer_xaudio2.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CAdpcmXAudio2::CAdpcmXAudio2()
{
	
}

CAdpcmXAudio2::~CAdpcmXAudio2()
{
	
}

/// Submit the next ADPCM buffer, only 1 buffer can be submitted at a time!
void CAdpcmXAudio2::submitSourceBuffer(CBufferXAudio2 *buffer, bool infiniteLoop)
{
	if (!_Buffer) nlerror("Only 1 ADPCM buffer can be submitted at a time!");

	++_InvalidCounter;
	bool _InfiniteLoop = infiniteLoop;
	_SourceSize = buffer->getSize();
	_SourceData = buffer->getData();
}

/// Reset the decoder, clear the queued buffer
void CAdpcmXAudio2::flushSourceBuffers()
{
	++_InvalidCounter;
	_SourceData = NULL;
	_SourceSize = 0;
	_State.PreviousSample = 0;
	_State.StepIndex = 0;
}

void CAdpcmXAudio2::OnVoiceProcessingPassStart(UINT32 BytesRequired)
{    
	if (BytesRequired > 0)
	{
		// nlwarning(NLSOUND_XAUDIO2_PREFIX "Bytes Required: %u", BytesRequired);
		uint invalid_counter = _InvalidCounter;
		uint8 *source_data = _SourceData;
		if (source_data)
		{		
			IBuffer::TADPCMState adpcm_state = _State;
			bool infinite_loop = _InfiniteLoop;
			uint32 source_size = _SourceSize;

			if (_InvalidCounter != invalid_counter) // buffer changed by main thread
				{ _State.PreviousSample = 0; _State.StepIndex = 0; return; } 
			
			uint32 minimum = BytesRequired * 2; // give some more than required
			if (minimum > sizeof(_Buffer) - _BufferPos) _BufferPos = 0;
			uint16 *buffer = &_Buffer[_BufferPos];

			uint32 length = 0; // -- ! decode here ! --

			_State = adpcm_state;
			
			if (_InvalidCounter != invalid_counter) // buffer changed by main thread
				{ _State.PreviousSample = 0; _State.StepIndex = 0; return; } 

			_BufferPos += length;

			if (length)
			{
				XAUDIO2_BUFFER xbuffer;
				xbuffer.AudioBytes = length;
				xbuffer.Flags = 0;
				xbuffer.LoopBegin = 0;
				xbuffer.LoopCount = 0;
				xbuffer.LoopLength = 0;
				xbuffer.pAudioData = (BYTE *)buffer;
				xbuffer.pContext = NULL; // nothing here for now
				xbuffer.PlayBegin = 0;
				xbuffer.PlayLength = 0;

				_SourceVoice->SubmitSourceBuffer(&xbuffer);
			}
			else
			{
				flushSourceBuffers();
			}
		}
	}
}

void CAdpcmXAudio2::OnVoiceProcessingPassEnd()
{ 
	
}

void CAdpcmXAudio2::OnStreamEnd()
{ 
	
}

void CAdpcmXAudio2::OnBufferStart(void *pBufferContext)
{    
	
}

void CAdpcmXAudio2::OnBufferEnd(void *pBufferContext)
{ 
	
}

void CAdpcmXAudio2::OnLoopEnd(void *pBufferContext)
{    
	
}

void CAdpcmXAudio2::OnVoiceError(void *pBufferContext, HRESULT Error)
{ 
	
}

} /* namespace NLSOUND */

/* end of file */