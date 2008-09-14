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
#include "nel/misc/debug.h"
#include "nel/misc/dynloadlib.h"


#ifdef NL_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#endif // NL_OS_WINDOWS

using namespace NLMISC;

namespace NLSOUND
{

// Interface version
const uint32 ISoundDriver::InterfaceVersion = 0x0A;

#ifdef NL_STATIC

/// Statically linked driver stuff... ***deprecated*** ***todo***
extern ISoundDriver* createISoundDriverInstance(ISoundDriver::IStringMapperProvider *stringMapper);
extern uint32 interfaceVersion();
extern void outputProfile(std::string &out);
extern ISoundDriver::TDriver getDriverType();

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
	
	if (driverType != DriverAuto && getDriverType() != driverType)
		nlwarning("Statically linked sound driver %s is not the same as the selected sound driver %s.", getDriverName(getDriverType()), getDriverName(driverType));
	nlinfo("Creating %s sound driver. This driver is statically linked into this application.", getDriverName(getDriverType()));
	
	ISoundDriver *result = createISoundDriverInstance(stringMapper);
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

	ISoundDriver *ret = createSoundDriver(useEax, stringMapper, forceSoftwareBuffer);
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
