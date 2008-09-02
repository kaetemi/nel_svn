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

// Project includes

// NeL includes
#include <nel/misc/big_file.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/mem_stream.h>
#include <nel/misc/stream.h>

// STL includes

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

CMusicChannelXAudio2::CMusicChannelXAudio2(CSoundDriverXAudio2 *soundDriver) 
: _Active(1), _Balance(1.f), _Gain(1.0f), /*_Playing(false), */_Fading(false), _FadeTime(0.0f)
{
	_MusicVoices[0].init(soundDriver);
	_MusicVoices[1].init(soundDriver);
	_Streams[0] = NULL;
	_Streams[1] = NULL;
}

CMusicChannelXAudio2::~CMusicChannelXAudio2()
{
	delete _Streams[0]; _Streams[0] = NULL;
	delete _Streams[1]; _Streams[1] = NULL;
}

void CMusicChannelXAudio2::switchVoice(uint fadeTime)
{
	if (fadeTime) { _Active = getInactive(); _Fading = true; _FadeTime = (float)fadeTime / 1000.f; }
	else { _Fading = false; _Balance = _Active ? 1.0f : 0.0f; updateVolume(); }
	_MusicVoices[_Active].stop();
	delete _Streams[_Active]; _Streams[_Active] = NULL;
}

void CMusicChannelXAudio2::play(NLMISC::CIFile &file, uint xFadeTime, bool loop)
{
	nlinfo("play music preloaded");

	/*_Playing = true;*/
	switchVoice(xFadeTime);
	
	CMemStream *memstream = new CMemStream(true, false, file.getFileSize());
	_Streams[_Active] = memstream;
	file.serialBuffer(const_cast<uint8 *>(memstream->buffer()), file.getFileSize());
	_MusicVoices[_Active].play(file.getStreamName(), memstream, loop);
}

void CMusicChannelXAudio2::play(const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop)
{
	nlinfo("play music async");

	// get real name instead of bnp stuff
	string real_filename;
	vector<std::string> filename;
	explode<std::string>(path, ".", filename, true);
	if (toLower(filename[filename.size() - 1]) == "bnp")
	{
		// need to reverse stupid getFileInfo thingy from nlsound system ...
		nlinfo("Looking for music file in %s %u %u", path.c_str(), fileOffset, fileSize);
		vector<string> files;
		CBigFile::getInstance().list(CFile::getFilename(path), files);
		vector<string>::iterator it(files.begin()), end(files.end());
		for (; it != end; ++it)
		{
			uint32 file_offset;
			uint32 file_size;
			CBigFile::getInstance().getFileInfo(*it, file_size, file_offset); // todo: use correct stuff
			// nlinfo("%s %s %u %u %u %u", path.c_str(), real_filename.c_str(), fileOffset, file_offset, fileSize, file_size);
			if (file_offset == fileOffset)
			{
				real_filename = *it;
				nlinfo("Found music file %s in big file %s", real_filename.c_str(), path.c_str());
				break;
			}
		}
		if (real_filename.empty()) 
		{
			nlwarning("Offset for music file not found in BNP");
			real_filename = path;
		}
	}
	else real_filename = path;

	/*_Playing = true;*/
	switchVoice(xFadeTime);
	
	CIFile *ifile = new CIFile(path);
	_Streams[_Active] = ifile;
	ifile->seek(fileOffset, NLMISC::IStream::begin);	
	_MusicVoices[_Active].play(real_filename, ifile, loop);
}

void CMusicChannelXAudio2::stop(uint fadeTimeMs)
{
	switchVoice(fadeTimeMs); // switch to stopped voice :)
}

void CMusicChannelXAudio2::update(float dt)
{
	if (_Fading) 
	{
		switch (_Active)
		{
		case 0:
			_Balance -= dt / _FadeTime;
			if (_Balance <= 0.0f)
			{
				_Balance = 0.0f;
				_Fading = false;
				_MusicVoices[getInactive()].stop();
				delete _Streams[getInactive()]; _Streams[getInactive()] = NULL;
			}
			break;
		case 1:
			_Balance += dt / _FadeTime;
			if (_Balance >= 1.0f)
			{
				_Balance = 1.0f;
				_Fading = false;
				_MusicVoices[getInactive()].stop();
				delete _Streams[getInactive()]; _Streams[getInactive()] = NULL;
			}
			break;
		}
		updateVolume();
	}
	if (_Streams[0]) if (_MusicVoices[0].isEnded())
	{
		_MusicVoices[0].stop();
		delete _Streams[0]; _Streams[0] = NULL;
	}
	if (_Streams[1]) if (_MusicVoices[1].isEnded())
	{
		_MusicVoices[1].stop();
		delete _Streams[1]; _Streams[1] = NULL;
	}
}

} /* namespace NLSOUND */

/* end of file */
