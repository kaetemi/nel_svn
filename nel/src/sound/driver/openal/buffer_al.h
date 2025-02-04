/** \file buffer_al.h
 * OpenAL buffer
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

#ifndef NL_BUFFER_AL_H
#define NL_BUFFER_AL_H
#include <nel/misc/types_nl.h>

namespace NLSOUND {

/**
 * OpenAL buffer
 *
 * A buffer can be filled with data. An OpenAL buffer cannot be streamed in, i.e.
 * isFillMoreSupported() returns false (instead, streaming would be implemented
 * by buffer queueing).
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CBufferAL : public IBuffer
{
public:
	/// Constructor
	CBufferAL( ALuint buffername=0 );
	/// Destructor
	virtual ~CBufferAL();

	/// Return the buffer name (as an int)
	inline ALuint bufferName() { return _BufferName; }
	
	/** Preset the name of the buffer. Used for async loading to give a name
	 *	before the buffer is effectivly loaded.
	 *	If the name after loading of the buffer doesn't match the preset name,
	 *	the load will assert.
	 */
	virtual void setName(NLMISC::TStringId bufferName);
	/// Return the name of this buffer
	virtual NLMISC::TStringId getName() const;

	/// Set the sample format. (channels = 1, 2, ...; bitsPerSample = 8, 16; frequency = samples per second, 44100, ...)
	virtual void setFormat(TBufferFormat format, uint8 channels, uint8 bitsPerSample, uint32 frequency);
	/// Return the sample format informations.
	virtual void getFormat(TBufferFormat &format, uint8 &channels, uint8 &bitsPerSample, uint32 &frequency) const;
		/// Set the storage mode of this buffer, call before filling this buffer. Storage mode is always software if OptionSoftwareBuffer is enabled. Default is auto.
	virtual void setStorageMode(TStorageMode storageMode = IBuffer::StorageAuto);
	/// Get the storage mode of this buffer.
	virtual TStorageMode getStorageMode();

	/// Get a writable pointer to the buffer of specified size. Use capacity to specify the required bytes. Returns NULL in case of failure. It is only guaranteed that the original data is still available when using StorageSoftware and the specified size is not larger than the size specified in the last lock. Call setStorageMode() and setFormat() first.
	virtual uint8 *lock(uint capacity);
	/// Notify that you are done writing to this buffer, so it can be copied over to hardware if needed. Set size to the number of bytes actually written to the buffer. Returns true if ok.
	virtual bool unlock(uint size);
	/// Copy the data with specified size into the buffer. A readable local copy is only guaranteed when OptionLocalBufferCopy is set. Returns true if ok.
	virtual bool fill(const uint8 *src, uint size);
	
	/// Return the size of the buffer, in bytes.
	virtual uint getSize() const;
	/// Return the duration (in ms) of the sample in the buffer.
	virtual float getDuration() const;
	/// Return true if the buffer is stereo (multi-channel), false if mono.
	virtual bool isStereo() const;	
	/// Return true if the buffer is loaded. Used for async load/unload.
	virtual bool isBufferLoaded() const;
	
private:
	/// Buffer name
	ALuint _BufferName;
	/// Buffer name as string
	NLMISC::TStringId _Name;
	/// Sample format
	ALenum _SampleFormat;
	/// Frequency
	ALuint _Frequency;
	/// Buffer data (as OpenAL keeps it's own data and doesn't publish it back)
	uint8 *_Data;
	/// The capacity of the buffer
	uint _Capacity;
	/// The size of the data in the buffer
	uint _Size;
	/// Storage mode
	IBuffer::TStorageMode _StorageMode;

};

// TFrameStereo is used to access a sample pair of 8/16bit
// samples at once. To make sure the data is aligned properly
// the various compilers need some (unfortunately vendor
// specific hints) to pack the data as good as possible
// without adding alignment optimizations to it.

#ifdef _MSC_VER
#	pragma pack(push,1)
#endif

template <class T> struct TFrameStereo
{
	T	Channel1;
	T	Channel2;
}
#ifdef __GNUC__
	__attribute__ ((packed))
#endif
;

#ifdef _MSC_VER
#	pragma pack(pop)
#endif


} // NLSOUND


#endif // NL_BUFFER_AL_H

/* End of buffer_al.h */
