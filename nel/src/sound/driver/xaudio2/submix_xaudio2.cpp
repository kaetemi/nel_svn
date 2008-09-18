/**
 * \file submix_xaudio2.cpp
 * \brief CSubmixXAudio2
 * \date 2008-09-17 17:26GMT
 * \author Jan Boon (Kaetemi)
 * CSubmixXAudio2
 */

/* 
 * Copyright (C) 2008  by authors
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
#include "submix_xaudio2.h"

// STL includes

// NeL includes
// #include <nel/misc/debug.h>

// Project includes
#include "sound_driver_xaudio2.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

CSubmixXAudio2::CSubmixXAudio2(CSoundDriverXAudio2 *soundDriver) : _SoundDriver(soundDriver), _SubmixVoice(NULL)
{
	HRESULT hr;

	XAUDIO2_VOICE_DETAILS voice_details;
	soundDriver->getMasteringVoice()->GetVoiceDetails(&voice_details);

	if (FAILED(hr = soundDriver->getXAudio2()->CreateSubmixVoice(&_SubmixVoice, voice_details.InputChannels, voice_details.InputSampleRate, 0, 9000, NULL, NULL)))
		{ release(); nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSubmixVoice _SubmixVoice!"); return; }
}

CSubmixXAudio2::~CSubmixXAudio2()
{
	release();
}

void CSubmixXAudio2::release()
{
	if (_SoundDriver) { _SoundDriver->removeSubmix(this); _SoundDriver = NULL; }
	if (_SubmixVoice) { _SubmixVoice->DestroyVoice(); _SubmixVoice = NULL; }
}

/// Attach an effect to this submixer, set NULL to remove the effect
void CSubmixXAudio2::setEffect(IEffect *effect)
{
	XAUDIO2_VOICE_DETAILS voice_details;
	_SubmixVoice->GetVoiceDetails(&voice_details);
	XAUDIO2_EFFECT_DESCRIPTOR effect_descriptor;
	effect_descriptor.InitialState = TRUE;
	effect_descriptor.OutputChannels = voice_details.InputChannels;
	effect_descriptor.pEffect = CSoundDriverXAudio2::getEffectInternal(effect);
	if (!effect_descriptor.pEffect) { nlwarning(NLSOUND_XAUDIO2_PREFIX "pEffect NULL"); return; }
	XAUDIO2_EFFECT_CHAIN effect_chain;
	effect_chain.EffectCount = 1;
	effect_chain.pEffectDescriptors = &effect_descriptor;
	_SubmixVoice->SetEffectChain(&effect_chain);
}

/// Set the volume of this submixer
void CSubmixXAudio2::setGain(float gain)
{
	_SubmixVoice->SetVolume(gain);
}

} /* namespace NLSOUND */

/* end of file */
