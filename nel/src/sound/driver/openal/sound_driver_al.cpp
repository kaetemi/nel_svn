/** \file sound_driver_al.cpp
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

#include "stdopenal.h"
#include "sound_driver_al.h"

#include <nel/misc/path.h>
#include <nel/misc/dynloadlib.h>
#include <nel/misc/fast_mem.h>

#include "buffer_al.h"
#include "listener_al.h"
#include "effect_al.h"
#include "source_al.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {


// Currently, the OpenAL headers are different between Windows and Linux versions !
// AL_INVALID_XXXX are part of the spec, though.
/*#ifdef NL_OS_UNIX
#define AL_INVALID_ENUM AL_ILLEGAL_ENUM
#define AL_INVALID_OPERATION AL_ILLEGAL_COMMAND
#endif*/


#ifdef NL_DEBUG
// Test error in debug mode
void alTestError()
{
	ALuint errcode = alGetError();
	switch (errcode)
	{
	case AL_NO_ERROR : break;
	case AL_INVALID_NAME: nlerror("OpenAL: Invalid name");
	case AL_INVALID_ENUM: nlerror("OpenAL: Invalid enum");
	case AL_INVALID_VALUE: nlerror("OpenAL: Invalid value");
	case AL_INVALID_OPERATION: nlerror("OpenAL: Invalid operation");
	case AL_OUT_OF_MEMORY: nlerror("OpenAL: Out of memory");
	}
}
#endif

#if !FINAL_VERSION
void alTestWarning(const char *src)
{
	ALuint errcode = alGetError();
	switch (errcode)
	{
	case AL_NO_ERROR: break;
	case AL_INVALID_NAME: nlwarning("AL: Invalid Name paramater passed to AL call (%s)", src); break;
	case AL_INVALID_ENUM: nlwarning("AL: Invalid parameter passed to AL call (%s)", src); break;
	case AL_INVALID_VALUE: nlwarning("AL: Invalid enum parameter value (%s)", src); break;
	case AL_INVALID_OPERATION: nlwarning("AL: Illegal call (%s)", src); break;
	case AL_OUT_OF_MEMORY: nlerror("AL: Out of memory (%s)", src); break;
	}
}
#endif

#define INITIAL_BUFFERS 8
#define INITIAL_SOURCES 8
#define BUFFER_ALLOC_RATE 8
#define SOURCE_ALLOC_RATE 8

#define ROLLOFF_FACTOR_DEFAULT 1.0f

#ifndef NL_STATIC

class CSoundDriverALNelLibrary : public NLMISC::INelLibrary {
	void onLibraryLoaded(bool /* firstTime */) { }
	void onLibraryUnloaded(bool /* lastTime */) { }
};
NLMISC_DECL_PURE_LIB(CSoundDriverALNelLibrary)

#endif /* #ifndef NL_STATIC */

/*
 * Sound driver instance creation
 */
#ifdef NL_OS_WINDOWS

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver* createISoundDriverInstanceOpenAl
#else
__declspec(dllexport) ISoundDriver *NLSOUND_createISoundDriverInstance
#endif
	(ISoundDriver::IStringMapperProvider *stringMapper)
{
	return new CSoundDriverAL(stringMapper);
}

// ******************************************************************

#ifdef NL_STATIC
uint32 interfaceVersionOpenAl()
#else
__declspec(dllexport) uint32 NLSOUND_interfaceVersion()
#endif
{
	return ISoundDriver::InterfaceVersion;
}

// ******************************************************************

#ifdef NL_STATIC
void outputProfileOpenAl
#else
__declspec(dllexport) void NLSOUND_outputProfile
#endif
	(string &out)
{
	CSoundDriverAL::getInstance()->writeProfile(out);
}

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver::TDriver getDriverTypeOpenAl()
#else
__declspec(dllexport) ISoundDriver::TDriver NLSOUND_getDriverType()
#endif
{
	return ISoundDriver::DriverOpenAl;
}

// ******************************************************************

#elif defined (NL_OS_UNIX)

extern "C"
{
ISoundDriver* NLSOUND_createISoundDriverInstance(ISoundDriver::IStringMapperProvider *stringMapper)
{
	return new CSoundDriverAL(stringMapper);
}

uint32 NLSOUND_interfaceVersion ()
{
	return ISoundDriver::InterfaceVersion;
}
}

