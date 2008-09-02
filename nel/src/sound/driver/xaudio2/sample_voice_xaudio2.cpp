/**
 * \file sample_voice_xaudio2.cpp
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

/*
 * TODO:
 *  - ADPCM
 *    - ADPCMWAVEFORMAT
 */

#include "stdxaudio2.h"
#include "sample_voice_xaudio2.h"

// Project includes
#include "listener_xaudio2.h"

// NeL includes
// #include <nel/misc/debug.h>

// STL includes

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CSampleVoiceXAudio2::CSampleVoiceXAudio2(CSourceXAudio2 *owner, TSampleFormat format)
: _Owner(owner), _Format(format), _Pitch(1.f), _Buffer(NULL)
{
	nlwarning("Initializing CSampleVoiceXAudio2 format %u", (uint32)format);

	CSoundDriverXAudio2 *sound_driver = owner->getSoundDriver();
	nlassert(owner->getSoundDriver()->getListener());

	HRESULT hr;

	WAVEFORMATEX wfe; // todo: ADPCMWAVEFORMAT // wSamplesPerBlock // wNumCoef // aCoef
	wfe.cbSize = 0;

	nlassert(format == Mono16 || format == Mono16ADPCM || format == Mono16 || format == Stereo16 || format == Stereo8);

	wfe.wFormatTag = (format == Mono16ADPCM) 
		? WAVE_FORMAT_ADPCM
		: WAVE_FORMAT_PCM;
	wfe.nChannels = (format == Mono16 || format == Mono16ADPCM || format == Mono8)
		? 1
		: 2;
	wfe.wBitsPerSample = (format == Mono8 || format == Stereo8)
		? 8
		: 16;

	XAUDIO2_VOICE_DETAILS voice_details; // todo: get this at master voice creation to speed up
	owner->getSoundDriver()->getMasteringVoice()->GetVoiceDetails(&voice_details);
	wfe.nSamplesPerSec = voice_details.InputSampleRate; // todo: depend on submixer!!

	wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
	wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

	if (FAILED(hr = sound_driver->getXAudio2()->CreateSourceVoice(&_SourceVoice, &wfe, 0, XAUDIO2_DEFAULT_FREQ_RATIO, this, owner->getSoundDriver()->getListener()->getVoiceSends(), NULL)))
	{ if (_SourceVoice) _SourceVoice->DestroyVoice(); nlerror(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSourceVoice"); return; }
}

CSampleVoiceXAudio2::~CSampleVoiceXAudio2()
{
	nlwarning("Destroying CSampleVoiceXAudio2");

	if (_SourceVoice) _SourceVoice->DestroyVoice();
}

void CSampleVoiceXAudio2::updatePitch()
{
	if (_Buffer)
	{
		nlassert(_Owner); // todo: local copy of output rate here
		XAUDIO2_VOICE_DETAILS voice_details; // todo: get this at master voice creation to speed up
		_Owner->getSoundDriver()->getMasteringVoice()->GetVoiceDetails(&voice_details);
		_SourceVoice->SetFrequencyRatio(((float)_Buffer->getFreq() 
			/ (float)voice_details.InputSampleRate) * _Pitch);
	}
}

void CSampleVoiceXAudio2::OnVoiceProcessingPassStart(UINT32 BytesRequired)
{    
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbVoiceProcessingPassStart(BytesRequired);
}

void CSampleVoiceXAudio2::OnVoiceProcessingPassEnd()
{ 
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbVoiceProcessingPassEnd();
}

void CSampleVoiceXAudio2::OnStreamEnd()
{ 
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbStreamEnd();
}

void CSampleVoiceXAudio2::OnBufferStart(void *pBufferContext)
{    
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbBufferStart((CBufferXAudio2 *)pBufferContext);

	_Buffer = (CBufferXAudio2 *)pBufferContext;
	updatePitch();
	////// update buffer frequency :) todo: take into account other frequency modifiers!!
	////IBuffer *buffer = (IBuffer *)pBufferContext; // loool
	////_SourceVoice->SetFrequencyRatio((double)((CBufferXAudio2 *)buffer)->getFreq() 
	////	/ (double)NLSOUND_XAUDIO2_SOURCE_SAMPLES_PER_SEC);
	////// check how SetFrequencyRatio can be used to change the pitch vs changing bitrate/speed!!!!
	////// note: nel change pitch does change speed in other drivers too, so SetFreq is ok. :)
}

void CSampleVoiceXAudio2::OnBufferEnd(void *pBufferContext)
{ 
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbBufferEnd((CBufferXAudio2 *)pBufferContext);
}

void CSampleVoiceXAudio2::OnLoopEnd(void *pBufferContext)
{    
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbLoopEnd((CBufferXAudio2 *)pBufferContext);	
}

void CSampleVoiceXAudio2::OnVoiceError(void *pBufferContext, HRESULT Error)
{ 
	CSourceXAudio2 *owner = _Owner;
	if (owner) owner->cbVoiceError((CBufferXAudio2 *)pBufferContext, Error);	

	nlwarning(NLSOUND_XAUDIO2_PREFIX "CSourceXAudio2::OnVoiceError");
	nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	//release();
	//init();
	// todo: put everything back in as it should!
	// todo: static var in sound driver with last time of critical xa2 error
	//       only retry if previous problem more than 3 seconds ago to avoid hanging
}

} /* namespace NLSOUND */

/* end of file */
