/** \file simple_sound.h
 * CSound: a sound buffer and its static properties
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

#ifndef NL_SIMPLE_SOUND_H
#define NL_SIMPLE_SOUND_H

#include "nel/misc/string_mapper.h"
#include "sound.h"

namespace NLSOUND {

class ISoundDriver;
class IBuffer;
class CSound;



/**
 * A sound buffer and its static properties
 * \author Boris Boucher
 * \author Nevrax France
 * \date 2002
 */
class CSimpleSound : public CSound
{
public:
	/// Constructor
	CSimpleSound();
	/// Destructor
	virtual ~CSimpleSound();
	/** Allow to load sound files when corresponding wave file is missing
	 * (default: false, i.e. an input serial or a load throws an exception ESoundFileNotFound)
	 */
//	static void			allowMissingWave( bool b )			{ _AllowMissingWave = b; }
	/// Serialize
//	void				serial( NLMISC::IStream& s );
	/// Load the sound parameters from georges' form
	virtual void		importForm(const std::string& filename, NLGEORGES::UFormElm& formRoot);

	/// Return the buffer and the buffername if not null
	IBuffer*			getBuffer();
	/// Return true if distance and cone are meaningful
	bool				isDetailed() const					{ return _Detailed; }
	/// Return the min distance (if detailed())
	float				getMinDistance() const				{ return _MinDist; }
	/// Return the alpha attenuation value.
	float				getAlpha() const					{ return float(_Alpha); }
	/// Return the length of the sound in ms
	uint32				getDuration();
	/// Return the filename
	const NLMISC::TStringId&	getFilename() const					{ return _Filename; }
	/// Return the name of the buffer (must be unique)
	const NLMISC::TStringId&	getBuffername() const				{ return _Buffername; }

	/// Save (output stream only) (EDIT)
	//static void			save( const std::vector<CSound*>& container, NLMISC::IStream& s );

	/// Change the buffer.
	void				setBuffer(IBuffer *buffer);

	void				getSubSoundList(std::vector<std::pair<std::string, CSound*> > &subsounds) const;

	void				serial(NLMISC::IStream &s);


	void setAlpha(float alpha)
	{
		_Alpha = alpha;
	}

private:
	TSOUND_TYPE getSoundType() {return SOUND_SIMPLE;};

	// Allow to load sound files when corresponding wave file is missing ?
//	static bool			_AllowMissingWave;
	// Registration flag for assoc between buffer and sound.
	bool				_Registered;

	// Buffer
	IBuffer				*_Buffer;

	// Static properties
	bool				_Detailed;
	float				_MinDist;
	double				_Alpha;

	// true if the buffer name contains some %. It means that the buffer name can be know only at runtime
	bool				_NeedContext;

	// Sound name and filename (required for output (EDIT))
//	std::string			_Filename;
//	std::string			_Buffername;
	NLMISC::TStringId	_Filename;
	NLMISC::TStringId	_Buffername;

};

} // NLSOUND


#endif // NL_SIMPLE_SOUND_H

/* End of sound.h */

