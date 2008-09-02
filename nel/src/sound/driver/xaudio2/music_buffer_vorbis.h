/**
 * \file music_buffer_vorbis.h
 * \brief CMusicBufferVorbis
 * \date 2008-08-30 11:38GMT
 * \author Jan Boon (Kaetemi)
 * CMusicBufferVorbis
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

#ifndef NLSOUND_MUSIC_BUFFER_VORBIS_H
#define NLSOUND_MUSIC_BUFFER_VORBIS_H
#include "stdxaudio2.h"

// Project includes
#include "music_buffer.h"

// NeL includes

// 3rd Party includes
#ifdef NL_OS_WINDOWS
#	pragma warning( push )
#	pragma warning( disable : 4244 )
#endif
#include <vorbis/vorbisfile.h>
#ifdef NL_OS_WINDOWS
#	pragma warning( pop )
#endif

// STL includes

namespace NLSOUND {

/**
 * \brief CMusicBufferVorbis
 * \date 2008-08-30 11:38GMT
 * \author Jan Boon (Kaetemi)
 * CMusicBufferVorbis
 */
class CMusicBufferVorbis : public IMusicBuffer
{
protected:
	// far pointers
	NLMISC::IStream *_Stream;

	// pointers
	
	// instances
	OggVorbis_File _OggVorbisFile;
	bool _Loop;
	bool _IsMusicEnded;
	uint32 _StreamSize;
public:
	CMusicBufferVorbis(NLMISC::IStream *stream, bool loop);
	virtual ~CMusicBufferVorbis();

	static bool getSongTitle(const std::string &fileName, NLMISC::IStream *stream, std::string &result);

	inline NLMISC::IStream *getStream() { return _Stream; }
	inline uint32 getStreamSize() { return _StreamSize; }

	virtual uint32 getRequiredBytes();
	virtual uint32 getNextBytes(uint8 *buffer, uint32 minimum, uint32 maximum);
	virtual uint16 getChannels();
	virtual uint32 getSamplesPerSec();
	virtual uint16 getBitsPerSample();
	virtual bool isMusicEnded();
	virtual float getLength();
}; /* class CMusicBufferVorbis */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_MUSIC_BUFFER_VORBIS_H */

/* end of file */
