/** \file sound_system.h
 * This initilize the sound system
 *
 * $Id: sound_system.h,v 1.10 2003/07/30 17:37:57 vizerie Exp $
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


#ifndef OV_SOUND_SYTEM_H
#define OV_SOUND_SYTEM_H


#include <nel/misc/types_nl.h>
#include <nel/misc/vector.h>
#include <string>
#include <set>

#include "nel/sound/sound_anim_manager.h"


namespace NLSOUND
{
	class UAudioMixer;
	class USource;
}

namespace NLMISC
{
	class CMatrix;
}

/// this class init the sound system used by the object viewer
class CSoundSystem
{
public:
	/// set the name of the file containing the sound bank
/*	static void addSoundBank(const std::string &soundBankFileName)
	{
		_SoundBanksFileName.insert(soundBankFileName);
	}
*/	/// set the name of the file containing the sample bank
	static void addSampleBank(const std::string &sampleBankFileName)
	{
		_SampleBanksFileName.insert(sampleBankFileName);
	}

	static void setSamplePath(std::string& path)		{ _SamplePath = NLMISC::CPath::standardizePath(path, true); }
	static void setPackedSheetPath(std::string& path)		{ _PackedSheetPath = NLMISC::CPath::standardizePath(path, true); }

	/** Init the sound system this also load the sound bank
	  * See setSoundBank
	  */
	static void initSoundSystem(void);

	/// release the sound system
	static void releaseSoundSystem(void);

	/// set the listener matrix.
	static void setListenerMatrix(const NLMISC::CMatrix &m);

	/// poll sound. Must be called periodically
	static void poll(void);

	// spawn a sound at the user position
	static void play(const std::string &soundName);
	// create a sound at the user position (don't spawn it)
	static NLSOUND::USource *create(const std::string &soundName);

	// get the audio mixer, or null if init failed
	static NLSOUND::UAudioMixer *getAudioMixer(void)	{ return _AudioMixer; }	

	/// Load the sound animation with the specified name
	static void loadAnimation(std::string& name)		{ _AnimManager->loadAnimation(name); }

	/// Start playing a sound animation. 
	static void playAnimation(std::string& name, float lastTime, float curTime, NLSOUND::CSoundContext &context);

	/// Update the sound animations. 
	//static void updateAnimations(float lastTime, float curTime)	{ _AnimManager->update(lastTime, curTime); };


	/// Returns a reference to the animation manager
	static NLSOUND::CSoundAnimManager* getSoundAnimManager()		{ return _AnimManager; }

private:
	static NLSOUND::UAudioMixer			*_AudioMixer;
//	static std::set<std::string>		_SoundBanksFileName;
	static std::set<std::string>		_SampleBanksFileName;
	static NLSOUND::CSoundAnimManager	*_AnimManager;
	//static sint							_AnimIndex;
	//static NLSOUND::TSoundAnimId		_CurrentAnimation;
	//static NLSOUND::TSoundAnimPlayId	_CurrentPlayback;
	static NLMISC::CVector				_Zero;
	static std::string					_SamplePath;
	static std::string					_PackedSheetPath;

};


#endif