#endif // NL_OS_UNIX

/*
 * Constructor
 */
CSoundDriverAL::CSoundDriverAL(ISoundDriver::IStringMapperProvider *stringMapper) 
: _StringMapper(stringMapper), _AlDevice(NULL), _AlContext(NULL), 
_NbExpBuffers(0), _NbExpSources(0), _RolloffFactor(1.f)
{
	
}

/*
 * Destructor
 */
CSoundDriverAL::~CSoundDriverAL()
{
	// Remove the allocated (but not exported) source and buffer names
	if (!_Sources.empty()) alDeleteSources(compactAliveNames(_Sources, alIsSource), &*_Sources.begin());
	if (!_Buffers.empty()) alDeleteBuffers(compactAliveNames(_Buffers, alIsBuffer), &*_Buffers.begin());
	// Release internal resources of all remaining IEffect instances
	{
		set<CEffectAL *>::iterator it(_Effects.begin()), end(_Effects.end());
		for (; it != end; ++it) removeEffect(*it);
		_Effects.clear();
	}

	// OpenAL exit
	if (_AlContext) { alcDestroyContext(_AlContext); _AlContext = NULL; }
	if (_AlDevice) { alcCloseDevice(_AlDevice); _AlDevice = NULL; }
}

/// Return a list of available devices for the user. If the result is empty, you should use the default device.
// ***todo*** void CSoundDriverAL::getDevices(std::vector<std::string> &devices) { }

/// Initialize the driver with a user selected device. If device.empty(), the default or most appropriate device is used.
void CSoundDriverAL::init(std::string device, ISoundDriver::TSoundOptions options)
{
	// list of supported options in this driver
	// no adpcm, no manual rolloff (for now)
	const sint supportedOptions = 
		OptionEnvironmentEffects
		| OptionSoftwareBuffer
		| OptionLocalBufferCopy
		| OptionHasBufferStreaming;

	// list of forced options in this driver
	const sint forcedOptions = 0;

	// set the options
	_Options = (TSoundOptions)(((sint)options & supportedOptions) | forcedOptions);

	/* TODO: manual rolloff */
	/* TODO: multichannel */
	/* TODO: driver selection */

	// OpenAL initialization
	_AlDevice = alcOpenDevice(NULL);
	if (!_AlDevice) throw ESoundDriver("AL: Failed to open device");	
	int attrlist[] = { ALC_FREQUENCY, 44100,
	                   ALC_MONO_SOURCES, 12, 
	                   ALC_STEREO_SOURCES, 4, 
	                   ALC_INVALID };
	_AlContext = alcCreateContext(_AlDevice, attrlist);
	if (!_AlContext) { alcCloseDevice(_AlDevice); throw ESoundDriver("AL: Failed to create context"); }
	alcMakeContextCurrent(_AlContext);
	alTestError();

	// Display version information
	const ALchar *alversion, *alrenderer, *alvendor, *alext;
	alversion = alGetString(AL_VERSION);
	alrenderer = alGetString(AL_RENDERER);
	alvendor = alGetString(AL_VENDOR);
	alext = alGetString(AL_EXTENSIONS);
	alTestError();
	nldebug("AL: Loading OpenAL lib: %s, %s, %s", alversion, alrenderer, alvendor);
	nldebug("AL: Listing extensions: %s", alext);

	// Load and display extensions
	alExtInit(_AlDevice);
#if EAX_AVAILABLE
	nlinfo("AL: EAX: %s, EAX-RAM: %s, ALC_EXT_EFX: %s", 
		AlExtEax ? "Present" : "Not available", 
		AlExtXRam ? "Present" : "Not available", 
		AlExtEfx ? "Present" : "Not available");
#else
	nldebug("AL: EAX-RAM: %s, ALC_EXT_EFX: %s", 
		AlExtXRam ? "Present" : "Not available", 
		AlExtEfx ? "Present" : "Not available");
#endif
	alTestError();

	nldebug("AL: Max. sources: %u, Max. effects: %u", (uint32)countMaxSources(), (uint32)countMaxEffects());

	if (getOption(OptionEnvironmentEffects)) 
	{
		if (!AlExtEfx)
		{
			nlwarning("AL: ALC_EXT_EFX is required, environment effects disabled");
			_Options = (TSoundOptions)((uint)_Options & ~OptionEnvironmentEffects);
		}
		else if (!countMaxEffects())
		{		
			nlwarning("AL: No effects available, environment effects disabled");
			_Options = (TSoundOptions)((uint)_Options & ~OptionEnvironmentEffects);
		}
	}

	// Choose the I3DL2 model (same as DirectSound3D if not manual)
	if (getOption(OptionManualRolloff)) alDistanceModel(AL_NONE);
	else alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	alTestError();

	// Initial buffers and sources allocation
	allocateNewItems(alGenBuffers, alIsBuffer, _Buffers, _NbExpBuffers, INITIAL_BUFFERS);
	allocateNewItems(alGenSources, alIsSource, _Sources, _NbExpSources, INITIAL_SOURCES);
	alTestError();
}

