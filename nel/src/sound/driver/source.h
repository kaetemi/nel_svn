/**
 * Contains the ISource interface, as well as several '#define's that
 * specify the limits of parameters that can be passed to the source.
 * \file source.h
 * \brief Interface for physical sound sources
 * \author Olivier Cado
 * \author Nevrax France
 * \author Jan Boon (Kaetemi)
 * \date 2001-2009
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_SOURCE_H
#define NL_SOURCE_H
#include <nel/misc/types_nl.h>

#include <nel/misc/vector.h>
#include "sound_driver.h"

/** 
 * The minimum allowed gain is specified as 0.0f.
 * Inverting the wave by specifying a negative gain is not allowed.
 * \brief Minimum allowed gain (volume).
 */
#define NLSOUND_MIN_GAIN 0.0f
/**
 * The maximum allowed gain is specified as 1.0f.
 * OpenAL implementations may or may not clamp the gain to a maximum 
 * of 1.0f, so this maximum is forced on all implementations.
 * If you pass a value outside the minimum and maximum bounds,
 * it will automatically be clamped between them.
 * \brief Maximum allowed gain (volume).
 */
#define NLSOUND_MAX_GAIN 1.0f

/**
 * The minimum allowed pitch is specified as 0.0f.
 * Going backwards in time by specifying a negative pitch is illegal.
 * Setting the pitch to 0.0f is the same as pausing the source.
 * \brief Minimum allowed pitch.
 */
#define NLSOUND_MIN_PITCH 0.0f
/**
 * The maximum allowed pitch is specified as 8.0f.
 * Tests indicate that with OpenAL the pitch can be set to 8.0f, 
 * and with FMod to somewhere around 9.0f. The XAudio2 implementation
 * uses this value directly to configure the maximum pitch, which can
 * technically be as high as XAUDIO2_MAX_FREQ_RATIO which is 1024.0f.
 * If you pass a value outside the minimum and maximum bounds,
 * it will automatically be clamped between them.
 * \brief Maximum allowed pitch.
 */
#define NLSOUND_MAX_PITCH 8.0f

/**
 * The default gain is specified as 1.0f, which is the full volume.
 * Using this value, the output volume is the same as the original
 * input volume of the sample buffer.
 * \brief Default gain (volume).
 */
#define NLSOUND_DEFAULT_GAIN 1.0f
/**
 * The default pitch is specified as 1.0.
 * Using this value, the sample will be played at it's original rate.
 * \brief Default pitch.
 */
#define NLSOUND_DEFAULT_PITCH 1.0f

/**
 * The default direct gain is specified as 1.0f.
 * This is the default volume for the direct dry output channel.
 * \brief Default direct gain.
 */
#define NLSOUND_DEFAULT_DIRECT_GAIN 1.0f
/**
 * The default effect gain is specified as 1.0f.
 * This is the default volume for the effect output channel.
 * \brief Default effect gain.
 */
#define NLSOUND_DEFAULT_EFFECT_GAIN 1.0f

/**
 * The default filter cutoff high frequency is specified as 5000.0f.
 * Under OpenAL EFX this is always the reference high frequency.
 * \brief Default filter cutoff high frequency.
 */
#define NLSOUND_DEFAULT_FILTER_PASS_HF 5000.0f
/**
 * The default filter cutoff low frequency is specified as 250.0f.
 * Under OpenAL EFX this is always the reference low frequency.
 * \brief Default filter cutoff low frequency.
 */
#define NLSOUND_DEFAULT_FILTER_PASS_LF 250.0f
/**
 * The default filter pass gain is specified as 1.0f.
 * Using this value, the sound that is outside the cutoff frequencies
 * passes without attenuation, so that essentially the resulting
 * output is not filtered at all.
 * \brief Default filter pass gain.
 */
#define NLSOUND_DEFAULT_FILTER_PASS_GAIN 1.0f

