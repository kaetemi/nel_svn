/** \file ambiant_source.h
 * CAmbiantSource: Stereo mix of a envsound, seen as a source
 *
 * $Id: ambiant_source.h,v 1.6 2002/11/25 14:11:40 boucher Exp $
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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
#error "Deprecated"

#ifndef NL_AMBIANT_SOURCE_H
#define NL_AMBIANT_SOURCE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/time_nl.h"
#include "simple_source.h"
#include "env_sound_user.h"
#include "playable.h"


namespace NLSOUND {


/**
 * Stereo mix of a envsound, seen as a source (see CEnvSoundUser)
 *
 * Plays a stereo mix made up of two channels for crossfading random ambiant sounds,
 * plus a third channel for random sparse sounds.
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CAmbiantSource : public IPlayable
{
public:

	/// Constructor
	CAmbiantSource();
	/// Destructor
	virtual ~CAmbiantSource();
	/// Static init (call at the very beginning)
	static void				init() 
	{		
		//NLMISC_REGISTER_CLASS(CAmbiantSource); 			
	}

	
	/** Init. You can pass a position vector to link to (if the playable has stereo source(s))
	 * When reading from a stream, call init() *after* serial().
	 */
	virtual void			initPos( const NLMISC::CVector *posvector );
	/// Update
	virtual void			update();
	/// Enable (play with high priority) and set general gain, or disable (stop and set low priority).
	virtual void			enable( bool toplay, float gain );


	/// Serialize
	//virtual void			serial( NLMISC::IStream& s );
	//NLMISC_DECLARE_CLASS(CAmbiantSource);
	/// Return the stereo channels (EDIT)
	CSimpleSource				*getChannels() { return _StereoChannels; }
	/// Set properties (EDIT)
	void					setProperties( std::vector<TSoundId>& ambiantsounds,
										   std::vector<TSoundId>& sparsesounds,
										   uint32 crossfadeTimeMs=4000, uint32 sustainTimeMs=16000,
										   uint32 sparseAvgPeriodMs=30000 );

protected:

	/// Calc pos in cycle
	NLMISC::TTime			calcPosInCycle( bool& crossfade, uint32& leadchannel );
	/// Select a random sound in a bank
	TSoundId				getRandomSound( const std::vector<CSound*>& bank ) const;
	/// Calculate the next time a sparse sound plays (set NULL for no current sound)
	void					calcRandomSparseSoundTime( TSoundId currentsparesound );

private:

	// Must play or not
	bool					_Play;

	// Non-localized stereo sources
	CSimpleSource				_StereoChannels [MAX_ENV_CHANNELS];
	float					_StereoGain;

	// Sound banks
	std::vector<CSound*>	_AmbiantSounds, _SparseSounds;

	// Crossfade control
	NLMISC::TTime			_StartTime;
	bool					_Sustain;
	bool					_RandomSoundChosen;
	NLMISC::TTime			_NextSparseSoundTime;

	// Constants
	uint32					_CrossfadeTime;
	uint32					_SustainTime;
	uint32					_SparseAvgPeriod;

};


} // NLSOUND


#endif // NL_AMBIANT_SOURCE_H

/* End of ambiant_source.h */
