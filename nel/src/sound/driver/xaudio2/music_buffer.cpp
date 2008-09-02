/**
 * \file music_buffer.cpp
 * \brief IMusicBuffer
 * \date 2008-08-30 11:38GMT
 * \author Jan Boon (Kaetemi)
 * IMusicBuffer
 * 
 * $Id$
 */

/* 
 * Copyright (C) 2008  Jan Boon (Kaetemi)
 * 
 * This file is part of NLSOUND Music Library.
 * NLSOUND Music Library is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 * 
 * NLSOUND Music Library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NLSOUND Music Library; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */

#include "stdxaudio2.h"
#include "music_buffer.h"

// Project includes
#include "music_buffer_vorbis.h"

// NeL includes
#include <nel/misc/stream.h>
#include <nel/misc/file.h>

// STL includes

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

IMusicBuffer::IMusicBuffer()
{
	
}

IMusicBuffer::~IMusicBuffer()
{
	
}

std::string IMusicBuffer::getFileExtension(const std::string &fileName)
{
	vector<std::string> filename;
	explode<std::string>(fileName, ".", filename, true);
	return toLower(filename[filename.size() - 1]);
}

bool IMusicBuffer::getSongTitle(const std::string &fileName, NLMISC::IStream *stream, std::string &result)
{
	std::string file_ext = getFileExtension(fileName);
	if (file_ext == "ogg")
	{
		return CMusicBufferVorbis::getSongTitle(fileName, stream, result);
	}
	else
	{
		nlwarning("Music file extension unknown: '%s'", file_ext.c_str());
		result = fileName;
		return false;
	}
}

IMusicBuffer *IMusicBuffer::createMusicBuffer(const std::string &streamName, NLMISC::IStream *stream, bool loop)
{
	if (!stream)
	{
		nlwarning("Stream is NULL");
		return NULL;
	}
	std::string file_ext = getFileExtension(streamName);
	if (file_ext == "ogg")
	{
		return new CMusicBufferVorbis(stream, loop);
	}
	else
	{
		nlwarning("Music file extension unknown: '%s'", file_ext.c_str());
		return NULL;
	}
}

} /* namespace NLSOUND */

/* end of file */