namespace NLSOUND {
	class IBuffer;
	class ILoader;
	class IEffect;

/**
 * Sound source interface (implemented in sound driver dynamic library)
 * 
 * - If the buffer is mono, the source is played in 3D mode. For 
 * arguments as 3D vectors, use the NeL vector coordinate system:
\verbatim
   (top)
    z
    |  y (front)
    | /
    -----x (right)
\endverbatim
 *
 * - If the buffer is multi-channel, only distance rolloff is applied.
 * - All streaming related functionalities are thread-safe.
 * 
 * \author Olivier Cado
 * \author Nevrax France
 * \author Jan Boon (Kaetemi)
 * \date 2001-2009
 * \brief Interface for physical sound sources.
 */
class ISource
{
public:
	enum TFilter
	{
		FilterLowPass, 
		FilterBandPass, 
		FilterHighPass, 
	};
	
	/// Constructor
	ISource() { }
	/// Destructor
	virtual ~ISource() { }
	
	/// \name Initialization
	//@{
	/**
	 * This function is used to switch between streaming and static 
	 * buffer modes. By default, streaming mode is off.
	 * Streaming mode must be enabled before calling functions 
	 * related to buffer streaming, such as  'submitStreamingBuffer' 
	 * and 'countStreamingBuffers'.
	 * In the default static buffer mode, only one buffer is set 
	 * active on this source, and can be replayed or looped as many 
	 * times as needed.
	 * When in streaming mode, multiple buffers are chained after each
	 * other, and you must make sure that the source does not run out 
	 * of data, to avoid sound stopping glitches.
	 * The source must be stopped before trying to change the mode, 
	 * if a static buffer was set it must be detached as well.
	 * \brief Switch between streaming and static buffer modes.
	 * \param streaming Set to true to enable streaming mode, or 
	 * false to use static buffers. If you omit this parameter, it
	 * will be set as true, and streaming will be enabled.
	 */
	virtual void setStreaming(bool streaming = true) = 0;
	/**
	 * Sets the buffer that is used for playback by this source.
	 * The static buffer will remain active on the source until 
	 * this function is called with a NULL parameter, or until the 
	 * mode is changed to streaming. It is possible to play or loop 
	 * this buffer as often as needed,  as long as it is attached 
	 * to this source.
	 * If you attach a multichannel (stereo) buffer, the source will 
	 * automatically be set to relative mode. Setting a mono channel 
	 * buffer will automatically set the relative mode back to it's
	 * original setting. It is not possible to enable relative mode 
	 * with a multichannel buffer, instead you must manually split 
	 * the sound data into multiple channels and use multiple sources.
	 * You cannot use this function in streaming mode, where you must 
	 * use 'submitStreamingBuffer' instead.
	 * A buffer can be attached to more than once source.
	 * Before destroying a buffer, it must be detached from all 
	 * sources it's attached to, which can be done by calling this 
	 * function with a NULL parameter as buffer on all relevant sources.
	 * \brief Attach a buffer to this source.
	 * \param buffer The buffer to be attached on this source. It must 
	 * be created on the same sound driver instance as this source. Set 
	 * this parameter to NULL to detach a previously set buffer.
	 */
	virtual void setStaticBuffer(IBuffer *buffer) = 0;
	/**
	 * Returns the buffer that was attached to this source. A buffer 
	 * can by attached to this source by calling 'setStaticBuffer'.
	 * If no static buffer is set, or if the source is in streaming 
	 * mode, this function will return NULL.
	 * \brief Get the buffer that is attached to this source.
	 * \return A pointer to the attached IBuffer, or NULL if none.
	 */
	virtual IBuffer *getStaticBuffer() = 0;
	///// Add a buffer to the streaming queue.  A buffer of 100ms length is optimal for streaming. Buffers between 50ms and 100ms are optimal for streaming.
	///// Should be called by a thread which checks countStreamingBuffers every 50ms.Queue cleared on stop.
	virtual void submitStreamingBuffer(IBuffer *buffer) = 0;
	/**
	 * Returns the amount of buffers that are currently in the queue.
	 * This includes buffers that are waiting to be played, as well as 
	 * the buffer that is currently playing. Buffers that have finished 
	 * playing are removed from the queue, and do not count towards the 
	 * result of this function.
	 * It is recommended to have at least 2 or 3 buffers queued up when 
	 * streaming, to avoid sound stopping glitches.
	 * If you need to know the total amount of buffers that were added 
	 * into the queue, you should count them manually by increasing a 
	 * value each time 'submitStreamingBuffer' is called.
	 * This function always returns 0 when the source is in static 
	 * mode, when the source is stopped, or when no buffers have been
	 * added yet into the queue.
	 * \brief Get the number of buffers in the streaming queue.
	 * \return The number of buffers in the queue.
	 */
	virtual uint countStreamingBuffers() const = 0;
	//@}
	
