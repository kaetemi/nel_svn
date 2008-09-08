/**
 * \file eax_xaudio2.cpp
 * \brief CEaxXAudio2
 * \date 2008-09-04 00:47GMT
 * \author Jan Boon (Kaetemi)
 * CEaxXAudio2
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

#include "stdxaudio2.h"
#include "eax_xaudio2.h"

// STL includes

// NeL includes
// #include <nel/misc/debug.h>

// Project includes
#include "sound_driver_xaudio2.h"

using namespace std;
// using namespace NLMISC;

namespace NLSOUND {

bool CEaxXAudio2::_Init = false;
XAUDIO2FX_REVERB_PARAMETERS CEaxXAudio2::_Environments[CEaxXAudio2::_MaxEnvironments];

void CEaxXAudio2::init()
{
	if (_Init) return;
	_Init = true;

	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_GENERIC = XAUDIO2FX_I3DL2_PRESET_GENERIC;
	ReverbConvertI3DL2ToNative(&I3DL2_GENERIC, &_Environments[0]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_PADDEDCELL = XAUDIO2FX_I3DL2_PRESET_PADDEDCELL;
	ReverbConvertI3DL2ToNative(&I3DL2_PADDEDCELL, &_Environments[1]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_ROOM = XAUDIO2FX_I3DL2_PRESET_ROOM;
	ReverbConvertI3DL2ToNative(&I3DL2_ROOM, &_Environments[2]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_BATHROOM = XAUDIO2FX_I3DL2_PRESET_BATHROOM;
	ReverbConvertI3DL2ToNative(&I3DL2_BATHROOM, &_Environments[3]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_LIVINGROOM = XAUDIO2FX_I3DL2_PRESET_LIVINGROOM;
	ReverbConvertI3DL2ToNative(&I3DL2_LIVINGROOM, &_Environments[4]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_STONEROOM = XAUDIO2FX_I3DL2_PRESET_STONEROOM;
	ReverbConvertI3DL2ToNative(&I3DL2_STONEROOM, &_Environments[5]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_AUDITORIUM = XAUDIO2FX_I3DL2_PRESET_AUDITORIUM;
	ReverbConvertI3DL2ToNative(&I3DL2_AUDITORIUM, &_Environments[6]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_CONCERTHALL = XAUDIO2FX_I3DL2_PRESET_CONCERTHALL;
	ReverbConvertI3DL2ToNative(&I3DL2_CONCERTHALL, &_Environments[7]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_CAVE = XAUDIO2FX_I3DL2_PRESET_CAVE;
	ReverbConvertI3DL2ToNative(&I3DL2_CAVE, &_Environments[8]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_ARENA = XAUDIO2FX_I3DL2_PRESET_ARENA;
	ReverbConvertI3DL2ToNative(&I3DL2_ARENA, &_Environments[9]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_HANGAR = XAUDIO2FX_I3DL2_PRESET_HANGAR;
	ReverbConvertI3DL2ToNative(&I3DL2_HANGAR, &_Environments[10]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_CARPETEDHALLWAY = XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY;
	ReverbConvertI3DL2ToNative(&I3DL2_CARPETEDHALLWAY, &_Environments[11]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_HALLWAY = XAUDIO2FX_I3DL2_PRESET_HALLWAY;
	ReverbConvertI3DL2ToNative(&I3DL2_HALLWAY, &_Environments[12]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_STONECORRIDOR = XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR;
	ReverbConvertI3DL2ToNative(&I3DL2_STONECORRIDOR, &_Environments[13]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_ALLEY = XAUDIO2FX_I3DL2_PRESET_ALLEY;
	ReverbConvertI3DL2ToNative(&I3DL2_ALLEY, &_Environments[14]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_FOREST = XAUDIO2FX_I3DL2_PRESET_FOREST;
	ReverbConvertI3DL2ToNative(&I3DL2_FOREST, &_Environments[15]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_CITY = XAUDIO2FX_I3DL2_PRESET_CITY;
	ReverbConvertI3DL2ToNative(&I3DL2_CITY, &_Environments[16]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_MOUNTAINS = XAUDIO2FX_I3DL2_PRESET_MOUNTAINS;
	ReverbConvertI3DL2ToNative(&I3DL2_MOUNTAINS, &_Environments[17]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_QUARRY = XAUDIO2FX_I3DL2_PRESET_QUARRY;
	ReverbConvertI3DL2ToNative(&I3DL2_QUARRY, &_Environments[18]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_PLAIN = XAUDIO2FX_I3DL2_PRESET_PLAIN;
	ReverbConvertI3DL2ToNative(&I3DL2_PLAIN, &_Environments[19]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_PARKINGLOT = XAUDIO2FX_I3DL2_PRESET_PARKINGLOT;
	ReverbConvertI3DL2ToNative(&I3DL2_PARKINGLOT, &_Environments[20]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_SEWERPIPE = XAUDIO2FX_I3DL2_PRESET_SEWERPIPE;
	ReverbConvertI3DL2ToNative(&I3DL2_SEWERPIPE, &_Environments[21]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_UNDERWATER = XAUDIO2FX_I3DL2_PRESET_UNDERWATER;
	ReverbConvertI3DL2ToNative(&I3DL2_UNDERWATER, &_Environments[22]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_DRUGGED = { 100.0f, -1000, 0, 0.0f, 8.39f, 1.39f, -115, 0.002f, 985, 0.030f, 100.0f, 100.0f, 5000.0f };
	ReverbConvertI3DL2ToNative(&I3DL2_DRUGGED, &_Environments[23]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_DIZZY = { 100.0f, -1000, -400, 0.0f, 17.23f, 0.56f, -1713, 0.020f, -613, 0.030f, 100.0f, 100.0f, 5000.0f };
	ReverbConvertI3DL2ToNative(&I3DL2_DIZZY, &_Environments[24]);
	XAUDIO2FX_REVERB_I3DL2_PARAMETERS I3DL2_PSYCHOTIC = { 100.0f, -1000, -151, 0.0f, 7.56f, 0.91f, -626, 0.020f, 774, 0.030f, 100.0f, 100.0f, 5000.0f };
	ReverbConvertI3DL2ToNative(&I3DL2_PSYCHOTIC, &_Environments[25]);
}

void CEaxXAudio2::getEnvironment(uint envNum, XAUDIO2FX_REVERB_PARAMETERS* paramsOut)
{
	if (envNum < _MaxEnvironments)
		*paramsOut = _Environments[envNum];
	else
	{
		nlwarning("Invalid envNum %u, using _DefaultEnv %u!", (uint32)envNum, (uint32)_DefaultEnv);
		*paramsOut = _Environments[_DefaultEnv];
	}
}

} /* namespace NLSOUND */

/* end of file */
