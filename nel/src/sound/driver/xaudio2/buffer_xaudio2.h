/**
 * \file buffer_xaudio2.h
 * \brief CBufferXAudio2
 * \date 2008-08-20 17:21GMT
 * \author Jan Boon (Kaetemi)
 * CBufferXAudio2
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

#ifndef NLSOUND_BUFFER_XAUDIO2_H
#define NLSOUND_BUFFER_XAUDIO2_H
#include "stdxaudio2.h"

// Project includes

// NeL includes
#include "../buffer.h"

// STL includes

namespace NLSOUND {

/**
 * \brief CBufferXAudio2
 * \date 2008-08-20 17:21GMT
 * \author Jan Boon (Kaetemi)
 * CBufferXAudio2
 */
class CBufferXAudio2 : public IBuffer
{
	////	friend class	CSourceFMod;
 ////   uint32			_Size; 

	////FSOUND_SAMPLE	*_FModSample;
	////void		loadDataToFMod(uint8 *data);
	////
	////void		*lock();
	////void		unlock(void	*ptr);
protected:
	// pointers
	/// The data in this buffer
	uint8 *_Data;
	
	// instances
	/// XAudio2 buffer structure
	//XAUDIO2_BUFFER _Buffer; // not needed permanent :)
	////////UINT32 Flags; // Flags that provide additional information about the audio buffer. May be 0, or the following value. XAUDIO2_END_OF_STREAM
	////////UINT32 AudioBytes; // Size of the audio data, in bytes. Must be no larger than XAUDIO2_MAX_BUFFER_BYTES (defined in xaudio2.h) for PCM data and no larger than XMA_READBUFFER_MAX_BYTES (defined in xma2defs.h) for XMA data.
	////////const BYTE *pAudioData; // Pointer to the audio data.
	////////UINT32 PlayBegin; // First sample in the buffer that should be played.
	////////UINT32 PlayLength; // Length of the region to be played, in samples. A value of zero means to play the entire buffer, and, in this case, PlayBegin must be zero as well.
	////////UINT32 LoopBegin; // First sample of the region to be looped. The value of LoopBegin must be less than PlayBegin+PlayLength. LoopBegin can be less than PlayBegin. Use XAUDIO2_NO_LOOP_REGION if there is no loop.
	////////UINT32 LoopLength; // Length of the loop region, in samples. The value of LoopBegin+LoopLength must be greater than PlayBegin and less than PlayBegin+PlayLength. LoopLength must be zero if LoopBegin is set to XAUDIO2_NO_LOOP_REGION. If LoopBegin is not XAUDIO2_NO_LOOP_REGION then a loop length of zero indicates the entire sample should be looped.
	////////UINT32 LoopCount; // Number of times to loop through the loop region. This value can be between 0 and XAUDIO2_MAX_LOOP_COUNT, but must be zero if LoopBegin is set to XAUDIO2_NO_LOOP_REGION. To loop forever, set LoopCount to XAUDIO2_LOOP_INFINITE.
	////////void *pContext; // Context value to be passed back in callbacks to the client. This may be NULL.

	/// The size of the data in this buffer
	uint32 _Size;
	/// The name of the buffer
	NLMISC::TStringId _Name;
	/// The sample format
	TSampleFormat _Format;
	/// The sample frequency
	uint _Freq;
public:
	CBufferXAudio2();
	virtual ~CBufferXAudio2();
	//void release();

	inline uint8 *getData() { return _Data; }
	inline uint getFreq() { return _Freq; }
	inline TSampleFormat getFormat() { return _Format; }

	bool readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize);
	bool readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency);


	/** Preset the name of the buffer. Used for async loading to give a name
	 *	before the buffer is effectivly loaded.
	 *	If the name after loading of the buffer doesn't match the preset name,
	 *	the load will assert.
	 */
	virtual void presetName(const NLMISC::TStringId &bufferName);
	/// Set the sample format. Example: freq=44100
	virtual void setFormat(TSampleFormat format, uint freq);
	/// Set the buffer size and fill the buffer.  Return true if ok. Call setFormat() first.
	virtual bool fillBuffer(void *src, uint32 bufsize);

	/// Return the size of the buffer, in bytes
	virtual uint32 getSize() const;
	/// Return the duration (in ms) of the sample in the buffer
	virtual float getDuration() const;
	/// Return true if the buffer is stereo, false if mono
	virtual bool isStereo() const;
	/// Return the format and frequency
	virtual void getFormat( TSampleFormat& format, uint& freq ) const;

	/** Return true if the buffer is able to be fill part by part, false if it must be filled in one call
	 * OpenAL 1.0 -> false
	 */
	virtual bool isFillMoreSupported() const;
	/// Force the buffer size without filling data (if isFillMoreSupported() only)
	virtual void setSize(uint32 size);
	/** Fill the buffer partially (if isFillMoreSupported() only),
	 * beginning at the pos changed by a previous call to fillMore().
	 * If the pos+srcsize exceeds the buffer size, the exceeding data is put at the beginning
	 * of the buffer. srcsize must be smaller than the buffer size.
	 */
	virtual bool fillMore(void *src, uint32 srcsize);

	/// Return the name of this buffer
	virtual const NLMISC::TStringId& getName();

	/// Return true if the buffer is loaded. Used for async load/unload.
	virtual bool isBufferLoaded();

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