	/// \name Playback control
	//@{
	/// Set looping on/off for future playbacks (default: off), not available for streaming
	virtual void setLooping(bool l) = 0;
	/// Return the looping state
	virtual bool getLooping() const = 0;
	
	/// Play the static buffer (or stream in and play). This method can return false if the sample for this sound is unloaded.
	virtual bool play() = 0;
	/// Stop playing
	virtual void stop() = 0;
	/// Pause. Call play() to resume.
	virtual void pause() = 0;
	/// Return true if play() or pause(), false if stop().
	virtual bool isPlaying() const = 0;
	/// Return true if playing is finished or stop() has been called.
	virtual bool isStopped() const = 0;
	/// Return true if the playing source is paused
	virtual bool isPaused() const = 0;
	/// Returns the number of milliseconds the source has been playing
	virtual uint32 getTime() = 0;
	//@}
	
	/// \name Source properties
	//@{
	/// Set the position vector (default: (0,0,0)).
	virtual void setPos(const NLMISC::CVector& pos, bool deffered = true) = 0;
	/// Get the position vector.
	virtual const NLMISC::CVector &getPos() const = 0;
	/// Set the velocity vector (3D mode only, ignored in stereo mode) (default: (0,0,0))
	virtual void setVelocity(const NLMISC::CVector& vel, bool deferred = true) = 0;
	/// Get the velocity vector
	virtual void getVelocity(NLMISC::CVector& vel) const = 0;
	/// Set the direction vector (3D mode only, ignored in stereo mode) (default: (0,0,0) as non-directional)
	virtual void setDirection(const NLMISC::CVector& dir) = 0;
	/// Get the direction vector
	virtual void getDirection(NLMISC::CVector& dir) const = 0;
	/// Set the gain (volume value inside [0 , 1]). (default: 1)
	virtual void setGain(float gain) = 0;
	/// Get the gain
	virtual float getGain() const = 0;
	/// Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift of one octave.
	virtual void setPitch(float pitch) = 0;
	/// Get the pitch
	virtual float getPitch() const = 0;
	/// Set the source relative mode. If true, positions are interpreted relative to the listener position
	virtual void setSourceRelativeMode(bool mode) = 0;
	/// Get the source relative mode
	virtual bool getSourceRelativeMode() const = 0;
	/// Set the min and max distances (default: 1, MAX_FLOAT) (3D mode only)
	virtual void setMinMaxDistances(float mindist, float maxdist, bool deferred = true) = 0;
	/// Get the min and max distances
	virtual void getMinMaxDistances(float& mindist, float& maxdist) const = 0;
	/// Set the cone angles (in radian) and gain (in [0 , 1]) (default: 2PI, 2PI, 0)
	virtual void setCone(float innerAngle, float outerAngle, float outerGain) = 0;
	/// Get the cone angles (in radian)
	virtual void getCone(float& innerAngle, float& outerAngle, float& outerGain) const = 0;
	/** 
	 * Set the alpha value for the volume-distance curve.
	 * 
	 * Used only with OptionManualRolloff.
	 * Value ranges from -1.0 to 1.0, the default is 0.0.
	 * 
	 * - alpha = 0.0: The volume will decrease linearly between 0dB 
	 *   and -100 dB.
	 * - alpha = 1.0: The volume will decrease linearly between 1.0f 
	 *   and 0.0f (linear scale).
	 * - alpha = -1.0: The volume will decrease inversely with the 
	 *   distance (1/dist). This is the default distance attenuation 
	 *   used without OptionManualRolloff.
	 * 
	 * For any other value of alpha, an interpolation is be done 
	 * between the two adjacent curves. For example, if alpha equals 
	 * 0.5, the volume will be halfway between the linear dB curve and 
	 * the linear amplitude curve.
	 * \brief Set the alpha value for the volume-distance curve
	 */
	virtual void setAlpha(double a) = 0;
	//@}
	
