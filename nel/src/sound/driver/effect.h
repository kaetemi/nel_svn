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
}; /* class IEffect */

// effect presets (based on I3DL2 specification, see 3dl2help.h)
// note: room size not included!
#define NLSOUND_ENVIRONMENT_PRESET_DEFAULT \
-100.00f,  0.00f, 1.00f,0.50f,-100.00f,0.020f,-100.00f,0.040f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_GENERIC \
 -10.00f, -1.00f, 1.49f,0.83f, -26.02f,0.007f,   2.00f,0.011f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_PADDEDCELL \
 -10.00f,-60.00f, 0.17f,0.10f, -12.04f,0.001f,   2.07f,0.002f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_ROOM \
 -10.00f, -4.54f, 0.40f,0.83f, -16.46f,0.002f,   0.53f,0.003f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_BATHROOM \
 -10.00f,-12.00f, 1.49f,0.54f,  -3.70f,0.007f,  10.30f,0.011f,100.0f, 60.0f
#define NLSOUND_ENVIRONMENT_PRESET_LIVINGROOM \
 -10.00f,-60.00f, 0.50f,0.10f, -13.76f,0.003f, -11.04f,0.004f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_STONEROOM \
 -10.00f, -3.00f, 2.31f,0.64f,  -7.11f,0.012f,   0.83f,0.017f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_AUDITORIUM \
 -10.00f, -4.76f, 4.32f,0.59f,  -7.89f,0.020f,  -2.89f,0.030f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_CONCERTHALL \
 -10.00f, -5.00f, 3.92f,0.70f, -12.30f,0.020f,  -0.02f,0.029f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_CAVE \
 -10.00f,  0.00f, 2.91f,1.30f,  -6.02f,0.015f,  -3.02f,0.022f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_ARENA \
 -10.00f, -6.98f, 7.24f,0.33f, -11.66f,0.020f,   0.16f,0.030f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_HANGAR \
 -10.00f,-10.00f,10.05f,0.23f,  -6.02f,0.020f,   1.98f,0.030f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_CARPETEDHALLWAY \
 -10.00f,-40.00f, 0.30f,0.10f, -18.31f,0.002f, -16.30f,0.030f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_HALLWAY \
 -10.00f, -3.00f, 1.49f,0.59f, -12.19f,0.007f,   4.41f,0.011f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_STONECORRIDOR \
 -10.00f, -2.37f, 2.70f,0.79f, -12.14f,0.013f,   3.95f,0.020f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_ALLEY \
 -10.00f, -2.70f, 1.49f,0.86f, -12.04f,0.007f,  -0.04f,0.011f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_FOREST \
 -10.00f,-33.00f, 1.49f,0.54f, -25.60f,0.162f,  -6.13f,0.088f, 79.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_CITY \
 -10.00f, -8.00f, 1.49f,0.67f, -22.73f,0.007f, -22.17f,0.011f, 50.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_MOUNTAINS \
 -10.00f,-25.00f, 1.49f,0.21f, -27.80f,0.300f, -20.14f,0.100f, 27.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_QUARRY \
 -10.00f,-10.00f, 1.49f,0.83f,-100.00f,0.061f,   5.00f,0.025f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_PLAIN \
 -10.00f,-20.00f, 1.49f,0.50f, -24.66f,0.179f, -25.14f,0.100f, 21.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_PARKINGLOT \
 -10.00f,  0.00f, 1.65f,1.50f, -13.63f,0.008f, -11.53f,0.012f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_SEWERPIPE \
 -10.00f,-10.00f, 2.81f,0.14f,   4.29f,0.014f,   6.48f,0.021f, 80.0f, 60.0f
#define NLSOUND_ENVIRONMENT_PRESET_UNDERWATER \
 -10.00f,-40.00f, 1.49f,0.10f,  -4.49f,0.007f,  17.00f,0.011f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_SMALLROOM \
 -10.00f, -6.00f, 1.10f,0.83f,  -4.00f,0.005f,   5.00f,0.010f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_MEDIUMROOM \
 -10.00f, -6.00f, 1.30f,0.83f, -10.00f,0.010f,  -2.00f,0.020f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_LARGEROOM \
 -10.00f, -6.00f, 1.50f,0.83f, -16.00f,0.020f, -10.00f,0.040f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_MEDIUMHALL \
 -10.00f, -6.00f, 1.80f,0.70f, -13.00f,0.015f,  -8.00f,0.030f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_LARGEHALL \
 -10.00f, -6.00f, 1.80f,0.70f, -20.00f,0.030f, -14.00f,0.060f,100.0f,100.0f
