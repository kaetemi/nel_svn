/**
 * \file sound_driver_xaudio2.h
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

#ifndef NLSOUND_SOUND_DRIVER_XAUDIO2_H //todo: support MAKEINTRESOURCE for music files?
#define NLSOUND_SOUND_DRIVER_XAUDIO2_H
#include "stdxaudio2.h"

// STL includes
#include <iostream>

// NeL includes
#include <nel/misc/time_nl.h>

// Project includes
#include "source_xaudio2.h"
#include "buffer_xaudio2.h"
//#include "music_channel_xaudio2.h"

namespace NLSOUND {
	class IListener;
	class ISource;
	class IMusicChannel;
	class IBuffer;
	class CListenerXAudio2;
	class CSampleVoiceXAudio2;
	class CMusicChannelXAudio2;
	class CEffectXAudio2;

/**
 * \brief CSoundDriverXAudio2
 * \date 2008-08-20 10:52GMT
 * \author Jan Boon (Kaetemi)
 * CSoundDriverXAudio2 is an implementation of the ISoundDriver interface to run on XAudio2.
 */
class CSoundDriverXAudio2 : public ISoundDriver, public NLMISC::CManualSingleton<CSoundDriverXAudio2>
{
protected:
	// outside pointers
	/// The string mapper provided by client code.
	IStringMapperProvider *_StringMapper;
	/// Listener, created by client code.
	CListenerXAudio2 *_Listener;
	
	// pointers
	/// Pointer to XAudio2.
	IXAudio2 *_XAudio2;
	/// Pointer to XAudio2 Mastering Voice.
	IXAudio2MasteringVoice *_MasteringVoice;
	
	// system vars
	/// If XAudio2 is fully initialized.
	bool _SoundDriverOk;
	/// If CoInitializeEx has been called.
	bool _CoInitOk;
	/// Empty 3D Listener.
	X3DAUDIO_LISTENER _EmptyListener;
	/// Array with the allocated buffers.
	std::set<CBufferXAudio2 *> _Buffers;
	/// Array with the allocated sources.
	std::set<CSourceXAudio2 *> _Sources;
	/// Array with the allocated effects.
	std::set<CEffectXAudio2 *> _Effects;
	/// Array with the allocated music channels.
	std::set<CMusicChannelXAudio2 *> _MusicChannels;
	/// Initialization Handle of X3DAudio.
	X3DAUDIO_HANDLE _X3DAudioHandle; //I
	/// X3DAudio DSP Settings structure for 1 channel to all channels.
	X3DAUDIO_DSP_SETTINGS _DSPSettings;

	// performance stats
	uint _PerformancePCMBufferSize;
	uint _PerformanceADPCMBufferSize;
	uint _PerformanceSourcePlayCounter;
	uint _PerformanceMusicPlayCounter;
	uint _PerformanceCommit3DCounter;
	
	// user init vars
	/// Driver options
	TSoundOptions _Options;
	
public:
	/// (Internal) Constructor for CSoundDriverXAudio2.
	CSoundDriverXAudio2(ISoundDriver::IStringMapperProvider *stringMapper);
	/// (Internal) Destructor for CSoundDriverXAudio2.
	virtual ~CSoundDriverXAudio2();
	/// (Internal) Release all resources owned by CSoundDriverXAudio2.
	void release();

	/// (Internal) Register a data buffer with the performance counters.
	inline void performanceRegisterBuffer(IBuffer::TBufferFormat bufferFormat, uint size) 
	{ 
		switch (bufferFormat)
		{
		case IBuffer::FormatPCM: _PerformancePCMBufferSize += size; break;
		case IBuffer::FormatADPCM: _PerformanceADPCMBufferSize += size; break;
		}
	}
	/// (Internal) Remove a data buffer from the performance counters.
	inline void performanceUnregisterBuffer(IBuffer::TBufferFormat bufferFormat, uint size) 
	{ 
		switch (bufferFormat)
		{
		case IBuffer::FormatPCM: _PerformancePCMBufferSize -= size; break;
		case IBuffer::FormatADPCM: _PerformanceADPCMBufferSize -= size; break;
		}
	}
	/// (Internal) Increase the source play counter by one.
	inline void performanceIncreaseSourcePlayCounter() { ++_PerformanceSourcePlayCounter; }
	/// (Internal) Increase the music play counter by one.
	inline void performanceIncreaseMusicPlayCounter() { ++_PerformanceMusicPlayCounter; }
	/// (Internal) Increase the commit 3d counter by one.
	inline void performanceIncreaseCommit3DCounter() { ++_PerformanceCommit3DCounter; }
	
	/// (Internal) Initialize uninitialized sources with this format (so xaudio2 voices don't need to be created at runtime)
	void initSourcesFormat(IBuffer::TBufferFormat bufferFormat, uint8 channels, uint8 bitsPerSample);
	
