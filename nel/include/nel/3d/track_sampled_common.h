/** \file track_sampled_common.h
 * TODO: File description
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_TRACK_SAMPLED_COMMON_H
#define NL_TRACK_SAMPLED_COMMON_H

#include "nel/misc/types_nl.h"
#include "nel/misc/object_vector.h"
#include "nel/3d/track.h"


namespace NL3D {


// ***************************************************************************
/**
 * Abstract Base class for CTrackSampledQuat and CTrackSampledVector
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CTrackSampledCommon : public ITrack
{
public:

	/// Constructor
	CTrackSampledCommon();
	virtual ~CTrackSampledCommon();

	/// From UTrack/ITrack.
	// @{
	virtual bool					getLoopMode() const;
	virtual TAnimationTime			getBeginTime () const;
	virtual TAnimationTime			getEndTime () const;
	// @}

	/// Change the loop mode. true default
	void	setLoopMode(bool mode);


// **********************
protected:
	// Param of animation
	bool					_LoopMode;
	float					_BeginTime;
	float					_EndTime;
	float					_TotalRange;
	float					_OOTotalRange;
	// The frame Time == (_EndTime-_BeginTime)/NumKeys
	float					_DeltaTime;
	float					_OODeltaTime;

	// Typically, there is only one TimeBlock, for anim < 8.5 seconds (256/30 fps == 8.5 second).
	class	CTimeBlock
	{
	public:
		// Value to add to the key in the array to have real frame value.
		uint16									TimeOffset;
		// Value to add to the index to have Key index in _Keys.
		uint32									KeyOffset;

		// Key Time. Separated for optimal memory packing, and better cache use at dichotomy search
		NLMISC::CObjectVector<uint8, false>		Times;

		// For dicho comp
		bool		operator<=(const CTimeBlock &tb) const
		{
			return TimeOffset <= tb.TimeOffset;
		}

		void		serial(NLMISC::IStream &f);
	};

	// Time Values
	NLMISC::CObjectVector<CTimeBlock>			_TimeBlocks;


protected:

	enum	TEvalType	{EvalDiscard, EvalKey0, EvalInterpolate};

	// called by sons.
	TEvalType						evalTime (const TAnimationTime& date, uint numKeys, uint &keyId0, uint &keyId1, float &interpValue);

	// called by sons.
	void							serialCommon(NLMISC::IStream &f);

	/** Build the track time from a list of Keys.
	 *	\param timeList the list of key time. First must be ==0. nlassert if difference between 2 keys is > 255
	 *	\param beginTime map to the timeList[0] time.
	 *	\param endTime map to the timeList[size-1] time.
	 */
	void	buildCommon(const std::vector<uint16> &timeList, float beginTime, float endTime);

	/// used by derivers
	void	applySampleDivisorCommon(uint sampleDivisor, std::vector<uint32> &keepKeys);
};



} // NL3D


#endif // NL_TRACK_SAMPLED_COMMON_H

/* End of track_sampled_common.h */
