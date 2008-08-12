/** \file music_sound.cpp
 * TODO: File description
 *
 * $Id: music_sound.cpp,v 1.2 2004/11/15 10:25:06 lecroart Exp $
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

#include "stdsound.h"

#include "music_sound.h"
#include "nel/misc/path.h"
#include "nel/georges/u_form_elm.h"


using namespace std;
using namespace NLMISC;

namespace NLSOUND {


// ***************************************************************************
CMusicSound::CMusicSound()
{
	// init with NULL in case of unexcepted access
	_FileName= NULL;
	_FadeInLength= 2000;
	_FadeOutLength= 2000;
	_MinimumPlayTime= 10000;
	_TimeBeforeCanReplay= 0;
	LastStopTime= INT_MIN;
}

// ***************************************************************************
CMusicSound::~CMusicSound()
{
}


// ***************************************************************************
void		CMusicSound::importForm(const std::string& filename, NLGEORGES::UFormElm& root)
{
	NLGEORGES::UFormElm *psoundType;
	std::string dfnName;
	
	// some basic checking.
	root.getNodeByName(&psoundType, ".SoundType");
	nlassert(psoundType != NULL);
	psoundType->getDfnName(dfnName);
	nlassert(dfnName == "music_sound.dfn");
	
	// Call the base class
	CSound::importForm(filename, root);
	
	// fileName
	std::string musicFileName;
	root.getValueByName(musicFileName, ".SoundType.FileName");
	musicFileName = CFile::getFilename(musicFileName);
	_FileName = CStringMapper::map(musicFileName);
	
	// Other params
	root.getValueByName(_FadeInLength, ".SoundType.FadeInLength");
	root.getValueByName(_FadeOutLength, ".SoundType.FadeOutLength");
	root.getValueByName(_MinimumPlayTime, ".SoundType.MinimumPlayTime");
	root.getValueByName(_TimeBeforeCanReplay, ".SoundType.TimeBeforeCanReplay");
	
}

// ***************************************************************************
uint32		CMusicSound::getDuration()
{
	// Cannot know the length of this music sound. 
	// Since its not really a sound (played in an other "channel"), suppose 0
	return 0;
}

// ***************************************************************************
void		CMusicSound::getSubSoundList(std::vector<std::pair<std::string, CSound*> > &subsounds) const
{
	subsounds.clear();
}

// ***************************************************************************
void		CMusicSound::serial(NLMISC::IStream &s)
{
	sint	ver= s.serialVersion(0);
	CSound::serial(s);

	CStringMapper::serialString(s, _FileName);
	s.serial(_FadeInLength, _FadeOutLength);
	s.serial(_MinimumPlayTime, _TimeBeforeCanReplay);
}

// ***************************************************************************
float		CMusicSound::getMaxDistance() const
{
	// used in background_sound_manager, since 2D sound, return 0 because 
	// the sound must be cut once out of the patat
	return 0.f;
}

// ***************************************************************************
bool		CMusicSound::isDetailed() const
{
	return false;
}



} // NLSOUND
