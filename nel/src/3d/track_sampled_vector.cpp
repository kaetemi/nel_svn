/** \file track_sampled_vector.cpp
 * TODO: File description
 *
 * $Id: track_sampled_vector.cpp,v 1.5 2005/02/22 10:19:12 besson Exp $
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

#include "std3d.h"

#include "nel/misc/common.h"
#include "track_sampled_vector.h"

using namespace NLMISC;
using namespace std;


namespace NL3D 
{

// ***************************************************************************
// ***************************************************************************
// CTrackSampledVector
// ***************************************************************************
// ***************************************************************************


// ***************************************************************************
CTrackSampledVector::CTrackSampledVector()
{
}

// ***************************************************************************
CTrackSampledVector::~CTrackSampledVector()
{
}

// ***************************************************************************
void					CTrackSampledVector::serial(NLMISC::IStream &f)
{
	/*
	Version 0:
		- base version.
	*/
	(void)f.serialVersion(0);

	// serial Time infos.
	CTrackSampledCommon::serialCommon(f);

	// serial Keys.
	f.serial(_Keys);
}

// ***************************************************************************
void	CTrackSampledVector::build(const std::vector<uint16> &timeList, const std::vector<CVector> &keyList, 
	float beginTime, float endTime)
{
	nlassert( endTime>beginTime || (beginTime==endTime && keyList.size()<=1) );
	nlassert( keyList.size()==timeList.size() );
	uint i;

	// reset.
	uint	numKeys= keyList.size();
	_Keys.clear();
	_TimeBlocks.clear();

	// Build Common time information
	CTrackSampledCommon::buildCommon(timeList, beginTime, endTime);


	// Compute All Key values.
	//===================
	_Keys.resize(numKeys);
	for(i=0; i<numKeys;i++)
	{
		// no compression for now
		_Keys[i]= keyList[i];
	}

}

// ***************************************************************************
const IAnimatedValue	&CTrackSampledVector::eval (const TAnimationTime& date, CAnimatedValueBlock &avBlock)
{
	// Eval time, and get key interpolation info
	uint	keyId0;
	uint	keyId1;
	float	interpValue;
	TEvalType	evalType= evalTime(date, _Keys.size(), keyId0, keyId1, interpValue);

	// Discard? 
	if( evalType==EvalDiscard )
		return avBlock.ValVector;
	// One Key? easy, and quit.
	else if( evalType==EvalKey0 )
	{
		avBlock.ValVector.Value= _Keys[keyId0];
	}
	// interpolate
	else if( evalType==EvalInterpolate )
	{
		const CVector	&valueKey0= _Keys[keyId0];
		const CVector	&valueKey1= _Keys[keyId1];

		// interpolate
		avBlock.ValVector.Value= valueKey0*(1-interpValue) + valueKey1*interpValue;
	}
	else
	{
		nlstop;
	}

	return avBlock.ValVector;
}


// ***************************************************************************
void CTrackSampledVector::applySampleDivisor(uint sampleDivisor)
{
	if(sampleDivisor<=1)
		return;
	
	// **** build the key indices to keep, and rebuild the timeBlocks
	static	std::vector<uint32>		keepKeys;
	applySampleDivisorCommon(sampleDivisor, keepKeys);
	
	// **** rebuild the keys
	NLMISC::CObjectVector<CVector, false>		newKeys;
	newKeys.resize(keepKeys.size());
	for(uint i=0;i<newKeys.size();i++)
	{
		newKeys[i]= _Keys[keepKeys[i]];
	}
	// copy
	_Keys= newKeys;

	// TestYoyo
	/*nlinfo("ANIMQUAT:\t%d\t%d\t%d\t%d", sizeof(*this), _TimeBlocks.size(), 
		_TimeBlocks.size()?_TimeBlocks[0].Times.size():0,
		_Keys.size() * sizeof(CVector));*/
}


} // NL3D
