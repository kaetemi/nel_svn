/** \file sound_driver.cpp
 * ISoundDriver: sound driver interface
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

#include "sound_driver.h"

#ifdef NL_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#endif // NL_OS_WINDOWS

#include <nel/misc/debug.h>
#ifndef NL_STATIC
#	include <nel/misc/dynloadlib.h>
#endif

using namespace NLMISC;

// Driver availability for NL_STATIC compilation.
#if defined( NL_OS_WINDOWS )
#	define NL_FMOD_AVAILABLE 1
#	define NL_OPENAL_AVAILABLE 0
#	define NL_DSOUND_AVAILABLE 0
#	define NL_XAUDIO2_AVAILABLE 0
#elif defined( NL_OS_UNIX )
#	define NL_FMOD_AVAILABLE 1
#	define NL_OPENAL_AVAILABLE 1
#	define NL_DSOUND_AVAILABLE 0
#	define NL_XAUDIO2_AVAILABLE 0
#else
#	define NL_FMOD_AVAILABLE 0
#	define NL_OPENAL_AVAILABLE 0
#	define NL_DSOUND_AVAILABLE 0
#	define NL_XAUDIO2_AVAILABLE 0
#endif

namespace NLSOUND
{

/// Interface version, increase when any part of sound_lowlevel is changed.
/// Put your name in comment to make sure you don't commit with
/// the same interface version number as someone else.
const uint32 ISoundDriver::InterfaceVersion = 0x12; // Kaetemi

#ifdef NL_STATIC

#define NLSOUND_DECLARE_DRIVER(__soundDriver) \
	extern ISoundDriver* createISoundDriverInstance##__soundDriver##(ISoundDriver::IStringMapperProvider *stringMapper); \
	extern uint32 interfaceVersion##__soundDriver##(); \
	extern void outputProfile##__soundDriver##(std::string &out); \
	extern ISoundDriver::TDriver getDriverType##__soundDriver##();

#if NL_FMOD_AVAILABLE
	NLSOUND_DECLARE_DRIVER(FMod)
#endif
#if NL_OPENAL_AVAILABLE
	NLSOUND_DECLARE_DRIVER(OpenAl)
#endif
#if NL_DSOUND_AVAILABLE
	NLSOUND_DECLARE_DRIVER(DSound)
#endif
#if NL_XAUDIO2_AVAILABLE
	NLSOUND_DECLARE_DRIVER(XAudio2)
#endif

#else

typedef ISoundDriver* (*ISDRV_CREATE_PROC)(ISoundDriver::IStringMapperProvider *stringMapper);
const char *IDRV_CREATE_PROC_NAME = "NLSOUND_createISoundDriverInstance";

typedef uint32 (*ISDRV_VERSION_PROC)(void);
const char *IDRV_VERSION_PROC_NAME = "NLSOUND_interfaceVersion";

#endif

/// Return driver name from type.
const char *ISoundDriver::getDriverName(TDriver driverType)
{
	switch (driverType)
	{
		case DriverAuto: return "AUTO";
		case DriverFMod: return "FMod";
		case DriverOpenAl: return "OpenAL";
		case DriverDSound: return "DSound";
		case DriverXAudio2: return "XAudio2";
		default: return "UNKNOWN";
	}
}

/*
 * The static method which builds the sound driver instance
 */
