/** \file buffer_al.cpp
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

#include "stdopenal.h"
#include "buffer_al.h"

#include <nel/misc/fast_mem.h>

#include "sound_driver_al.h"

using namespace NLMISC;

namespace NLSOUND {

CBufferAL::CBufferAL(ALuint buffername) :
	IBuffer(), _BufferName(buffername), _SampleFormat(AL_INVALID), _Frequency(0),
	_Data(NULL), _Size(0), _StorageMode(IBuffer::StorageAuto), _Capacity(0)
{
	
}

CBufferAL::~CBufferAL()
{
	// delete local copy
	if (_Data != NULL)
	{
		delete[] _Data;
		_Data = NULL;
	}

	// delete OpenAL copy
	CSoundDriverAL *sdal = CSoundDriverAL::getInstance();
	//nlinfo("AL: Deleting buffer (name %u)", _BufferName );
	sdal->removeBuffer( this );
}

/** Preset the name of the buffer. Used for async loading to give a name
 *	before the buffer is effectivly loaded.
 *	If the name after loading of the buffer doesn't match the preset name,
 *	the load will assert.
 */
void CBufferAL::presetName(NLMISC::TStringId bufferName)
{
	_Name = bufferName;
}

/// Set the sample format. (channels = 1, 2, ...; bitsPerSample = 8, 16; frequency = samples per second, 44100, ...)
void CBufferAL::setFormat(TBufferFormat format, uint8 channels, uint8 bitsPerSample, uint32 frequency)
{
	TSampleFormat sampleFormat;
	bufferFormatToSampleFormat(format, channels, bitsPerSample, sampleFormat);
	switch (sampleFormat) 
	{
		case Mono8: _SampleFormat = AL_FORMAT_MONO8; break;
		case Mono16: _SampleFormat = AL_FORMAT_MONO16; break;
		case Stereo8: _SampleFormat = AL_FORMAT_STEREO8; break;
		case Stereo16: _SampleFormat = AL_FORMAT_STEREO16; break;
		default: nlstop; _SampleFormat = AL_INVALID;
	}
	_Frequency = frequency;
}

/// Get a writable pointer to the buffer of specified size. Returns NULL in case of failure. It is only guaranteed that the original data is still available when using StorageSoftware and the specified size is not larger than the available data. Call setStorageMode() and setFormat() first.
uint8 *CBufferAL::lock(uint capacity)
{
	nlassert((_SampleFormat != AL_INVALID) && (_Frequency != 0));

	if (_Data)
	{
		if (capacity > _Capacity) 
		{
			delete[] _Data;
			_Data = NULL;
		}
	}
	
	if (!_Data) _Data = new uint8[capacity];
	if (_Size > capacity) _Size = capacity;
	_Capacity = capacity;
	
	return _Data;
}

/// Notify that you are done writing to this buffer, so it can be copied over to hardware if needed. Returns true if ok.
bool CBufferAL::unlock(uint size)
{
	if (size > _Capacity) 
	{
		_Size = _Capacity;
		return false;
	}
	
	// Fill buffer (OpenAL one)
	_Size = size;
	alBufferData(_BufferName, _SampleFormat, _Data, _Size, _Frequency);
	
	if (_StorageMode != IBuffer::StorageSoftware && !CSoundDriverAL::getInstance()->getOption(ISoundDriver::OptionLocalBufferCopy))
	{
		delete[] _Data;
		_Data = NULL;
		_Capacity = 0;
	}

	// Error handling
	return (alGetError() == AL_NO_ERROR);
}

/// Copy the data with specified size into the buffer. A readable local copy is only guaranteed when OptionLocalBufferCopy is set. Returns true if ok.
bool CBufferAL::fill(const uint8 *src, uint size)
{
	nlassert((_SampleFormat != AL_INVALID) && (_Frequency != 0));

	bool localBufferCopy = CSoundDriverAL::getInstance()->getOption(ISoundDriver::OptionLocalBufferCopy);

	if (_Data)
	{
		if ((!localBufferCopy) || (size > _Capacity)) 
		{
			delete[] _Data;
			_Data = NULL;
			_Capacity = 0;
		}
	}
	
	_Size = size;
	
	if (localBufferCopy)
	{
		// Force a local copy of the buffer
		if (!_Data) 
		{
			_Data = new uint8[size];
			_Capacity = size;
		}
		CFastMem::memcpy(_Data, src, size);
	}
	
	// Fill buffer (OpenAL one)
	alBufferData(_BufferName, _SampleFormat, src, size, _Frequency);

	// Error handling
	return (alGetError() == AL_NO_ERROR);
}

/// Return the sample format informations.
void CBufferAL::getFormat(TBufferFormat &format, uint8 &channels, uint8 &bitsPerSample, uint32 &frequency) const
{
	TSampleFormat sampleFormat;
	switch (_SampleFormat)
	{
		case AL_FORMAT_MONO8: sampleFormat = Mono8; break;
		case AL_FORMAT_MONO16: sampleFormat = Mono16; break;
		case AL_FORMAT_STEREO8: sampleFormat = Stereo8; break;
		case AL_FORMAT_STEREO16: sampleFormat = Stereo16; break;
		default: sampleFormat = (TSampleFormat)~0; nlstop;
	}
	sampleFormatToBufferFormat(sampleFormat, format, channels, bitsPerSample);
	frequency = _Frequency;
}