/// Return options that are enabled (including those that cannot be disabled on this driver).
ISoundDriver::TSoundOptions CSoundDriverAL::getOptions()
{
	return _Options;
}

/// Return if an option is enabled (including those that cannot be disabled on this driver).
bool CSoundDriverAL::getOption(ISoundDriver::TSoundOptions option)
{
	return ((uint)_Options & (uint)option) == (uint)option;
}

/*
 * Allocate nb new items
 */
void CSoundDriverAL::allocateNewItems(TGenFunctionAL algenfunc, TTestFunctionAL altestfunc,
									  vector<ALuint>& names, uint index, uint nb )
{
	nlassert( index == names.size() );
	names.resize( index + nb );
	// FIXME assumption about inner workings of std::vector;
	// &(names[...]) only works with "names.size() - nbalive == 1"
	generateItems( algenfunc, altestfunc, nb, &(names[index]) );
}


/*
 * throwGenException
 */
void ThrowGenException( TGenFunctionAL algenfunc )
{
	if ( algenfunc == alGenBuffers )
		throw ESoundDriverGenBuf();
	else if ( algenfunc == alGenSources )
		throw ESoundDriverGenSrc();
	else
		nlstop;
}

/*
 * Generate nb buffers/sources
 */
void CSoundDriverAL::generateItems( TGenFunctionAL algenfunc, TTestFunctionAL altestfunc, uint nb, ALuint *array )
{
	// array is actually a std::vector element address!
	algenfunc( nb, array );

	// Error handling
	if ( alGetError() != AL_NO_ERROR )
	{
		ThrowGenException( algenfunc );
	}

	// Check buffers
	uint i;
	for ( i=0; i!=nb; i++ )
	{
		if ( ! altestfunc( array[i] ) )
		{
			ThrowGenException( algenfunc );
		}
	}
}

/*
 * Create a sound buffer
 */
IBuffer *CSoundDriverAL::createBuffer()
{
	CBufferAL *buffer = new CBufferAL(createItem(alGenBuffers, alIsBuffer, _Buffers, _NbExpBuffers, BUFFER_ALLOC_RATE));
	return buffer;
}


/*
 * Create a source
 */
ISource *CSoundDriverAL::createSource()
{
	CSourceAL *sourceal = new CSourceAL(createItem(alGenSources, alIsSource, _Sources, _NbExpSources, SOURCE_ALLOC_RATE));
	if ( _RolloffFactor != ROLLOFF_FACTOR_DEFAULT )
	{
		alSourcef(sourceal->sourceName(), AL_ROLLOFF_FACTOR, _RolloffFactor);
	}
	return sourceal;
}

/// Create a reverb effect
IReverbEffect *CSoundDriverAL::createReverbEffect()
{
	IReverbEffect *ieffect = NULL;
	CEffectAL *effectal = NULL;
	
	ALuint slot = AL_NONE;
	alGenAuxiliaryEffectSlots(1, &slot);
	if (alGetError() != AL_NO_ERROR)
	{
		nlwarning("AL: alGenAuxiliaryEffectSlots failed");
		return NULL;
	}
	
	ALuint effect = AL_NONE;
	alGenEffects(1, &effect);
	if (alGetError() != AL_NO_ERROR)
	{
		nlwarning("AL: alGenEffects failed");
		alDeleteAuxiliaryEffectSlots(1, &slot);
		return NULL; /* createEffect */
	}

#if EFX_CREATIVE_AVAILABLE
	alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
	if (alGetError() != AL_NO_ERROR)
	{
		nlinfo("AL: Creative Reverb Effect not supported, falling back to standard Reverb Effect");
	}
	else
	{
		alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, effect); alTestError();
		alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_AUXILIARY_SEND_AUTO, AL_TRUE); alTestError(); // auto only for reverb!
		CCreativeReverbEffectAL *eff = new CCreativeReverbEffectAL(this, effect, slot);
		ieffect = static_cast<IReverbEffect *>(eff);
		effectal = static_cast<CEffectAL *>(eff);
		nlassert(ieffect); nlassert(effectal);
		_Effects.insert(effectal);
		return ieffect;
	}