#define NLSOUND_ENVIRONMENT_PRESET_PLATE \
 -10.00f, -2.00f, 1.30f,0.90f,   0.00f,0.002f,   0.00f,0.010f,100.0f, 75.0f
//                                             in dB    ---
#define NLSOUND_MATERIAL_PRESET_SINGLEWINDOW  -28.00f, 0.71f
#define NLSOUND_MATERIAL_PRESET_DOUBLEWINDOW  -50.00f, 0.40f
#define NLSOUND_MATERIAL_PRESET_THINDOOR      -18.00f, 0.66f
#define NLSOUND_MATERIAL_PRESET_THICKDOOR     -44.00f, 0.64f
#define NLSOUND_MATERIAL_PRESET_WOODWALL      -40.00f, 0.50f
#define NLSOUND_MATERIAL_PRESET_BRICKWALL     -50.00f, 0.60f
#define NLSOUND_MATERIAL_PRESET_STONEWALL     -60.00f, 0.68f
#define NLSOUND_MATERIAL_PRESET_CURTAIN       -12.00f, 0.15f

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
			float diffusion, float density, float roomSize = 100.0f) : 
			RoomFilter(roomFilter), RoomFilterHF(roomFilterHF), 
			DecayTime(decayTime), DecayHFRatio(decayHFRatio), Reflections(reflections), 
			ReflectionsDelay(reflectionsDelay), LateReverb(lateReverb), 
			LateReverbDelay(lateReverbDelay), Diffusion(diffusion), Density(density), 
			RoomSize(roomSize) { }
		/// Default constructor.
		CEnvironment() : RoomFilter(-100.00f), RoomFilterHF(0.00f), 
			DecayTime(1.0f), DecayHFRatio(0.5f), Reflections(-100.00f), 
			ReflectionsDelay(0.02f), LateReverb(-100.00f), LateReverbDelay(0.04f), 
			Diffusion(100.0f), Density(100.0f), RoomSize(100.0f) { }
		/// Constructor which copies another environment and gives it a new roomsize.
		CEnvironment(const CEnvironment &environment, float roomSize) : 
			RoomFilter(environment.RoomFilter), RoomFilterHF(environment.RoomFilterHF), 
			DecayTime(environment.DecayTime), DecayHFRatio(environment.DecayHFRatio), 
			Reflections(environment.Reflections), ReflectionsDelay(environment.ReflectionsDelay), 
			LateReverb(environment.LateReverb), LateReverbDelay(environment.LateReverbDelay), 
			Diffusion(environment.Diffusion), Density(environment.Density), RoomSize(roomSize) { }
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
			Density((env0.Density * (1.0f - balance)) + (env1.Density * balance)), 
			RoomSize((env0.RoomSize * (1.0f - balance)) + (env1.RoomSize * balance)) { }
		/// [-100.00, 0] in dB, default: -100.00 dB
		float RoomFilter;
		/// [-100.00, 0] in dB, default: 0 mB
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
		/// [1.0, 100.0], default: 100.0f; influences environment parameters, 100.0f no change
		float RoomSize;
		/* This struct can *float* on water! */
	};

	IReverbEffect();
	virtual ~IReverbEffect();

	/// Set the environment (you have full control now, have fun)
	virtual void setEnvironment(const CEnvironment &environment) = 0;
}; /* class IReverbEffect */

extern IReverbEffect::CEnvironment EnvironmentPresets[];

enum TEnvironment
{
	EnvironmentGeneric = 0, 
	EnvironmentPaddedCell = 1, 
	EnvironmentRoom = 2, 
	EnvironmentBathRoom = 3, 
	EnvironmentLivingRoom = 4, 
	EnvironmentStoneRoom = 5, 
	EnvironmentAuditorium = 6, 
	EnvironmentConcertHall = 7, 
	EnvironmentCave = 8, 
	EnvironmentArena = 9, 
	EnvironmentHangar = 10, 
	EnvironmentCarpetedHallway = 11, 
	EnvironmentHallway = 12, 
	EnvironmentStoneCorridor = 13, 
	EnvironmentAlley = 14, 
	EnvironmentForest = 15, 
	EnvironmentCity = 16, 
	EnvironmentMountains = 17, 
	EnvironmentQuarry = 18, 
	EnvironmentPlain = 19, 
	EnvironmentParkingLot = 20, 
	EnvironmentSewerPipe = 21, 
	EnvironmentUnderwater = 22, 
	EnvironmentSmallRoom = 23, 
	EnvironmentMediumRoom = 24, 
	EnvironmentLargeRoom = 25, 
	EnvironmentMediumHall = 26, 
	EnvironmentLargeHall = 27, 
	EnvironmentPlate = 28, 

	EnvironmentCount = 29
};

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EFFECT_H */

/* end of file */
