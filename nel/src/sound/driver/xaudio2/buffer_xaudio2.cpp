/**
 * \file buffer_xaudio2.cpp
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

#include "stdxaudio2.h"
#include "buffer_xaudio2.h"

// STL includes

// NeL includes
#include <nel/misc/debug.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>

// Project includes
#include "sound_driver_xaudio2.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CBufferXAudio2::CBufferXAudio2(CSoundDriverXAudio2 *soundDriver) 
: _SoundDriver(soundDriver), _Data(NULL), 
_Size(0), _Name(NULL), _Format((IBuffer::TBufferFormat)~0),
_Channels(0), _BitsPerSample(0), _Frequency(0)
{
	
}

CBufferXAudio2::~CBufferXAudio2()
{
	release();
}

void CBufferXAudio2::release()
{
	if (_SoundDriver)
	{
		// Remove the buffer from the driver.
		_SoundDriver->removeBuffer(this);
		// Update stats.
		_SoundDriver->performanceUnregisterBuffer(_Format, _Size);
		_SoundDriver = NULL;
	}
	// Release possible _Data
	delete[] _Data; _Data = NULL;
}

/// Allocate a new writable buffer. If this buffer was already allocated, the previous data is released.
/// May return NULL if the format or frequency is not supported by the driver.
uint8 *CBufferXAudio2::openWritable(uint size, TBufferFormat bufferFormat, uint8 channels, uint8 bitsPerSample, uint32 frequency)
{
	if (_Data)
	{
		_SoundDriver->performanceUnregisterBuffer(_Format, _Size);
		if (size > _Size) delete[] _Data; _Data = NULL;
	}
	
	if (!_Data) _Data = new uint8[size];
	
	_Format = bufferFormat;
	_Channels = channels;
	_BitsPerSample = bitsPerSample;
	_Frequency = frequency;
	_Size = size;
	
	_SoundDriver->performanceRegisterBuffer(_Format, _Size);
	
	return _Data;
}

/// Tell that you are done writing to this buffer, so it can be copied over to hardware if needed.
/// If keepLocal is true, a local copy of the buffer will be kept (so allocation can be re-used later).
/// keepLocal overrides the OptionLocalBufferCopy flag. The buffer can use this function internally.
void CBufferXAudio2::lockWritable(bool keepLocal)
{
	// does nothing in this driver
}

bool CBufferXAudio2::readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize)
{
	TSampleFormat format = (TSampleFormat)~0;

	// If name has been preset, it must match.
	static NLMISC::TStringId empty(CSoundDriverXAudio2::getInstance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverXAudio2::getInstance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	if (nameId != empty) nlassertex(nameId == _Name, ("The preset buffer name doesn't match!"));
	_Name = nameId;

	// Create mmio stuff
	MMIOINFO mmioinfo;
	memset(&mmioinfo, 0, sizeof(MMIOINFO));
	mmioinfo.fccIOProc = FOURCC_MEM;
	mmioinfo.pchBuffer = (HPSTR)wavData;
	mmioinfo.cchBuffer = dataSize;
	HMMIO hmmio = mmioOpen(NULL, &mmioinfo, MMIO_READ | MMIO_DENYWRITE);
	if (!hmmio) { throw ESoundDriver("Failed to open the file"); }

	// Find wave
	MMCKINFO mmckinforiff;
	memset(&mmckinforiff, 0, sizeof(MMCKINFO));
	mmckinforiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(hmmio, &mmckinforiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) { mmioClose(hmmio, 0); throw ESoundDriver("mmioDescend WAVE failed"); }

	// Find fmt
	MMCKINFO mmckinfofmt;
	memset(&mmckinfofmt, 0, sizeof(MMCKINFO));
	mmckinfofmt.ckid = mmioFOURCC('f', 'm', 't', ' '); 
	if (mmioDescend(hmmio, &mmckinfofmt, &mmckinforiff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) { mmioClose(hmmio, 0); throw ESoundDriver("mmioDescend fmt failed"); }
	WAVEFORMATEX *wavefmt = (WAVEFORMATEX *)(&wavData[mmckinfofmt.dwDataOffset]);
	if (mmioAscend(hmmio, &mmckinfofmt, 0) != MMSYSERR_NOERROR) { mmioClose(hmmio, 0); throw ESoundDriver("mmioAscend fmt failed"); }

	// Find data
	MMCKINFO mmckinfodata;
	memset(&mmckinfodata, 0, sizeof(MMCKINFO));
	mmckinfodata.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmio, &mmckinfodata, &mmckinforiff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) { mmioClose(hmmio, 0); throw ESoundDriver("mmioDescend data failed"); }
	BYTE *wavedata = (BYTE *)(&wavData[mmckinfodata.dwDataOffset]);
	if (mmioAscend(hmmio, &mmckinfodata, 0) != MMSYSERR_NOERROR) { mmioClose(hmmio, 0); throw ESoundDriver("mmioAscend data failed"); }

	// Close mmio
	mmioClose(hmmio, 0);

	// Get format
	switch (wavefmt->nChannels)
	{
	case 1:
		switch (wavefmt->wFormatTag)
		{
		case WAVE_FORMAT_PCM:
			switch (wavefmt->wBitsPerSample)
			{
			case 8:
				format = Mono8;
				break;
			case 16:
				format = Mono16;
				break;
			default:
				throw ESoundDriver(toString("wBitsPerSample invalid (%i)", (sint32)wavefmt->wBitsPerSample));
			}
			break;
		case WAVE_FORMAT_ADPCM:
			switch (wavefmt->wBitsPerSample)
			{
			case 16:
				format = Mono16ADPCM;
				break;
			default:
				throw ESoundDriver(toString("wBitsPerSample invalid (%i)", (sint32)wavefmt->wBitsPerSample));
			}
			break;
		default:
			throw ESoundDriver(toString("wFormatTag invalid (%i)", (sint32)wavefmt->wFormatTag));
		}
		break;
	case 2:
		switch (wavefmt->wFormatTag)
		{
		case WAVE_FORMAT_PCM:
			switch (wavefmt->wBitsPerSample)
			{
			case 8:
				format = Stereo8;
				break;
			case 16:
				format = Stereo16;
				break;
			default:
				throw ESoundDriver(toString("wBitsPerSample invalid (%i)", (sint32)wavefmt->wBitsPerSample));
			}
			break;
		default:
			throw ESoundDriver(toString("wFormatTag invalid (%i)", (sint32)wavefmt->wFormatTag));
		}
		break;
	default:
		throw ESoundDriver(toString("nChannels invalid (%i)", (sint32)wavefmt->nChannels));
	}

	// Copy stuff
	TBufferFormat bufferFormat;
	uint8 channels;
	uint8 bitsPerSample;
	sampleFormatToBufferFormat(format, bufferFormat, channels, bitsPerSample);
	uint8 *wbuffer = openWritable(mmckinfodata.cksize, bufferFormat, channels, bitsPerSample, wavefmt->nSamplesPerSec);
	CFastMem::memcpy(wbuffer, wavedata, mmckinfodata.cksize);
	lockWritable(true);
	return true;
}

bool CBufferXAudio2::readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat sampleFormat, uint32 frequency)
{
	// If name has been preset, it must match.
	static NLMISC::TStringId empty(CSoundDriverXAudio2::getInstance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverXAudio2::getInstance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	if (nameId != empty) nlassertex(nameId == _Name, ("The preset buffer name doesn't match!"));
	_Name = nameId;

	// Copy stuff from params
	TBufferFormat bufferFormat;
	uint8 channels;
	uint8 bitsPerSample;
	sampleFormatToBufferFormat(sampleFormat, bufferFormat, channels, bitsPerSample);
	uint8 *wbuffer = openWritable(dataSize, bufferFormat, channels, bitsPerSample, frequency);
	CFastMem::memcpy(wbuffer, rawData, dataSize);
	lockWritable(true);
	return true;
}

/** Preset the name of the buffer. Used for async loading to give a name
 *	before the buffer is effectivly loaded.
 *	If the name after loading of the buffer doesn't match the preset name,
 *	the load will assert.
 */
