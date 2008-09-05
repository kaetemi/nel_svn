/**
 * \file sound_driver_xaudio2.cpp
 * \brief CSoundDriverXAudio2
 * \date 2008-08-20 10:52GMT
 * \author Jan Boon (Kaetemi)
 * CSoundDriverXAudio2
 * 
 * $Id$
 */

/* 
 * Copyright (C) 2008  Jan Boon (Kaetemi)
 * 
 * This file is part of NLSOUND XAudio2 Driver.
 * NLSOUND XAudio2 Driver is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 * 
 * NLSOUND XAudio2 Driver is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NLSOUND XAudio2 Driver; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */

/*
 * TODO:
 *  - Profile
 *    - writeProfile
 *  - Bench
 *    - startBench
 *    - endBench
 *    - displayBench
 */

#include "stdxaudio2.h"
#include "sound_driver_xaudio2.h"

// STL includes
#include <cmath>

// NeL includes
#include <nel/misc/debug.h>
#include <nel/misc/hierarchical_timer.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/dynloadlib.h>
#include <nel/misc/command.h>
#include "../sound_driver.h"
#include "music_buffer.h" // ../

// Project includes
#include "listener_xaudio2.h"
#include "source_xaudio2.h"
#include "music_channel_xaudio2.h"
#include "eax_xaudio2.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

// ******************************************************************

#ifndef NL_STATIC
class CSoundDriverXAudio2NelLibrary : public NLMISC::INelLibrary { 
	void onLibraryLoaded(bool firstTime) { } 
	void onLibraryUnloaded(bool lastTime) { }  
};
NLMISC_DECL_PURE_LIB(CSoundDriverXAudio2NelLibrary)

HINSTANCE CSoundDriverXAudio2DllHandle = NULL;
BOOL WINAPI DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	CSoundDriverXAudio2DllHandle = (HINSTANCE)hModule;
	return TRUE;
}
#endif /* #ifndef NL_STATIC */

// ***************************************************************************

#ifdef NL_STATIC
ISoundDriver* createISoundDriverInstance
#else
__declspec(dllexport) ISoundDriver *NLSOUND_createISoundDriverInstance
#endif
	(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer)
{
	CSoundDriverXAudio2 *driver = new CSoundDriverXAudio2(useEax, stringMapper, forceSoftwareBuffer);
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
	// -- CSoundDriverXAudio2::instance()->writeProfile(out);
}

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver::TDriver getDriverType()
#else
__declspec(dllexport) ISoundDriver::TDriver NLSOUND_getDriverType()
#endif
{
	return ISoundDriver::DriverXAudio2;
}

// ******************************************************************

#ifdef NL_DEBUG

static XAUDIO2_DEBUG_CONFIGURATION NLSOUND_XAUDIO2_DEBUG_CONFIGURATION_DISABLED = {
  0, 0, true, true, true, true
};

NLMISC_CATEGORISED_COMMAND(nel, xa2DebugDisable, "", "")
{
	CSoundDriverXAudio2::getInstance()->getXAudio2()->SetDebugConfiguration(&NLSOUND_XAUDIO2_DEBUG_CONFIGURATION_DISABLED);
	return true;
}

static XAUDIO2_DEBUG_CONFIGURATION NLSOUND_XAUDIO2_DEBUG_CONFIGURATION_HEAVY = {
  ~XAUDIO2_LOG_FUNC_CALLS & ~XAUDIO2_LOG_LOCKS & ~XAUDIO2_LOG_MEMORY, 0, true, true, true, true
};

NLMISC_CATEGORISED_COMMAND(nel, xa2DebugHeavy, "", "")
{
	CSoundDriverXAudio2::getInstance()->getXAudio2()->SetDebugConfiguration(&NLSOUND_XAUDIO2_DEBUG_CONFIGURATION_HEAVY);
	return true;
}

#endif /* NL_DEBUG */

#if !FINAL_VERSION

NLMISC_CATEGORISED_COMMAND(nel, setEaxEnvironment, "Set the id and size of the eax environment", "<id> <size>")
{
	if (args.size() != 2) return false;
	CSoundDriverXAudio2::getInstance()->getListener()->setEnvironment((uint)atoi(args[0].c_str()), (float)atoi(args[0].c_str()));
	return true;
}

NLMISC_CATEGORISED_COMMAND(nel, enableEaxEnvironment, "Enable eax environment effect", "")
{
	CSoundDriverXAudio2::getInstance()->getListener()->getReverbVoice()->SetVolume(1.0f);
	return true;
}

