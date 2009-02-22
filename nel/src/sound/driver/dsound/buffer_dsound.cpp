/** \file buffer_dsound.cpp
 * DirectSound sound buffer
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


#include "stddsound.h"
#include "buffer_dsound.h"
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "sound_driver_dsound.h"

#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>

using namespace NLMISC;
using namespace std;

namespace NLSOUND {

static const std::string	EmptyString;

// Custom mutimedia IO proc.
/*LRESULT NelIOProc(LPSTR lpmmioinfo, UINT uMsg, LONG lParam1, LONG lParam2)
{
	MMIOINFO *mmioinfo = (MMIOINFO*) lpmmioinfo;

	switch (uMsg)
	{
	case MMIOM_OPEN:
		{
			// do some validity checking.
			nlassert((mmioinfo->dwFlags & MMIO_CREATE) == 0);

			char *fileName = (char*)lParam1;
			std::string fullName = NLMISC::CPath::lookup(fileName, false);
			if (fullName.empty())
			{
				mmioinfo->adwInfo[0] = NULL;
				return MMIOERR_CANNOTOPEN;
			}

			NLMISC::CIFile	*pfile = new NLMISC::CIFile(fullName);

			mmioinfo->adwInfo[0] = (DWORD)pfile;
			return MMSYSERR_NOERROR ;
		}
		break;
	case MMIOM_CLOSE:
		{
			NLMISC::CIFile *file = (NLMISC::CIFile *)mmioinfo->adwInfo[0];
			delete file;
			return 0;
		}
		break;
	case MMIOM_READ:
		{
			uint8 *pdst = (uint8*) lParam1;
			uint  bytes = (uint) lParam2;

			nlassert(mmioinfo->adwInfo[0] != NULL);
			NLMISC::CIFile *file = (NLMISC::CIFile *)mmioinfo->adwInfo[0];
			bytes = std::min(uint(file->getFileSize() - file->getPos()), bytes);
			file->serialBufferWithSize(pdst, bytes);

			mmioinfo->lBufOffset = file->getPos();

			return bytes;
		}
		break;
	case MMIOM_SEEK:
		{
			uint newPos = (uint) lParam1;
			uint seekMode = lParam2;

			nlassert(mmioinfo->adwInfo[0] != NULL);
			NLMISC::CIFile *file = (NLMISC::CIFile *)mmioinfo->adwInfo[0];

			switch(seekMode)
			{
			case SEEK_CUR:
				file->seek(newPos, NLMISC::IStream::current);
				break;
			case SEEK_END:
				file->seek(newPos, NLMISC::IStream::end);
				break;
			case SEEK_SET:
				file->seek(newPos, NLMISC::IStream::begin);
				break;
			}

			mmioinfo->lBufOffset = file->getPos();

			return mmioinfo->lBufOffset;
		}
		break;
	case MMIOM_WRITE:
		nlassert("Mutimedia IO write is not supported !");
		break;
	case MMIOM_WRITEFLUSH:
		nlassert("Mutimedia IO write is not supported !");
		break;
	}
}
*/


CBufferDSound::CBufferDSound()
{
	_Name = CSoundDriverDSound::instance()->getStringMapper()->map(EmptyString);
    _Data = NULL;
    _Size = 0;
    _Format = Mono16;
    _Freq = 0;
}

CBufferDSound::~CBufferDSound()
{
//	nldebug("Destroying DirectSound buffer %s (%p)", CSoundDriverDSound::instance()->getStringMapper()->unmap(_Name).c_str(), this);

    if (_Data != NULL)
    {
        delete[] _Data;
    }
}

void CBufferDSound::presetName(const NLMISC::TStringId &bufferName)
{
	_Name = bufferName;
}

/// Set the sample format. (channels = 1, 2, ...; bitsPerSample = 8, 16; frequency = samples per second, 44100, ...)
void CBufferDSound::setFormat(TBufferFormat format, uint8 channels, uint8 bitsPerSample, uint frequency)
{
	bufferFormatToSampleFormat(format, channels, bitsPerSample, _Format);
	_Freq = frequency;
}

