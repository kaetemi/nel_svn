/**
 * \file source_xaudio2.h
 * \brief CSourceXAudio2
 * \date 2008-08-20 15:53GMT
 * \author Jan Boon (Kaetemi)
 * CSourceXAudio2
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

#ifndef NLSOUND_SOURCE_XAUDIO2_H
#define NLSOUND_SOURCE_XAUDIO2_H
#include "stdxaudio2.h"

// Project includes
#include "sample_voice_xaudio2.h"

// NeL includes
#include "../source.h"
#include "../sound_driver.h"
#include "../buffer.h"

// STL includes

namespace NLSOUND {
	class CSoundDriverXAudio2;

/**
 * \brief CSourceXAudio2
 * \date 2008-08-20 15:53GMT
 * \author Jan Boon (Kaetemi)
 * CSourceXAudio2
 */
class CSourceXAudio2 : public ISource
{
protected:
	// far pointers
	CSoundDriverXAudio2 *_SoundDriver; // not changed at runtime
	CBufferXAudio2 *_NextBuffer; // MT
	CBufferXAudio2 *_HasBuffer; // MT

	// pointers
	CSampleVoiceXAudio2 *_SampleVoice; // MT, once set never becomes NULL until destruct of class
	
	// instances // dont need 3dchanged, remove
	/*bool _SourceOk; */ //bool _3DChanged;
	// bool _HasBuffer; // MT
	NLMISC::CMutex _Mutex;/*, _IsPaused*/;
	float _Doppler;
	X3DAUDIO_EMITTER _Emitter;
	X3DAUDIO_CONE _Cone;

	// user vars
	float _MinDistance;
	float _MaxDistance;
	float _Pitch;
	float _Gain;
	bool _IsPlaying;
	bool _IsLooping; // MT
	NLMISC::CVector _Pos; // getPos sucks
	bool _Relative; // sources relative to listener position (listener + source = actual source location)
private:
	// call only when entered mutex!
	void startNextBuffer(); // MT

public:
	CSourceXAudio2(CSoundDriverXAudio2 *soundDriver);
	//void init();
	virtual ~CSourceXAudio2();
	void release();

	void commit3DChanges();
	inline CSoundDriverXAudio2 *getSoundDriver() { return _SoundDriver; }

	// XAudio2 Callbacks
    // Called just before this voice's processing pass begins.
    void cbVoiceProcessingPassStart(uint32 BytesRequired);
    // Called just after this voice's processing pass ends.
    void cbVoiceProcessingPassEnd();
    // Called when this voice has just finished playing a buffer stream
    // (as marked with the XAUDIO2_END_OF_STREAM flag on the last buffer).
    void cbStreamEnd();
    // Called when this voice is about to start processing a new buffer.
    void cbBufferStart(CBufferXAudio2* pBufferContext);
    // Called when this voice has just finished processing a buffer.
    // The buffer can now be reused or destroyed.
    void cbBufferEnd(CBufferXAudio2* pBufferContext);
    // Called when this voice has just reached the end position of a loop.
    void cbLoopEnd(CBufferXAudio2* pBufferContext);
    // Called in the event of a critical error during voice processing,
    // such as a failing XAPO or an error from the hardware XMA decoder.
    // The voice may have to be destroyed and re-created to recover from
    // the error.  The callback arguments report which buffer was being
    // processed when the error occurred, and its HRESULT code.
    void cbVoiceError(CBufferXAudio2* pBufferContext, HRESULT Error);

	/// \name Initialization
	//@{
	/** Set the buffer that will be played (no streaming)
	 * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
	 * otherwise the source is considered as a 3D source.
	 */
	virtual void setStaticBuffer(IBuffer *buffer); //{ _Buffer = buffer; }
	/// Return the buffer, or NULL if streaming is used.
	virtual IBuffer *getStaticBuffer(); //					{ return _Buffer; }
	///** Set the sound loader that will be used to stream in the data to play
	// * If the buffer is stereo, the source mode becomes stereo and the source relative mode is on,
	// * otherwise the source is considered as a 3D source.
	// */
	//virtual void setStreamLoader(ILoader *loader) { _Loader = loader; }
	//@}
	