/*
 * Return the size of the buffer, in bytes
 */
uint32 CBufferAL::getSize() const
{
	return _Size;
	/*ALint value;
	alGetBufferi(_BufferName, AL_SIZE, &value);
	nlassert(alGetError() == AL_NO_ERROR);
	return value;*/
}

/*
 * Return the duration (in ms) of the sample in the buffer
 */
float CBufferAL::getDuration() const
{
	if ( _Frequency == 0 )
		return 0;

	uint32 bytespersample;
	switch ( _SampleFormat ) {
		case AL_FORMAT_MONO8:
			bytespersample = 1;
			break;

		case AL_FORMAT_MONO16:
		case AL_FORMAT_STEREO8:
			bytespersample = 2;
			break;

		case AL_FORMAT_STEREO16:
			bytespersample = 4;
			break;

		default:
			return 0;
	}

	return (float)(getSize()) * 1000.0f / (float)_Frequency / (float)bytespersample;
}

/*
 * Return true if the buffer is stereo, false if mono
 */
bool CBufferAL::isStereo() const
{
	return (_SampleFormat==AL_FORMAT_STEREO8) || (_SampleFormat==AL_FORMAT_STEREO16);
}

/// Return the name of this buffer
NLMISC::TStringId CBufferAL::getName() const
{
	return _Name;
}

bool CBufferAL::isBufferLoaded() const
{
	return (_SampleFormat != AL_INVALID && _Data != NULL && _Size > 0 && _Frequency > 0);
}

	
/// Set the storage mode of this buffer, call before filling this buffer. Storage mode is always software if OptionSoftwareBuffer is enabled. Default is auto.
void CBufferAL::setStorageMode(TStorageMode storageMode)
{
	_StorageMode = storageMode;
}

/// Get the storage mode of this buffer.
IBuffer::TStorageMode CBufferAL::getStorageMode()
{
	return _StorageMode;
}

/**
 * Made after CBufferFMod, with a few changes and additional
 * support for the 8bit data stuff.
 */
uint32 CBufferAL::getBufferMono16(std::vector<sint16> &result)
{
	// don't do anything if the current buffer has no format
	if (_SampleFormat == AL_INVALID)
		return 0;

	if (_Data == NULL || _Size == 0)
		return 0;

	// clear result buffer
	result.clear();

	// and fill it with data depending on the _SampleFormat
	uint nbSample = 0;
	switch (_SampleFormat) {

		case AL_FORMAT_MONO16:

			nbSample = _Size / 2;

			result.reserve(nbSample);
			result.insert(result.begin(), (sint16*)_Data, ((sint16*)_Data)+nbSample);

			return nbSample;

		case AL_FORMAT_STEREO16:
			{
				nbSample = _Size / 4;

				result.reserve(nbSample);
				TFrameStereo<sint16> *frame = (TFrameStereo<sint16> *)_Data;
				for (uint i = 0; i < nbSample; i++) {
					sint32 tmp = (sint32)frame[i].Channel1 + (sint32)frame[i].Channel2;
					// round up in case lowest bit is 1
					tmp = tmp + (tmp & 1);
					// make the final result 16bit wide again
					result[i] = (sint16)(tmp >> 1);
				}

				return nbSample;
			}

		case AL_FORMAT_MONO8:

			nbSample = _Size;

			result.reserve(nbSample);
			for (uint i = 0; i < nbSample; i++)
				result[i] = ((sint16)_Data[i]) << 8;

			return nbSample;

		case AL_FORMAT_STEREO8:
			{
				nbSample = _Size / 2;

				result.reserve(nbSample);
				TFrameStereo<sint8> *frame = (TFrameStereo<sint8> *)_Data;
				for (uint i = 0; i < nbSample; i++) {
					sint16 tmp = (sint16)frame[i].Channel1 + (sint16)frame[i].Channel2;
					result[i] = tmp << 7;
				}

				return nbSample;
			}
	}

	// Failure
	return 0;
}

uint32 CBufferAL::getBufferADPCMEncoded(std::vector<uint8> &result)
{
	if (_SampleFormat != AL_FORMAT_MONO16)
		return 0;

	if (_Data == NULL || _Size == 0)
		return 0;

	result.clear();

	// Allocate ADPCM dest
	uint32 nbSample = _Size / 2;
	nbSample &= 0xfffffffe; // make it even, may miss one sample, though
	result.resize(nbSample / 2);

	// encode
	TADPCMState	state;
	state.PreviousSample = 0;
	state.StepIndex = 0;
	encodeADPCM((sint16*)_Data, &result[0], nbSample, state);

	return nbSample;
}


} // NLSOUND