	/// (Internal) Returns the listener for this driver.
	inline CListenerXAudio2 *getListener() { return _Listener; }
	/// (Internal) Returns the XAudio2 interface.
	inline IXAudio2 *getXAudio2() { return _XAudio2; }
	/// (Internal) Returns the XAudio2 Mastering Voice interface.
	inline IXAudio2MasteringVoice *getMasteringVoice() { return _MasteringVoice; }
	/// (Internal) Returns the string mapper provided by client code.
	inline IStringMapperProvider *getStringMapper() { return _StringMapper; }
	/// (Internal) Returns the handle to X3DAudio.
	inline X3DAUDIO_HANDLE &getX3DAudio() { return _X3DAudioHandle; }
	/// (Internal) Returns the structure to receive X3DAudio calculations.
	inline X3DAUDIO_DSP_SETTINGS *getDSPSettings() { return &_DSPSettings; }
	/// (Internal) Returns an X3DAudio listener at 0 position.
	inline X3DAUDIO_LISTENER *getEmptyListener() { return &_EmptyListener; }
	/// (Internal) Returns if EAX is enabled.
	inline bool useEax() { return getOption(OptionEnvironmentEffects); }
	
	/// (Internal) Create an XAudio2 source voice of the specified format.
	IXAudio2SourceVoice *createSourceVoice(IBuffer::TBufferFormat bufferFormat, uint8 channels, uint8 bitsPerSample, IXAudio2VoiceCallback *callback);
	/// (Internal) Destroy an XAudio2 source voice.
	void destroySourceVoice(IXAudio2SourceVoice *sourceVoice);

	/// Return a list of available devices for the user. If the result is empty, you should use the default device.
	// ***todo*** virtual void getDevices(std::vector<std::string> &devices);
	/// Initialize the driver with a user selected device. If device.empty(), the default or most appropriate device is used.
	virtual void init(std::string device, TSoundOptions options);

	/// Return options that are enabled (including those that cannot be disabled on this driver).
	virtual TSoundOptions getOptions();
	/// Return if an option is enabled (including those that cannot be disabled on this driver).
	virtual bool getOption(TSoundOptions option);
	
	/// Create the listener instance
	virtual	IListener *createListener();
	/// Create a source, destroy with delete
	virtual	ISource *createSource();
	/// Create a sound buffer, destroy with delete
	virtual	IBuffer *createBuffer();
	/// Create an effect
	virtual IEffect *createEffect(IEffect::TEffectType effectType);
	/// Return the maximum number of sources that can created
	virtual uint countMaxSources();
	/// Return the maximum number of effects that can be created
	virtual uint countMaxEffects();
	
	/// Read a WAV data in a buffer (format supported: Mono16, Mono8, Stereo16, Stereo8).
	virtual bool readWavBuffer(IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize);
	/// Read data from the data block. All supported formats are implemented.
	virtual bool readRawBuffer(IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat sampleFormat, uint32 frequency);
	
	/// Commit all the changes made to 3D settings of listener and sources.
	virtual void commit3DChanges();
	
	/// Write information about the driver to the output stream.
	virtual void writeProfile(std::string& out) ;
	
	/// Does not create a sound loader... that's really awesome but what does it do?
	virtual void startBench();
	virtual void endBench();
	virtual void displayBench(NLMISC::CLog *log);
	
	/// Create a music channel, destroy with destroyMusicChannel.
	virtual IMusicChannel *createMusicChannel();
	
	/** Get music info. Returns false if the song is not found or the function is not implemented.
	 *  \param filepath path to file, CPath::lookup done by driver
	 *  \param artist returns the song artist (empty if not available)
	 *  \param title returns the title (empty if not available)
	 */
	virtual bool getMusicInfo(const std::string &filepath, std::string &artist, std::string &title);

	/// Get audio/container extensions that are supported natively by the driver implementation.
	virtual void getMusicExtensions(std::vector<std::string> & /* extensions */) const { }
	/// Return if a music extension is supported by the driver's music channel.
	virtual bool isMusicExtensionSupported(const std::string & /* extension */) const { return false; }
	
	/// (Internal) Remove a buffer (should be called by the destructor of the buffer class).
	void removeBuffer(CBufferXAudio2 *buffer);	
	/// (Internal) Remove a source (should be called by the destructor of the source class).
	void removeSource(CSourceXAudio2 *source);
	/// (Internal) Remove a source (should be called by the destructor of the music channel class).
	void removeMusicChannel(CMusicChannelXAudio2 *musicChannel);	
	/// (Internal) Remove the listener (should be called by the destructor of the listener class)
	inline void removeListener(CListenerXAudio2 *listener) { nlassert(_Listener == listener); _Listener = NULL; }
	/// (Internal) Remove an effect (should be called by the destructor of the effect class)
	void removeEffect(CEffectXAudio2 *effect);

}; /* class CSoundDriverXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SOUND_DRIVER_XAUDIO2_H */

/* end of file */
