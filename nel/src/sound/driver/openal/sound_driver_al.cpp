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

#include "buffer_al.h"
#include "listener_al.h"
#include "nel/misc/path.h"
#include "nel/misc/dynloadlib.h"
#include "../sound_driver.h"

using namespace std;
using namespace NLMISC;


namespace NLSOUND {


#if EAX_AVAILABLE == 1
// EAXSet global function
EAXSet					EAXSetProp = NULL;

// EAXGet global function
EAXGet					EAXGetProp = NULL;
#endif


// Currently, the OpenAL headers are different between Windows and Linux versions !
// AL_INVALID_XXXX are part of the spec, though.
/*#ifdef NL_OS_UNIX
#define AL_INVALID_ENUM AL_ILLEGAL_ENUM
#define AL_INVALID_OPERATION AL_ILLEGAL_COMMAND
#endif*/


#ifdef NL_DEBUG
// Test error in debug mode
void TestALError()
{
	ALuint errcode = alGetError();
	switch( errcode )
	{
	case AL_NO_ERROR : break;
	case AL_INVALID_NAME : nlerror( "OpenAL: Invalid name" );
	case AL_INVALID_ENUM  : nlerror( "OpenAL: Invalid enum" );
	case AL_INVALID_VALUE  : nlerror( "OpenAL: Invalid value" );
	case AL_INVALID_OPERATION  : nlerror( "OpenAL: Invalid operation" );
	case AL_OUT_OF_MEMORY  : nlerror( "OpenAL: Out of memory" );
	// alGetString( errcode ) seems to fail !
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
	void onLibraryLoaded(bool firstTime) { }
	void onLibraryUnloaded(bool lastTime) { }
};
NLMISC_DECL_PURE_LIB(CSoundDriverALNelLibrary)

#endif /* #ifndef NL_STATIC */

/*
 * Sound driver instance creation
 */
#ifdef NL_OS_WINDOWS

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver* createISoundDriverInstance
#else
__declspec(dllexport) ISoundDriver *NLSOUND_createISoundDriverInstance
#endif
	(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer)
{
	CSoundDriverAL *driver = new CSoundDriverAL();
	driver->init();
	return driver;
}

// ******************************************************************

#ifdef NL_STATIC
uint32 interfaceVersion()
#else
__declspec(dllexport) uint32 NLSOUND_interfaceVersion()
#endif
{
	return ISoundDriver::InterfaceVersion;
}

// ******************************************************************

#ifdef NL_STATIC
void outputProfile
#else
__declspec(dllexport) void NLSOUND_outputProfile
#endif
	(string &out)
{
	CSoundDriverAL::instance()->writeProfile(out);
}

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver::TDriver getDriverType()
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
ISoundDriver* NLSOUND_createISoundDriverInstance (bool useEax)
{
	CSoundDriverAL *driver = new CSoundDriverAL();
	driver->init();
	return driver;
}

uint32 NLSOUND_interfaceVersion ()
{
	return ISoundDriver::InterfaceVersion;
}
}

#endif // NL_OS_UNIX


// The instance of the singleton
CSoundDriverAL	*CSoundDriverAL::_Instance = NULL;


/*
 * Constructor
 */
CSoundDriverAL::CSoundDriverAL() :
	ISoundDriver(), _NbExpBuffers( 0 ), _NbExpSources( 0 ), _RolloffFactor( 1.0f )
{
	if ( _Instance == NULL )
	{
		_Instance = this;
	}
	else
	{
		nlerror( "Sound driver singleton instanciated twice" );
	}
}


/*
 * Destructor
 */
CSoundDriverAL::~CSoundDriverAL()
{
	// Remove the allocated (but not exported) source and buffer names
	alDeleteSources(compactAliveNames( _Sources, alIsSource ), &*_Sources.begin());
	alDeleteBuffers(compactAliveNames( _Buffers, alIsBuffer ), &*_Buffers.begin());

	// OpenAL exit
	alutExit();

	_Instance = NULL;
}


/*
 * Initialization
 */
bool CSoundDriverAL::init()
{
	// OpenAL initialization
	alutInit( NULL, NULL );

	// Display version information
	const ALchar *alversion, *alrenderer, *alvendor, *alext;
	alversion = alGetString( AL_VERSION );
	alrenderer = alGetString( AL_RENDERER );
	alvendor = alGetString( AL_VENDOR );
	alext = alGetString( AL_EXTENSIONS );
	TestALError();
	nlinfo( "Loading OpenAL lib: %s, %s, %s", alversion, alrenderer, alvendor );
	nlinfo( "Listing extensions: %s", alext );

#if EAX_AVAILABLE == 1
    // Set EAX environment if EAX is available
	if ( alIsExtensionPresent((ALchar *)"EAX") == AL_TRUE ) // or EAX2.0
	{
		nlinfo( "Initializing EAX" );
	    EAXSetProp = (EAXSet)alGetProcAddress((ALchar*)"EAXSet");
		EAXGetProp = (EAXGet)alGetProcAddress((ALchar*)"EAXGet");
		if ( EAXSetProp != NULL )
		{
			unsigned long ulEAXVal;
			long lGlobalReverb;
		    lGlobalReverb = 0;
			EAXSetProp( &DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOM, 0, &lGlobalReverb, sizeof(unsigned long) );
			ulEAXVal = EAX_ENVIRONMENT_GENERIC;
			EAXSetProp( &DSPROPSETID_EAX_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, 0, &ulEAXVal, sizeof(unsigned long) );
		}
	}
	else
#endif
	{
		nlinfo( "EAX not available" );
	}

	// Choose the I3DL2 model (same as DirectSound3D)
	alDistanceModel( AL_INVERSE_DISTANCE_CLAMPED );
	TestALError();

	// Initial buffers and sources allocation
	allocateNewItems( alGenBuffers, alIsBuffer, _Buffers, _NbExpBuffers, INITIAL_BUFFERS );
	allocateNewItems( alGenSources, alIsSource, _Sources, _NbExpSources, INITIAL_SOURCES );

	return true;
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


/*
 * Remove a buffer
 */
void			CSoundDriverAL::removeBuffer( IBuffer *buffer )
{
	nlassert( buffer != NULL );
	CBufferAL *bufferAL = dynamic_cast<CBufferAL*>(buffer);
	if ( ! deleteItem( bufferAL->bufferName(), alDeleteBuffers, _Buffers ) )
	{
		nlwarning( "Deleting buffer: name not found" );
	}
}


/*
 * Remove a source
 */
void			CSoundDriverAL::removeSource( ISource *source )
{
	nlassert( source != NULL );
	CSourceAL *sourceAL = dynamic_cast<CSourceAL*>(source);
	if ( ! deleteItem( sourceAL->sourceName(), alDeleteSources, _Sources ) )
	{
		nlwarning( "Deleting source: name not found" );
	}
}


/*
 * Delete a buffer or a source
 */
bool			CSoundDriverAL::deleteItem( ALuint name, TDeleteFunctionAL aldeletefunc, vector<ALuint>& names )
{
	vector<ALuint>::iterator ibn = find( names.begin(), names.end(), name );
	if ( ibn == names.end() )
	{
		return false;
	}
	aldeletefunc( 1, &*ibn );
	*ibn = AL_NONE;
	TestALError();
	return true;
}


/*
 * Create the listener instance
 */
IListener		*CSoundDriverAL::createListener()
{
	nlassert( CListenerAL::instance() == NULL );
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
	TestALError();
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
bool CSoundDriverAL::loadWavFile(IBuffer *destbuffer, const char *filename)
{
	ALsizei size,freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop;
	alutLoadWAVFile( const_cast<char*>(filename), &format, &data, &size, &freq, &loop ); // last arg in some al.h
	if ( data == NULL )
		return false;
	nldebug("  format after load = %x", (uint)format);

	destbuffer->setFormat( ALtoNLSoundFormat(format), freq );
	destbuffer->fillBuffer( data, size );

	string ext = CFile::getFilenameWithoutExtension(filename);
// TODO	static_cast<CBufferAL*>(destbuffer)->setName(ext);

	alutUnloadWAV(format,data,size,freq); // Where is it on Linux ?!?
	return true;
}

/*
 * loads a memory mapped .wav-file into the given buffer
 */
bool CSoundDriverAL::readWavBuffer(IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize) {
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
}

bool CSoundDriverAL::readRawBuffer( IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	nlassert(destbuffer != NULL);
	nlassert(rawData != NULL);
	if (dataSize == 0) {// ???
		nlwarning("CSoundDriverAL::readRawBuffer() -- dataSize == 0");
		return true;
	}
	// FIXME check for correct buffer name
	destbuffer->setFormat(format, (uint)frequency);
	destbuffer->fillBuffer(rawData, dataSize);
	return true;
}

bool CSoundDriverAL::playMusic(uint channel, NLMISC::CIFile &file, uint xFadeTime, bool loop) {
	return false;
}

bool CSoundDriverAL::playMusicAsync(uint channel, const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop) {
	return false;
}

void CSoundDriverAL::stopMusic(uint channel, uint xFadeTime) {
}


void CSoundDriverAL::pauseMusic(uint channel) {
}


void CSoundDriverAL::resumeMusic(uint channel) {
}


bool CSoundDriverAL::getSongTitle(const std::string &filename, std::string &result, uint fileOffset, uint fileSize) {
	result = CFile::getFilenameWithoutExtension (filename);
	return true;
}


bool CSoundDriverAL::isMusicEnded(uint channel) {
	return true;
}


float CSoundDriverAL::getMusicLength(uint channel) {
	return 0.0f;
}


void CSoundDriverAL::setMusicVolume(uint channel, float gain) {
}

} // NLSOUND
