/**
 * \file buffer_xaudio2.h
 * \brief CBufferXAudio2
 * \date 2008-08-20 17:21GMT
 * \author Jan Boon (Kaetemi)
 * CBufferXAudio2
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

#ifndef NLSOUND_BUFFER_XAUDIO2_H
#define NLSOUND_BUFFER_XAUDIO2_H
#include "stdxaudio2.h"

// STL includes

// NeL includes
#include "../buffer.h"

// Project includes

namespace NLSOUND {
	class CSoundDriverXAudio2;

/**
 * \brief CBufferXAudio2
 * \date 2008-08-20 17:21GMT
 * \author Jan Boon (Kaetemi)
 * CBufferXAudio2 is an implementation of the IBuffer interface to run on XAudio2.
 */
class CBufferXAudio2 : public IBuffer
{
protected:
	// outside pointers
	/// The sound driver that owns this buffer, used for stats. (artificial limit)
	CSoundDriverXAudio2 *_SoundDriver;
	
	// pointers
	/// The sample data in this buffer.
	uint8 *_Data;
	
	// instances
	// XAudio2 buffer structure, could have one pre-configured 
	// here for optimization (looping state unknown).
	// XAUDIO2_BUFFER _Buffer;

	/// The size of the data in this buffer
	uint _Size;
	/// The name of the buffer
	NLMISC::TStringId _Name;
	/// The sample format
	TSampleFormat _Format;
	/// The sample frequency
	uint32 _Freq;
public:
	CBufferXAudio2(CSoundDriverXAudio2 *soundDriver);
	virtual ~CBufferXAudio2();
	void release();

	/// Returns a pointer to the PCM or ADPCM bytes.
	inline uint8 *getData() { return _Data; }
	/// Returns the sample rate.
	inline uint getFreq() { return _Freq; }
	/// Returns the sample format.
	inline TSampleFormat getFormat() { return _Format; }

	/// Allocate a new writable buffer. If this buffer was already allocated, the previous data is released.
	/// May return NULL if the format or frequency is not supported by the driver.
	virtual uint8 *openWritable(uint size, TSampleFormat format, uint32 frequency);
	/// Tell that you are done writing to this buffer, so it can be copied over to hardware if needed.
	/// If keepLocal is true, a local copy of the buffer will be kept (so allocation can be re-used later).
	/// keepLocal overrides the OptionLocalBufferCopy flag. The buffer can use this function internally.
	virtual void lockWritable(bool keepLocal);

	/// Read the audio data from a WAV format buffer.
	bool readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize);
	bool readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency);


	/** Preset the name of the buffer. Used for async loading to give a name
	 *	before the buffer is effectivly loaded.
	 *	If the name after loading of the buffer doesn't match the preset name,
	 *	the load will assert.
	 */
	virtual void presetName(const NLMISC::TStringId &bufferName);
	/// Set the sample format. Example: freq=44100.
	virtual void setFormat(TSampleFormat format, uint freq);
	/// Set the buffer size and fill the buffer. Return true if ok. Call setFormat() first.
	virtual bool fillBuffer(void *src, uint32 bufsize);

	/// Return the size of the buffer, in bytes.
	virtual uint32 getSize() const;
	/// Return the duration (in ms) of the sample in the buffer.
	virtual float getDuration() const;
	/// Return true if the buffer is stereo, false if mono.
	virtual bool isStereo() const;
	/// Return the format and frequency.
	virtual void getFormat( TSampleFormat& format, uint& freq ) const;

	/** Return true if the buffer is able to be fill part by part, false if it must be filled in one call
	 * OpenAL 1.0 -> false
	 */
	virtual bool isFillMoreSupported() const;
	/// Force the buffer size without filling data (if isFillMoreSupported() only).
	virtual void setSize(uint32 size);
	/** Fill the buffer partially (if isFillMoreSupported() only),
	 * beginning at the pos changed by a previous call to fillMore().
	 * If the pos+srcsize exceeds the buffer size, the exceeding data is put at the beginning
	 * of the buffer. srcsize must be smaller than the buffer size.
	 */
	virtual bool fillMore(void *src, uint32 srcsize);

	/// Return the name of this buffer
	virtual const NLMISC::TStringId& getName() const;

	/// Return true if the buffer is loaded. Used for async load/unload.
	virtual bool isBufferLoaded() const;

	/** Unoptimized utility function designed to build ADPCM encoded sample bank file.
	 *	Return the number of sample in the buffer.
	 */
	virtual uint32 getBufferADPCMEncoded(std::vector<uint8> &result);
	/** Unoptimized utility function designed to build Mono 16 bits encoded sample bank file.
	 *	Return the number of sample in the buffer.
	 */
	virtual uint32 getBufferMono16(std::vector<sint16> &result);
	//@}
}; /* class CBufferXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_BUFFER_XAUDIO2_H */

/* end of file */