ISoundDriver *ISoundDriver::createDriver(IStringMapperProvider *stringMapper, TDriver driverType)
{
#ifdef NL_STATIC
	
	nlinfo("Creating statically linked sound driver %s", getDriverName(driverType));
	
	ISoundDriver *result = NULL;
	switch (driverType)
	{
		// switch between available drivers
#	if NL_FMOD_AVAILABLE
		case DriverFMod: result = createISoundDriverInstanceFMod(stringMapper); break;
#	endif
#	if NL_OPENAL_AVAILABLE
		case DriverOpenAl: result = createISoundDriverInstanceOpenAl(stringMapper); break;
#	endif
#	if NL_DSOUND_AVAILABLE
		case DriverDSound: result = createISoundDriverInstanceDSound(stringMapper); break;
#	endif
#	if NL_XAUDIO2_AVAILABLE
		case DriverXAudio2: result = createISoundDriverInstanceXAudio2(stringMapper); break;
#	endif
		// auto driver = first available in this order: FMod, OpenAl, XAudio2, DSound
#	if NL_FMOD_AVAILABLE
		case DriverAuto: result = createISoundDriverInstanceFMod(stringMapper); break;
#	elif NL_OPENAL_AVAILABLE
		case DriverAuto: result = createISoundDriverInstanceOpenAl(stringMapper); break;
#	elif NL_XAUDIO2_AVAILABLE
		case DriverAuto: result = createISoundDriverInstanceXAudio2(stringMapper); break;
#	elif NL_DSOUND_AVAILABLE
		case DriverAuto: result = createISoundDriverInstanceDSound(stringMapper); break;
#	endif
		// unavailable driver = FAIL
		default: throw ESoundDriverNotFound(getDriverName(driverType));
	}
	if (!result) throw ESoundDriverCantCreateDriver(getDriverName(driverType)); 
	return result;
	
#else

	ISDRV_CREATE_PROC createSoundDriver = NULL;
	ISDRV_VERSION_PROC versionDriver = NULL;

	// dll selected
	std::string	dllName;

	// Choose the DLL
	switch(driverType)
	{
	case DriverFMod:
#if defined (NL_OS_WINDOWS)
		dllName = "nel_drv_fmod_win";
#elif defined (NL_OS_UNIX)
		dllName = "nel_drv_fmod";
#else
#		error "Driver name not define for this platform"
#endif // NL_OS_UNIX / NL_OS_WINDOWS
		break;
	case DriverOpenAl:
#ifdef NL_OS_WINDOWS
		dllName = "nel_drv_openal_win";
#elif defined (NL_OS_UNIX)
		dllName = "nel_drv_openal";
#else
#		error "Driver name not define for this platform"
#endif
		break;
	case DriverDSound:
#ifdef NL_OS_WINDOWS
		dllName = "nel_drv_dsound_win";
#elif defined (NL_OS_UNIX)
		nlerror("DriverDSound doesn't exist on Unix because it requires DirectX");
#else
#		error "Driver name not define for this platform"
#endif
		break;
	case DriverXAudio2:
#ifdef NL_OS_WINDOWS
		dllName = "nel_drv_xaudio2_win";
#elif defined (NL_OS_UNIX)
		nlerror("DriverXAudio2 doesn't exist on Unix because it requires DirectX");
#else
#		error "Driver name not define for this platform"
#endif
		break;
	default:
#ifdef NL_OS_WINDOWS
		dllName = "nel_drv_dsound_win";
#elif defined (NL_OS_UNIX)
		dllName = "nel_drv_openal";
#else
#		error "Driver name not define for this platform"
#endif
		break;
	}

	CLibrary driverLib;
	// Load it (adding standard nel pre/suffix, looking in library path and not taking ownership)
	if (!driverLib.loadLibrary(dllName, true, true, false))
	{
		throw ESoundDriverNotFound(dllName);
	}

	/**
	 *  MTR: Is there a way with NLMISC to replace SearchFile() ? Until then, no info for Linux.
	 */
#ifdef NL_OS_WINDOWS
	char buffer[1024], *ptr;
	uint len = SearchPath (NULL, dllName.c_str(), NULL, 1023, buffer, &ptr);
	if( len )
		nlinfo ("Using the library '%s' that is in the directory: '%s'", dllName.c_str(), buffer);
#endif

	createSoundDriver = (ISDRV_CREATE_PROC) driverLib.getSymbolAddress(IDRV_CREATE_PROC_NAME);
	if (createSoundDriver == NULL)
	{
#ifdef NL_OS_WINDOWS
		nlinfo( "Error: %u", GetLastError() );
#else
		nlinfo( "Error: Unable to load Sound Driver." );
#endif
		throw ESoundDriverCorrupted(dllName);
	}

	versionDriver = (ISDRV_VERSION_PROC) driverLib.getSymbolAddress(IDRV_VERSION_PROC_NAME);
	if (versionDriver != NULL)
	{
		if (versionDriver()<ISoundDriver::InterfaceVersion)
			throw ESoundDriverOldVersion(dllName);
		else if (versionDriver()>ISoundDriver::InterfaceVersion)
			throw ESoundDriverUnknownVersion(dllName);
	}

	ISoundDriver *ret = createSoundDriver(stringMapper);
	if ( ret == NULL )
	{
		throw ESoundDriverCantCreateDriver(dllName);
	}
	else
	{
		// Fill the DLL name
		ret->_DllName = driverLib.getLibFileName();
	}

	return ret;

#endif /* NL_STATIC */
}

} // NLSOUND
