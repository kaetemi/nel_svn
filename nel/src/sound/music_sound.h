/** \file music_sound.h
 * TODO: File description
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

#ifndef NL_MUSIC_SOUND_H
#define NL_MUSIC_SOUND_H

#include "nel/misc/string_mapper.h"
#include "sound.h"


namespace NLSOUND {


// ***************************************************************************
/**
 * A sound describing a streamable music to play
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2004
 */
class CMusicSound : public CSound
{
public:

	/// Constructor
	CMusicSound();
	/// Destructor
	virtual ~CMusicSound();

	/// \name From CSound
	//@{
	/// Load the sound parameters from georges' form
	virtual void		importForm(const std::string& filename, NLGEORGES::UFormElm& formRoot);
	virtual TSOUND_TYPE getSoundType() {return SOUND_MUSIC;}
	virtual uint32		getDuration();
	virtual void		getSubSoundList(std::vector<std::pair<std::string, CSound*> > &subsounds) const;
	virtual void		serial(NLMISC::IStream &s);
	virtual float		getMaxDistance() const;
	virtual bool		isDetailed() const;
	//@}

	/// Return the filename
	NLMISC::TStringId	getFileName() const					{ return _FileName; }
	sint32				getFadeInLength() const {return _FadeInLength;}
	sint32				getFadeOutLength() const {return _FadeOutLength;}
	sint32				getMinimumPlayTime() const {return _MinimumPlayTime;}
	sint32				getTimeBeforeCanReplay() const {return _TimeBeforeCanReplay;}

public:

	// For CMusicSoundManager. Mark the last time (in ms) this music was stoped, after a play. INT_MIN by default
	NLMISC::TTime		LastStopTime;

private:
	// Music FileName
	NLMISC::TStringId	_FileName;
	// time in ms
	sint32			_FadeInLength;
	sint32			_FadeOutLength;
	sint32			_MinimumPlayTime;
	sint32			_TimeBeforeCanReplay;
};


} // NLSOUND


#endif // NL_MUSIC_SOUND_H

/* End of music_sound.h */
