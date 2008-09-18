/** \file sound_driver_al.h
 * OpenAL sound driver
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

#ifndef NL_SOUND_DRIVER_AL_H
#define NL_SOUND_DRIVER_AL_H
#include <nel/misc/types_nl.h>

#include "source_al.h"
#include "buffer_al.h"

namespace NLSOUND {


// alGenBuffers, alGenSources
//typedef ALAPI ALvoid ALAPIENTRY (*TGenFunctionAL) ( ALsizei, ALuint* );
typedef void (*TGenFunctionAL) ( ALsizei, ALuint* );

// alDeleteBuffers
typedef void (*TDeleteFunctionAL) ( ALsizei, const ALuint* );

// alIsBuffer, alIsSource
//typedef ALAPI ALboolean ALAPIENTRY (*TTestFunctionAL) ( ALuint );
typedef ALboolean (*TTestFunctionAL) ( ALuint );

#if !FINAL_VERSION
void alTestWarning(const char *src);
#else
#define alTestWarning(__src)
#endif

#ifdef NL_DEBUG
void alTestError();
#else
#define alTestError() alTestWarning("alTestError")
#endif

/**
 * OpenAL sound driver
 *
 * The caller of the create methods is responsible for the deletion of the created objects
 * These objects must be deleted before deleting the ISoundDriver instance.
 *
 *
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CSoundDriverAL : public ISoundDriver, public NLMISC::CManualSingleton<CSoundDriverAL>
{
private:
	// outside pointers
	/// The string mapper provided by client code.
	IStringMapperProvider *_StringMapper;

	// openal pointers
	// OpenAL device
	ALCdevice *_AlDevice;
	// OpenAL context
	ALCcontext *_AlContext;

	// system vars
	// Allocated buffers
	std::vector<ALuint> _Buffers;
	// Allocated sources
	std::vector<ALuint> _Sources;
	// Allocated submixers
	std::vector<ALuint> _Submixes;
	// Allocated effects
	std::vector<ALuint> _Effects;
	// Number of exported buffers (including any deleted buffers)
	uint _NbExpBuffers;
	// Number of exported sources (including any deleted sources)
	uint _NbExpSources;

	// user vars
	// Rolloff factor (not in the listener in OpenAL, but relative to the sources)
	float _RolloffFactor; // ***todo*** move
	/// Driver options
	TSoundOptions _Options;
public:

	/// Constructor
	CSoundDriverAL(ISoundDriver::IStringMapperProvider *stringMapper);

	inline ALCdevice *getAlDevice() { return _AlDevice; }
	inline ALCcontext *getAlContext() { return _AlContext; }

	/// Return a list of available devices for the user. If the result is empty, you should use the default device.
	// ***todo*** virtual void getDevices(std::vector<std::string> &devices);
	/// Initialize the driver with a user selected device. If device.empty(), the default or most appropriate device is used.
	virtual void init(std::string device, TSoundOptions options);

	/// Return options that are enabled (including those that cannot be disabled on this driver).
	virtual TSoundOptions getOptions();
	/// Return if an option is enabled (including those that cannot be disabled on this driver).
	virtual bool getOption(TSoundOptions option);

	/// Create a sound buffer
	virtual	IBuffer *createBuffer();
	/// Create the listener instance
	virtual	IListener *createListener();
	/// Create a source
	virtual	ISource *createSource();
	/// Create a submix
	virtual ISubmix *createSubmix();
	/// Create an effect
	virtual IEffect *createEffect(IEffect::TEffectType effectType);
	/// Return the maximum number of sources that can created
	virtual uint countMaxSources();
	/// Return the maximum number of submixers that can be created
	virtual uint countMaxSubmixes();
	
	virtual bool readWavBuffer(IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize);
	
	virtual bool readRawBuffer(IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency);
	
	virtual void startBench() { /* todo */ }
	virtual void endBench() { /* todo */ }
	virtual void displayBench(NLMISC::CLog *log) { /* TODO */ }


	/// Change the rolloff factor and apply to all sources
	void applyRolloffFactor(float f);

	/// Temp
	virtual bool loadWavFile(IBuffer *destbuffer, const char *filename);

	/// Commit all the changes made to 3D settings of listener and sources
	virtual void commit3DChanges() { }

	/// Write information about the driver to the output stream.
	virtual void writeProfile(std::string& out) { }

public:

	/// Destructor
	virtual					~CSoundDriverAL();

protected:

	friend CBufferAL::~CBufferAL();
	friend CSourceAL::~CSourceAL();

	/// Remove a buffer
	void					removeBuffer( IBuffer *buffer );

	/// Remove a source
	void					removeSource( ISource *source );

protected:

	/// Allocate nb new buffers or sources
	void					allocateNewItems( TGenFunctionAL algenfunc, TTestFunctionAL altestfunc,
											  std::vector<ALuint>& names, uint index, uint nb );
	
	/// Generate nb buffers
	void					generateItems( TGenFunctionAL algenfunc, TTestFunctionAL altestfunc, uint nb, ALuint *array );

	/// Remove names of deleted items and return the number of valid items
	uint					compactAliveNames( std::vector<ALuint>& names, TTestFunctionAL testfunc );

	/// Create a sound buffer or a sound source
	ALuint					createItem( TGenFunctionAL algenfunc, TTestFunctionAL altestfunc,
										std::vector<ALuint>& names, uint& index, uint allocrate );

	/// Delete a buffer or a source
	bool					deleteItem( ALuint name, TDeleteFunctionAL aldeletefunc, std::vector<ALuint>& names );
};


} // NLSOUND


#endif // NL_SOUND_DRIVER_AL_H

/* End of sound_driver_al.h */
