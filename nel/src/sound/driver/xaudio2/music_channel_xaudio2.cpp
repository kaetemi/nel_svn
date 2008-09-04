/**
 * \file music_channel_xaudio2.cpp
 * \brief CMusicChannelXAudio2
 * \date 2008-08-30 13:31GMT
 * \author Jan Boon (Kaetemi)
 * CMusicChannelXAudio2
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

#include "stdxaudio2.h"
#include "music_channel_xaudio2.h"

// STL includes

// NeL includes
#include <nel/misc/big_file.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/mem_stream.h>
#include <nel/misc/stream.h>
#include "music_buffer.h"

// Project includes
#include "sound_driver_xaudio2.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CMusicChannelXAudio2::CMusicChannelXAudio2(CSoundDriverXAudio2 *soundDriver) 
: _MusicBuffer(NULL), _SourceVoice(NULL), _BufferPos(0), _SoundDriver(soundDriver), _Gain(1.0)
{
	stop();
}

CMusicChannelXAudio2::~CMusicChannelXAudio2()
{
	stop();
}

/** Play some music (.ogg etc...)
 *	NB: if an old music was played, it is first stop with stopMusic()
 *	\param filepath file path, CPath::lookup is done here
 *  \param async stream music from hard disk, preload in memory if false
 *	\param loop must be true to play the music in loop. 
 */
bool CMusicChannelXAudio2::play(const std::string &filepath, bool async, bool loop)
{
	nlinfo(NLSOUND_XAUDIO2_PREFIX "play %s %u", filepath.c_str(), (uint32)loop);

	HRESULT hr;

	stop();

	_MusicBuffer = IMusicBuffer::createMusicBuffer(filepath, async, loop);
	
	if (_MusicBuffer)
	{
		WAVEFORMATEX wfe;
		wfe.cbSize = 0;
		wfe.wFormatTag = WAVE_FORMAT_PCM; // todo: getFormat();
		wfe.nChannels = _MusicBuffer->getChannels();
		wfe.wBitsPerSample = _MusicBuffer->getBitsPerSample();
		wfe.nSamplesPerSec = _MusicBuffer->getSamplesPerSec();
		wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
		wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

		XAUDIO2_VOICE_DETAILS voice_details;
		_SoundDriver->getMasteringVoice()->GetVoiceDetails(&voice_details);

		nlinfo(NLSOUND_XAUDIO2_PREFIX "Creating music voice with %u channels, %u bits per sample, %u samples per sec, "
			"on mastering voice with %u channels, %u samples per sec", 
			(uint32)wfe.nChannels, (uint32)wfe.wBitsPerSample, (uint32)wfe.nSamplesPerSec, 
			(uint32)voice_details.InputChannels, (uint32)voice_details.InputSampleRate);

		if (FAILED(hr = _SoundDriver->getXAudio2()->CreateSourceVoice(&_SourceVoice, &wfe, XAUDIO2_VOICE_NOPITCH, 1.0f, this, NULL, NULL)))
		{ 
			nlwarning(NLSOUND_XAUDIO2_PREFIX "FAILED CreateSourceVoice"); 
			stop(); return false; 
		}

		_SourceVoice->SetVolume(_Gain);
		_SourceVoice->Start(0);
	}
	else
	{
		nlwarning(NLSOUND_XAUDIO2_PREFIX "no _MusicBuffer");
		return false;
	}
	
	return true;
}

/** Stop the music previously loaded and played (the Memory is also freed)
 */
void CMusicChannelXAudio2::stop()
{
	if (_SourceVoice) { _SourceVoice->DestroyVoice(); _SourceVoice = NULL; }
	if (_MusicBuffer) { delete _MusicBuffer; _MusicBuffer = NULL; }
	// memset(_Buffer, 0, sizeof(_Buffer));
	_BufferPos = 0;
}

/** Pause the music previously loaded and played (the Memory is not freed)
 */
void CMusicChannelXAudio2::pause()
{
	if (_SourceVoice) _SourceVoice->Stop(0);
}

/** Resume the music previously paused
 */
void CMusicChannelXAudio2::resume()
{
	if (_SourceVoice) _SourceVoice->Start(0);
}

/** Return true if a song is finished.
 */