#endif		

	alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
	if (alGetError() != AL_NO_ERROR)
	{
		nlwarning("AL: Reverb Effect not supported");
		alDeleteAuxiliaryEffectSlots(1, &slot);
		alDeleteEffects(1, &effect);
		return NULL; /* createEffect */
	}
	else
	{
		alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, effect); alTestError();
		alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_AUXILIARY_SEND_AUTO, AL_TRUE); alTestError(); // auto only for reverb!
		CStandardReverbEffectAL *eff = new CStandardReverbEffectAL(this, effect, slot);
		ieffect = static_cast<IReverbEffect *>(eff);
		effectal = static_cast<CEffectAL *>(eff);
		nlassert(ieffect); nlassert(effectal);
		_Effects.insert(effectal);
		return ieffect;
	}
}

/// Return the maximum number of sources that can created
uint CSoundDriverAL::countMaxSources()
{
	// software allows 256 sources (software audio ftw!)
	// cheap openal cards 32, expensive openal cards 128
	// trying to go too high is safely handled anyways
	return 128;
}

/// Return the maximum number of effects that can be created, which is only 1 in openal software mode :(
uint CSoundDriverAL::countMaxEffects()
{
	if (!getOption(OptionEnvironmentEffects)) return 0;
	if (!AlExtEfx) return 0;
	ALCint max_auxiliary_sends;
	alcGetIntegerv(_AlDevice, ALC_MAX_AUXILIARY_SENDS, 1, &max_auxiliary_sends);
	return (uint)max_auxiliary_sends;
}

/*
 * Create a sound buffer or a sound source
 */
ALuint CSoundDriverAL::createItem(TGenFunctionAL algenfunc, TTestFunctionAL altestfunc,
								  vector<ALuint>& names, uint& index, uint allocrate)
{
	nlassert( index <= names.size() );
	if ( index == names.size() )
	{
		// Generate new items
		uint nbalive = compactAliveNames( names, altestfunc );
		if ( nbalive == names.size() )
		{
			// Extend vector of names
			// FIXME? assumption about inner workings of std::vector
			allocateNewItems( algenfunc, altestfunc, names, index, allocrate );
		}
		else
		{
			// Take the room of the deleted names
			nlassert(nbalive < names.size());
			index = nbalive;
			// FIXME assumption about inner workings of std::vector;
			// &(names[...]) only works with "names.size() - nbalive == 1"
			generateItems(algenfunc, altestfunc, names.size() - nbalive, &(names[nbalive]));
		}
	}

	// Return the name of the item
	nlassert( index < names.size() );
	ALuint itemname = names[index];
	index++;
	return itemname;
}


/*
 * Remove names of deleted buffers and return the number of valid buffers
 */
uint CSoundDriverAL::compactAliveNames( vector<ALuint>& names, TTestFunctionAL altestfunc )
{
	vector<ALuint>::iterator iball, ibcompacted;
	for ( iball=names.begin(), ibcompacted=names.begin(); iball!=names.end(); ++iball )
	{
		// iball is incremented every iteration
		// ibcompacted is not incremented if a buffer is not valid anymore
		if ( altestfunc( *iball ) )
		{
			*ibcompacted = *iball;
			++ibcompacted;
		}
	}
	nlassert( ibcompacted <= names.end() );
	return ibcompacted - names.begin();
}


/// Remove a buffer
void CSoundDriverAL::removeBuffer(CBufferAL *buffer)
{
	nlassert(buffer != NULL);
	if (!deleteItem( buffer->bufferName(), alDeleteBuffers, _Buffers))
		nlwarning("AL: Deleting buffer: name not found");
}

/// Remove a source
void CSoundDriverAL::removeSource(CSourceAL *source)
{
	nlassert(source != NULL);
	if (!deleteItem( source->sourceName(), alDeleteSources, _Sources))
		nlwarning("AL: Deleting source: name not found");
}

