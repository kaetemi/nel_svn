/** \file track_sampled_quat_small_header.h
 * TODO: File description
 */

/* Copyright, 2000-2003 Nevrax Ltd.
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

#ifndef NL_TRACK_SAMPLED_QUAT_SMALL_HEADER_H
#define NL_TRACK_SAMPLED_QUAT_SMALL_HEADER_H

#include "nel/misc/types_nl.h"
#include "nel/3d/track_sampled_quat.h"


namespace NL3D 
{


// ***************************************************************************
/** see CTrackSamplePack
 */
class	CTrackSampleHeader
{
public:
	// Param of animation
	bool					LoopMode;
	float					BeginTime;
	float					EndTime; 
	float					TotalRange;
	float					OOTotalRange;
	// The frame Time == (EndTime-BeginTime)/NumKeys
	float					DeltaTime;
	float					OODeltaTime;
};
	

// ***************************************************************************
/** Used to build a CTrackSamplePack from CTrackSampledQuat
 */
class CTrackSampleCounter
{
public:
	std:: vector<CTrackSampleHeader>	TrackHeaders;
	uint								NumKeys;

	CTrackSampleCounter()
	{
		NumKeys= 0;
	}
};


// ***************************************************************************
/** see CTrackSampledQuatSmallHeader usage
 */
class CTrackSamplePack
{
public:
	NLMISC::CObjectVector<CTrackSampleHeader, false>	TrackHeaders;
	NLMISC::CObjectVector<uint8, false>					Times;
	NLMISC::CObjectVector<CQuatPack, false>				Keys;
};


// ***************************************************************************
/** For minimum CTrackSampledQuat Header Overhead (44 bytes here). This is a compressed
 *	version of CTrackSampledQuat. It works only with 1 TimeBlock (95% of animations)
 *	and assumes that most of CTrackSampledCommon data (loop etc...) is the same for all tracks of an animation
 *	The final size of this class is:
 *		4		(vtable)
 *		4		ptr on CTrackSamplePack
 *		1+1+2	offset in CTrackSamplePack
 */
class CTrackSampledQuatSmallHeader : public ITrack
{
public:

	/// Constructor
	CTrackSampledQuatSmallHeader(CTrackSamplePack *pack, uint8 headerIndex, uint8 numKeys, uint16 keyIndex);
	virtual ~CTrackSampledQuatSmallHeader();
	// not designed to be serialized
	CTrackSampledQuatSmallHeader() {nlstop;}
	NLMISC_DECLARE_CLASS (CTrackSampledQuatSmallHeader);
	
	/// From UTrack/ITrack.
	// @{
	virtual bool					getLoopMode() const;
	virtual TAnimationTime			getBeginTime () const;
	virtual TAnimationTime			getEndTime () const;
	virtual const IAnimatedValue	&eval (const TAnimationTime& date, CAnimatedValueBlock &avBlock);
	// NB: serial assert cause not serialised but compiled at runtime
	virtual void					serial(NLMISC::IStream &f);
	// NB: do not support sample division: it must be applied before compression
	// @}

protected:
	// Ptr on global data. only one in CAnimation 
	CTrackSamplePack				*_TrackSamplePack;
	// The index of misc Anim header data in _TrackSamplePack->TrackHeaders
	uint8							_IndexTrackHeader;
	// The Number of Keys of this track
	uint8							_NumKeys;
	// The index of starting key in _TrackSamplePack->Times and in _TrackSamplePack->Keys
	uint16							_KeyIndex;

	// same code than CTrackSampledCommon
	enum	TEvalType	{EvalDiscard, EvalKey0, EvalInterpolate};
	TEvalType						evalTime (const TAnimationTime& date, uint &keyId0, uint &keyId1, float &interpValue);
	
};	


} // NL3D


#endif // NL_TRACK_SAMPLED_QUAT_SMALL_HEADER_H

/* End of track_sampled_quat_small_header.h */
