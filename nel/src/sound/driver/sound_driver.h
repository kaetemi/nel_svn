/** \file sound_driver.h
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

#ifndef NL_SOUND_DRIVER_H
#define NL_SOUND_DRIVER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/string_mapper.h"
#include "nel/misc/common.h"
#include "nel/misc/file.h"

/// This namespace contains the sound classes
namespace NLSOUND {


class IBuffer;
class IListener;
class ISource;
class IMusicChannel;

/** Configuration for compiling with or without EAX support.
 *	Set to 0 if you don't have EAX library or don't want EAX support.
 *	This definition impact on code generation for driver AND sound lib.
 * NO EAX on linux
 */
#ifdef NL_OS_WINDOWS
#define EAX_AVAILABLE	1
#endif

/**
 *	Configuration to compile with manual or API (directx or open AL) rolloff factor.
 *	0 => API (directx or open AL) rollOff control.
 *		ISource::setAlpha() has no impact.
 *		IListener::setRollOffFactor() works
 *	1 => Manual rollOff control
 *		ISource::setAlpha() change the shape of attenuation
 *		IListener::setRollOffFactor() has no impact
 */
#define MANUAL_ROLLOFF	1


/*
 * Sound sample format
 */
enum TSampleFormat { Mono8, Mono16ADPCM, Mono16, Stereo8, Stereo16 };



/**
 * Abstract sound driver (implemented in sound driver dynamic library)
 *
 * The caller of the create methods is responsible for the deletion of the created objects.
 * These objects must be deleted before deleting the ISoundDriver instance.
 *
 * The driver is a singleton. To access, only the pointer returned by createDriver()
 * is provided.
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class ISoundDriver
{
public:

	/// Driver Creation Choice
	enum	TDriver
	{
		DriverAuto = 0,
		DriverFMod,
		DriverOpenAl,
		DriverDSound,
		DriverXAudio2,
		NumDrivers
	};

	/** The interface must be implemented and provided to the driver
	 *	in order to have a coherent string mapping.
	 *	The driver must not call directly CStringMapper method because
	 *	the static map container are located in a lib, so the main
	 *	code and the driver have theire own version of the static
	 *	container !
	 */
	class IStringMapperProvider
	{
	public:
		virtual ~IStringMapperProvider() {}
		/// map a string
		virtual const NLMISC::TStringId map(const std::string &str) =0;
		/// unmap a string
		virtual const std::string &unmap(const NLMISC::TStringId &stringId) =0;
	};

	/// Version of the driver interface. To increment when the interface change.
	static const uint32		InterfaceVersion;

	/** The static method which builds the sound driver instance
	 * In case of failure, can throw one of these ESoundDriver exception objects:
	 * ESoundDriverNotFound, ESoundDriverCorrupted, ESoundDriverOldVersion, ESoundDriverUnknownVersion
	 *
	 * You can request support for EAX. If EAX is requested and if there is enougth hardware
	 * buffer replay, then only hardware buffer are created when calling createBuffer.
	 * If the number of available hardware buffer is less than 10, then EAX is ignored.
	 *
	 *	\param driverType set DriverFMod if you want to use FMod driver (nel_drv_fmod_win_??.dll)
	 *	\param forceSoftwareBuffer (used only by FMod for now) force Buffer to be loaded in software (may be faster)
	*/
	static	ISoundDriver	*createDriver(bool useEax, IStringMapperProvider *stringMapper, TDriver driverType = DriverAuto, bool forceSoftwareBuffer = false);

	/// Create a sound buffer, destroy with delete
	virtual	IBuffer			*createBuffer() = 0;

	/// Create the listener instance
	virtual	IListener		*createListener() = 0;

	/// Return the maximum number of sources that can created
	virtual uint			countMaxSources() = 0;

	/// Create a source, destroy with delete
	virtual	ISource			*createSource() = 0;

	/// Read a WAV data in a buffer (format supported: Mono16, Mono8, Stereo16, Stereo8)
	virtual bool			readWavBuffer( IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize) = 0;

	/// FMod driver Note: ADPCM format are converted and stored internally in Mono16 format (hence IBuffer::getFormat() return Mono16)
	virtual bool			readRawBuffer( IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency) = 0;

	/// Commit all the changes made to 3D settings of listener and sources
	virtual void			commit3DChanges() = 0;

	/// Write information about the driver to the output stream.
	virtual void			writeProfile(std::string& out) = 0;

	// Does not create a sound loader

	virtual void	startBench() =0;
	virtual void	endBench() =0;
	virtual void	displayBench(NLMISC::CLog *log) =0;

	// Filled at createDriver()
	const std::string &getDllName() const { return _DllName; }

	/// Create a music channel, destroy with destroyMusicChannel
	virtual IMusicChannel *createMusicChannel() =0;

	/// Destroy a music channel
	virtual void destroyMusicChannel(IMusicChannel *musicChannel) =0;
	
	/** Get music info. Returns false if the song is not found or the function is not implemented.
	 *  \param filepath path to file, CPath::lookup done by driver
	 *  \param artist returns the song artist (empty if not available)
	 *  \param title returns the title (empty if not available)
	 */
	virtual bool getMusicInfo(const std::string &filepath, std::string &artist, std::string &title) =0;

	/// Destructor
	virtual	~ISoundDriver() {}