bool CBufferDSound::fillBuffer(const void *src, uint bufsize)
{
    return false;
}

/// Return the sample format informations.
void CBufferDSound::getFormat(TBufferFormat &format, uint8 &channels, uint8 &bitsPerSample, uint &frequency) const
{
	sampleFormatToBufferFormat(_Format, format, channels, bitsPerSample);
	frequency = _Freq;
}

/// Return the size of the buffer, in bytes.
uint CBufferDSound::getSize() const
{
	return _Size;
}

float CBufferDSound::getDuration() const
{
    float frames = (float) _Size;

    switch (_Format)
	{
    case Mono8:
        break;
    case Mono16ADPCM:
        frames *= 2.0f;
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

    return 1000.0f * frames / (float) _Freq;
}

bool CBufferDSound::isStereo() const
{
	return (_Format == Stereo8) || (_Format == Stereo16);
}

/// Return the name of this buffer
NLMISC::TStringId CBufferDSound::getName() const
{
	return _Name;
}

/// Return true if the buffer is loaded. Used for async load/unload.
bool CBufferDSound::isBufferLoaded() const
{
	return _Data != NULL;
}

	
/// Set the storage mode of this buffer, call before filling this buffer. Storage mode is always software if OptionSoftwareBuffer is enabled. Default is auto.
void CBufferDSound::setStorageMode(TStorageMode /* storageMode */)
{
	// not implemented
}

/// Get the storage mode of this buffer.
IBuffer::TStorageMode CBufferDSound::getStorageMode()
{
	// not implemented
	return IBuffer::StorageAuto;
}

bool CBufferDSound::readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize)
{
    sint error;
    sint32 num;
    HMMIO hmmio;
    WAVEFORMATEX format;
    MMCKINFO riff_chunk;
    MMCKINFO data_chunk;
    MMCKINFO chunk;


    if (_Data != NULL)
    {
        delete [] _Data;
        _Data = NULL;
    }

/*	NLMISC::CIFile	ifile(file);
	uint size = ifile.getFileSize();
	uint8 *buffer = new uint8[ifile.getFileSize()];
	ifile.serialBuffer(buffer, size);
*/
	uint size = dataSize;
	uint8 *buffer = wavData;

	MMIOINFO mmioInfo;
	memset(&mmioInfo, 0, sizeof(mmioInfo));
	mmioInfo.pchBuffer = (char*)buffer;
	mmioInfo.fccIOProc = FOURCC_MEM;
	mmioInfo.cchBuffer = size;


    hmmio = mmioOpen(NULL, &mmioInfo, MMIO_READ | MMIO_DENYWRITE);

    if (hmmio == NULL)
    {
        throw ESoundDriver("Failed to open the file");
    }


    // Check it's a WAVE file
    riff_chunk.ckid = FOURCC_RIFF;

    error = (sint) mmioDescend(hmmio, &riff_chunk, NULL, 0);

    if ((error != 0) || (riff_chunk.ckid != FOURCC_RIFF) || (riff_chunk.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Not a WAVE file");
    }


    // Search the format chunk
    chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');

    error = (sint) mmioDescend(hmmio, &chunk, &riff_chunk, MMIO_FINDCHUNK);

    if (error != 0)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Couldn't find the format chunk");
    }

    if (chunk.cksize < (long) sizeof(PCMWAVEFORMAT))
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Invalid format chunk size");
    }


    // read in the format data

    num = mmioRead(hmmio, (HPSTR) &format, (long) sizeof(format));
    if (num != (long) sizeof(format))
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Read failed");
    }

    format.cbSize = 0;

    // Get out of the format chunk

    if (mmioAscend(hmmio, &chunk, 0) != 0)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Read failed");
    }


    // copy the format data

    if (format.wFormatTag != WAVE_FORMAT_PCM)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Unsupported sample format");
    }

    _Freq = format.nSamplesPerSec;

    if (format.nChannels == 1)
    {
        if (format.wBitsPerSample == 8)
        {
            _Format = Mono8;
        }
        else if (format.wBitsPerSample == 16)
        {
            _Format = Mono16;
        }
        else
        {
            mmioClose(hmmio, 0);
            throw ESoundDriver("Unsupported sample size");
        }
    }
    else if (format.nChannels == 2)
    {
        if (format.wBitsPerSample == 8)
        {
            _Format = Stereo8;
        }
        else if (format.wBitsPerSample == 16)
        {
            _Format = Stereo16;
        }
        else
        {
            mmioClose(hmmio, 0);
            throw ESoundDriver("Unsupported sample size");
        }
    }
    else // Shouldn't normally happen
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Unsupported number of channels");
    }


    // Set the file position to the beginning of the data chunk */

    sint32 pos = mmioSeek(hmmio, riff_chunk.dwDataOffset + sizeof(FOURCC), SEEK_SET);

    if (pos < 0)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Read to set the read position");
    }

    data_chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');

    if (mmioDescend(hmmio, &data_chunk, &riff_chunk, MMIO_FINDCHUNK) != 0)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Read to set the read position");
    }


    // Allocate the sample buffer
    _Size = data_chunk.cksize;

    _Data = new uint8[_Size];

    if (_Data == NULL)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Out of memory");
    }


    // Read the sample data

    num = mmioRead(hmmio, (HPSTR) _Data, _Size);

    if (num < 0)
    {
		delete [] _Data;
		_Data= NULL;
        throw ESoundDriver("Failed to read the samples");
    }
    else if ((uint32) num < _Size)
    {
        // FIXME: print warning or throw exception ???
        char* p = (char*) _Data;
        ZeroMemory(p + num, _Size - num);
    }


    mmioClose(hmmio, 0);

	static NLMISC::TStringId	empty(CSoundDriverDSound::instance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverDSound::instance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	// if name is preseted, the name must match.
	if (_Name != empty)
	{
		nlassertex(nameId == _Name, ("The preseted name and buffer name doen't match !"));
	}
	_Name = nameId;

	return true;
}


