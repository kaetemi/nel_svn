/** \file music_source.h
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

#ifndef NL_MUSIC_SOURCE_H
#define NL_MUSIC_SOURCE_H

#include "nel/misc/types_nl.h"
#include "source_common.h"


namespace NLSOUND {


// ***************************************************************************
/**
 * A source that play music
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2004
 */
class CMusicSource : public CSourceCommon
{
public:
	/// Constructor
	CMusicSource	(class CMusicSound *sound=NULL, bool spawn=false, TSpawnEndCallback cb=0, void *cbUserParam = 0, NL3D::CCluster *cluster = 0);
	/// Destructor
	~CMusicSource	();

	/// Return the sound binded to the source (or NULL if there is no sound)
	virtual TSoundId				getSound();

	virtual void					play();
	/// Stop playing
	virtual void					stop();

	TSOURCE_TYPE					getType() const								{return SOURCE_MUSIC;}

private:

	class CMusicSound				*_MusicSound;
};


} // NLSOUND


#endif // NL_MUSIC_SOURCE_H

/* End of music_source.h */
