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

// Project includes
#include "source_xaudio2.h"
#include "buffer_xaudio2.h"
//#include "music_channel_xaudio2.h"

// NeL includes
#include <nel/misc/time_nl.h>

// STL includes
#include <iostream>

// Defines
#define NLSOUND_XAUDIO2_NAME "NLSOUND XAudio2 Driver"
#define NLSOUND_XAUDIO2_PREFIX NLSOUND_XAUDIO2_NAME ": "

// TEMP !!! check from device and stuff :)
//#define NLSOUND_XAUDIO2_SOURCE_CHANNELS 1
//#define NLSOUND_XAUDIO2_SOURCE_BITS_PER_SAMPLE 16
//#define NLSOUND_XAUDIO2_SOURCE_SAMPLES_PER_SEC 44100
//22050

// swap y and z
#define NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(to, from) (to).x = (from).x; (to).y = (from).z; (to).z = (from).y;
#define NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(to, from) (to).x = (from).x; (to).y = (from).z; (to).z = (from).y;

// no swap
//#define NLSOUND_XAUDIO2_X3DAUDIO_VECTOR_FROM_VECTOR(to, from) (to).x = (from).x; (to).y = (from).y; (to).z = (from).z;
//#define NLSOUND_XAUDIO2_VECTOR_FROM_X3DAUDIO_VECTOR(to, from) (to).x = (from).x; (to).y = (from).y; (to).z = (from).z;

namespace NLSOUND {
	class IListener;
	class ISource;
	class IBuffer;
	class CListenerXAudio2;
	class CSampleVoiceXAudio2;
	class CMusicChannelXAudio2;

////// ***************************************************************************
/////*
////	DRIVER FMOD LIMITATIONS: *** from fmod ***
////
////	- EAX is not supported (setEnvironnement() / setEAXProperty() no-op)
////	- ADPCM is not supported (decompressed and the format change internaly)
////	- deffered param on ISource::setPos() etc... does not work. Always deffered.
////	- No cooperative level change in FMod as in DSOUND (default???)
////	
////*/
////// ***************************************************************************

/**
 * \brief CSoundDriverXAudio2
 * \date 2008-08-20 10:52GMT
 * \author Jan Boon (Kaetemi)
 * CSoundDriverXAudio2
 */
class CSoundDriverXAudio2 : public ISoundDriver, public NLMISC::CManualSingleton<CSoundDriverXAudio2>
{
protected:
	// far pointers
	/// The string mapper provided by client code
	IStringMapperProvider *_StringMapper;

	// pointers
	/// Pointer to XAudio2
	IXAudio2 *_XAudio2;
	/// Pointer to XAudio2 Mastering Voice
	IXAudio2MasteringVoice *_MasteringVoice;
	/// Listener
	CListenerXAudio2 *_Listener;
	/// Array with the allocated sources
	std::set<CSourceXAudio2 *> _Sources;
	/// Array with the allocated unused "destroyed" sample voices only
	std::set<CSampleVoiceXAudio2 *> _SampleVoices;
	/// Array with the allocated music channels
	std::vector<CMusicChannelXAudio2 *> _MusicChannels;

	// instances
	/// If XAudio2 is fully initialized.
	bool _SoundDriverOk;
	/// If CoInitializeEx has been called.
	bool _CoInitOk;
	/// Last update time.
	NLMISC::TTime _LastTime;
	/// Empty 3D Listener
	X3DAUDIO_LISTENER _EmptyListener;

	// other
	/// Initialization Handle of X3DAudio
	X3DAUDIO_HANDLE _X3DAudioHandle; //I
	/// X3DAudio DSP Settings structure for 1 channel to all channels
	X3DAUDIO_DSP_SETTINGS _DSPSettings;
public:
	CSoundDriverXAudio2(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer);
	virtual ~CSoundDriverXAudio2();
	void release();

	inline CListenerXAudio2 *getListener() { return _Listener; }
	inline IXAudio2 *getXAudio2() { return _XAudio2; }
	inline IXAudio2MasteringVoice *getMasteringVoice() { return _MasteringVoice; }
	inline IStringMapperProvider *getStringMapper() { return _StringMapper; }
	inline X3DAUDIO_HANDLE &getX3DAudio() { return _X3DAudioHandle; }
	inline X3DAUDIO_DSP_SETTINGS *getDSPSettings() { return &_DSPSettings; }
	inline X3DAUDIO_LISTENER *getEmptyListener() { return &_EmptyListener; }

	CSampleVoiceXAudio2 *createSampleVoice(CSourceXAudio2 *owner, TSampleFormat format); // checks pool
	void destroySampleVoice(CSampleVoiceXAudio2 *sampleVoice, bool stop); // doesn't really destroy

