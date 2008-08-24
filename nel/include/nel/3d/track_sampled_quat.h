/** \file track_sampled_quat.h
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

#ifndef NL_TRACK_SAMPLED_QUAT_H
#define NL_TRACK_SAMPLED_QUAT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/object_vector.h"
#include "nel/misc/quat.h"
#include "nel/3d/track_sampled_common.h"


namespace NL3D
{


// For Debug only (must be defined). Correct serialized version is with compression.
#define	NL3D_TSQ_ALLOW_QUAT_COMPRESS


// ***************************************************************************
// For Debug only. Correct serialized version is with compression.
#ifdef NL3D_TSQ_ALLOW_QUAT_COMPRESS
/** A packed quaternion.
 */
class	CQuatPack
{
public:
	sint16		x,y,z,w;

	void		pack(const CQuat &quat);
	void		unpack(CQuat &quat);

	void		serial(NLMISC::IStream &f)
	{
		// NB: no version here.
		f.serial(x,y,z,w);
	}

	bool	operator==(const CQuatPack &oq) const
	{
		return x==oq.x && y==oq.y && z==oq.z && w==oq.w;
	}

};
#else
// A dummy packed quaternion.
class	CQuatPack
{
public:
	CQuat	q;

	void		pack(const CQuat &quat)	{q= quat;}
	void		unpack(CQuat &quat)		{quat= q;}
	void		serial(NLMISC::IStream &f)	{f.serial(q);}
	bool	operator==(const CQuatPack &oq) const {return q==oq.q;}
};
#endif


// ***************************************************************************
/**
 * This track is supposed to be Lighter in memory than CTrackKeyFramerTCBQuat, and also is maybe faster.
 *	The track is an oversampled version of CTrackKeyFramerTCBQuat (or any quat interpolator), to 30 fps for example,
 *	but each key is 9 bytes in memory, instead of 96.
 *	Only linear interpolation is performed (use CQuat::slerp) between 2 keys. And Keys are precomputed
 *	to be correctly on the same quaternion hemisphere from the preceding to the next.
 *
 *	9 bytes per key is achieved by encoding this way:
 *		1 byte for the length/key time, measured in samples, and not in second (hence we can skip at max 255 keys).
 *		8 byte for a light normalized quaternion: x,y,z,w are stored in 16 bits.
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CTrackSampledQuat : public CTrackSampledCommon
{
public:

	/// Constructor
	CTrackSampledQuat();
	virtual ~CTrackSampledQuat();
	NLMISC_DECLARE_CLASS (CTrackSampledQuat);

	/// From UTrack/ITrack.
	// @{
	virtual const IAnimatedValue	&eval (const TAnimationTime& date, CAnimatedValueBlock &avBlock);
	virtual void					serial(NLMISC::IStream &f);
	virtual void applySampleDivisor(uint sampleDivisor);
	// @}

	/** Build the track from a list of CKey.
	 *	They must be already precompiled. ie they must all lies on the same hemisphere from prec key.
	 *	nlassert if ! same length.
	 *	\param timeList the list of key time. First must be ==0. nlassert if difference between 2 keys is > 255
	 *	\param keyList the list of keys, not yet compressed to CQuatPack (done internally)
	 *	\param beginTime map to the timeList[0] time.
	 *	\param endTime map to the timeList[size-1] time.
	 */
	void	build(const std::vector<uint16> &timeList, const std::vector<CQuat> &keyList,
		float beginTime, float endTime);

	/// For Quat Track Header Compression
	// @{
	virtual bool	applyTrackQuatHeaderCompressionPass0(CTrackSampleCounter &quatCounter);
	virtual ITrack	*applyTrackQuatHeaderCompressionPass1(uint &globalKeyOffset, CTrackSamplePack &quatPacker);
	// @}

// **********************
protected:

	// Key Values
	NLMISC::CObjectVector<CQuatPack, false>		_Keys;
};


} // NL3D


#endif // NL_TRACK_SAMPLED_QUAT_H

/* End of track_sampled_quat.h */
