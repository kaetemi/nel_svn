/** \file sound_driver.cpp
 * ISoundDriver: sound driver interface
 *
 * $Id: sound_driver.cpp,v 1.21 2006/05/31 12:03:21 boucher Exp $
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
# include <windows.h>
# undef min
# undef max
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

typedef ISoundDriver* (*ISDRV_CREATE_PROC)(bool, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer); 
const char *IDRV_CREATE_PROC_NAME = "NLSOUND_createISoundDriverInstance";

typedef uint32 (*ISDRV_VERSION_PROC)(void); 
const char *IDRV_VERSION_PROC_NAME = "NLSOUND_interfaceVersion";



/*
 * The static method which builds the sound driver instance
 */
ISoundDriver	*ISoundDriver::createDriver(bool useEax, IStringMapperProvider *stringMapper, TDriver driverType, bool forceSoftwareBuffer)
{
	ISDRV_CREATE_PROC	createSoundDriver = NULL;
	ISDRV_VERSION_PROC	versionDriver = NULL;

	// dll selected
	std::string	dllName;
	
	
//#ifdef NL_OS_WINDOWS

	// WINDOWS code.
//	HINSTANCE			hInst;

	// Chooose the DLL
	if(driverType==DriverFMod)
	{
#if defined (NL_OS_WINDOWS)
		dllName= "nel_drv_fmod_win";
//		#ifdef NL_DEBUG_FAST
//		dllName= "nel_drv_fmod_win_df.dll";
//		#elif defined (NL_DEBUG)
//		dllName= "nel_drv_fmod_win_d.dll";
//		#elif defined (NL_RELEASE_DEBUG)
//		dllName= "nel_drv_fmod_win_rd.dll";
//		#elif defined (NL_RELEASE)
//		dllName= "nel_drv_fmod_win_r.dll";
//		#else
//		#error "Unknown dll name"
//		#endif
#elif defined (NL_OS_UNIX)
		dllName= "nel_drv_fmod";
#else
# error "Driver name not define for this platform"
#endif // NL_OS_UNIX / NL_OS_WINDOWS
	}
	else
	{
#ifdef NL_OS_WINDOWS
		dllName = "nel_drv_dsound_win";
#elif defined (NL_OS_UNIX)
		dllName = "nel_drv_openal";
#else
# error "Driver name not define for this platform"
#endif
//		dllName= NLSOUND_DLL_NAME;
	}

	CLibrary driverLib;
	// Load it (adding standard nel pre/sufixe, looking in library path and not taking ownership)
	if (!driverLib.loadLibrary(dllName, true, true, false))
//	hInst = LoadLibrary(dllName.c_str());
//	if (!hInst)
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
//	createSoundDriver = (ISDRV_CREATE_PROC) GetProcAddress (hInst, IDRV_CREATE_PROC_NAME);
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
//	versionDriver = (ISDRV_VERSION_PROC) GetProcAddress (hInst, IDRV_VERSION_PROC_NAME);
	if (versionDriver != NULL)
	{
		if (versionDriver()<ISoundDriver::InterfaceVersion)
			throw ESoundDriverOldVersion(dllName);
		else if (versionDriver()>ISoundDriver::InterfaceVersion)
			throw ESoundDriverUnknownVersion(dllName);
	}

//#elif defined (NL_OS_UNIX)
//
//	// Unix code
//	dllName= NLSOUND_DLL_NAME;
//	void *handle = dlopen(dllName.c_str(), RTLD_NOW);
//
//	if (handle == NULL)
//	{
//		nlwarning ("when loading dynamic library '%s': %s", dllName.c_str(), dlerror());
//		throw ESoundDriverNotFound(dllName);
//	}
//
//	/* Not ANSI. Might produce a warning */
//	createSoundDriver = (ISDRV_CREATE_PROC) dlsym (handle, IDRV_CREATE_PROC_NAME);
//	if (createSoundDriver == NULL)
//	{
//		nlwarning ("when getting function in dynamic library '%s': %s", dllName.c_str(), dlerror());
//		throw ESoundDriverCorrupted(dllName);
//	}
//
//	versionDriver = (ISDRV_VERSION_PROC) dlsym (handle, IDRV_VERSION_PROC_NAME);
//	if (versionDriver != NULL)
//	{
//		if (versionDriver()<ISoundDriver::InterfaceVersion)
//			throw ESoundDriverOldVersion(dllName);
//		else if (versionDriver()>ISoundDriver::InterfaceVersion)
//			throw ESoundDriverUnknownVersion(dllName);
//	}
//
//#else // NL_OS_UNIX
//#error "Dynamic DLL loading not implemented!"
//#endif // NL_OS_UNIX

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
}


} // NLSOUND