	///// Set the gain (volume value inside [0 , 1]). (default: 1), can't go over 1.0 on some systems
	//void setGain(float gain);
	///// Get the gain
	//float getGain() const;

	/// Create a sound buffer
	virtual	IBuffer *createBuffer();
	/// Create the listener instance
	virtual	IListener *createListener();
	/// Return the maximum number of sources that can created
	virtual uint countMaxSources();
	/// Create a source
	virtual	ISource *createSource();

	/// Read a WAV data in a buffer (format supported: Mono16, Mono8, Stereo16, Stereo8)
	virtual bool readWavBuffer(IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize);
	/// FMod driver Note: ADPCM format are converted and stored internally in Mono16 format (hence IBuffer::getFormat() return Mono16)
	virtual bool readRawBuffer(IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency);
	
	/// Commit all the changes made to 3D settings of listener and sources
	virtual void commit3DChanges();

	/// Write information about the driver to the output stream.
	virtual void writeProfile(std::string& out) ;

	// Does not create a sound loader
	virtual void startBench();
	virtual void endBench();
	virtual void displayBench(NLMISC::CLog *log);

		/** Play some music syncrhonously (.ogg etc...) (implemented in fmod only)
	 *	FMOD: The File is loaded synchronously in memory, but decompressed by FMod in a thread
	 *	Hence if the ogg fileSize is 5 Mb, it will take only 5 Mb in memory (not the decompressed 40 Mb size)
	 *	NB: if an old music was played, it is first stop with stopMusic()
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 *	\param CIFile opened file (must use a CIFile if for instance you want to load from a BNP, and CBigFile is static....)
	 *	\param xFadeTime if not 0 the old music played is not stoped imediatly but a cross-fade of xFadeTime (in ms) is made between the 2.
	 */

	virtual bool playMusic(uint channel, NLMISC::CIFile &file, uint xFadeTime, bool loop);
	/** Play some music asynchronously (.ogg etc...) (implemented in fmod only)
	 *	FMOD: the file is load asynchronously
	 *	NB: if an old music was played, it is first stop with stopMusic()
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently	 *	\param path full file path (no CPath::lookup is done since static)
	 *	\param xFadeTime if not 0 the old music played is not stoped imediatly but a cross-fade of xFadeTime (in ms) is made between the 2.
	 *	\param fileOffset and fileSize: if not 0, use it to load a .ogg that reside in a BNP. 
	 *		the offset and size have to be retrieved with CBigFile methods. 
	 *		e.g.: use either 
	 *			playMusicAsync("C:/test/mymusic.ogg");
	 *		or
	 * 			playMusicAsync("C:/test/mydata.bnp", offsetOfOggInBnp, sizeOfOggInBnp);
	 *		Notice that you must give the full path of the bnp (eg: "C:/test/mydata.bnp") in path.
	 *	\param loop must be true to play the music in loop. 
	 */

	virtual bool playMusicAsync(uint channel, const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop);
	/** Stop the music previously loaded and played (the Memory is also freed)
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 *	\param xFadeTime if not 0 the old music played is not stoped but faded out of xFadeTime (in ms)
	 */

	virtual void stopMusic(uint channel, uint xFadeTime);
	/** Pause the music previously loaded and played (the Memory is not freed)
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual void pauseMusic(uint channel);
	
	/** Resume the music previously paused
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual void resumeMusic(uint channel);

	/** Get the song title. Returns false if the song is not found or the function is not implemented. 
	 * If the song as no name, result is filled with the filename.
	 */
	virtual bool getSongTitle(const std::string &filename, std::string &result, uint fileOffset=0, uint fileSize=0);

	/** Return true if a song is finished.
	 *	NB: in case of cross fading, the channel is considered "ended" if all fading are done
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual bool isMusicEnded(uint channel);
	
	/** Return the total length (in second) of the music currently played
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual float getMusicLength(uint channel);
	
	/** Set the music volume (if any music played). (volume value inside [0 , 1]) (default: 1)
	 *	NB: the volume of music is NOT affected by IListener::setGain()
	 *	\param channel up to 2 channels are available for now 0 and 1 (any other value will fail), so that 2 music can be played concurently
	 */
	virtual void setMusicVolume(uint channel, float gain);

protected:
	/// Remove a buffer (should be called by the friend destructor of the buffer class)
	friend CBufferXAudio2::~CBufferXAudio2();
	virtual void removeBuffer(IBuffer *buffer);

	/// Remove a source (should be called by the friend destructor of the source class)
	friend void CSourceXAudio2::release();
	virtual void removeSource(ISource *source);

}; /* class CSoundDriverXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SOUND_DRIVER_XAUDIO2_H */

/* end of file */