bool CMusicChannelXAudio2::isEnded()
{
	if (_MusicBuffer)
	{
		if (_MusicBuffer->isMusicEnded())
		{
			nldebug(NLSOUND_XAUDIO2_PREFIX "isEnded() -> stop()");
			stop();
			return true;
		}
		else
		{
			return false;
		}
	}
	else 
	{
		return true;
	}
}

/** Return the total length (in second) of the music currently played
 */
float CMusicChannelXAudio2::getLength()
{
	if (_MusicBuffer) return _MusicBuffer->getLength(); 
	else return .0f;
}

/** Set the music volume (if any music played). (volume value inside [0 , 1]) (default: 1)
 *	NB: the volume of music is NOT affected by IListener::setGain()
 */
void CMusicChannelXAudio2::setVolume(float gain)
{
	_Gain = gain;
	if (_SourceVoice) _SourceVoice->SetVolume(gain);
}

void CMusicChannelXAudio2::OnVoiceProcessingPassStart(UINT32 BytesRequired)
{    
	if (BytesRequired > 0)
	{
		//nlwarning(NLSOUND_XAUDIO2_PREFIX "Bytes Required: %u", BytesRequired); // byte req to not have disruption
		
		if (_MusicBuffer)
		{
			uint32 minimum = BytesRequired;
			if (_MusicBuffer->getRequiredBytes() > minimum) minimum = _MusicBuffer->getRequiredBytes();
			if (minimum > sizeof(_Buffer) - _BufferPos) _BufferPos = 0;
			uint32 maximum = sizeof(_Buffer) - _BufferPos;
			uint8 *buffer = &_Buffer[_BufferPos];
			uint32 length = _MusicBuffer->getNextBytes(buffer, minimum, maximum);
			_BufferPos += length;

			if (length)
			{
				XAUDIO2_BUFFER xbuffer;
				xbuffer.AudioBytes = length;
				xbuffer.Flags = 0;
				xbuffer.LoopBegin = 0;
				xbuffer.LoopCount = 0;
				xbuffer.LoopLength = 0;
				xbuffer.pAudioData = buffer;
				xbuffer.pContext = NULL; // nothing here for now
				xbuffer.PlayBegin = 0;
				xbuffer.PlayLength = 0;

				_SourceVoice->SubmitSourceBuffer(&xbuffer);
			}
			else
			{
				nldebug(NLSOUND_XAUDIO2_PREFIX "!length -> delete _MusicBuffer");
				delete _MusicBuffer; _MusicBuffer = NULL;
				_SourceVoice->Discontinuity();
			}
		}
	}
}

void CMusicChannelXAudio2::OnVoiceProcessingPassEnd()
{ 
	
}

void CMusicChannelXAudio2::OnStreamEnd()
{ 
	
}

void CMusicChannelXAudio2::OnBufferStart(void *pBufferContext)
{    
	
}

void CMusicChannelXAudio2::OnBufferEnd(void *pBufferContext)
{ 
	
}

void CMusicChannelXAudio2::OnLoopEnd(void *pBufferContext)
{    
	
}

void CMusicChannelXAudio2::OnVoiceError(void *pBufferContext, HRESULT Error)
{ 
	
}

//void CMusicChannelXAudio2::switchVoice(uint fadeTime)
//{
//	if (fadeTime) { _Active = getInactive(); _Fading = true; _FadeTime = (float)fadeTime / 1000.f; }
//	else { _Fading = false; _Balance = _Active ? 1.0f : 0.0f; updateVolume(); }
//	_MusicVoices[_Active].stop();
//	delete _Streams[_Active]; _Streams[_Active] = NULL;
//}

////void CMusicChannelXAudio2::play(NLMISC::CIFile &file, uint xFadeTime, bool loop)
////{
////	// nldebug(NLSOUND_XAUDIO2_PREFIX "play music preloaded");
////
////	/*_Playing = true;*/
////	switchVoice(xFadeTime);
////	
////	CMemStream *memstream = new CMemStream(true, false, file.getFileSize());
////	_Streams[_Active] = memstream;
////	file.serialBuffer(const_cast<uint8 *>(memstream->buffer()), file.getFileSize());
////	_MusicVoices[_Active].play(file.getStreamName(), memstream, loop);
////}