/// Remove an effect
void CSoundDriverAL::removeEffect(CEffectAL *effect)
{
	nlassert(effect != NULL);

	set<CEffectAL *>::iterator it = _Effects.find(effect);
	if (it == _Effects.end()) 
		{ nlwarning("AL: Deleting effect: name not found"); return; }

	ALuint slotname = effect->getAuxEffectSlot();
	ALuint effectname = effect->getAlEffect();
	alDeleteAuxiliaryEffectSlots(1, &slotname);
	alDeleteEffects(1, &effectname);
	_Effects.erase(it);
}


/*
 * Delete a buffer or a source
 */
bool CSoundDriverAL::deleteItem( ALuint name, TDeleteFunctionAL aldeletefunc, vector<ALuint>& names )
{
	vector<ALuint>::iterator ibn = find( names.begin(), names.end(), name );
	if ( ibn == names.end() )
	{
		return false;
	}
	aldeletefunc( 1, &*ibn );
	*ibn = AL_NONE;
	alTestError();
	return true;
}


/*
 * Create the listener instance
 */
IListener		*CSoundDriverAL::createListener()
{
	nlassert(!CListenerAL::isInitialized());
	return new CListenerAL();
}


/*
 * Apply changes of rolloff factor to all sources
 */
void			CSoundDriverAL::applyRolloffFactor( float f )
{
	_RolloffFactor = f;
	vector<ALuint>::iterator ibn;
	for ( ibn=_Sources.begin(); ibn!=_Sources.end(); ++ibn )
	{
		alSourcef( *ibn, AL_ROLLOFF_FACTOR, _RolloffFactor );
	}
	alTestError();
}


/*
 * Helper for loadWavFile()
 */
TSampleFormat ALtoNLSoundFormat( ALenum alformat )
{
	switch ( alformat )
	{
	case AL_FORMAT_MONO8 : return Mono8;
	case AL_FORMAT_MONO16 : return Mono16;
	case AL_FORMAT_STEREO8 : return Stereo8;
	case AL_FORMAT_STEREO16 : return Stereo16;
	default : nlstop; return Mono8;
	}
}


/*
 * Temp
 */
bool CSoundDriverAL::loadWavFile(IBuffer * /* destbuffer */, const char * /* filename */)
{
/*	ALsizei size,freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop;
	alutLoadWAVFile( const_cast<char*>(filename), &format, &data, &size, &freq, &loop ); // last arg in some al.h
	if ( data == NULL )
		return false;
	nldebug("AL:   format after load = %x", (uint)format);

	destbuffer->setFormat( ALtoNLSoundFormat(format), freq );
	destbuffer->fillBuffer( data, size );

	string ext = CFile::getFilenameWithoutExtension(filename);
// TODO	static_cast<CBufferAL*>(destbuffer)->setName(ext);

	alutUnloadWAV(format,data,size,freq); // Where is it on Linux ?!?
	return true;
	*/
	return false;
}

/*
 * loads a memory mapped .wav-file into the given buffer
 */
bool CSoundDriverAL::readWavBuffer(IBuffer * /* destbuffer */, const std::string & /* name */, uint8 * /* wavData */, uint /* dataSize */) 
{
	/*
	ALenum format;
	ALsizei size;
	ALfloat frequency;
	ALvoid *sampleData;

	// FIXME check for correct buffer name
	sampleData = alutLoadMemoryFromFileImage ((ALvoid *)wavData, (ALsizei)dataSize,
                                              &format, &size, &frequency);
    destbuffer->setFormat(ALtoNLSoundFormat(format), (uint)frequency);
    destbuffer->fillBuffer((void*)sampleData, (uint32)size);
    free(sampleData);
    return true;
	*/
	return false;
}

bool CSoundDriverAL::readRawBuffer(IBuffer *destbuffer, const std::string & /* name */, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	nlassert(destbuffer != NULL);
	nlassert(rawData != NULL);
	if (dataSize == 0) {// ???
		nlwarning("AL: CSoundDriverAL::readRawBuffer() -- dataSize == 0");
		return true;
	}
	// FIXME check for correct buffer name
	destbuffer->setFormat(format, (uint)frequency);
	destbuffer->fill(rawData, dataSize);
	return true;
}

} // NLSOUND