	/// \name Playback control
	//@{
	/// Set looping on/off for future playbacks (default: off)
	virtual void setLooping(bool l);
	/// Return the looping state
	virtual bool getLooping() const;
	/** Play the static buffer (or stream in and play).
	 *	This method can return false if the sample for this sound is unloaded.
	 */
	virtual bool play();
	/// Stop playing
	virtual void stop();
	/// Pause. Call play() to resume.
	virtual void pause();
	/// Return the playing state
	virtual bool isPlaying() const;
	/// Return true if playing is finished or stop() has been called.
	virtual bool isStopped() const;
	/// Update the source (e.g. continue to stream the data in)
	virtual bool update();
	/// Returns the number of milliseconds the source has been playing
	virtual uint32 getTime();
	//@}

	/// \name Source properties
	//@{
	/** Set the position vector (default: (0,0,0)).
	 * 3D mode -> 3D position
	 * st mode -> x is the pan value (from left (-1) to right (1)), set y and z to 0
	 */
	virtual void setPos(const NLMISC::CVector& pos, bool deffered = true);
	/** Get the position vector.
	 * See setPos() for details.
	 */
	virtual const NLMISC::CVector &getPos() const;
	/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
	virtual void setVelocity(const NLMISC::CVector& vel, bool deferred = true);
	/// Get the velocity vector
	virtual void getVelocity(NLMISC::CVector& vel) const;
	/// Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
	virtual void setDirection(const NLMISC::CVector& dir);
	/// Get the direction vector
	virtual void getDirection(NLMISC::CVector& dir) const;
	/** Set the gain (volume value inside [0 , 1]). (default: 1)
	 * 0.0 -> silence
	 * 0.5 -> -6dB
	 * 1.0 -> no attenuation
	 * values > 1 (amplification) not supported by most drivers
	 */
	virtual void setGain(float gain);
	/// Get the gain
	virtual float getGain() const;
	/** Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
	 * of one octave. 0 is not a legal value.
	 */
	virtual void setPitch(float pitch);
	/// Get the pitch
	virtual float getPitch() const;
	/// Set the source relative mode. If true, positions are interpreted relative to the listener position
	virtual void setSourceRelativeMode(bool mode);
	/// Get the source relative mode
	virtual bool getSourceRelativeMode() const;
	/// Set the min and max distances (default: 1, MAX_FLOAT) (3D mode only)
	virtual void setMinMaxDistances(float mindist, float maxdist, bool deferred = true);
	/// Get the min and max distances
	virtual void getMinMaxDistances(float& mindist, float& maxdist) const;
	/// Set the cone angles (in radian) and gain (in [0 , 1]) (default: 2PI, 2PI, 0)
	virtual void setCone(float innerAngle, float outerAngle, float outerGain);
	/// Get the cone angles (in radian)
	virtual void getCone(float& innerAngle, float& outerAngle, float& outerGain) const;
	/// Set any EAX source property if EAX available
	virtual void setEAXProperty(uint prop, void *value, uint valuesize);
	///** Set the alpha value for the volume-distance curve
	// *
	// *	Usefull only if MANUAL_ROLLOFF==1. value from -1 to 1 (default 0)
	// * 
	// *  alpha.0: the volume will decrease linearly between 0dB and -100 dB
	// *  alpha = 1.0: the volume will decrease linearly between 1.0 and 0.0 (linear scale)
	// *  alpha = -1.0: the volume will decrease inversely with the distance (1/dist). This
	// *                is the default used by DirectSound/OpenAL
	// * 
	// *  For any other value of alpha, an interpolation is be done between the two
	// *  adjacent curves. For example, if alpha equals 0.5, the volume will be halfway between
	// *  the linear dB curve and the linear amplitude curve.
	// */
	///// 
	//virtual void setAlpha(double a) {  }
	//@}
}; /* class CSourceXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SOURCE_XAUDIO2_H */

/* end of file */
