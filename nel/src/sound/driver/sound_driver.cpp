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


/** DLL NAME selection for standard driver
 */
//#ifdef NL_OS_WINDOWS
//# if _MSC_VER >= 1300	// visual .NET, use different dll name
//#  define NLSOUND_DLL_NAME "nldriver_openal"
//# else
//#  define NLSOUND_DLL_NAME "nel_drv_dsound_win"
//# endif
//#elif defined (NL_OS_UNIX)
//# define NLSOUND_DLL_NAME "nel_drv_openal"
//#else
//# error "Unknown system"
//#endif
//
//#ifdef NL_OS_WINDOWS
//
//#if _MSC_VER >= 1300	// visual .NET, use different dll name
//	// must test it first, because NL_DEBUG_FAST and NL_DEBUG are declared at same time.
//#ifdef NL_DEBUG_FAST
//#define NLSOUND_DLL_NAME "nldriver_openal_df.dll"
//#elif defined (NL_DEBUG)
//#define NLSOUND_DLL_NAME "nldriver_openal_d.dll"
//#elif defined (NL_RELEASE_DEBUG)
//#define NLSOUND_DLL_NAME "nldriver_openal_rd.dll"
//#elif defined (NL_RELEASE)
//#define NLSOUND_DLL_NAME "nldriver_openal_r.dll"
//#else
//#error "Unknown dll name"
//#endif
//
//#else
//
//	// must test it first, because NL_DEBUG_FAST and NL_DEBUG are declared at same time.
//#ifdef NL_DEBUG_FAST
//#define NLSOUND_DLL_NAME "nel_drv_dsound_win_df.dll"
//#elif defined (NL_DEBUG)
//#define NLSOUND_DLL_NAME "nel_drv_dsound_win_d.dll"
//#elif defined (NL_RELEASE_DEBUG)
//#define NLSOUND_DLL_NAME "nel_drv_dsound_win_rd.dll"
//#elif defined (NL_RELEASE)
//#define NLSOUND_DLL_NAME "nel_drv_dsound_win_r.dll"
//#else
//#error "Unknown dll name"
//#endif
//
//#endif
//
//#elif defined (NL_OS_UNIX)
//#define NLSOUND_DLL_NAME "libnel_drv_openal.so"
//#else
//#error "Unknown system"
//#endif


// Interface version
const uint32 ISoundDriver::InterfaceVersion = 0x08;

#ifdef NL_STATIC

extern ISoundDriver* createISoundDriverInstance(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer);
extern uint32 interfaceVersion();
extern void outputProfile(std::string &out);
extern ISoundDriver::TDriver getDriverType();

#else

typedef ISoundDriver* (*ISDRV_CREATE_PROC)(bool, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer);
const char *IDRV_CREATE_PROC_NAME = "NLSOUND_createISoundDriverInstance";

typedef uint32 (*ISDRV_VERSION_PROC)(void);
const char *IDRV_VERSION_PROC_NAME = "NLSOUND_interfaceVersion";

#endif

/*
 * The static method which builds the sound driver instance
 */
ISoundDriver	*ISoundDriver::createDriver(bool useEax, IStringMapperProvider *stringMapper, TDriver driverType, bool forceSoftwareBuffer)
{
#ifdef NL_STATIC

	if (getDriverType() != driverType) nlwarning("Statically linked sound driver is not the same as the selected sound driver.");

	std::string driverName;
	switch (getDriverType())
	{
	case DriverFMod:
		driverName = "FMod";
		break;
	case DriverOpenAl:
		driverName = "OpenAL";
		break;
	case DriverDSound:
		driverName = "DirectSound";
		break;
	case DriverXAudio2:
		driverName = "XAudio2";
		break;
	default:
		driverName = "UNKNOWN";
	}

	nlinfo("Creating %s sound driver. This driver is statically linked into this application.", driverName.c_str());

	return createISoundDriverInstance(useEax, stringMapper, forceSoftwareBuffer);

#else

	ISDRV_CREATE_PROC	createSoundDriver = NULL;
	ISDRV_VERSION_PROC	versionDriver = NULL;

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
