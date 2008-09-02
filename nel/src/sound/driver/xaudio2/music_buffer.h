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

// Project includes

// NeL includes

// STL includes

namespace NLMISC {
	class IStream;
	class CIFile;
}

namespace NLSOUND {

/**
 * \brief IMusicBuffer
 * \date 2008-08-30 11:38GMT
 * \author Jan Boon (Kaetemi)
 * IMusicBuffer
 */
class IMusicBuffer
{
protected:
	// pointers
	// ...
	
	// instances
	// ...
public:
	IMusicBuffer();
	virtual ~IMusicBuffer();

	virtual uint32 getRequiredBytes() =0;
	virtual uint32 getNextBytes(uint8 *buffer, uint32 minimum, uint32 maximum) =0;
	virtual uint16 getChannels() =0;
	virtual uint32 getSamplesPerSec() =0;
	virtual uint16 getBitsPerSample() =0;
	virtual bool isMusicEnded() =0;
	virtual float getLength() =0; // total time in seconds

	static bool getSongTitle(const std::string &fileName, NLMISC::IStream *stream, std::string &result);

	/// create may return NULL if unknown extension
	static IMusicBuffer *createMusicBuffer(const std::string &streamName, NLMISC::IStream *stream, bool loop);
	inline static void destroyMusicBuffer(IMusicBuffer *musicBuffer) { musicBuffer->destroyMusicBuffer(); }
	inline void destroyMusicBuffer() { delete this; }

private:
	static std::string getFileExtension(const std::string &fileName);
}; /* class IMusicBuffer */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_MUSIC_BUFFER_H */

/* end of file */