bool CBufferDSound::readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	// free any existing data
    if (_Data != NULL)
    {
        delete [] _Data;
        _Data = NULL;
    }

	_Format = format;
	_Size = dataSize;
    // Allocate the sample buffer
	_Data = new uint8 [_Size];

    // read in the format data
	memcpy(_Data, rawData, dataSize);

    _Freq = frequency;


    // Allocate the sample buffer

	static NLMISC::TStringId	empty(CSoundDriverDSound::instance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverDSound::instance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	// if name is preseted, the name must match.
	if (_Name != empty)
	{
		nlassertex(nameId == _Name, ("The preseted name and buffer name doen't match !"));
	}
	_Name = nameId;

	return true;
}

uint32 CBufferDSound::getBufferADPCMEncoded(vector<uint8> &result)
{
	result.clear();

	if (_Data == 0)
		return 0;

	if (_Format != Mono16)
		return 0;

	uint32 nbSample = _Size/2;
	nbSample &= 0xfffffffe;

	result.resize(nbSample / 2);

	TADPCMState	state;
	state.PreviousSample = 0;
	state.StepIndex = 0;
	encodeADPCM((sint16*)_Data, &result[0], nbSample, state);

	return nbSample;
}

uint32 CBufferDSound::getBufferMono16(std::vector<sint16> &result)
{
	result.clear();

	if (_Data == 0)
		return 0;

	if (_Format == Mono16)
	{
		uint nbSample = _Size/2;
		nbSample &= 0xfffffffe;

		result.reserve(nbSample);
		result.insert(result.begin(), (sint16*)_Data, ((sint16*)_Data)+nbSample);

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
			result[i] = (frame->Channel1>>1) +(frame->Channel2>>1);
		}

		return nbSample;
	}
	else
		return 0;
}


} // NLSOUND



