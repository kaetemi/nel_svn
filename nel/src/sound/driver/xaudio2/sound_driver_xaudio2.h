/**
 * \file sound_driver_xaudio2.h
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

/**
 * \brief CSoundDriverXAudio2
 * \date 2008-08-20 10:52GMT
 * \author Jan Boon (Kaetemi)
 * CSoundDriverXAudio2 is an implementation of the ISoundDriver interface to run on XAudio2.
 */
class CSoundDriverXAudio2 : public ISoundDriver, public NLMISC::CManualSingleton<CSoundDriverXAudio2>
{
protected:
	// far pointers
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
	/// Array with the allocated source channels.
	std::set<CSourceXAudio2 *> _SourceChannels;
	/// Array with the allocated music channels.
	std::set<CMusicChannelXAudio2 *> _MusicChannels;
	/// Initialization Handle of X3DAudio.
	X3DAUDIO_HANDLE _X3DAudioHandle; //I
	/// X3DAudio DSP Settings structure for 1 channel to all channels.
	X3DAUDIO_DSP_SETTINGS _DSPSettings;
	
	// user init vars
	/// If eax is used.
	const bool _UseEax;
	
public:
	/// (Internal) Constructor for CSoundDriverXAudio2.
	CSoundDriverXAudio2(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer);
	/// (Internal) Destructor for CSoundDriverXAudio2.
	virtual ~CSoundDriverXAudio2();
	/// (Internal) Release all resources owned by CSoundDriverXAudio2.
	void release();
	
	/// (Internal) Initialize uninitialized sources with this format (so xaudio2 voices don't need to be created at runtime)
	void initSourcesFormat(TSampleFormat format);
	
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
	inline bool useEax() { return _UseEax; }
	
	/// (Internal) Create an XAudio2 source voice of the specified format.
	IXAudio2SourceVoice *createSourceVoice(TSampleFormat format);
	/// (Internal) Destroy an XAudio2 source voice.
	void destroySourceVoice(IXAudio2SourceVoice *sourceVoice);
	
	/// Create a sound buffer.
	virtual	IBuffer *createBuffer();
	/// Create the listener instance.
	virtual	IListener *createListener();
	/// Return the maximum number of sources that can created.
	virtual uint countMaxSources();
	/// Create a source channel.
	virtual	ISource *createSource();
	
	/// Read a WAV data in a buffer (format supported: Mono16, Mono8, Stereo16, Stereo8).
	virtual bool readWavBuffer(IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize);
	/// FMod driver Note: ADPCM format are converted and stored internally in Mono16 format (hence IBuffer::getFormat() return Mono16).
	virtual bool readRawBuffer(IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency);
	
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
	
	/// Destroy a music channel.
	virtual void destroyMusicChannel(IMusicChannel *musicChannel);
	
	/** Get music info. Returns false if the song is not found or the function is not implemented.
	 *  \param filepath path to file, CPath::lookup done by driver
	 *  \param artist returns the song artist (empty if not available)
	 *  \param title returns the title (empty if not available)
	 */
	virtual bool getMusicInfo(const std::string &filepath, std::string &artist, std::string &title);
	
	/// (Internal) Remove a buffer (should be called by the friend destructor of the buffer class).
	virtual void removeBuffer(IBuffer *buffer);
	
	/// (Internal) Remove a source (should be called by the friend destructor of the source class).
	virtual void removeSource(ISource *source);
	
	/// (Internal) Remove the listener (called by destructor of listener class)
	inline void removeListener(CListenerXAudio2 *listener) { nlassert(_Listener == listener); _Listener = NULL; }

}; /* class CSoundDriverXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SOUND_DRIVER_XAUDIO2_H */

/* end of file */
