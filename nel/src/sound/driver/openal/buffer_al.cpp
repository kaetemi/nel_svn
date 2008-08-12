/** \file buffer_al.cpp
 * OpenAL buffer
 *
 * $Id: buffer_al.cpp,v 1.8 2003/03/03 13:01:28 boucher Exp $
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

#include "stdopenal.h"

#include "buffer_al.h"

namespace NLSOUND {


/*
 * Constructor
 */
CBufferAL::CBufferAL( ALuint buffername ) :
	IBuffer(), _BufferName(buffername), _SampleFormat(AL_INVALID), _Frequency(0)
{
}


/*
 * Destructor
 */
CBufferAL::~CBufferAL()
{
	CSoundDriverAL *sdal = CSoundDriverAL::instance();
	//nlinfo( "Deleting buffer (name %u)", _BufferName );
	sdal->removeBuffer( this );
}

void CBufferAL::presetName(const NLMISC::TStringId &bufferName)
{
	_Name = bufferName;
}


/*
 * Return the size of the buffer, in bytes
 */
uint32		CBufferAL::getSize() const
{
	ALint value;
	alGetBufferi( _BufferName, AL_SIZE, &value );
	nlassert( alGetError() == AL_NO_ERROR );
	return value;
}


/*
 * Return true if the buffer is stereo, false if mono
 */
bool		CBufferAL::isStereo() const
{
	return (_SampleFormat==AL_FORMAT_STEREO8) || (_SampleFormat==AL_FORMAT_STEREO16);
}


/*
 * Return the format and frequency
 */
void		CBufferAL::getFormat( TSampleFormat& format, uint& freq ) const
{
	switch ( _SampleFormat )
	{
	case AL_FORMAT_MONO8 : format = Mono8; break;
	case AL_FORMAT_MONO16 : format = Mono16; break;
	case AL_FORMAT_STEREO8 : format = Stereo8; break;
	case AL_FORMAT_STEREO16 : format = Stereo16; break;
	default : nlstop;
	}
	freq = _Frequency;
}


/*
 * Return the duration (in ms) of the sample in the buffer
 */
float		CBufferAL::getDuration() const
{
	if ( _Frequency == 0 )
	{
		return 0;
	}
	uint32 bytespersample;
	switch ( _SampleFormat )
	{
	case AL_FORMAT_MONO8 : bytespersample = 1; break;
	case AL_FORMAT_MONO16 : bytespersample = 2; break;
	case AL_FORMAT_STEREO8 : bytespersample = 2; break;
	case  AL_FORMAT_STEREO16 : bytespersample = 4; break;
	default : return 0;
	}
	return (float)(getSize()) * 1000.0f / (float)_Frequency / (float)bytespersample;
}


/*
 * Set the sample format. Example: freq=44100
 */
void		CBufferAL::setFormat( TSampleFormat format, uint freq )
{
	switch ( format )
	{
	case Mono8 : _SampleFormat = AL_FORMAT_MONO8; break;
	case Mono16 : _SampleFormat = AL_FORMAT_MONO16; break;
	case Stereo8 : _SampleFormat = AL_FORMAT_STEREO8; break;
	case Stereo16 : _SampleFormat = AL_FORMAT_STEREO16; break;
	default		   : nlstop; _SampleFormat = AL_INVALID;
	}
	_Frequency = freq;
}


/*
 * Set the buffer size and fill the buffer. Return true if ok.
 */
bool		CBufferAL::fillBuffer( void *src, uint32 bufsize )
{
	nlassert( src != NULL );
	nlassert( (_SampleFormat != AL_INVALID) && (_Frequency != 0 ) );

	// Fill buffer
	alBufferData( _BufferName, _SampleFormat, src, bufsize, _Frequency );

	// Error handling
	return ( alGetError() == AL_NO_ERROR );
}


} // NLSOUND
