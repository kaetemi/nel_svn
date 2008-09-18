/**
 * \file sound_driver_xaudio2.cpp
 * \brief CSoundDriverXAudio2
 * \date 2008-08-20 10:52GMT
 * \author Jan Boon (Kaetemi)
 * CSoundDriverXAudio2
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
#include "submix_xaudio2.h"
#include "effect_xaudio2.h"

using namespace std;
using namespace NLMISC;

/// Sample rate for master voice (device).
/// Default (0) under windows is 44100 (CD) or 48000 (DVD). 
/// Note 1: OpenAL driver uses 22050 at the moment.
/// Note 2: 44100 seems to be the optimal value here.
#define NLSOUND_XAUDIO2_MASTER_SAMPLE_RATE 44100

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
ISoundDriver* createISoundDriverInstanceXAudio2
#else
__declspec(dllexport) ISoundDriver *NLSOUND_createISoundDriverInstance
#endif
	(ISoundDriver::IStringMapperProvider *stringMapper)
{
	return new CSoundDriverXAudio2(stringMapper);
}

// ******************************************************************

#ifdef NL_STATIC
uint32 interfaceVersionXAudio2()
#else
__declspec(dllexport) uint32 NLSOUND_interfaceVersion()
#endif
{
	return ISoundDriver::InterfaceVersion;
}

// ******************************************************************

#ifdef NL_STATIC
void outputProfileXAudio2
#else
__declspec(dllexport) void NLSOUND_outputProfile
#endif
	(string &out)
{
	CSoundDriverXAudio2::getInstance()->writeProfile(out);
}

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver::TDriver getDriverTypeXAudio2()
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

// ******************************************************************

CSoundDriverXAudio2::CSoundDriverXAudio2(ISoundDriver::IStringMapperProvider *stringMapper) 
	: _StringMapper(stringMapper), _XAudio2(NULL), _MasteringVoice(NULL), 
	_SoundDriverOk(false), _CoInitOk(false), _Listener(NULL), 
	_PerformanceCommit3DCounter(0), _PerformanceMono16ADPCMBufferSize(0), 
	_PerformanceMono16BufferSize(0), _PerformanceMono8BufferSize(0), 
	_PerformanceMusicPlayCounter(0), _PerformanceSourcePlayCounter(0), 
	_PerformanceStereo16BufferSize(0), _PerformanceStereo8BufferSize(0)
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Creating CSoundDriverXAudio2");

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
	
	HRESULT hr;

	// Windows
#ifdef NL_OS_WINDOWS // CoInitializeEx not on xbox, lol
	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))"); return; }
	_CoInitOk = true;
#endif
}

CSoundDriverXAudio2::~CSoundDriverXAudio2()
{
	release();

	// Windows
#ifdef NL_OS_WINDOWS
	if (_CoInitOk) CoUninitialize();
	_CoInitOk = false;
#else
	nlassert(!_CoInitOk);
#endif

	nlwarning(NLSOUND_XAUDIO2_PREFIX "Destroying CSoundDriverXAudio2");
}

#define NLSOUND_XAUDIO2_RELEASE(pointer) if (_SoundDriverOk) nlassert(pointer) \
	/*if (pointer) {*/ delete pointer; pointer = NULL; /*}*/
#define NLSOUND_XAUDIO2_RELEASE_EX(pointer, command) if (_SoundDriverOk) nlassert(pointer) \
	if (pointer) { command; pointer = NULL; }
void CSoundDriverXAudio2::release()
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Releasing CSoundDriverXAudio2");

	// WARNING: Only internal resources are released here, 
	// the created instances must still be released by the user!

	// Release internal resources of all remaining IMusicChannel instances
	{
		set<CMusicChannelXAudio2 *>::iterator it(_MusicChannels.begin()), end(_MusicChannels.end());
		for (; it != end; ++it) (*it)->release();
		_MusicChannels.clear();
	}
	// Release internal resources of all remaining ISource instances
	{
		set<CSourceXAudio2 *>::iterator it(_Sources.begin()), end(_Sources.end());
		for (; it != end; ++it) (*it)->release();
		_Sources.clear();
	}
	// Release internal resources of all remaining IBuffer instances
	{
		set<CBufferXAudio2 *>::iterator it(_Buffers.begin()), end(_Buffers.end());
		for (; it != end; ++it) (*it)->release();
		_Buffers.clear();
	}
	// Release internal resources of all remaining ISubmix instances
	{
		set<CSubmixXAudio2 *>::iterator it(_Submixes.begin()), end(_Submixes.end());
		for (; it != end; ++it) (*it)->release();
		_Submixes.clear();
	}
	// Release internal resources of all remaining IEffect instances
	{
		set<IEffect *>::iterator it(_Effects.begin()), end(_Effects.end());
		for (; it != end; ++it) releaseEffect(*it);
		_Effects.clear();
	}
	// Release internal resources of the IListener instance
	if (_Listener) { _Listener->release(); _Listener = NULL; }

	// X3DAudio
	NLSOUND_XAUDIO2_RELEASE(_DSPSettings.pMatrixCoefficients);

	// XAudio2
	NLSOUND_XAUDIO2_RELEASE_EX(_MasteringVoice, _MasteringVoice->DestroyVoice());
	NLSOUND_XAUDIO2_RELEASE_EX(_XAudio2, _XAudio2->Release());
	_SoundDriverOk = false;
}

