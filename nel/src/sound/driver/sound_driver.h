/** \file sound_driver.h
 * ISoundDriver: sound driver interface
 *
 * $Id: sound_driver.h,v 1.27 2004/12/13 17:51:09 berenguier Exp $
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

	/// Create a sound buffer
	virtual	IBuffer			*createBuffer() = 0;

	/// Create the listener instance
	virtual	IListener		*createListener() = 0;

	/// Return the maximum number of sources that can created
	virtual uint			countMaxSources() = 0;

	/// Create a source
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
	const std::string		&getDllName() const {return _DllName;}

	/** Play some music syncrhonously (.mp3 etc...) (implemented in fmod only)
	 *	FMOD: The File is loaded synchronously in memory, but decompressed by FMod in a thread
	 *	Hence if the mp3 fileSize is 5 Mb, it will take only 5 Mb in memory (not the decompressed 40 Mb size)
	 *	NB: if an old music was played, it is first stop with stopMusic()
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 *	\param CIFile opened file (must use a CIFile if for instance you want to load from a BNP, and CBigFile is static....)
	 *	\param xFadeTime if not 0 the old music played is not stoped imediatly but a cross-fade of xFadeTime (in ms) is made between the 2.
	 */
	virtual bool	playMusic(uint channel, NLMISC::CIFile &file, uint xFadeTime, bool loop) =0;

	/** Play some music asynchronously (.mp3 etc...) (implemented in fmod only)
	 *	FMOD: the file is load asynchronously
	 *	NB: if an old music was played, it is first stop with stopMusic()
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently	 *	\param path full file path (no CPath::lookup is done since static)
	 *	\param xFadeTime if not 0 the old music played is not stoped imediatly but a cross-fade of xFadeTime (in ms) is made between the 2.
	 *	\param fileOffset and fileSize: if not 0, use it to load a .mp3 that reside in a BNP. 
	 *		the offset and size have to be retrieved with CBigFile methods. 
	 *		e.g.: use either 
	 *			playMusicAsync("C:/test/mymusic.mp3");
	 *		or
	 * 			playMusicAsync("C:/test/mydata.bnp", offsetOfMp3InBnp, sizeOfMp3InBnp);
	 *		Notice that you must give the full path of the bnp (eg: "C:/test/mydata.bnp") in path.
	 *	\param loop must be true to play the music in loop. 
	 */
	virtual bool	playMusicAsync(uint channel, const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop) =0;
	
	/** Stop the music previously loaded and played (the Memory is also freed)
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 *	\param xFadeTime if not 0 the old music played is not stoped but faded out of xFadeTime (in ms)
	 */
	virtual void	stopMusic(uint channel, uint xFadeTime) =0;
	
	/** Pause the music previously loaded and played (the Memory is not freed)
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual void	pauseMusic(uint channel) =0;
	
	/** Resume the music previously paused
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual void	resumeMusic(uint channel) =0;

	/** Get the song title. Returns false if the song is not found or the function is not implemented. 
	 * If the song as no name, result is filled with the filename.
	 */
	virtual bool	getSongTitle(const std::string &filename, std::string &result, uint fileOffset=0, uint fileSize=0) =0;

	/** Return true if a song is finished.
	 *	NB: in case of cross fading, the channel is considered "ended" if all fading are done
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual bool	isMusicEnded(uint channel) =0;
	
	/** Return the total length (in second) of the music currently played
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual float	getMusicLength(uint channel) =0;
	
	/** Set the music volume (if any music played). (volume value inside [0 , 1]) (default: 1)
	 *	NB: the volume of music is NOT affected by IListener::setGain()
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual void	setMusicVolume(uint channel, float gain) =0;

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