////void CMusicChannelXAudio2::play(const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop)
////{
////	// nldebug(NLSOUND_XAUDIO2_PREFIX "play music async, %s", path.c_str());
////	
////	// get real name instead of bnp stuff
////	string real_filename;
////	vector<std::string> filename;
////	explode<std::string>(path, ".", filename, true);
////	bool seekOffset = true;
////	try
////	{
////		if (toLower(filename[filename.size() - 1]) == "bnp")
////		{
////			// need to reverse stupid getFileInfo thingy from nlsound system ...
////			nldebug(NLSOUND_XAUDIO2_PREFIX "Looking for music file in %s %u %u", path.c_str(), fileOffset, fileSize);
////			vector<string> files;
////			CBigFile::getInstance().list(CFile::getFilename(path), files);
////			vector<string>::iterator it(files.begin()), end(files.end());
////			for (; it != end; ++it)
////			{
////				uint32 file_offset;
////				uint32 file_size;
////				CBigFile::getInstance().getFileInfo(CFile::getFilename(path) + "@" + *it, file_size, file_offset); // todo: use correct stuff
////				// nlinfo(NLSOUND_XAUDIO2_PREFIX "%s %s %u %u %u %u", path.c_str(), real_filename.c_str(), fileOffset, file_offset, fileSize, file_size);
////				if (file_offset == fileOffset)
////				{
////					real_filename = *it;
////					nldebug(NLSOUND_XAUDIO2_PREFIX "Found music file %s in big file %s", real_filename.c_str(), path.c_str());
////					seekOffset = false;
////					break;
////				}
////			}
////			if (real_filename.empty()) 
////			{
////				nlwarning(NLSOUND_XAUDIO2_PREFIX "Offset %u for music file not found in BNP %s", (uint32)fileOffset, path.c_str());
////				real_filename = path;
////			}
////		}
////		else real_filename = path;
////		real_filename = CPath::lookup(real_filename);
////	}
////	catch (...)
////	{
////		nlwarning(" - - - - - - this code sucks - - - - - - fix music implementation - - - - - - ");
////		real_filename = CPath::lookup(real_filename);
////		seekOffset = true;
////	}
////
////	/*_Playing = true;*/
////	switchVoice(xFadeTime);
////	
////	CIFile *ifile = new CIFile();
////	ifile->setCacheFileOnOpen(false);
////	ifile->allowBNPCacheFileOnOpen(false);
////	ifile->open(real_filename);
////	_Streams[_Active] = ifile;
////	if (seekOffset) ifile->seek(fileOffset, NLMISC::IStream::begin);	
////	_MusicVoices[_Active].play(real_filename, ifile, loop);
////}

////void CMusicChannelXAudio2::update(float dt)
////{
////	//if (_Fading) 
////	//{
////	//	switch (_Active)
////	//	{
////	//	case 0:
////	//		_Balance -= dt / _FadeTime;
////	//		if (_Balance <= 0.0f)
////	//		{
////	//			_Balance = 0.0f;
////	//			_Fading = false;
////	//			_MusicVoices[getInactive()].stop();
////	//			delete _Streams[getInactive()]; _Streams[getInactive()] = NULL;
////	//		}
////	//		break;
////	//	case 1:
////	//		_Balance += dt / _FadeTime;
////	//		if (_Balance >= 1.0f)
////	//		{
////	//			_Balance = 1.0f;
////	//			_Fading = false;
////	//			_MusicVoices[getInactive()].stop();
////	//			delete _Streams[getInactive()]; _Streams[getInactive()] = NULL;
////	//		}
////	//		break;
////	//	}
////	//	updateVolume();
////	//}
////	//if (_Streams[0]) if (_MusicVoices[0].isEnded())
////	//{
////	//	_MusicVoices[0].stop();
////	//	delete _Streams[0]; _Streams[0] = NULL;
////	//}
////	//if (_Streams[1]) if (_MusicVoices[1].isEnded())
////	//{
////	//	_MusicVoices[1].stop();
////	//	delete _Streams[1]; _Streams[1] = NULL;
////	//}
////}

} /* namespace NLSOUND */

/* end of file */