protected:

	/// Constructor
	ISoundDriver() {}

	/// Remove a buffer (should be called by the friend destructor of the buffer class)
	virtual void			removeBuffer( IBuffer *buffer ) = 0;

	/// Remove a source (should be called by the friend destructor of the source class)
	virtual void			removeSource( ISource *source ) = 0;

private:
	std::string				_DllName;
};


/**
 * Sound driver exceptions
 */
class ESoundDriver : public NLMISC::Exception
{
public:
	ESoundDriver() : NLMISC::Exception( "Sound driver error" ) {}
	ESoundDriver( const char *reason ) : NLMISC::Exception( reason ) {}
	ESoundDriver( const std::string &reason ) : NLMISC::Exception( reason.c_str() ) {}
};


/**
 * ESoundDriverNotFound
 */
class ESoundDriverNotFound : public ESoundDriver
{
public:
	ESoundDriverNotFound(const std::string &dllName) : ESoundDriver( dllName + " or third-party library not found" ) {}
};


/**
 * ESoundDriverCorrupted
 */
class ESoundDriverCorrupted : public ESoundDriver
{
public:
	ESoundDriverCorrupted(const std::string &dllName) : ESoundDriver( std::string("Can't get NLSOUND_createISoundDriverInstance from ") + dllName + " (Bad dll?)" ) {}
};


/**
 * ESoundDriverOldVersion
 */
class ESoundDriverOldVersion : public ESoundDriver
{
public:
	ESoundDriverOldVersion(const std::string &dllName) : ESoundDriver( dllName + " is a too old version. Ask for a more recent file" ) {}
};


/**
 * ESoundDriverUnknownVersion
 */
class ESoundDriverUnknownVersion : public ESoundDriver
{
public:
	ESoundDriverUnknownVersion(const std::string &dllName) : ESoundDriver( dllName + " is more recent than the application" ) {}
};


/**
 * ESoundDriverCantCreateDriver
 */
class ESoundDriverCantCreateDriver : public ESoundDriver
{
public:
	ESoundDriverCantCreateDriver(const std::string &dllName) : ESoundDriver( dllName + " can't create driver" ) {}
};


/**
 * ESoundDriverGenBuf
 */
class ESoundDriverGenBuf : public ESoundDriver
{
public:
	ESoundDriverGenBuf() : ESoundDriver( "Unable to generate sound buffers" ) {}
};


/**
 * ESoundDriverGenBuf
 */
class ESoundDriverGenSrc : public ESoundDriver
{
public:
	ESoundDriverGenSrc() : ESoundDriver( "Unable to generate sound sources" ) {}
};


/**
 * ESoundDriverNotSupp
 */
class ESoundDriverNotSupp : public ESoundDriver
{
public:
	ESoundDriverNotSupp() : ESoundDriver( "Operation not supported by sound driver" ) {}
};


} // NLSOUND


#endif // NL_SOUND_DRIVER_H

/* End of sound_driver.h */
