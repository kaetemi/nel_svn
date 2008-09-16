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

	virtual TEffectType getType() = 0;
}; /* class IEffect */

// I3DL2 effect presets (part of I3DL2 specification, see 3dl2help.h)
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_DEFAULT \
-10000,    0,0.0f, 1.00f,0.50f,-10000,0.020f,-10000,0.040f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_GENERIC \
 -1000, -100,0.0f, 1.49f,0.83f, -2602,0.007f,   200,0.011f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL \
 -1000,-6000,0.0f, 0.17f,0.10f, -1204,0.001f,   207,0.002f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_ROOM \
 -1000, -454,0.0f, 0.40f,0.83f, -1646,0.002f,    53,0.003f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_BATHROOM \
 -1000,-1200,0.0f, 1.49f,0.54f,  -370,0.007f,  1030,0.011f,100.0f, 60.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM \
 -1000,-6000,0.0f, 0.50f,0.10f, -1376,0.003f, -1104,0.004f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_STONEROOM \
 -1000, -300,0.0f, 2.31f,0.64f,  -711,0.012f,    83,0.017f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM \
 -1000, -476,0.0f, 4.32f,0.59f,  -789,0.020f,  -289,0.030f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL \
 -1000, -500,0.0f, 3.92f,0.70f, -1230,0.020f,    -2,0.029f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_CAVE \
 -1000,    0,0.0f, 2.91f,1.30f,  -602,0.015f,  -302,0.022f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_ARENA \
 -1000, -698,0.0f, 7.24f,0.33f, -1166,0.020f,    16,0.030f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_HANGAR \
 -1000,-1000,0.0f,10.05f,0.23f,  -602,0.020f,   198,0.030f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY \
 -1000,-4000,0.0f, 0.30f,0.10f, -1831,0.002f, -1630,0.030f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_HALLWAY \
 -1000, -300,0.0f, 1.49f,0.59f, -1219,0.007f,   441,0.011f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR \
 -1000, -237,0.0f, 2.70f,0.79f, -1214,0.013f,   395,0.020f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_ALLEY \
 -1000, -270,0.0f, 1.49f,0.86f, -1204,0.007f,    -4,0.011f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_FOREST \
 -1000,-3300,0.0f, 1.49f,0.54f, -2560,0.162f,  -613,0.088f, 79.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_CITY \
 -1000, -800,0.0f, 1.49f,0.67f, -2273,0.007f, -2217,0.011f, 50.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS \
 -1000,-2500,0.0f, 1.49f,0.21f, -2780,0.300f, -2014,0.100f, 27.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_QUARRY \
 -1000,-1000,0.0f, 1.49f,0.83f,-10000,0.061f,   500,0.025f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_PLAIN \
 -1000,-2000,0.0f, 1.49f,0.50f, -2466,0.179f, -2514,0.100f, 21.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT \
 -1000,    0,0.0f, 1.65f,1.50f, -1363,0.008f, -1153,0.012f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE \
 -1000,-1000,0.0f, 2.81f,0.14f,   429,0.014f,   648,0.021f, 80.0f, 60.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_UNDERWATER \
 -1000,-4000,0.0f, 1.49f,0.10f,  -449,0.007f,  1700,0.011f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_SMALLROOM \
 -1000, -600,0.0f, 1.10f,0.83f,  -400,0.005f,   500,0.010f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM \
 -1000, -600,0.0f, 1.30f,0.83f, -1000,0.010f,  -200,0.020f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_LARGEROOM \
 -1000, -600,0.0f, 1.50f,0.83f, -1600,0.020f, -1000,0.040f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL \
 -1000, -600,0.0f, 1.80f,0.70f, -1300,0.015f,  -800,0.030f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_LARGEHALL \
 -1000, -600,0.0f, 1.80f,0.70f, -2000,0.030f, -1400,0.060f,100.0f,100.0f,5000.0f
