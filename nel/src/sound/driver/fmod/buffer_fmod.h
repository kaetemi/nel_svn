/** \file buffer_fmod.h
 * FMod buffer
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

#ifndef NL_BUFFER_FMOD_H
#define NL_BUFFER_FMOD_H


#include "../buffer.h"
#include <fmod.h>


namespace NLSOUND {

/**
 *  Buffer for the FMod implementation of the audio driver.
 *
 * A buffer represents a sound file loaded in RAM.
 *
 * \author Peter Hanappe, Olivier Cado
 * \author Nevrax France
 * \date 2002
 */
class CBufferFMod : public IBuffer
{
	friend class CSourceFMod;
public:

	/// Constructor
	CBufferFMod();
	/// Destructor
	virtual	~CBufferFMod();
	
	/// Read the audio data from a WAV format buffer.
	bool readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize);
	bool readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat sampleFormat, uint32 frequency);

	/** Preset the name of the buffer. Used for async loading to give a name
	 *	before the buffer is effectivly loaded.
	 *	If the name after loading of the buffer doesn't match the preset name,
	 *	the load will assert.
	 */
	virtual void presetName(const NLMISC::TStringId &bufferName);
	/// Set the sample format. (channels = 1, 2, ...; bitsPerSample = 8, 16; frequency = samples per second, 44100, ...)
	virtual void setFormat(TBufferFormat format, uint8 channels, uint8 bitsPerSample, uint frequency);
	/// Set the buffer size and fill the buffer.  Return true if ok. Call setStorageMode() and setFormat() first.
	virtual bool fillBuffer(const void *src, uint bufsize);
	
	/// Return the sample format informations.
	virtual void getFormat(TBufferFormat &format, uint8 &channels, uint8 &bitsPerSample, uint &frequency) const;
	/// Return the size of the buffer, in bytes.
	virtual uint getSize() const;
	/// Return the duration (in ms) of the sample in the buffer.
	virtual float getDuration() const;
	/// Return true if the buffer is stereo (multi-channel), false if mono.
	virtual bool isStereo() const;
	
	/// Return the name of this buffer
	virtual NLMISC::TStringId getName() const;
	
	/// Return true if the buffer is loaded. Used for async load/unload.
	virtual bool isBufferLoaded() const;
	
	/// Set the storage mode of this buffer, call before filling this buffer. Storage mode is always software if OptionSoftwareBuffer is enabled. Default is auto.
	virtual void setStorageMode(TStorageMode storageMode = IBuffer::StorageAuto);
	/// Get the storage mode of this buffer.
	virtual TStorageMode getStorageMode();
	
	/** Unoptimized utility function designed to build ADPCM encoded sample bank file.
	 *	Return the number of sample in the buffer.
	 */
	virtual uint32 getBufferADPCMEncoded(std::vector<uint8> &result);
	/** Unoptimized utility function designed to build Mono 16 bits encoded sample bank file.
	 *	Return the number of sample in the buffer.
	 */
	virtual uint32 getBufferMono16(std::vector<sint16> &result);

private:

	NLMISC::TStringId _Name;
    uint _Size;
    TSampleFormat _Format;
    uint _Freq;
	FSOUND_SAMPLE *_FModSample;
	
	void loadDataToFMod(uint8 *data);
	
	void *lock();
	void unlock(void *ptr);

};


} // NLSOUND


#endif // NL_BUFFER_FMOD_H