/// Return a list of available devices for the user. If the result is empty, you should use the default device.
// ***todo*** void CSoundDriverXAudio2::getDevices(std::vector<std::string> &devices) { }

/// Initialize the driver with a user selected device. If device.empty(), the default or most appropriate device is used.
void CSoundDriverXAudio2::init(std::string device, TSoundOptions options)
{
	nlwarning(NLSOUND_XAUDIO2_PREFIX "Initializing CSoundDriverXAudio2");

	// set the options: always use software buffer, always have local copy
	_Options = options;
	_Options = (TSoundOptions)((uint)_Options | OptionSoftwareBuffer);
	_Options = (TSoundOptions)((uint)_Options | OptionLocalBufferCopy);

	HRESULT hr;

	uint32 flags = 0;
#ifdef NL_DEBUG
	flags |= XAUDIO2_DEBUG_ENGINE; // comment when done using this :)
#endif

	// XAudio2
	if (FAILED(hr = XAudio2Create(&_XAudio2, flags, XAUDIO2_DEFAULT_PROCESSOR)))
		{ release(); throw ESoundDriver(NLSOUND_XAUDIO2_PREFIX "XAudio2 failed to initialize. Please install the latest version of the DirectX End-User Runtimes."); return; }
	if (FAILED(hr = _XAudio2->CreateMasteringVoice(&_MasteringVoice, 0, NLSOUND_XAUDIO2_MASTER_SAMPLE_RATE, 0, 0, NULL)))
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

	_SoundDriverOk = true;
}

/// Return options that are enabled (including those that cannot be disabled on this driver).
ISoundDriver::TSoundOptions CSoundDriverXAudio2::getOptions()
{
	return _Options;
}

/// Return if an option is enabled (including those that cannot be disabled on this driver).
bool CSoundDriverXAudio2::getOption(ISoundDriver::TSoundOptions option)
{
	return ((uint)_Options & (uint)option) == (uint)option;
}

/// Tell sources without voice about a format
void CSoundDriverXAudio2::initSourcesFormat(TSampleFormat format)
{
	std::set<CSourceXAudio2 *>::iterator it(_Sources.begin()), end(_Sources.end());
	for (; it != end; ++it) { if (!(*it)->getSourceVoice()) { (*it)->initFormat(format); } }
}

