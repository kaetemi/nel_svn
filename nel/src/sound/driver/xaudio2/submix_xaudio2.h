/**
 * \file submix_xaudio2.h
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

#ifndef NLSOUND_SUBMIX_XAUDIO2_H
#define NLSOUND_SUBMIX_XAUDIO2_H
#include <nel/misc/types_nl.h>

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {
	class CSoundDriverXAudio2;

/**
 * \brief CSubmixXAudio2
 * \date 2008-09-17 17:26GMT
 * \author Jan Boon (Kaetemi)
 * CSubmixXAudio2
 */
class CSubmixXAudio2 : public ISubmix
{
protected:
	// outside pointers
	CSoundDriverXAudio2 *_SoundDriver;
	IEffect *_Effect;
	
	// pointers
	IXAudio2SubmixVoice *_SubmixVoice;
public:
	CSubmixXAudio2(CSoundDriverXAudio2 *soundDriver);
	virtual ~CSubmixXAudio2();
	void release();

	inline IXAudio2SubmixVoice *getSubmixVoice() { return _SubmixVoice; }

	/// Attach an effect to this submixer, set NULL to remove the effect
	virtual void setEffect(IEffect *effect);

	/// Set the volume of this submixer
	virtual void setGain(float gain);
}; /* class CSubmixXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SUBMIX_XAUDIO2_H */

/* end of file */
