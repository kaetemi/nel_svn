/**
 * \file listener_xaudio2.h
 * \brief CListenerXAudio2
 * \date 2008-08-20 12:32GMT
 * \author Jan Boon (Kaetemi)
 * CListenerXAudio2
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

#ifndef NLSOUND_LISTENER_XAUDIO2_H
#define NLSOUND_LISTENER_XAUDIO2_H
#include "stdxaudio2.h"

// Project includes

// NeL includes
#include "../listener.h"
#include "../sound_driver.h"
#include <nel/misc/matrix.h>

// STL includes

namespace NLSOUND {

/**
 * \brief CListenerXAudio2
 * \date 2008-08-20 12:32GMT
 * \author Jan Boon (Kaetemi)
 * CListenerXAudio2
 */
class CListenerXAudio2 : public IListener, public NLMISC::CManualSingleton<CListenerXAudio2>
{
protected:
	// far pointers
	CSoundDriverXAudio2 *_SoundDriver;

	// pointers
	IXAudio2SubmixVoice *_SubmixVoice; //I
	
	// instances
	X3DAUDIO_LISTENER _Listener; //R
	NLMISC::CVector _Pos; //R
	bool _ListenerOk; //R
	/// Reference to the Submix Voice
	XAUDIO2_VOICE_SENDS _VoiceSends;

	// user vars
	/// Doppler scaler, set by user
	float _DopplerScaler;
	/// Distance/Roloff scaler
	float _DistanceScaler;
public:
	CListenerXAudio2(CSoundDriverXAudio2 *soundDriver);
	virtual ~CListenerXAudio2();
	void release();

	inline CSoundDriverXAudio2 *getSoundDriver() { return _SoundDriver; }
	inline X3DAUDIO_LISTENER *getListener() { return &_Listener; }
	inline IXAudio2SubmixVoice *getSubmixVoice() { return _SubmixVoice; }
	inline XAUDIO2_VOICE_SENDS *getVoiceSends() { return &_VoiceSends; }
	inline float getDopplerScaler() { return _DopplerScaler; }
	inline float getDistanceScaler() { return _DistanceScaler; }

	/// \name Listener properties
	//@{
	/// Set the position vector (default: (0,0,0)) (3D mode only)
	virtual void setPos(const NLMISC::CVector& pos);
	/** Get the position vector.
	 * See setPos() for details.
	 */
	virtual const NLMISC::CVector &getPos() const;
	/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
	virtual void setVelocity(const NLMISC::CVector& vel);
	/// Get the velocity vector
	virtual void getVelocity(NLMISC::CVector& vel) const;
	/// Set the orientation vectors (3D mode only, ignored in stereo mode) (default: (0,1,0), (0,0,-1))
	virtual void setOrientation(const NLMISC::CVector& front, const NLMISC::CVector& up);
	/// Get the orientation vectors
	virtual void getOrientation(NLMISC::CVector& front, NLMISC::CVector& up) const;
	/** Set the gain (volume value inside [0 , 1]). (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
	virtual void setGain(float gain);
	/// Get the gain
	virtual float getGain() const;
	//@}

	/// \name Global properties
	//@{
	/// Set the doppler factor (default: 1) to exaggerate or not the doppler effect
	virtual void setDopplerFactor(float f);
	/// Set the rolloff factor (default: 1) to scale the distance attenuation effect
	virtual void setRolloffFactor(float f);
	/// Set DSPROPERTY_EAXLISTENER_ENVIRONMENT and DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE if EAX available (see EAX listener properties)
	virtual void setEnvironment(uint env, float size=ENVFX_DEFAULT_SIZE);
	/// Set any EAX listener property if EAX available
	virtual void setEAXProperty(uint prop, void *value, uint valuesize);
	//@}
}; /* class CListenerXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_LISTENER_XAUDIO2_H */

/* end of file */
