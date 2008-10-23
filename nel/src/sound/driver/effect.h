/**
 * \file effect.h
 * \brief IEffect
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IEffect
 */

/* 
 * Copyright (C) 2008  by authors
 * 
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 * 
 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#ifndef NLSOUND_EFFECT_H
#define NLSOUND_EFFECT_H
#include <nel/misc/types_nl.h>

// STL includes
#include <math.h>

// NeL includes

// Project includes

namespace NLSOUND {

/**
 * \brief IEffect
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IEffect
 */
class IEffect
{
public:
	enum TEffectType
	{
		Reverb
	};

	IEffect();
	virtual ~IEffect();

	/// Get the type of effect (reverb, etc)
	virtual TEffectType getType() = 0;

	/// Set the volume of this effect
	virtual void setGain(float gain) = 0;
}; /* class IEffect */

////                                             in dB    ---
//#define NLSOUND_MATERIAL_PRESET_SINGLEWINDOW  -28.00f, 0.71f
//#define NLSOUND_MATERIAL_PRESET_DOUBLEWINDOW  -50.00f, 0.40f
//#define NLSOUND_MATERIAL_PRESET_THINDOOR      -18.00f, 0.66f
//#define NLSOUND_MATERIAL_PRESET_THICKDOOR     -44.00f, 0.64f
//#define NLSOUND_MATERIAL_PRESET_WOODWALL      -40.00f, 0.50f
//#define NLSOUND_MATERIAL_PRESET_BRICKWALL     -50.00f, 0.60f
//#define NLSOUND_MATERIAL_PRESET_STONEWALL     -60.00f, 0.68f
//#define NLSOUND_MATERIAL_PRESET_CURTAIN       -12.00f, 0.15f

inline float decibelsToAmplitudeRatio(float d)
{
	return powf(10.0f, d / 20.0f);
}

/**
 * \brief IReverbEffect
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IReverbEffect
 */
class IReverbEffect : public IEffect
{
public:
	/// Reverb environment
	struct CEnvironment
	{
		/// Constructor with all parameters, can be used with presets, roomsize.
		CEnvironment(float roomFilter, float roomFilterHF, 
			float decayTime, float decayHFRatio, float reflections, 
			float reflectionsDelay, float lateReverb, float lateReverbDelay, 
			float diffusion, float density) : 
			RoomFilter(roomFilter), RoomFilterHF(roomFilterHF), 
			DecayTime(decayTime), DecayHFRatio(decayHFRatio), Reflections(reflections), 
			ReflectionsDelay(reflectionsDelay), LateReverb(lateReverb), 
			LateReverbDelay(lateReverbDelay), Diffusion(diffusion), Density(density) { }
		/// Default constructor.
		CEnvironment() : RoomFilter(-100.00f), RoomFilterHF(0.00f), 
			DecayTime(1.0f), DecayHFRatio(0.5f), Reflections(-100.00f), 
			ReflectionsDelay(0.02f), LateReverb(-100.00f), LateReverbDelay(0.04f), 
			Diffusion(100.0f), Density(100.0f) { }
		/// Constructor to fade between two environments.
		CEnvironment(const CEnvironment &env0, const CEnvironment &env1, float balance) :
			RoomFilter((env0.RoomFilter * (1.0f - balance)) + (env1.RoomFilter * balance)), 
			RoomFilterHF((env0.RoomFilterHF * (1.0f - balance)) + (env1.RoomFilterHF * balance)), 
			DecayTime((env0.DecayTime * (1.0f - balance)) + (env1.DecayTime * balance)), 
			DecayHFRatio((env0.DecayHFRatio * (1.0f - balance)) + (env1.DecayHFRatio * balance)), 
			Reflections((env0.Reflections * (1.0f - balance)) + (env1.Reflections * balance)), 
			ReflectionsDelay((env0.ReflectionsDelay * (1.0f - balance)) + (env1.ReflectionsDelay * balance)), 
			LateReverb((env0.LateReverb * (1.0f - balance)) + (env1.LateReverb * balance)), 
			LateReverbDelay((env0.LateReverbDelay * (1.0f - balance)) + (env1.LateReverbDelay * balance)), 
			Diffusion((env0.Diffusion * (1.0f - balance)) + (env1.Diffusion * balance)), 
			Density((env0.Density * (1.0f - balance)) + (env1.Density * balance)) { }
		/// [-100.00, 0] in dB, default: -100.00 dB
		float RoomFilter;
		/// [-100.00, 0] in dB, default: 0 dB
		float RoomFilterHF;
		/// [0.1, 20.0] in seconds, default: 1.0 s
		float DecayTime;
		/// [0.1, 2.0], default: 0.5
		float DecayHFRatio;
		/// [-100.00, 10.00] in dB, default: -100.00 dB
		float Reflections;
		/// [0.0, 0.3] in seconds, default: 0.02 s
		float ReflectionsDelay;
		/// [-100.00, 20.00] in dB, default: -100.00 dB
		float LateReverb;
		/// [0.0, 0.1] in seconds, default: 0.04 s
		float LateReverbDelay;
		/// [0.0, 100.0] (percentage), default: 100.0 %
		float Diffusion;
		/// [0.0, 100.0] (percentage), default: 100.0 %
		float Density;
		/* This struct can *float* on water! */
	};

	IReverbEffect();
	virtual ~IReverbEffect();

	/// Set the environment (you have full control now, have fun); size: [1.0, 100.0], default: 100.0f; influences environment parameters, 100.0f no change
	virtual void setEnvironment(const CEnvironment &environment = CEnvironment(), float roomSize = 100.0f) = 0;
}; /* class IReverbEffect */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EFFECT_H */

/* end of file */