#define NLSOUND_I3DL2_ENVIRONMENT_PRESET_PLATE \
 -1000, -200,0.0f, 1.30f,0.90f,     0,0.002f,     0,0.010f,100.0f, 75.0f,5000.0f
#define NLSOUND_I3DL2_MATERIAL_PRESET_SINGLEWINDOW  -2800, 0.71f
#define NLSOUND_I3DL2_MATERIAL_PRESET_DOUBLEWINDOW  -5000, 0.40f
#define NLSOUND_I3DL2_MATERIAL_PRESET_THINDOOR      -1800, 0.66f
#define NLSOUND_I3DL2_MATERIAL_PRESET_THICKDOOR     -4400, 0.64f
#define NLSOUND_I3DL2_MATERIAL_PRESET_WOODWALL      -4000, 0.50f
#define NLSOUND_I3DL2_MATERIAL_PRESET_BRICKWALL     -5000, 0.60f
#define NLSOUND_I3DL2_MATERIAL_PRESET_STONEWALL     -6000, 0.68f
#define NLSOUND_I3DL2_MATERIAL_PRESET_CURTAIN       -1200, 0.15f

/**
 * \brief IReverb
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IReverb
 */
class IReverb : public IEffect
{
public:
	/// I3DL2 compatible reverb environment (see 3dl2.h)
	struct CEnvironment
	{
		CEnvironment(sint32 room, sint32 roomHF, float roomRolloffFactor, 
			float decayTime, float decayHFRatio, sint32 reflections, 
			float reflectionsDelay, sint32 reverb, float reverbDelay, 
			float diffusion, float density, float hfReference) : 
			Room(room), RoomHF(roomHF), RoomRolloffFactor(roomRolloffFactor), 
			DecayTime(decayTime), DecayHFRatio(decayHFRatio), Reflections(reflections), 
			ReflectionsDelay(reflectionsDelay), Reverb(reverb), ReverbDelay(reverbDelay), 
			Diffusion(diffusion), Density(density), HFReference(hfReference) { }
		CEnvironment() : Room(-10000), RoomHF(0), RoomRolloffFactor(0.0f), 
			DecayTime(1.0f), DecayHFRatio(0.5f), Reflections(-10000), 
			ReflectionsDelay(0.02f), Reverb(-10000), ReverbDelay(0.04f), 
			Diffusion(100.0f), Density(100.0f), HFReference(5000.0f) { }
		/// [-10000, 0] in mB (hundredths of decibels), default: -10000 mB
		sint32 Room;
		/// [-10000, 0] in mB (hundredths of decibels), default: 0 mB
		sint32 RoomHF;
		/// [0.0, 10.0], default: 0.0
		float RoomRolloffFactor;
		/// [0.1, 20.0] in seconds, default: 1.0 s
		float DecayTime;
		/// [0.1, 2.0], default: 0.5
		float DecayHFRatio;
		/// [-10000, 1000] in mB (hundredths of decibels), default: -10000 mB
		sint32 Reflections;
		/// [0.0, 0.3] in seconds, default: 0.02 s
		float ReflectionsDelay;
		/// [-10000, 2000] in mB (hundredths of decibels), default: -10000 mB
		sint32 Reverb;
		/// [0.0, 0.1] in seconds, default: 0.04 s
		float ReverbDelay;
		/// [0.0, 100.0] (percentage), default: 100.0 %
		float Diffusion;
		/// [0.0, 100.0] (percentage), default: 100.0 %
		float Density;
		/// [20.0, 20000.0] in Hz, default: 5000.0 Hz
		float HFReference;
	};

	IReverb();
	virtual ~IReverb();

	/// Set the environment (you have full control now, have fun)
	virtual void setEnvironment(const CEnvironment &environment) = 0;
	/// Set the size of the room, modifies the environment or uses api specific room size implementation.
	virtual void setRoomSize(float roomSize) = 0;
}; /* class IReverb */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EFFECT_H */

/* end of file */
