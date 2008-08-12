/** \file ambiant_source.cpp
 * CAmbiantSource: Stereo mix of a envsound, seen as a source
 *
 * $Id: ambiant_source.cpp,v 1.10 2002/11/25 14:11:40 boucher Exp $
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

#include "stdsound.h"

#include "ambiant_source.h"
#include "sound.h"

using namespace NLMISC;
using namespace std;


namespace NLSOUND {


// If this flag is defined, one ambiant sound cannot be the next one to itself
#define ENVSOUND_DONT_DUPLICATE_AMBIANT


/*
 * Constructor
 */
CAmbiantSource::CAmbiantSource() : _Play(false),
								   _StereoGain(0.0f),
								   _Sustain(false),
								   _RandomSoundChosen(false),
								   _NextSparseSoundTime(0),
								   _CrossfadeTime(4000),
								   _SustainTime(8000),
								   _SparseAvgPeriod(20000)
{
	_StereoChannels[AMBIANT_CH1].setLooping( true );
	_StereoChannels[AMBIANT_CH2].setLooping( true );
	//_StereoChannels[SPARSE_CH].setLooping( false );

	srand( (uint32)CTime::getLocalTime() );
}


/*
 * Destructor
 */
CAmbiantSource::~CAmbiantSource()
{
	CAudioMixerUser::instance()->removeMySource( &_StereoChannels[AMBIANT_CH1] );
	CAudioMixerUser::instance()->removeMySource( &_StereoChannels[AMBIANT_CH2] );
	CAudioMixerUser::instance()->removeMySource( &_StereoChannels[SPARSE_CH] );

	// Delete sounds: now done in CAudioMixerUser::~CAudioMixerUser()
	/*vector<CSound*>::iterator ipsnds;
	for ( ipsnds=_AmbiantSounds.begin(); ipsnds!=_AmbiantSounds.end(); ++ipsnds )
	{
		nldebug( "Deleting ambiant sound" );
		delete (*ipsnds);
	}
	for ( ipsnds=_SparseSounds.begin(); ipsnds!=_SparseSounds.end(); ++ipsnds )
	{
		nldebug( "Deleting sparse sound" );
		delete (*ipsnds);
	}
	*/
}


/* Init. You can pass a position vector to link to (if the playable has stereo source(s))
 * When reading from a stream, call init() *after* serial().
 */
void CAmbiantSource::initPos( const CVector *posvector )
{
	// Initialize ambiant sound channels
	if ( ! _AmbiantSounds.empty()  )
	{
		_StereoChannels[AMBIANT_CH1].set3DPositionVector( posvector );
		_StereoChannels[AMBIANT_CH1].setSound( getRandomSound( _AmbiantSounds ) );
		_StereoChannels[AMBIANT_CH1].setGain( 0.0f );
		_StereoChannels[AMBIANT_CH1].setPriority( LowPri);
		CAudioMixerUser::instance()->addSource( &_StereoChannels[AMBIANT_CH1] );
		CAudioMixerUser::instance()->giveTrack( &_StereoChannels[AMBIANT_CH1] );
		
		if ( _AmbiantSounds.size() > 1 )
		{
			_StereoChannels[AMBIANT_CH2].set3DPositionVector( posvector );
			_StereoChannels[AMBIANT_CH2].setSound( getRandomSound( _AmbiantSounds ) );
			_StereoChannels[AMBIANT_CH2].setGain( 0.0f );
			_StereoChannels[AMBIANT_CH2].setPriority( LowPri);
			CAudioMixerUser::instance()->addSource( &_StereoChannels[AMBIANT_CH2] );
			CAudioMixerUser::instance()->giveTrack( &_StereoChannels[AMBIANT_CH2] );
		}
	}

	// Initialize sparse sounds channel
	if ( ! _SparseSounds.empty() )
	{
		_StereoChannels[SPARSE_CH].set3DPositionVector( posvector );
		_StereoChannels[SPARSE_CH].setPriority( LowPri );
		_StereoChannels[SPARSE_CH].setSound( getRandomSound( _SparseSounds ) );
		CAudioMixerUser::instance()->addSource( &_StereoChannels[SPARSE_CH] );
		CAudioMixerUser::instance()->giveTrack( &_StereoChannels[SPARSE_CH] );
	}
}


/*
 * Enable (play with high priority) and set general gain, or disable (stop and set low priority).
 */
