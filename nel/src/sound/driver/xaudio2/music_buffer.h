/**
 * \file music_buffer.h
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

#ifndef NLSOUND_MUSIC_BUFFER_H
#define NLSOUND_MUSIC_BUFFER_H
#include "stdxaudio2.h"

// STL includes

// NeL includes

// Project includes

namespace NLMISC {
	class IStream;
	class CIFile;
}

namespace NLSOUND {

/**
 * \brief IMusicBuffer
 * \date 2008-08-30 11:38GMT
 * \author Jan Boon (Kaetemi)
 * IMusicBuffer is only used by the driver implementation to stream 
 * music files into a readable format (it's a simple decoder interface).
 * You should not call these functions (getSongTitle) on nlsound or user level, 
 * as a driver might have additional music types implemented.
 */
class IMusicBuffer
{
private:
	// pointers
	/// Stream from file created by IMusicBuffer
	NLMISC::IStream *_InternalStream;

public:
	IMusicBuffer();
	virtual ~IMusicBuffer();

	/// Create a new music buffer, may return NULL if unknown type, destroy with delete. Filepath lookup done here. If async is true, it will stream from hd, else it will load in memory first.
	static IMusicBuffer *createMusicBuffer(const std::string &filepath, bool async, bool loop);

	/// Create a new music buffer from a stream, type is file extension like "ogg" etc.
	static IMusicBuffer *createMusicBuffer(const std::string &type, NLMISC::IStream *stream, bool loop);

	/// Get information on a music file (only artist and title at the moment).
	static bool getInfo(const std::string &filepath, std::string &artist, std::string &title);

	/// Get how many bytes the music buffer requires for output minimum.
	virtual uint32 getRequiredBytes() =0;

	/// Get an amount of bytes between minimum and maximum (can be lower than minimum if at end).
	virtual uint32 getNextBytes(uint8 *buffer, uint32 minimum, uint32 maximum) =0;

	/// Get the amount of channels (2 is stereo) in output.
	virtual uint16 getChannels() =0;

	/// Get the samples per second (often 44100) in output.
	virtual uint32 getSamplesPerSec() =0;

	/// Get the bits per sample (often 16) in output.
	virtual uint16 getBitsPerSample() =0;

	/// Get if the music has ended playing (never true if loop).
	virtual bool isMusicEnded() =0;

	/// Get the total time in seconds.
	virtual float getLength() =0;
}; /* class IMusicBuffer */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_MUSIC_BUFFER_H */

/* end of file */