void CBufferXAudio2::presetName(const NLMISC::TStringId &bufferName)
{
	_Name = bufferName;
}

void CBufferXAudio2::setFormat(TBufferFormat format, uint8 channels, uint8 bitsPerSample, uint frequency)
{
	_Format = format;
	_Channels = channels;
	_Frequency = frequency;
	_BitsPerSample = bitsPerSample;
}

/// Set the buffer size and fill the buffer.  Return true if ok. Call setStorageMode() and setFormat() first.
bool CBufferXAudio2::fillBuffer(const void *src, uint bufsize)
{
	uint8* wbuffer = openWritable(bufsize, _Format, _Channels, _BitsPerSample, _Frequency);
	CFastMem::memcpy(wbuffer, src, bufsize);
	lockWritable(true);
	return true;
}

/// Return the sample format informations.
void CBufferXAudio2::getFormat(TBufferFormat &format, uint8 &channels, uint8 &bitsPerSample, uint &frequency) const
{
	format = _Format;
	channels = _Channels;
	bitsPerSample = _BitsPerSample;
	frequency = _Frequency;
}

/// Return the size of the buffer, in bytes
uint CBufferXAudio2::getSize() const
{
	return _Size;
}

/// Return the duration (in ms) of the sample in the buffer
float CBufferXAudio2::getDuration() const
{
	float frames = (float)_Size;

	switch (_Format) 
	{
	case FormatADPCM:
		nlassert(_Channels == 1 && _BitsPerSample == 16);
		frames *= 2.0f;
		break;
	case FormatPCM:
		frames /= (((float)_BitsPerSample) / 8.0f);
		frames /= ((float)_Channels);
		break;
	}

	return 1000.0f * frames / (float)_Frequency;
}

