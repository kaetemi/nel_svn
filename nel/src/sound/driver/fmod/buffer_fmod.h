/** \file buffer_fmod.h
 * FMod buffer
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

#ifndef NL_BUFFER_FMOD_H
#define NL_BUFFER_FMOD_H


#include "../buffer.h"
#include <fmod.h>


namespace NLSOUND {


/**
 *  Buffer for the FMod implementation of the audio driver.
 *
 * A buffer represents a sound file loaded in RAM.
 *
 * \author Peter Hanappe, Olivier Cado
 * \author Nevrax France
 * \date 2002
 */
class CBufferFMod : public IBuffer
{
public:

	/// Constructor
	CBufferFMod();
	/// Destructor
	virtual	~CBufferFMod();

	virtual void			presetName(const NLMISC::TStringId &bufferName);

	/// Set the sample format. Example: freq=44100
	virtual void			setFormat( TSampleFormat format, uint freq );

    /// Set the buffer size and fill the buffer. Return true if ok. Call setFormat() first.
	virtual bool			fillBuffer( void *src, uint32 bufsize );

	/// Return the size of the buffer, in bytes
    virtual uint32			getSize() const				{ return _Size; }

	/// Return the duration (in ms) of the sample in the buffer
    virtual float			getDuration() const;

    /// Return true if the buffer is stereo, false if mono
    virtual bool			isStereo() const			{ return (_Format == Stereo8) || (_Format == Stereo16); }

    /// Return the format and frequency
    virtual void			getFormat( TSampleFormat& format, uint& freq ) const   { format = _Format; freq = _Freq; }


	/** Return true if the buffer is able to be fill part by part, false if it must be filled in one call
	 * (OpenAL 1.0 -> false)
	 */
	virtual bool			isFillMoreSupported() const	{ return false; }

    /// Force the buffer size without filling data (if isFillMoreSupported() only)
	//virtual void		setSize( uint32 size )					{ throw ESoundDriverNotSupp(); }

    /** Fill the buffer partially (if isFillMoreSupported() only),
	 * beginning at the pos changed by a previous call to fillMore().
	 * If the pos+srcsize exceeds the buffer size, the exceeding data is put at the beginning
	 * of the buffer. srcsize must be smaller than the buffer size.
	 */
	//virtual bool		fillMore( void *src, uint32 srcsize )	{ throw ESoundDriverNotSupp(); }


	bool					readWavBuffer(const std::string &name, uint8 *wavData, uint dataSize);

	bool					readRawBuffer(const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency);

	virtual uint32			getBufferADPCMEncoded(std::vector<uint8> &result);
	virtual uint32			getBufferMono16(std::vector<sint16> &result);


	/// Return the name of the buffer
	virtual const NLMISC::TStringId&	getName()		{ return _Name; }

	virtual bool			isBufferLoaded()			{ return _FModSample != 0; }

private:
	friend class	CSourceFMod;

	NLMISC::TStringId	_Name;

    uint32			_Size;

    TSampleFormat	_Format;

    uint			_Freq;

	FSOUND_SAMPLE	*_FModSample;

	void		loadDataToFMod(uint8 *data);

	void		*lock();
	void		unlock(void	*ptr);
};


} // NLSOUND


#endif // NL_BUFFER_FMOD_H