void			CAmbiantSource::enable( bool toplay, float gain )
{
	// Calc position in cycle
	bool crossfade;
	uint32 leadchannel;
	if ( _AmbiantSounds.size() > 1 )
	{
		calcPosInCycle( crossfade, leadchannel );
	}
	else
	{
		crossfade = false;
		leadchannel = AMBIANT_CH1;
	}

	// Enable/disable
	if ( toplay )
	{
		_StereoGain = gain;

		if ( ! _Play )
		{
			// Start lead channel
			if ( _StereoChannels[leadchannel].getSound() != NULL )
			{
				nldebug( "AM: Envsound: Switch on channel %u", leadchannel );
				_StereoChannels[leadchannel].setPriority( HighPri ) ;
				_StereoChannels[leadchannel].play();
			}

			// If crossfading, start back channel
			if ( crossfade && (_StereoChannels[1-leadchannel].getSound() != NULL) )
			{
				nldebug( "AM: Envsound: Switch on channel %u", 1-leadchannel );
				_StereoChannels[1-leadchannel].setPriority( HighPri ) ;
				_StereoChannels[1-leadchannel].play();
			}

			// Calc when the next spare sound will play
			calcRandomSparseSoundTime( NULL );

			_Play = true;
		}
		// The SPARSE_CH is added only when needed
	}
	else
	{
		if ( _Play )
		{
			// Stop lead channel
			if ( _StereoChannels[leadchannel].getSound() != NULL )
			{
				nldebug( "AM: Envsound: Switch off channel %u", leadchannel );
				_StereoChannels[leadchannel].stop();
				_StereoChannels[leadchannel].setPriority( LowPri );
			}

			// If crossfading, stop back channel
			if ( crossfade && (_StereoChannels[1-leadchannel].getSound() != NULL) )
			{
				nldebug( "AM: Envsound: Switch off channel %u", 1-leadchannel );
				_StereoChannels[1-leadchannel].stop();
				_StereoChannels[1-leadchannel].setPriority( LowPri );
			}

			// Stop spare channel, anyway
			if ( _StereoChannels[SPARSE_CH].getSound() != NULL )
			{
				nldebug( "AM: Envsound: Switch off sparse channel" );
				_StereoChannels[SPARSE_CH].stop();
				_StereoChannels[SPARSE_CH].setPriority( LowPri );
			}

			_Play = false;
		}
	}
}


/*
 * Calc pos in cycle
 */
TTime CAmbiantSource::calcPosInCycle( bool& crossfade, uint32& leadchannel )
{
	TTime pos = CTime::getLocalTime();
	uint32 cycletime = _CrossfadeTime + _SustainTime;
	pos = pos % (cycletime*2);

	// Calc which channel will be the lead one
	if ( pos < cycletime )
	{
		leadchannel = 0;
	}
	else
	{
		leadchannel = 1;
		pos = pos - (cycletime);
	}

	// Calc if the pos is in the first part (crossfade) or in the other part (sustain)
	crossfade = ( pos < _CrossfadeTime );
	
	return pos;
}


/*
 * Update the stereo mix (call evenly)
 */