/// Return true if the buffer is stereo, false if mono
bool CBufferXAudio2::isStereo() const
{
	return _Channels > 1;
}

/// Return the name of this buffer
NLMISC::TStringId CBufferXAudio2::getName() const
{
	return _Name;
}

/// Return true if the buffer is loaded. Used for async load/unload.
bool CBufferXAudio2::isBufferLoaded() const
{
	return _Data != NULL;
}
	
/// Set the storage mode of this buffer, call before filling this buffer. Storage mode is always software if OptionSoftwareBuffer is enabled. Default is auto.
void CBufferXAudio2::setStorageMode(IBuffer::TStorageMode /* storageMode */)
{
	// software sound, no hardware storage mode
}

/// Get the storage mode of this buffer.
IBuffer::TStorageMode CBufferXAudio2::getStorageMode()
{
	return IBuffer::StorageSoftware;
}

/** Unoptimized utility function designed to build ADPCM encoded sample bank file.
 *	Return the number of sample in the buffer.
 */
uint32 CBufferXAudio2::getBufferADPCMEncoded(std::vector<uint8> &result)
{
	// from NLSOUND DSound Driver, Copyright (C)  2001 Nevrax Ltd.
	// from NLSOUND FMod Driver, Copyright (C)  2001 Nevrax Ltd.

	// Prepare empty result
	result.clear();

	// Verify Buffer
	if (!_Data) return 0;
	if (_Format != Mono16) return 0;

	// Allocate ADPCM dest
	uint32 nbSample = _Size / 2;
	nbSample &= 0xfffffffe;
	result.resize(nbSample / 2);

	// Encode
	TADPCMState	state;
	state.PreviousSample = 0;
	state.StepIndex = 0;
	encodeADPCM((sint16*)_Data, &result[0], nbSample, state);

	// Return result
	return nbSample;
}

/** Unoptimized utility function designed to build Mono 16 bits encoded sample bank file.
 *	Return the number of sample in the buffer.
 */
uint32 CBufferXAudio2::getBufferMono16(std::vector<sint16> &result)
{
	// from NLSOUND DSound Driver, Copyright (C)  2001 Nevrax Ltd.

	result.clear();

	if (!_Data) return 0;

	if (_Format == Mono16)
	{
		uint nbSample = _Size / 2;
		nbSample &= 0xfffffffe;

		result.reserve(nbSample);
		result.insert(result.begin(), (sint16*)_Data, ((sint16*)_Data) + nbSample);

		return nbSample;
	}
	else if (_Format == Stereo16)
	{
		uint nbSample = _Size/4;
		nbSample &= 0xfffffffe;

		struct TFrame
		{
			sint16	Channel1;
			sint16	Channel2;
		};
		result.reserve(nbSample);
		TFrame *frame = (TFrame *)_Data;
		for (uint i=0; i<nbSample; ++i)
		{
			result[i] = (sint16)(((sint32)frame->Channel1 + (sint32)frame->Channel2) / 2);
		}

		return nbSample;
	}
	else
		return 0;
}

} /* namespace NLSOUND */

/* end of file */
