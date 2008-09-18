/**
 * \file effect_xaudio2.h
 * \brief CReverbEffectXAudio2
 * \date 2008-09-17 17:27GMT
 * \author Jan Boon (Kaetemi)
 * CReverbEffectXAudio2
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

#ifndef NLSOUND_EFFECT_XAUDIO2_H
#define NLSOUND_EFFECT_XAUDIO2_H
#include <nel/misc/types_nl.h>

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {
	class CSoundDriverXAudio2;

/**
 * \brief CReverbEffectXAudio2
 * \date 2008-09-17 17:27GMT
 * \author Jan Boon (Kaetemi)
 * CReverbEffectXAudio2
 */
class CReverbEffectXAudio2 : public IReverbEffect
{
protected:
	// outside pointers
	CSoundDriverXAudio2 *_SoundDriver;

	// pointers
	IUnknown *_Effect;
public:
	CReverbEffectXAudio2(CSoundDriverXAudio2 *soundDriver);
	virtual ~CReverbEffectXAudio2();
	void release();

	inline IUnknown *getEffect() { return _Effect; }

	/// Get the type of effect (reverb, etc)
	virtual TEffectType getType();

	/// Set the environment (you have full control now, have fun)
	virtual void setEnvironment(const CEnvironment &environment);
}; /* class CReverbEffectXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EFFECT_XAUDIO2_H */

/* end of file */