void CAmbiantSource::update()
{
	if ( (!_Play) || (_StereoGain==0.0f) )
	{
		return;
	}

	// Calc pos in cycle
	bool crossfade;
	uint32 leadchannel, backchannel=0;
	TTime posInCycle=0;
	if ( _AmbiantSounds.size() > 1 )
	{
		posInCycle = calcPosInCycle( crossfade, leadchannel );
		backchannel = 1 - leadchannel;
	}
	else
	{
		// If there is less than 2 sounds, no crossfade, always sustain (a single sound must be looping)
		crossfade = false;
		leadchannel = AMBIANT_CH1;
		_Sustain = true;
	}
	
	// Crossfade the first two sources
	if ( crossfade )
	{
		// Attack
		float ratio = (float)posInCycle / (float)_CrossfadeTime;
		_StereoChannels[leadchannel].setRelativeGain( ratio*_StereoGain );
		_StereoChannels[backchannel].setRelativeGain( (1.0f - ratio)*_StereoGain );

		// Start next sound
		if ( _Sustain )
		{
			nldebug( "AM: EnvSound: Beginning crossfade: channel #%u rising", leadchannel );
			_StereoChannels[leadchannel].setPriority( HighPri ) ;
			_StereoChannels[leadchannel].play();
			_Sustain = false;
		}
	}
	else
	{
		// Set sustain gain (takes into account the possible changes to _StereoGain)
		_StereoChannels[leadchannel].setRelativeGain( _StereoGain );

		// Prepare next ambiant sound
		if ( ! _Sustain )
		{
			_Sustain = true;
			TSoundId nextsound = getRandomSound( _AmbiantSounds );
#ifdef ENVSOUND_DONT_DUPLICATE_AMBIANT
			nlassert( _AmbiantSounds.size() > 1 ); // or infinite loop
			while ( nextsound == _StereoChannels[leadchannel].getSound() )
			{
				nldebug( "AM: EnvSound: Avoiding ambiant sound duplication..." );
				nextsound = getRandomSound( _AmbiantSounds );
			}
#endif
			nldebug( "AM: EnvSound: Sustain: channel #1" );
			_StereoChannels[backchannel].setRelativeGain( 0.0f );
			_StereoChannels[backchannel].stop(); // we don't set the priority to LowPri
			_StereoChannels[backchannel].setSound( nextsound );
		}
	}

	// Add a short random sound into the third source
	if ( ! _SparseSounds.empty() )
	{
		// Set sustain gain (takes into account the possible changes to _StereoGain)
		_StereoChannels[SPARSE_CH].setRelativeGain( _StereoGain );

		// Start next sparse sound
		TTime now = CTime::getLocalTime();
		if ( now > _NextSparseSoundTime )
		{
			TSoundId nextsound = getRandomSound( _SparseSounds );
			_StereoChannels[SPARSE_CH].stop();
			_StereoChannels[SPARSE_CH].setSound( nextsound );
			_StereoChannels[SPARSE_CH].setPriority( MidPri );
			_StereoChannels[SPARSE_CH].play();
			nldebug( "AM: EnvSound: Playing sparse sound" );
			if ( _StereoChannels[SPARSE_CH].getTrack() == NULL )
			{
				nldebug( "AM: Ensound: Switch on sparse channel" );
				nlassert( _StereoChannels[SPARSE_CH].getSound() != NULL );
			}
			// Does not leave the track
			calcRandomSparseSoundTime( nextsound );
		}
	}
}


/*
 * Select a random sound in a bank
 */
TSoundId	CAmbiantSource::getRandomSound( const std::vector<CSound*>& bank ) const
{
	nlassert( ! bank.empty() );
	// Note: does not work with a very big size (rand()*bank.size() would overflow)
	uint32 r = rand()*bank.size()/(RAND_MAX+1);
	nlassert( r < bank.size() );
	nldebug( "AM: EnvSound: Prepared random sound number %u of %u", r, bank.size()-1 );

	return bank[r];
}




/*
 * Calculate the next time a sparse sound plays
 */
void		CAmbiantSource::calcRandomSparseSoundTime( TSoundId currentsparesound )
{
	uint32 delay = (uint)((float)rand() * (float)(_SparseAvgPeriod*2) / (float)RAND_MAX);

	// Check the next sound will play after the current one
	if ( currentsparesound != NULL )
	{
		uint32 soundlength = currentsparesound->getDuration();
		if ( delay <= soundlength )
		{
			delay = soundlength+1;
		}
	}

	nldebug( "AM: EnvSound: Next sparse sound will play in %u ms", delay );
	_NextSparseSoundTime = CTime::getLocalTime() + delay;
}


/*
 * Serialize
 */
/*
void					CAmbiantSource::serial( NLMISC::IStream& s )
{
	// If you change this, increment the version number in CEnvSoundUser::load() !

	// Constants
	s.serial( _CrossfadeTime );
	s.serial( _SustainTime );
	s.serial( _SparseAvgPeriod );

	// Stereo sound banks (sounds allocated here once per pointer, deleted by CAudioMixerUser::~CAudioMixerUser())
	s.serialContPtr( _AmbiantSounds );
	s.serialContPtr( _SparseSounds );

	// Register within the audio mixer for deletion at the end
	vector<CSound*>::iterator ips;
	for ( ips=_AmbiantSounds.begin(); ips!=_AmbiantSounds.end(); ++ips )
	{
		CAudioMixerUser::instance()->addAmbiantSound( (*ips) );
	}
	for ( ips=_SparseSounds.begin(); ips!=_SparseSounds.end(); ++ips )
	{
		CAudioMixerUser::instance()->addAmbiantSound( (*ips) );
	}
}

*/

/*
 * Set properties (EDIT)
 */
void		CAmbiantSource::setProperties( std::vector<TSoundId>& ambiantsounds,
										   std::vector<TSoundId>& sparsesounds,
										   uint32 crossfadeTimeMs, uint32 sustainTimeMs,
										   uint32 sparseAvgPeriodMs )
{
	_AmbiantSounds = ambiantsounds;
	_SparseSounds = sparsesounds;
	_CrossfadeTime = crossfadeTimeMs;
	_SustainTime = sustainTimeMs;
	_SparseAvgPeriod = sparseAvgPeriodMs;
}


} // NLSOUND