/// (Internal) Create an XAudio2 source voice of the specified format.
IXAudio2SourceVoice *CSoundDriverXAudio2::createSourceVoice(TSampleFormat format, IXAudio2VoiceCallback *callback)
{
	nlassert(_Listener);

	HRESULT hr;

	WAVEFORMATEX wfe;
	wfe.cbSize = 0;

	nlassert(format == Mono16 || format == Mono16ADPCM || format == Mono16 || format == Stereo16 || format == Stereo8);

	wfe.wFormatTag = WAVE_FORMAT_PCM;

	wfe.nChannels = (format == Mono16 || format == Mono16ADPCM || format == Mono8)
		? 1
		: 2;
	wfe.wBitsPerSample = (format == Mono8 || format == Stereo8)
		? 8
		: 16;

	XAUDIO2_VOICE_DETAILS voice_details;
	_Listener->getOutputVoice()->GetVoiceDetails(&voice_details);
	wfe.nSamplesPerSec = voice_details.InputSampleRate;

	wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
	wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

	// NOTE: 32.0f allows at lowest 1378.125hz audio samples, increase if you need even lower bitrate (or higher pitch).
	// TODO: Set callback (in CSourceXAudio2 maybe) for when error happens on voice, so we can restart it!
	IXAudio2SourceVoice *source_voice = NULL;

	if (FAILED(hr = _XAudio2->CreateSourceVoice(&source_voice, &wfe, 0, 32.0f, callback, NULL, NULL)))
	{ if (source_voice) source_voice->DestroyVoice(); nlerror(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSourceVoice"); return NULL; }

	return source_voice;
}

/// (Internal) Destroy an XAudio2 source voice.
void CSoundDriverXAudio2::destroySourceVoice(IXAudio2SourceVoice *sourceVoice)
{
	if (sourceVoice) sourceVoice->DestroyVoice();
}

/// Create a music channel
IMusicChannel *CSoundDriverXAudio2::createMusicChannel()
{
	CMusicChannelXAudio2 *music_channel = new CMusicChannelXAudio2(this);
	_MusicChannels.insert(music_channel);
	return static_cast<IMusicChannel *>(music_channel);
}

/// Create the listener instance
IListener *CSoundDriverXAudio2::createListener()
{
	if (!_Listener) _Listener = new CListenerXAudio2(this);
	return static_cast<IListener *>(_Listener);
}

/// Create a source, destroy with delete
ISource *CSoundDriverXAudio2::createSource()
{
	CSourceXAudio2 *source = new CSourceXAudio2(this);
	_Sources.insert(source);
	return static_cast<ISource *>(source);
}

/// Create a sound buffer, destroy with delete
IBuffer *CSoundDriverXAudio2::createBuffer()
{
	CBufferXAudio2 *buffer = new CBufferXAudio2(this);
	_Buffers.insert(buffer);
	return static_cast<IBuffer *>(buffer);
}

/// Create a submix
ISubmix *CSoundDriverXAudio2::createSubmix()
{
	CSubmixXAudio2 *submix = new CSubmixXAudio2(this);
	if (submix->getSubmixVoice())
	{
		_Submixes.insert(submix);
		return static_cast<ISubmix *>(submix);
	}
	delete submix; return NULL;
}

/// Create an effect
IEffect *CSoundDriverXAudio2::createEffect(IEffect::TEffectType effectType)
{
	IEffect *effect = NULL;
	switch (effectType)
	{
		case IEffect::Reverb:
		{
			CReverbEffectXAudio2 *reverb = new CReverbEffectXAudio2(this);
			if (reverb->getEffect()) { effect = static_cast<IEffect *>(reverb); break; }
			else { delete reverb; return NULL; }
		}
		default:
		{
			nlwarning(NLSOUND_XAUDIO2_PREFIX "Invalid effect type");
			return NULL;
		}
	}
	nlassert(effect);
	_Effects.insert(effect);
	return effect;
}

/// Return the maximum number of sources that can created
uint CSoundDriverXAudio2::countMaxSources()
{
	// the only limit is the user's cpu
	// keep similar to openal limit for now ...
	return 128;
}

/// Return the maximum number of submixers that can be created
uint CSoundDriverXAudio2::countMaxSubmixes()
{
	// the only limit is the user's cpu
	// openal only allows 1 in software ...
	return 32;
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
	performanceIncreaseCommit3DCounter();

	// Sync up sources & listener 3d position.
	{
		std::set<CSourceXAudio2 *>::iterator it(_Sources.begin()), end(_Sources.end());
		for (; it != end; ++it) { (*it)->updateState(); (*it)->update3DChanges(); }
	}
}

/// Write information about the driver to the output stream.
void CSoundDriverXAudio2::writeProfile(std::string& out)
{
	XAUDIO2_PERFORMANCE_DATA performance;
	_XAudio2->GetPerformanceData(&performance);

	out = toString(NLSOUND_XAUDIO2_NAME)
		+ "\n\tMono8BufferSize: " + toString(_PerformanceMono8BufferSize)
		+ "\n\tMono16BufferSize: " + toString(_PerformanceMono16BufferSize)
		+ "\n\tMono16ADPCMBufferSize: " + toString(_PerformanceMono16ADPCMBufferSize)
		+ "\n\tStereo8BufferSize: " + toString(_PerformanceStereo8BufferSize)
		+ "\n\tStereo16BufferSize: " + toString(_PerformanceStereo16BufferSize)
		+ "\n\tSourcePlayCounter: " + toString(_PerformanceSourcePlayCounter)
		+ "\n\tMusicPlayCounter: " + toString(_PerformanceMusicPlayCounter)
		+ "\n\tCommit3DCounter: " + toString(_PerformanceCommit3DCounter)
		+ "\nXAUDIO2_PERFORMANCE_DATA"
		+ "\n\tAudioCyclesSinceLastQuery: " + toString(performance.AudioCyclesSinceLastQuery)
		+ "\n\tTotalCyclesSinceLastQuery: " + toString(performance.TotalCyclesSinceLastQuery)
		+ "\n\tMinimumCyclesPerQuantum: " + toString(performance.MinimumCyclesPerQuantum)
		+ "\n\tMaximumCyclesPerQuantum: " + toString(performance.MaximumCyclesPerQuantum)
		+ "\n\tMemoryUsageInBytes: " + toString(performance.MemoryUsageInBytes)
		+ "\n\tCurrentLatencyInSamples: " + toString(performance.CurrentLatencyInSamples)
		+ "\n\tGlitchesSinceEngineStarted: " + toString(performance.GlitchesSinceEngineStarted)
		+ "\n\tActiveSourceVoiceCount: " + toString(performance.ActiveSourceVoiceCount)
		+ "\n\tTotalSourceVoiceCount: " + toString(performance.TotalSourceVoiceCount)
		+ "\n\tActiveSubmixVoiceCount: " + toString(performance.ActiveSubmixVoiceCount)
		+ "\n\tTotalSubmixVoiceCount: " + toString(performance.TotalSubmixVoiceCount)
		+ "\n\tActiveXmaSourceVoices: " + toString(performance.ActiveXmaSourceVoices)
		+ "\n\tActiveXmaStreams: " + toString(performance.ActiveXmaStreams)
		+ "\n";
	return;
}

// Does not create a sound loader .. what does it do then?
void CSoundDriverXAudio2::startBench()
{
	NLMISC::CHTimer::startBench();
}

void CSoundDriverXAudio2::endBench()
{
	NLMISC::CHTimer::endBench();
}

void CSoundDriverXAudio2::displayBench(NLMISC::CLog *log)
{
	NLMISC::CHTimer::displayHierarchicalByExecutionPathSorted(log, CHTimer::TotalTime, true, 48, 2);
	NLMISC::CHTimer::displayHierarchical(log, true, 48, 2);
	NLMISC::CHTimer::displayByExecutionPath(log, CHTimer::TotalTime);
	NLMISC::CHTimer::display(log, CHTimer::TotalTime);
}

/** Get music info. Returns false if the song is not found or the function is not implemented.
 *  \param filepath path to file, CPath::lookup done by driver
 *  \param artist returns the song artist (empty if not available)
 *  \param title returns the title (empty if not available)
 */
bool CSoundDriverXAudio2::getMusicInfo(const std::string &filepath, std::string &artist, std::string &title)
{
	// add support for additional non-standard music file types info here
	return IMusicBuffer::getInfo(filepath, artist, title);
}

/// Remove a buffer (should be called by the friend destructor of the buffer class)
void CSoundDriverXAudio2::removeBuffer(CBufferXAudio2 *buffer)
{
	if (_Buffers.find(buffer) != _Buffers.end()) _Buffers.erase(buffer);
	else nlwarning("removeBuffer already called");
}

/// Remove a source (should be called by the friend destructor of the source class)
void CSoundDriverXAudio2::removeSource(CSourceXAudio2 *source)
{
	if (_Sources.find(source) != _Sources.end()) _Sources.erase(source);
	else nlwarning("removeSource already called");
}
	
/// (Internal) Remove a source (should be called by the destructor of the source class).
void CSoundDriverXAudio2::removeMusicChannel(CMusicChannelXAudio2 *musicChannel)
{
	if (_MusicChannels.find(musicChannel) != _MusicChannels.end()) _MusicChannels.erase(musicChannel);
	else nlwarning("removeMusicChannel already called");
}
	
/// (Internal) Remove a submix (should be called by the destructor of the submix class)
void CSoundDriverXAudio2::removeSubmix(CSubmixXAudio2 *submix)
{
	if (_Submixes.find(submix) != _Submixes.end()) _Submixes.erase(submix);
	else nlwarning("removeSubmix already called");
}

/// (Internal) Remove an effect (should be called by the destructor of the effect class)
void CSoundDriverXAudio2::removeEffect(IEffect *effect)
{
	if (_Effects.find(effect) != _Effects.end()) _Effects.erase(effect);
	else nlwarning("removeEffect already called");
}

/// (Internal) Get internal effect object of an effect.
IUnknown *CSoundDriverXAudio2::getEffectInternal(IEffect *effect)
{
	switch (effect->getType())
	{
	case IEffect::Reverb:
		return static_cast<CReverbEffectXAudio2 *>(effect)->getEffect();
		break;
	default:
		nlwarning(NLSOUND_XAUDIO2_PREFIX "Invalid effect type");
		return NULL;
	}
}

/// (Internal) Call the release function of an effect.
void CSoundDriverXAudio2::releaseEffect(IEffect *effect)
{
	switch (effect->getType())
	{
	case IEffect::Reverb:
		static_cast<CReverbEffectXAudio2 *>(effect)->release();
		break;
	default:
		nlwarning(NLSOUND_XAUDIO2_PREFIX "Invalid effect type");
	}
}
	
/// (Internal) Set the voice of an effect.
void CSoundDriverXAudio2::setEffectVoice(IEffect *effect, IXAudio2Voice *voice)
{
	switch (effect->getType())
	{
	case IEffect::Reverb:
		static_cast<CReverbEffectXAudio2 *>(effect)->setVoice(voice);
		break;
	default:
		nlwarning(NLSOUND_XAUDIO2_PREFIX "Invalid effect type");
	}
}

} /* namespace NLSOUND */

/* end of file */