	/// \name Direct output
	//@{
	/// Enable or disable direct output [true/false], default: true
	virtual void setDirect(bool enable = true) = 0;
	/// Return if the direct output is enabled
	virtual bool getDirect() const = 0;
	/// Set the gain for the direct path
	virtual void setDirectGain(float gain = NLSOUND_DEFAULT_DIRECT_GAIN) = 0;
	/// Get the gain for the direct path
	virtual float getDirectGain() const = 0;
	
	/// Enable or disable the filter for the direct channel
	virtual void enableDirectFilter(bool enable = true) = 0;
	/// Check if the filter on the direct channel is enabled
	virtual bool isDirectFilterEnabled() const = 0;
	/// Set the filter parameters for the direct channel
	virtual void setDirectFilter(TFilter filter, float lowFrequency = NLSOUND_DEFAULT_FILTER_PASS_LF, float highFrequency = NLSOUND_DEFAULT_FILTER_PASS_HF, float passGain = NLSOUND_DEFAULT_FILTER_PASS_GAIN) = 0;
	/// Get the filter parameters for the direct channel
	virtual void getDirectFilter(TFilter &filterType, float &lowFrequency, float &highFrequency, float &passGain) const = 0;
	/// Set the direct filter gain
	virtual void setDirectFilterPassGain(float passGain = NLSOUND_DEFAULT_FILTER_PASS_GAIN) = 0;
	/// Get the direct filter gain
	virtual float getDirectFilterPassGain() const = 0;
	//@}
	
	/// \name Effect output
	//@{
	/// Set the effect send for this source, NULL to disable. [IEffect], default: NULL
	virtual void setEffect(IReverbEffect *reverbEffect) = 0;
	/// Get the effect send for this source
	virtual IEffect *getEffect() const = 0;
	/// Set the gain for the effect path
	virtual void setEffectGain(float gain = NLSOUND_DEFAULT_EFFECT_GAIN) = 0;
	/// Get the gain for the effect path
	virtual float getEffectGain() const = 0;
	
	/// Enable or disable the filter for the effect channel
	virtual void enableEffectFilter(bool enable = true) = 0;
	/// Check if the filter on the effect channel is enabled
	virtual bool isEffectFilterEnabled() const = 0;
	/// Set the filter parameters for the effect channel
	virtual void setEffectFilter(TFilter filter, float lowFrequency = NLSOUND_DEFAULT_FILTER_PASS_LF, float highFrequency = NLSOUND_DEFAULT_FILTER_PASS_HF, float passGain = NLSOUND_DEFAULT_FILTER_PASS_GAIN) = 0;
	/// Get the filter parameters for the effect channel
	virtual void getEffectFilter(TFilter &filterType, float &lowFrequency, float &highFrequency, float &passGain) const = 0;
	/// Set the effect filter gain
	virtual void setEffectFilterPassGain(float passGain = NLSOUND_DEFAULT_FILTER_PASS_GAIN) = 0;
	/// Get the effect filter gain
	virtual float getEffectFilterPassGain() const = 0;
	//@}
	
protected:
	
	// common method used only with OptionManualRolloff. return the volume in 1/100th DB  ( = mB)modified
	static sint32 computeManualRollOff(sint32 volumeMB, sint32 mbMin, sint32 mbMax, double alpha, float sqrdist, float distMin, float distMax);
	// common method used only with OptionManualRolloff. return the rolloff in amplitude ratio (gain)
	static float computeManualRolloff(double alpha, float sqrdist, float distMin, float distMax);
};


} // NLSOUND


#endif // NL_SOURCE_H

/* End of source.h */
