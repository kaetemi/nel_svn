/** \file sound_animation.h
 * A sound event marer on a sound track
 *
 * $Id: sound_animation.h,v 1.8 2005/02/22 10:14:13 besson Exp $
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

#ifndef NL_SOUND_ANIM_TRACK_H
#define NL_SOUND_ANIM_TRACK_H

#include "sound_anim_manager.h"

namespace NLMISC
{
	class IStream;
}

namespace NLSOUND {

class CSoundAnimMarker;
class UAudioMixer;

typedef std::vector<CSoundAnimMarker*> TMarkerVector;



class CSoundAnimation
{
public:

	enum 
	{ 
		NoId = -1
	};

	CSoundAnimation(std::string& name, TSoundAnimId id) : _Name(name), _Id(id), _Dirty(false) {}

	virtual ~CSoundAnimation() {}

	/** Add a new marker */
	virtual void				addMarker(CSoundAnimMarker* marker);

	/** Remove a marker */
	virtual void				removeMarker(CSoundAnimMarker* marker);

	/** Return the number of markers in this track
	 */
	virtual uint32				countMarkers()							{ return _Markers.size(); }

	/** Return a marker of this track given its index */
	virtual CSoundAnimMarker*	getMarker(uint32 i)						{ return _Markers[i]; }

	/** Return the name of the animation  */
	virtual std::string&		getName()								{ return _Name; }


	/** Load from an xml file */
	virtual void				load();

	/** Save to an xml document */
	virtual void				save();

	/** Return the filename of the animation */
	virtual std::string&		getFilename()							{ return _Filename; }
	
	/** Set the filename of the animation 
	 */
	virtual void				setFilename(std::string& name)			{ _Filename = name; }

	/** Returns whether the sound animation changed since the last save. (Editing support) */
	virtual bool				isDirty()								{ return _Dirty; }

	/** Set the dirty flag (Editing support) */
	virtual void				setDirty(bool b)						{ _Dirty = b; }

	/** Play the sounds of the markers that fall within the specified time interval. */
	virtual void				play(UAudioMixer* mixer, float lastTime, float curTime, NL3D::CCluster *cluster, CSoundContext &context);

protected:

	/// Sort all the markers according to their time
	virtual void				sort();

	/** The unique ID of the animation */
	TSoundAnimId				_Id;

	/** The name of the animation */
	std::string					_Name;

	/** The set of markers */
	TMarkerVector				_Markers;

	/** The filename */
	std::string					_Filename;

	/** Has the sound animation changed since the last save? (Editing support) */
	bool						_Dirty;

};

} // namespace NLSOUND

#endif // NL_SOUND_ANIM_TRACK_H