NLMISC_CATEGORISED_COMMAND(nel, disableEaxEnvironment, "Disable eax environment effect", "")
{
	CSoundDriverXAudio2::getInstance()->getListener()->getReverbVoice()->SetVolume(0.0f);
	return true;
}

#endif /* !FINAL_VERSION */

// ******************************************************************

CSoundDriverXAudio2::CSoundDriverXAudio2(bool useEax, 
	ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer) 
	: _StringMapper(stringMapper), _XAudio2(NULL), _MasteringVoice(NULL), 
	_SoundDriverOk(false), _CoInitOk(false), _Listener(NULL), _UseEax(useEax)
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Initializing CSoundDriverXAudio2");

	// Initializes EAX environment presets if not initialized yet.
	if (useEax) CEaxXAudio2::init();

	HRESULT hr;

	memset(&_X3DAudioHandle, 0, sizeof(_X3DAudioHandle));
	memset(&_DSPSettings, 0, sizeof(_DSPSettings));
	memset(&_EmptyListener, 0, sizeof(_EmptyListener));

	_EmptyListener.OrientFront.x = 0.0f;
	_EmptyListener.OrientFront.y = 0.0f;
	_EmptyListener.OrientFront.z = 1.0f;
	_EmptyListener.OrientTop.x = 0.0f;
	_EmptyListener.OrientTop.y = 1.0f;
	_EmptyListener.OrientTop.z = 0.0f;
	_EmptyListener.Position.x = 0.0f;
	_EmptyListener.Position.y = 0.0f;
	_EmptyListener.Position.z = 0.0f;
	_EmptyListener.Velocity.x = 0.0f;
	_EmptyListener.Velocity.y = 0.0f;
	_EmptyListener.Velocity.z = 0.0f;

	// Windows
#ifdef NL_OS_WINDOWS // CoInitializeEx not on xbox, lol
	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))"); return; }
	_CoInitOk = true;
#endif

	uint32 flags = 0;
#ifdef NL_DEBUG
	flags |= XAUDIO2_DEBUG_ENGINE; // comment when done using this :)
#endif

	// XAudio2
	if (FAILED(hr = XAudio2Create(&_XAudio2, flags, XAUDIO2_DEFAULT_PROCESSOR)))
		{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "XAudio2 failed to initialize. Please install the latest version of the DirectX End-User Runtimes."); return; }
	if (FAILED(hr = _XAudio2->CreateMasteringVoice(&_MasteringVoice, 0, 44100, 0, 0, NULL)))
		{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "FAILED CreateMasteringVoice _MasteringVoice!"); return; }
	
	// X3DAudio
	// speed of sound in meters per second for dry air at approximately 20C, used with X3DAudioInitialize
	// #define X3DAUDIO_SPEED_OF_SOUND 343.5f
	// todo replace SPEAKER_STEREO
	X3DAudioInitialize(SPEAKER_STEREO, X3DAUDIO_SPEED_OF_SOUND, _X3DAudioHandle);
	XAUDIO2_VOICE_DETAILS voice_details;
	_MasteringVoice->GetVoiceDetails(&voice_details);
	_DSPSettings.SrcChannelCount = 1; // ?! // number of channels in the emitter
	_DSPSettings.DstChannelCount = voice_details.InputChannels; // ?! // how many speakers do you have
	_DSPSettings.pMatrixCoefficients = new FLOAT32[_DSPSettings.SrcChannelCount * _DSPSettings.DstChannelCount];

	// Time
	_LastTime = NLMISC::CTime::getLocalTime();

	_SoundDriverOk = true;
}

CSoundDriverXAudio2::~CSoundDriverXAudio2()
{
	release();
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Destroying CSoundDriverXAudio2");
}

#define NLSOUND_XAUDIO2_RELEASE(pointer) if (_SoundDriverOk) nlassert(pointer) \
	/*if (pointer) {*/ delete pointer; pointer = NULL; /*}*/
#define NLSOUND_XAUDIO2_RELEASE_EX(pointer, command) if (_SoundDriverOk) nlassert(pointer) \
	if (pointer) { command; pointer = NULL; }
