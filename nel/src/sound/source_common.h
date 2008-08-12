/** \file source_common.h
 * CSourceUSer: implementation of USource
 *
 * $Id: source_common.h,v 1.12 2005/02/22 10:19:20 besson Exp $
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

#ifndef NL_SOURCE_COMMON_H
#define NL_SOURCE_COMMON_H

#include "nel/misc/types_nl.h"
#include "nel/sound/u_source.h"
#include "nel/3d/cluster.h"
#include "sound.h"


namespace NLSOUND {

class CSourceCommon : public USource
{
	friend class CAudioMixerUser;
public:
	
	enum TSOURCE_TYPE
	{
		SOURCE_SIMPLE,
		SOURCE_COMPLEX,
		SOURCE_BACKGROUND,
		SOURCE_MUSIC
	};

	CSourceCommon(TSoundId id, bool spawn, TSpawnEndCallback cb, void *cbUserParam, NL3D::CCluster *cluster);

	~CSourceCommon();


	/// Get the type the the source.
	virtual TSOURCE_TYPE	getType() const = 0;

	void					setPriority( TSoundPriority pr);
	/// Return the priority
	TSoundPriority			getPriority() const								{ return _Priority; }
	void					setLooping( bool loop );
	bool					getLooping() const;
	void					play();
	void					stop();
	bool					isPlaying()									{ return _Playing; }
	void					setPos( const NLMISC::CVector& pos ) ;
	const NLMISC::CVector	&getPos() const;
	void					setVelocity( const NLMISC::CVector& vel );
	void					setDirection( const NLMISC::CVector& dir );
	void					setGain( float gain );
	void					setRelativeGain( float gain );
	float					getRelativeGain() const;
	void					setSourceRelativeMode( bool mode );
	/// return the user param for the user callback
	void							*getCallbackUserParam(void) const			{ return _CbUserParam; }
	/// Tells this source not to call its callbacks when it ends. This is valid for spawned sources only.
	virtual	void					unregisterSpawnCallBack()					{ _SpawnEndCb = NULL; }
	/// Get the velocity vector
	virtual void					getVelocity( NLMISC::CVector& vel ) const	{ vel = _Velocity; }
	/// Get the direction vector
	virtual void					getDirection( NLMISC::CVector& dir ) const	{ dir = _Direction; }
	/// Get the gain
	virtual float					getGain() const								{ return _Gain; }
	/// Get the pitch
	virtual float					getPitch() const							{ return _Pitch; }
	/// Get the source relative mode
	virtual bool					getSourceRelativeMode() const				{ return _RelativeMode; }
	/// Set the position vector to return for a stereo source (default: NULL)
	void							set3DPositionVector( const NLMISC::CVector *pos )	{ _3DPosition = pos; }
	/// Return the spawn state
	bool							isSpawn() const								{ return _Spawn; }
	/** Shift the frequency. 1.0f equals identity, each reduction of 50% equals a pitch shift
	 * of one octave. 0 is not a legal value.
	 */
	virtual void					setPitch( float pitch );

	virtual uint32					getTime();

	NL3D::CCluster					*getCluster() const { return _Cluster; } 

	/** This method is called from backgroup sound to check if
	 *	subsound need to be restarted (ie subsound in loop mode).
	 */
	virtual void					checkup() {};

protected:
	// Dynamic properties
	TSoundPriority					_Priority;
	bool							_Playing;
	bool							_Looping;

	NLMISC::CVector					_Position;
	NLMISC::CVector					_Velocity;
	NLMISC::CVector					_Direction;
	float							_Gain;
	float							_Pitch;
	bool							_RelativeMode;

	/// Gain not affected by setRelativeGain and used to compute _Gain.
	float							_InitialGain;

	// Playing start time
	NLMISC::TTime					_PlayStart;

	// Position to return, for a stereo source
	const NLMISC::CVector			*_3DPosition;

	// Spawn state
	const bool						_Spawn;
	TSpawnEndCallback				_SpawnEndCb;
	void							*_CbUserParam;
	NL3D::CCluster					*_Cluster;

	/// An optional user var controler.
	NLMISC::TStringId				_UserVarControler;

};

} // NLSOUND


#endif //NL_SOURCE_COMMON_H
