/**
 * \file music_voice_xaudio2.cpp
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

#include "stdxaudio2.h"
#include "music_voice_xaudio2.h"

// STL includes

// NeL includes
#include <nel/misc/file.h>

// Project includes

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CMusicVoiceXAudio2::CMusicVoiceXAudio2() 
: _MusicBuffer(NULL), _SourceVoice(NULL), _BufferPos(0), _SoundDriver(NULL), _Gain(1.0)
{
	// call init before using :)
}

CMusicVoiceXAudio2::~CMusicVoiceXAudio2()
{
	reset();
}

void CMusicVoiceXAudio2::init(CSoundDriverXAudio2 *soundDriver)
{
	_SoundDriver = soundDriver;
	reset();
}

void CMusicVoiceXAudio2::reset()
{
	if (_SourceVoice) { _SourceVoice->DestroyVoice(); _SourceVoice = NULL; }
	if (_MusicBuffer) { IMusicBuffer::destroyMusicBuffer(_MusicBuffer); _MusicBuffer = NULL; }
	// memset(_Buffer, 0, sizeof(_Buffer));
	_BufferPos = 0;
}

void CMusicVoiceXAudio2::play(const std::string &streamName, NLMISC::IStream *stream, bool loop)
{
	nlinfo(NLSOUND_XAUDIO2_PREFIX "play %s %u", streamName.c_str(), (uint32)loop);

	HRESULT hr;

	reset();

	_MusicBuffer = IMusicBuffer::createMusicBuffer(streamName, stream, loop);
	
	if (_MusicBuffer)
	{
		WAVEFORMATEX wfe;
		wfe.cbSize = 0;
		wfe.wFormatTag = WAVE_FORMAT_PCM; // todo: getFormat();
		wfe.nChannels = _MusicBuffer->getChannels();
		wfe.wBitsPerSample = _MusicBuffer->getBitsPerSample();
		wfe.nSamplesPerSec = _MusicBuffer->getSamplesPerSec();
		wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
		wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

		XAUDIO2_VOICE_DETAILS voice_details;
		_SoundDriver->getMasteringVoice()->GetVoiceDetails(&voice_details);

		nlinfo(NLSOUND_XAUDIO2_PREFIX "Creating music voice with %u channels, %u bits per sample, %u samples per sec, "
			"on mastering voice with %u channels, %u samples per sec", 
			(uint32)wfe.nChannels, (uint32)wfe.wBitsPerSample, (uint32)wfe.nSamplesPerSec, 
			(uint32)voice_details.InputChannels, (uint32)voice_details.InputSampleRate);

		if (FAILED(hr = _SoundDriver->getXAudio2()->CreateSourceVoice(&_SourceVoice, &wfe, XAUDIO2_VOICE_NOPITCH, 1.0f, this, NULL, NULL)))
		{ nlerror(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSourceVoice"); return; }
		_SourceVoice->SetVolume(_Gain);

		_SourceVoice->Start(0);
	}
	else
	{
		nlwarning(NLSOUND_XAUDIO2_PREFIX "no _MusicBuffer");
	}
}

void CMusicVoiceXAudio2::pause()
{
	if (_SourceVoice) _SourceVoice->Stop(0);
}

void CMusicVoiceXAudio2::resume()
{
	if (_SourceVoice) _SourceVoice->Start(0);
}

void CMusicVoiceXAudio2::stop()
{
	reset();
}

void CMusicVoiceXAudio2::OnVoiceProcessingPassStart(UINT32 BytesRequired)
{    
	if (BytesRequired > 0)
	{
		//nlwarning(NLSOUND_XAUDIO2_PREFIX "Bytes Required: %u", BytesRequired); // byte req to not have disruption
		
		if (_MusicBuffer)
		{
			uint32 minimum = BytesRequired;
			if (_MusicBuffer->getRequiredBytes() > minimum) minimum = _MusicBuffer->getRequiredBytes();
			if (minimum > sizeof(_Buffer) - _BufferPos) _BufferPos = 0;
			uint32 maximum = sizeof(_Buffer) - _BufferPos;
			uint8 *buffer = &_Buffer[_BufferPos];
			uint32 length = _MusicBuffer->getNextBytes(buffer, minimum, maximum);
			_BufferPos += length;

			if (length)
			{
				XAUDIO2_BUFFER xbuffer;
				xbuffer.AudioBytes = length;
				xbuffer.Flags = 0;
				xbuffer.LoopBegin = 0;
				xbuffer.LoopCount = 0;
				xbuffer.LoopLength = 0;
				xbuffer.pAudioData = buffer;
				xbuffer.pContext = NULL; // nothing here for now
				xbuffer.PlayBegin = 0;
				xbuffer.PlayLength = 0;

				_SourceVoice->SubmitSourceBuffer(&xbuffer);
			}
			else
			{
				IMusicBuffer::destroyMusicBuffer(_MusicBuffer); _MusicBuffer = NULL;
				_SourceVoice->Discontinuity();
			}
		}
	}
}

void CMusicVoiceXAudio2::OnVoiceProcessingPassEnd()
{ 
	
}

void CMusicVoiceXAudio2::OnStreamEnd()
{ 
	
}

void CMusicVoiceXAudio2::OnBufferStart(void *pBufferContext)
{    
	
}

void CMusicVoiceXAudio2::OnBufferEnd(void *pBufferContext)
{ 
	
}

void CMusicVoiceXAudio2::OnLoopEnd(void *pBufferContext)
{    
	
}

void CMusicVoiceXAudio2::OnVoiceError(void *pBufferContext, HRESULT Error)
{ 
	
}

} /* namespace NLSOUND */

/* end of file */
