/** \file sound_anim_marker.h
 * A sound event marer on a sound track
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef NL_SOUND_ANIM_MARKER_H
#define NL_SOUND_ANIM_MARKER_H

#include "nel/misc/string_mapper.h"
#include "nel/3d/cluster.h"
#include "u_source.h"


namespace NLMISC
{
	class IStream;
}


namespace NLSOUND {


typedef std::set<NLMISC::TStringId> TMarkerSoundSet;

class UAudioMixer;


class CSoundAnimMarker
{
public:

	CSoundAnimMarker(float time = 0.0f) : _Time(time) {}
	virtual ~CSoundAnimMarker();

	/** Set the time of this marker */
	virtual void			setTime(float time)		{ _Time = time; }

	/** Returns the time of this marker */
	virtual float			getTime()	const			{ return _Time; }

	/** Add a new sound in the set of to-be-played sounds for this marker */
	virtual void			addSound(const NLMISC::TStringId &soundName);

	/** Remove a sound */
	virtual void			removeSound(const NLMISC::TStringId &soundName);

	/** Return the set of sounds of this marker */
	virtual void			getSounds(std::vector<NLMISC::TStringId> &sounds);

	/** Play all the sounds of this marker */
	virtual void			play(UAudioMixer* mixer, NL3D::CCluster *cluster, CSoundContext &context);


protected:

	/** The set of sounds to be played */
	TMarkerSoundSet			_Sounds;

	/** The time position of this marker */
	float					_Time;
};

} // namespace NLSOUND

#endif // NL_SOUND_ANIM_MARKER_H