void CSoundDriverXAudio2::release()
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Releasing CSoundDriverXAudio2");

	// Driver (listeners etc todo)
	// Stop any played music
	{
		set<CMusicChannelXAudio2 *>::iterator it(_MusicChannels.begin()), end(_MusicChannels.end());
		for (; it != end; ++it)
		{
			nlwarning("CMusicChannelXAudio2 was not deleted by user, deleting now!");
			delete *it;
		}
		_MusicChannels.clear();
	}
	// Assure that the remaining sources have released all their channels before closing
	{
		set<CSourceXAudio2*>::iterator it(_SourceChannels.begin()), end(_SourceChannels.end());
		for (; it != end; ++it)
		{
			(*it)->release(); // WARNING: The sources are NOT DELETED automagically!
		}
	}
	// Stop the listener
	if (_Listener) _Listener->release(); // LISTENER AND SOURCES DELETED AT NLSOUND USER LEVEL

	// X3DAudio
	NLSOUND_XAUDIO2_RELEASE(_DSPSettings.pMatrixCoefficients);

	// XAudio2
	NLSOUND_XAUDIO2_RELEASE_EX(_MasteringVoice, _MasteringVoice->DestroyVoice());
	NLSOUND_XAUDIO2_RELEASE_EX(_XAudio2, _XAudio2->Release());
	_SoundDriverOk = false;

	// Windows
#ifdef NL_OS_WINDOWS
	if (_CoInitOk) CoUninitialize();
	_CoInitOk = false;
#else
	nlassert(!_CoInitOk);
#endif
}

///** Set the gain (volume value inside [0 , 1]). (default: 1)
// * 0.0 -> silence
// * 0.5 -> -6dB
// * 1.0 -> no attenuation
// * values > 1 (amplification) not supported by most drivers
// */
//void CSoundDriverXAudio2::setGain(float gain)
//{
//	_MasteringVoice->SetVolume(gain);
//}
//
///// Get the gain
//float CSoundDriverXAudio2::getGain() const
//{
//	float gain;
//	_MasteringVoice->GetVolume(&gain);
//	return gain;
//}

/// Create a sound buffer
IBuffer *CSoundDriverXAudio2::createBuffer()
{
	return new CBufferXAudio2();
}

/// Create the listener instance
IListener *CSoundDriverXAudio2::createListener()
{
	if (!_Listener) _Listener = new CListenerXAudio2(this);
	return static_cast<IListener *>(_Listener);
}

/// Return the maximum number of sources that can created
uint CSoundDriverXAudio2::countMaxSources()
{
	return 512; // there is no real limit, but this should be pretty heavy
}

/// Create a source
ISource *CSoundDriverXAudio2::createSource()
{
	CSourceXAudio2* src = new CSourceXAudio2(this);
	_SourceChannels.insert(src);
	return static_cast<ISource *>(src);
}

/// Read a WAV data in a buffer (format supported: Mono16, Mono8, Stereo16, Stereo8)
bool CSoundDriverXAudio2::readWavBuffer(IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize)
{
	return ((CBufferXAudio2 *)destbuffer)->readWavBuffer(name, wavData, dataSize);
}

/// FMod driver Note: ADPCM format are converted and stored internally in Mono16 format (hence IBuffer::getFormat() return Mono16)
bool CSoundDriverXAudio2::readRawBuffer(IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	return ((CBufferXAudio2 *)destbuffer)->readRawBuffer(name, rawData, dataSize, format, frequency);
}

/// Commit all the changes made to 3D settings of listener and sources
void CSoundDriverXAudio2::commit3DChanges()
{
	TTime current_time = NLMISC::CTime::getLocalTime();
	TTime delta_time = current_time - _LastTime;
	float dtf = ((float)delta_time) / 1000.f;
	// Sync up sources & listener 3d position.
	{
		std::set<CSourceXAudio2 *>::iterator it(_SourceChannels.begin()), end(_SourceChannels.end());
		for (; it != end; ++it) { (*it)->update(); (*it)->commit3DChanges(); }
	}
	//// Update music faders
	//{
	//	std::set<CMusicChannelXAudio2 *>::iterator it(_MusicChannels.begin()), end(_MusicChannels.end());
	//	for (; it != end; ++it) (*it)->update(dtf);
	//}
	_LastTime = current_time;
}

/// Write information about the driver to the output stream.
void CSoundDriverXAudio2::writeProfile(std::string& out)
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	out = NLSOUND_XAUDIO2_NAME "\n---\nlalalalalaaaa";
	return;
}

// Does not create a sound loader .. what does it do then?
void CSoundDriverXAudio2::startBench()
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return;
}

void CSoundDriverXAudio2::endBench()
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return;
}

void CSoundDriverXAudio2::displayBench(NLMISC::CLog *log)
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return;
}

/// Create a music channel
IMusicChannel *CSoundDriverXAudio2::createMusicChannel()
{
	CMusicChannelXAudio2 *music_channel = new CMusicChannelXAudio2(this);
	_MusicChannels.insert(music_channel);
	return static_cast<IMusicChannel *>(music_channel);
}

