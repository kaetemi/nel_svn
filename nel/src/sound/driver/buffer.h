/** \file buffer.h
 * IBuffer: sound buffer interface
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

#ifndef NL_BUFFER_H
#define NL_BUFFER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/string_mapper.h"
#include "sound_driver.h"


namespace NLSOUND {

/**
 * Sound buffer interface (implemented in sound driver dynamic library)
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class IBuffer
{
public:
	/// Compression format of the sample.
	enum TBufferFormat
	{
		/// Standard PCM format. Todo: specify endianness.
		FormatPCM, 
		/// ADPCM format, only available for 1 channel at 16 bits per sample.
		/// This is only implemented in the DSound and XAudio2 driver.
		FormatADPCM
	};
	
	/** Preset the name of the buffer. Used for async loading to give a name
	 *	before the buffer is effectivly loaded.
	 *	If the name after loading of the buffer doesn't match the preset name,
	 *	the load will assert.
	 */
	virtual void presetName(const NLMISC::TStringId &bufferName) = 0;
	/// Set the sample format. (channels = 1, 2, ...; frequency = samples per second, 44100, ...; bitsPerSample = 8, 16)
	virtual void setFormat(TBufferFormat format, uint8 channels, uint frequency, uint8 bitsPerSample) { throw ESoundDriverNotSupp(); }
	/// Set the buffer size and fill the buffer.  Return true if ok. Call setStorageMode() and setFormat() first.
	virtual bool fillBuffer( void *src, uint32 bufsize ) = 0;

	/// Return the sample format informations.
	virtual void getFormat(TBufferFormat &format, uint8 &channels, uint &frequency, uint8 &bitsPerSample) { throw ESoundDriverNotSupp(); }
	/// Return the size of the buffer, in bytes.
	virtual uint32 getSize() const = 0;
	/// Return the duration (in ms) of the sample in the buffer.
	virtual float getDuration() const = 0;
	/// Return true if the buffer is stereo (multi-channel), false if mono.
	virtual bool isStereo() const = 0;

	/// Return the name of this buffer
	virtual const NLMISC::TStringId& getName() const = 0;

	/// Return true if the buffer is loaded. Used for async load/unload.
	virtual bool isBufferLoaded() const = 0;
	
	//@{
	//\name Functions for controlling X-RAM extension of OpenAL *** TODO ***
	/// The storage mode of this buffer
	enum TStorageMode
	{
		/// Put buffer in sound hardware memory if possible, else in machine ram.
		StorageAuto, 
		/// Put buffer in sound hardware memory (fails if not possible).
		StorageHardware, 
		/// Put buffer in machine ram (used for streaming).
		StorageSoftware
	};
	/// Set the storage mode of this buffer, call before filling this buffer. Storage mode is always software if OptionSoftwareBuffer is enabled. Default is auto.
	virtual void setStorageMode(TStorageMode storageMode = IBuffer::StorageAuto) { throw ESoundDriverNotSupp(); }
	/// Get the storage mode of this buffer.
	virtual TStorageMode getStorageMode() { throw ESoundDriverNotSupp(); }
	//@}

	//@{
	//\name ***deprecated***
	/// Set the sample format. Example: freq=44100. ***deprecated***
	virtual void setFormat(TSampleFormat format, uint freq) = 0;
	/// Return the format and frequency. ***deprecated***
	virtual void getFormat(TSampleFormat& format, uint& freq) const = 0;
	//@}
	
	//@{
	//\name ADPCM utility methods
	struct TADPCMState
	{
		/// Previous output sample
		sint16	PreviousSample;
		/// Stepsize table index
		uint8	StepIndex;
	};
	// Encode 16 wav buffer into ADPCM
	static void encodeADPCM(sint16 *indata, uint8 *outdata, uint nbSample, TADPCMState &state);
	static void decodeADPCM(uint8 *indata, sint16 *outdata, uint nbSample, TADPCMState &state);	
	/** Unoptimized utility function designed to build ADPCM encoded sample bank file.
	 *	Return the number of sample in the buffer.
	 */
	virtual uint32 getBufferADPCMEncoded(std::vector<uint8> &result) = 0;
	/** Unoptimized utility function designed to build Mono 16 bits encoded sample bank file.
	 *	Return the number of sample in the buffer.
	 */
	virtual uint32 getBufferMono16(std::vector<sint16> &result) = 0;
	
private:
	static const sint _IndexTable[16];
	static const uint _StepsizeTable[89];
	//@}
	
protected:
	/// Constructor
	IBuffer() {};
	
public:
	/// Destructor
	virtual ~IBuffer() {}
	
};

} // NLSOUND

#endif // NL_BUFFER_H

/* End of buffer.h */
