/** \file buffer_fmod.cpp
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


#include "stdfmod.h"
#include "buffer_fmod.h"
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "sound_driver_fmod.h"

#ifdef NL_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#	include <mmsystem.h>
#endif

using namespace NLMISC;
using namespace std;

namespace NLSOUND {

static const std::string	EmptyString;


// ***************************************************************************
CBufferFMod::CBufferFMod()
{
	_Name = CSoundDriverFMod::instance()->getStringMapper()->map(EmptyString);
    _Size = 0;
    _Format = Mono16;
    _Freq = 0;
	_FModSample= NULL;
}

// ***************************************************************************
CBufferFMod::~CBufferFMod()
{
    if (_FModSample!=NULL)
    {
		// delete FMod sample
		loadDataToFMod(NULL);
    }
}

// ***************************************************************************
void CBufferFMod::presetName(const NLMISC::TStringId &bufferName)
{
	_Name = bufferName;
}


// ***************************************************************************
void CBufferFMod::setFormat( TSampleFormat format, uint freq )
{
    _Format = format;
    _Freq = freq;
}


// ***************************************************************************
bool CBufferFMod::fillBuffer( void *src, uint32 bufsize )
{
    return false;
}


// ***************************************************************************
float CBufferFMod::getDuration() const
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


// ***************************************************************************
bool CBufferFMod::readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize)
{

	if (_FModSample)
    {
		// delete FMod sample
		loadDataToFMod(NULL);
    }

#ifdef NL_OS_WINDOWS
    sint error;
    sint32 num;
    HMMIO hmmio;
    WAVEFORMATEX format;
    MMCKINFO riff_chunk;
    MMCKINFO data_chunk;
    MMCKINFO chunk;

	uint size = dataSize;

	MMIOINFO mmioInfo;
	memset(&mmioInfo, 0, sizeof(mmioInfo));
	mmioInfo.pchBuffer = (char*)wavData;
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

    uint8	*data = new uint8[_Size];

    if (data == NULL)
    {
        mmioClose(hmmio, 0);
        throw ESoundDriver("Out of memory");
    }


    // Read the sample data

    num = mmioRead(hmmio, (HPSTR) data, _Size);

    if (num < 0)
    {
		delete[] data;
		data= NULL;
        throw ESoundDriver("Failed to read the samples");
    }
    else if ((uint32) num < _Size)
    {
        // FIXME: print warning or throw exception ???
        char* p = (char*) data;
        ZeroMemory(p + num, _Size - num);
    }


    mmioClose(hmmio, 0);
 #else // NL_OS_WINDOWS
	char hdrstr[4];
	unsigned long Offset = 0L;

	const uint HDR_MAG_SIZE=4;
	const uint FMT_TAG_SIZE=2;

	// get the RIFF identifier
	memcpy(&hdrstr, wavData, HDR_MAG_SIZE);
	hdrstr[4]='\0';
	if(strcmp(hdrstr, "RIFF") == 0)
		Offset += HDR_MAG_SIZE;
	else
		throw ESoundDriver("Failed to read the RIFF identifier");

	// seek chunk size.
	Offset += HDR_MAG_SIZE;

	// check for wave format
	memcpy(&hdrstr, wavData+Offset, HDR_MAG_SIZE);
	hdrstr[4]='\0';
	if(strcmp(hdrstr, "WAVE") == 0)
		Offset += HDR_MAG_SIZE;
	else
		throw ESoundDriver("Not a WAVE format.");

	// check format id
	memcpy(&hdrstr, wavData+Offset, HDR_MAG_SIZE);
	hdrstr[4]='\0';
	if(strcmp(hdrstr, "fmt ") == 0)
		Offset+=HDR_MAG_SIZE;
	else
		throw ESoundDriver("Failed to read the fmt chunk ID.");

	// seek the format chunk size
	Offset += HDR_MAG_SIZE;

	// check the format tag, must be PCM
	short fmtTag;
	memcpy(&fmtTag, wavData+Offset, FMT_TAG_SIZE);
	if(fmtTag == 1)         // PCM
		Offset += FMT_TAG_SIZE;
	else // nothing else supported.
		throw ESoundDriver("Unsupported format.");

	// get the number of channels
	short channels;
	memcpy(&channels, wavData+Offset, FMT_TAG_SIZE);
	Offset += FMT_TAG_SIZE;

	// get the sample rate.
	long sampleRate;
	memcpy(&sampleRate, wavData+Offset, HDR_MAG_SIZE);
	Offset += HDR_MAG_SIZE;
	_Freq=sampleRate;

	// seek avg data rate size
	Offset += HDR_MAG_SIZE;

	// get bytes per sample
	short bytesPerSample;
	memcpy(&bytesPerSample, wavData+Offset, FMT_TAG_SIZE);
	if(bytesPerSample == 1)
		_Format = Mono8;
	else if(bytesPerSample == 2 && channels == 1)
		_Format = Mono16;
	else if(bytesPerSample == 2 && channels == 2)
		_Format = Stereo8;
	else if(bytesPerSample == 4)
		_Format = Stereo16;
	Offset += FMT_TAG_SIZE;

	// seek bits per sample
	Offset += FMT_TAG_SIZE;

	// go through and find the data.
	bool currentChunkData;
	uint8 *data=NULL;
	while(Offset < dataSize)
	{
		long chunkLength;
		currentChunkData=false;

		// get the chunk type
		memcpy(&hdrstr, wavData+Offset, HDR_MAG_SIZE);
		hdrstr[4]='\0';
		if(strcmp(hdrstr, "data") == 0)
			currentChunkData=true;
		Offset += HDR_MAG_SIZE;

		// get how big the up-coming chunk is.
		memcpy(&chunkLength, wavData+Offset, HDR_MAG_SIZE);
		Offset += HDR_MAG_SIZE;

		// if the chunk type was 'data' then copy the chunk for fmod
		if(currentChunkData)
		{
			_Size=chunkLength;
			data = new uint8[_Size];
			memcpy(data, wavData+Offset, _Size);
		}

		Offset += chunkLength;
	}
#endif

	static NLMISC::TStringId	empty(CSoundDriverFMod::instance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverFMod::instance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	// if name is preseted, the name must match.
	if (_Name != empty)
	{
		nlassertex(nameId == _Name, ("The preseted name and buffer name doen't match !"));
	}
	_Name = nameId;

	// Load to FMOD
	loadDataToFMod(data);

	return true;
}


// ***************************************************************************
bool CBufferFMod::readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	// free any existing data
    if (_FModSample != NULL)
    {
		// delete FMod sample
		loadDataToFMod(NULL);
    }

	_Format = format;
	_Size = dataSize;
    _Freq = frequency;


    // Allocate the sample buffer
	static NLMISC::TStringId	empty(CSoundDriverFMod::instance()->getStringMapper()->map(""));
	NLMISC::TStringId nameId = CSoundDriverFMod::instance()->getStringMapper()->map(CFile::getFilenameWithoutExtension(name));
	// if name is preseted, the name must match.
	if (_Name != empty)
	{
		nlassertex(nameId == _Name, ("The preseted name and buffer name doen't match !"));
	}
	_Name = nameId;

	// Load to FMod
	loadDataToFMod(rawData);

	return true;
}

// ***************************************************************************
uint32 CBufferFMod::getBufferADPCMEncoded(vector<uint8> &result)
{
	result.clear();

	if (_FModSample == NULL)
		return 0;

	if (_Format != Mono16)
		return 0;

	// Lock FMOD Sample
	void	*data= lock();
	if(!data)
		return 0;

	// Allocate ADPCM dest
	uint32 nbSample = _Size/2;
	nbSample &= 0xfffffffe;
	result.resize(nbSample / 2);

	// encode
	TADPCMState	state;
	state.PreviousSample = 0;
	state.StepIndex = 0;
	encodeADPCM((sint16*)data, &result[0], nbSample, state);

	// Unlock FMOD sample
	unlock(data);

	return nbSample;
}

// ***************************************************************************
uint32 CBufferFMod::getBufferMono16(std::vector<sint16> &result)
{
	result.clear();

	if (_FModSample == 0)
		return 0;

	if (_Format == Mono16)
	{
		// lock FMOD sample
		void	*data= lock();
		if(data)
		{
			uint nbSample = _Size/2;
			nbSample &= 0xfffffffe;

			result.reserve(nbSample);
			result.insert(result.begin(), (sint16*)data, ((sint16*)data)+nbSample);

			// unlock FMOD sample
			unlock(data);

			return nbSample;
		}
	}
	else if (_Format == Stereo16)
	{
		// lock FMOD sample
		void	*data= lock();
		if(data)
		{
			uint nbSample = _Size/4;
			nbSample &= 0xfffffffe;

			struct TFrame
			{
				sint16	Channel1;
				sint16	Channel2;
			};
			result.reserve(nbSample);
			TFrame *frame = (TFrame *)data;
			for (uint i=0; i<nbSample; ++i)
			{
				result[i] = (frame->Channel1>>1) +(frame->Channel2>>1);
			}

			// unlock FMOD sample
			unlock(data);

			return nbSample;
		}
	}

	// Failure
	return 0;
}


// ***************************************************************************
void	CBufferFMod::loadDataToFMod(uint8 *data)
{
	// Delete old one
	if(_FModSample)
	{
		FSOUND_Sample_Free(_FModSample);
		_FModSample= NULL;
	}

	// if some data, create new one
	if(data)
	{
		uint8	*tmpData= NULL;
		uint8	*uploadData= data;

		// if format is ADPCM, decode into Mono16
		if(_Format==Mono16ADPCM)
		{
			// create Mono16 dest buffer
			uint	nbSample= _Size*2;
			tmpData= new uint8 [nbSample * sizeof(sint16)];

			// uncompress
			TADPCMState	state;
			state.PreviousSample = 0;
			state.StepIndex = 0;
			decodeADPCM(data, (sint16*)tmpData, nbSample, state);

			// change upload data, _Format and _Size to fit the new format
			uploadData= tmpData;
			_Format= Mono16;
			_Size= nbSample*2;
		}

		// create FMod sample and upload according to format
		uint32	type= 0;
		switch(_Format)
		{
		case Mono8: type= FSOUND_8BITS|FSOUND_MONO; break;
		case Mono16: type= FSOUND_16BITS|FSOUND_MONO; break;
		case Stereo8: type= FSOUND_8BITS|FSOUND_STEREO; break;
		case Stereo16: type= FSOUND_16BITS|FSOUND_STEREO; break;
		default: nlstop;
		};
		uint32	commonType= FSOUND_LOADRAW|FSOUND_LOOP_NORMAL|FSOUND_LOADMEMORY;
		// if can use hardware buffer
		if(!CSoundDriverFMod::instance()->forceSofwareBuffer())
			commonType|= FSOUND_HW3D;
		// create FMod sample
		_FModSample= FSOUND_Sample_Load(FSOUND_FREE, (const char*)uploadData, commonType|type, 0, _Size);

		// clear any temporary data
		if(tmpData)
		{
			delete [] tmpData;
		}
	}
}


// ***************************************************************************
void		*CBufferFMod::lock()
{
	if(!_FModSample)
		return NULL;

	void	*ptr0, *ptr1;
	uint	len0, len1;
	if(!FSOUND_Sample_Lock(_FModSample, 0, _Size, &ptr0, &ptr1, &len0, &len1))
		return 0;
	nlassert(ptr1== NULL && len1==0);
	nlassert(len0==_Size);

	return ptr0;
}

// ***************************************************************************
void		CBufferFMod::unlock(void *ptr)
{
	if(!_FModSample || !ptr)
		return;

	FSOUND_Sample_Unlock(_FModSample, ptr, NULL, _Size, 0);
}


} // NLSOUND