/// Destroy a music channel
void CSoundDriverXAudio2::destroyMusicChannel(IMusicChannel *musicChannel)
{
	_MusicChannels.erase(static_cast<CMusicChannelXAudio2 *>(musicChannel));
	delete musicChannel;
}

/** Get music info. Returns false if the song is not found or the function is not implemented. 
 *  If the song has no name, result is filled with the filename.
 *  \param filepath path to file, CPath::lookup done by driver
 *  \param artist returns the song artist (empty if not available)
 *  \param title returns the title (empty if not available)
 */
bool CSoundDriverXAudio2::getMusicInfo(const std::string &filepath, std::string &artist, std::string &title)
{
	// add support for additional non-standard music file types info here
	return IMusicBuffer::getInfo(filepath, artist, title);
}

///** Play some music syncrhonously (.ogg etc...) (implemented in fmod only)
// *	FMOD: The File is loaded synchronously in memory, but decompressed by FMod in a thread
// *	Hence if the ogg fileSize is 5 Mb, it will take only 5 Mb in memory (not the decompressed 40 Mb size)
// *	NB: if an old music was played, it is first stop with stopMusic()
// *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
// *	\param CIFile opened file (must use a CIFile if for instance you want to load from a BNP, and CBigFile is static....)
// *	\param xFadeTime if not 0 the old music played is not stoped imediatly but a cross-fade of xFadeTime (in ms) is made between the 2.
// */
//bool CSoundDriverXAudio2::playMusic(uint channel, NLMISC::CIFile &file, uint xFadeTime, bool loop)
//{
//	//_MusicChannels[channel]->play(file, xFadeTime, loop);
//	//return true; // todo
//	return false;
//}
//
///** Play some music asynchronously (.ogg etc...) (implemented in fmod only)
// *	FMOD: the file is load asynchronously
// *	NB: if an old music was played, it is first stop with stopMusic()
// *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently	 *	\param path full file path (no CPath::lookup is done since static)
// *	\param xFadeTime if not 0 the old music played is not stoped imediatly but a cross-fade of xFadeTime (in ms) is made between the 2.
// *	\param fileOffset and fileSize: if not 0, use it to load a .ogg that reside in a BNP. 
// *		the offset and size have to be retrieved with CBigFile methods. 
// *		e.g.: use either 
// *			playMusicAsync("C:/test/mymusic.ogg");
// *		or
// * 			playMusicAsync("C:/test/mydata.bnp", offsetOfOggInBnp, sizeOfOggInBnp);
// *		Notice that you must give the full path of the bnp (eg: "C:/test/mydata.bnp") in path.
// *	\param loop must be true to play the music in loop. 
// */
//bool CSoundDriverXAudio2::playMusicAsync(uint channel, const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop)
//{
//	//if (!CFile::fileExists(path)) { _MusicChannels[channel]->stop(xFadeTime); return false; }
//
//	//_MusicChannels[channel]->play(path, xFadeTime, fileOffset, fileSize, loop);
//	//return true;
//	return false;
//}
//
///** Get the song title. Returns false if the song is not found or the function is not implemented. 
// * If the song as no name, result is filled with the filename.
// */
//bool CSoundDriverXAudio2::getSongTitle(const std::string &filename, std::string &result, uint fileOffset, uint fileSize)
//{
//	std::string filepath = CPath::lookup(filename, false);
//	if (!CFile::fileExists(filepath)) return false;
//	
//	CIFile *ifile = new CIFile(filepath);
//	ifile->seek(fileOffset, NLMISC::IStream::begin);
//	bool res = IMusicBuffer::getSongTitle(CFile::getFilename(filepath), ifile, result);
//	delete ifile;
//	return res;
//}

/// Remove a buffer (should be called by the friend destructor of the buffer class)
void CSoundDriverXAudio2::removeBuffer(IBuffer *buffer)
{
	// does nothing here .. see createBuffer
}

/// Remove a source (should be called by the friend destructor of the source class)
void CSoundDriverXAudio2::removeSource(ISource *source)
{
	if (_SourceChannels.find((CSourceXAudio2 *)source) != _SourceChannels.end())
		_SourceChannels.erase((CSourceXAudio2 *)source); // note: IT DOESN'T DELETE
	else nlwarning("removeSource already called");
	// SOURCE ARE DELETED IN CTrack / mixing_track.h ...
	// -> use delete to call this function ^^'
}

} /* namespace NLSOUND */

/* end of file */
