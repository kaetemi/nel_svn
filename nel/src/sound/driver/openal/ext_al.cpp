/**
 * \file ext_al.cpp
 * \brief CExtAl
 * \date 2008-09-15 15:42GMT
 * \author Jan Boon (Kaetemi)
 * OpenAL extensions
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

#include "stdopenal.h"
#include "ext_al.h"

extern "C"
{

void alExtInit(ALCdevice *device)
{
	nldebug("AL: Initializing extensions");

#if EAX_AVAILABLE
	// EAX
	if (AlExtEax = (alIsExtensionPresent("EAX") == AL_TRUE))
	{
		eaxSet = (EAXSet)alGetProcAddress("EAXSet");
		eaxGet = (EAXGet)alGetProcAddress("EAXGet");
		if (!eaxSet || !eaxGet)
		{
			nlwarning("AL: EAX alGetProcAddress failed");
			AlExtEax = false;
		}
	}
#endif
	
	// EAX-RAM
	if (AlExtXRam = ((alIsExtensionPresent("EAX-RAM") == AL_TRUE)
		|| (alIsExtensionPresent("EAX_RAM") == AL_TRUE)))
	{
		eaxSetBufferMode = (EAXSetBufferMode)alGetProcAddress("EAXSetBufferMode");
		eaxGetBufferMode = (EAXGetBufferMode)alGetProcAddress("EAXGetBufferMode");
		if (!eaxSetBufferMode || !eaxGetBufferMode)
		{
			nlwarning("AL: EAX-RAM alGetProcAddress failed");
			AlExtXRam = false;
		}
	}
	
	// EFX
	if (AlExtEfx = (alcIsExtensionPresent(device, "ALC_EXT_EFX") == ALC_TRUE))
	{
		// effect objects
		alGenEffects = (LPALGENEFXOBJECTS)alGetProcAddress("alGenEffects");
		alDeleteEffects = (LPALDELETEEFXOBJECTS)alGetProcAddress("alDeleteEffects");
		alIsEffect = (LPALISEFXOBJECT)alGetProcAddress("alIsEffect");
		alEffecti = (LPALEFXOBJECTI)alGetProcAddress("alEffecti");
		alEffectiv = (LPALEFXOBJECTIV)alGetProcAddress("alEffectiv");
		alEffectf = (LPALEFXOBJECTF)alGetProcAddress("alEffectf");
		alEffectfv = (LPALEFXOBJECTFV)alGetProcAddress("alEffectfv");
		alGetEffecti = (LPALGETEFXOBJECTI)alGetProcAddress("alGetEffecti");
		alGetEffectiv = (LPALGETEFXOBJECTIV)alGetProcAddress("alGetEffectiv");
		alGetEffectf = (LPALGETEFXOBJECTF)alGetProcAddress("alGetEffectf");
		alGetEffectfv = (LPALGETEFXOBJECTFV)alGetProcAddress("alGetEffectfv");
		// effect objects
		alGenFilters = (LPALGENEFXOBJECTS)alGetProcAddress("alGenFilters");
		alDeleteFilters = (LPALDELETEEFXOBJECTS)alGetProcAddress("alDeleteFilters");
		alIsFilter = (LPALISEFXOBJECT)alGetProcAddress("alIsFilter");
		alFilteri = (LPALEFXOBJECTI)alGetProcAddress("alFilteri");
		alFilteriv = (LPALEFXOBJECTIV)alGetProcAddress("alFilteriv");
		alFilterf = (LPALEFXOBJECTF)alGetProcAddress("alFilterf");
		alFilterfv = (LPALEFXOBJECTFV)alGetProcAddress("alFilterfv");
		alGetFilteri = (LPALGETEFXOBJECTI)alGetProcAddress("alGetFilteri");
		alGetFilteriv = (LPALGETEFXOBJECTIV)alGetProcAddress("alGetFilteriv");
		alGetFilterf = (LPALGETEFXOBJECTF)alGetProcAddress("alGetFilterf");
		alGetFilterfv = (LPALGETEFXOBJECTFV)alGetProcAddress("alGetFilterfv");
		// submix objects
		alGenAuxiliaryEffectSlots = (LPALGENEFXOBJECTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
		alDeleteAuxiliaryEffectSlots = (LPALDELETEEFXOBJECTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");
		alIsAuxiliaryEffectSlot = (LPALISEFXOBJECT)alGetProcAddress("alIsAuxiliaryEffectSlot");
		alAuxiliaryEffectSloti = (LPALEFXOBJECTI)alGetProcAddress("alAuxiliaryEffectSloti");
		alAuxiliaryEffectSlotiv = (LPALEFXOBJECTIV)alGetProcAddress("alAuxiliaryEffectSlotiv");
		alAuxiliaryEffectSlotf = (LPALEFXOBJECTF)alGetProcAddress("alAuxiliaryEffectSlotf");
		alAuxiliaryEffectSlotfv = (LPALEFXOBJECTFV)alGetProcAddress("alAuxiliaryEffectSlotfv");
		alGetAuxiliaryEffectSloti = (LPALGETEFXOBJECTI)alGetProcAddress("alGetAuxiliaryEffectSloti");
		alGetAuxiliaryEffectSlotiv = (LPALGETEFXOBJECTIV)alGetProcAddress("alGetAuxiliaryEffectSlotiv");
		alGetAuxiliaryEffectSlotf = (LPALGETEFXOBJECTF)alGetProcAddress("alGetAuxiliaryEffectSlotf");
		alGetAuxiliaryEffectSlotfv = (LPALGETEFXOBJECTFV)alGetProcAddress("alGetFilterfv");
		if (!alGenEffects || !alGenFilters || !alGenAuxiliaryEffectSlots)
		{
			nlwarning("AL: ALC_EXT_EFX alcGetProcAddress failed");
			AlExtEfx = false;
		}
	}
}

#if EAX_AVAILABLE
// EAX
bool AlExtEax = false;
EAXSet eaxSet = NULL;
EAXGet eaxGet = NULL;
#endif

// EAX-RAM
bool AlExtXRam = false;
EAXSetBufferMode eaxSetBufferMode = NULL;
EAXGetBufferMode eaxGetBufferMode = NULL;

// ALC_EXT_EFX
bool AlExtEfx = false;
// effect objects
LPALGENEFXOBJECTS alGenEffects = NULL;
LPALDELETEEFXOBJECTS alDeleteEffects = NULL;
LPALISEFXOBJECT alIsEffect = NULL;
LPALEFXOBJECTI alEffecti = NULL;
LPALEFXOBJECTIV alEffectiv = NULL;
LPALEFXOBJECTF alEffectf = NULL;
LPALEFXOBJECTFV alEffectfv = NULL;
LPALGETEFXOBJECTI alGetEffecti = NULL;
LPALGETEFXOBJECTIV alGetEffectiv = NULL;
LPALGETEFXOBJECTF alGetEffectf = NULL;
LPALGETEFXOBJECTFV alGetEffectfv = NULL;
// filter objects
LPALGENEFXOBJECTS alGenFilters = NULL;
LPALDELETEEFXOBJECTS alDeleteFilters = NULL;
LPALISEFXOBJECT alIsFilter = NULL;
LPALEFXOBJECTI alFilteri = NULL;
LPALEFXOBJECTIV alFilteriv = NULL;
LPALEFXOBJECTF alFilterf = NULL;
LPALEFXOBJECTFV alFilterfv = NULL;
LPALGETEFXOBJECTI alGetFilteri = NULL;
LPALGETEFXOBJECTIV alGetFilteriv = NULL;
LPALGETEFXOBJECTF alGetFilterf = NULL;
LPALGETEFXOBJECTFV alGetFilterfv = NULL;
// submix objects
LPALGENEFXOBJECTS alGenAuxiliaryEffectSlots = NULL;
LPALDELETEEFXOBJECTS alDeleteAuxiliaryEffectSlots = NULL;
LPALISEFXOBJECT alIsAuxiliaryEffectSlot = NULL;
LPALEFXOBJECTI alAuxiliaryEffectSloti = NULL;
LPALEFXOBJECTIV alAuxiliaryEffectSlotiv = NULL;
LPALEFXOBJECTF alAuxiliaryEffectSlotf = NULL;
LPALEFXOBJECTFV alAuxiliaryEffectSlotfv = NULL;
LPALGETEFXOBJECTI alGetAuxiliaryEffectSloti = NULL;
LPALGETEFXOBJECTIV alGetAuxiliaryEffectSlotiv = NULL;
LPALGETEFXOBJECTF alGetAuxiliaryEffectSlotf = NULL;
LPALGETEFXOBJECTFV alGetAuxiliaryEffectSlotfv = NULL;

}

/* end of file */
