/**
 * \file buffer_xaudio2.cpp
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

/*
 * TODO:
 *  - ADPCM
 *    - ADPCMWAVEFORMAT
 *  - Fill More
 *    - fillBuffer
 *    - isFillMoreSupported
 *    - setSize
 *    - fillMore
 */

#include "stdxaudio2.h"
#include "buffer_xaudio2.h"

// Project includes

// NeL includes
#include <nel/misc/debug.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>

// STL includes

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CBufferXAudio2::CBufferXAudio2() : _Data(NULL)
{
	
}

CBufferXAudio2::~CBufferXAudio2()
{
	CSoundDriverXAudio2::getInstance()->removeBuffer(this);

	// Release possible _Data
	delete[] _Data; _Data = NULL;
}

//void CBufferXAudio2::release()
//{
//
//}

bool CBufferXAudio2::readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize)
{
	// "Allocate the sample" buffer or something
	static NLMISC::TStringId empty(CSoundDriverXAudio2::getInstance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverXAudio2::getInstance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	// If name has been preset, it must match.
	if (nameId != empty) nlassertex(nameId == _Name, ("The preset buffer name doesn't match!"));
	_Name = nameId;

	// Free any existing _Data if it exists
	delete[] _Data; _Data = NULL;

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
				_Format = Mono8;
				break;
			case 16:
				_Format = Mono16;
				break;
			default:
				throw ESoundDriver(toString("wBitsPerSample invalid (%i)", (sint32)wavefmt->wBitsPerSample));
			}
			break;
		case WAVE_FORMAT_ADPCM:
			switch (wavefmt->wBitsPerSample)
			{
			case 16:
				_Format = Mono16ADPCM;
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
				_Format = Stereo8;
				break;
			case 16:
				_Format = Stereo16;
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

	// Get frequency
	_Freq = wavefmt->nSamplesPerSec;

	// Copy stuff
	_Size = mmckinfodata.cksize;
	_Data = new uint8[_Size];
	CFastMem::memcpy(_Data, wavedata, _Size);
	return true;
}

bool CBufferXAudio2::readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	// "Allocate the sample" buffer or something
	static NLMISC::TStringId empty(CSoundDriverXAudio2::getInstance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverXAudio2::getInstance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	// If name has been preset, it must match.
	if (nameId != empty) nlassertex(nameId == _Name, ("The preset buffer name doesn't match!"));
	_Name = nameId;

	// Free any existing _Data if it exists
	delete[] _Data; _Data = NULL;

	// Copy stuff from params
	_Format = format;
	_Size = dataSize;
	_Data = new BYTE[dataSize];
	CFastMem::memcpy(_Data, rawData, dataSize);
	_Freq = frequency;
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

/// Set the sample format. Example: freq=44100
void CBufferXAudio2::setFormat(TSampleFormat format, uint freq)
{
    _Format = format;
    _Freq = freq;
}

/// Set the buffer size and fill the buffer.  Return true if ok. Call setFormat() first.
bool CBufferXAudio2::fillBuffer(void *src, uint32 bufsize)
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return false;
}

/// Return the size of the buffer, in bytes
uint32 CBufferXAudio2::getSize() const
{
	return _Size;
}

/// Return the duration (in ms) of the sample in the buffer
float CBufferXAudio2::getDuration() const
{
	// from NLSOUND DSound Driver, Copyright (C)  2001 Nevrax Ltd.

    float frames = (float)_Size;

    switch (_Format) 
	{
    case Mono8:
        break;
    case Mono16ADPCM:
        frames *= 2.0f; // don't think this is right...
        break;
    case Mono16:
        frames /= 2.0f;
        break;
    case Stereo8:
        frames /= 2.0f;
        break;
    case Stereo16:
        frames /= 4.0f;
        break;
    }

    return 1000.0f * frames / (float)_Freq;
}

/// Return true if the buffer is stereo, false if mono
bool CBufferXAudio2::isStereo() const
{
	return (_Format == Stereo8) || (_Format == Stereo16);
}

/// Return the format and frequency
void CBufferXAudio2::getFormat( TSampleFormat& format, uint& freq ) const
{
	format = _Format;
	freq = _Freq;
}

/** Return true if the buffer is able to be fill part by part, false if it must be filled in one call
 * OpenAL 1.0 -> false
 */
bool CBufferXAudio2::isFillMoreSupported() const
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return false;
}

/// Force the buffer size without filling data (if isFillMoreSupported() only)
void CBufferXAudio2::setSize(uint32 size)
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return;
}

/** Fill the buffer partially (if isFillMoreSupported() only),
 * beginning at the pos changed by a previous call to fillMore().
 * If the pos+srcsize exceeds the buffer size, the exceeding data is put at the beginning
 * of the buffer. srcsize must be smaller than the buffer size.
 */
bool CBufferXAudio2::fillMore(void *src, uint32 srcsize)
{
	// -- nlerror(NLSOUND_XAUDIO2_PREFIX "not implemented");
	return false;
}

/// Return the name of this buffer
const NLMISC::TStringId &CBufferXAudio2::getName()
{
	return _Name;
}

/// Return true if the buffer is loaded. Used for async load/unload.
bool CBufferXAudio2::isBufferLoaded()
{
	return _Data != NULL;
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
