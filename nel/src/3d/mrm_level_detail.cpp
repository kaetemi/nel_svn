/** \file mrm_level_detail.cpp
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


#include "std3d.h"

#include "nel/3d/mrm_level_detail.h"


namespace NL3D
{


// ***************************************************************************
void			CMRMLevelDetail::compileDistanceSetup()
{
	// Compute _OODistDelta.
	OODistanceDelta= 1.0f / (DistanceCoarsest - DistanceFinest);
	/* Compute exponent pow, such that 0.5= dMiddle^pow;
		ie 0.5= e(ln dMiddle * pow)
	*/
	float	dMiddle= (DistanceCoarsest - DistanceMiddle) * OODistanceDelta;
	DistancePow= (float)(log(0.5) / log(dMiddle));
}


// ***************************************************************************
float			CMRMLevelDetail::getLevelDetailFromDist(float dist)
{
	if(dist <= DistanceFinest)
		return 1;
	if(dist >= DistanceCoarsest)
		return 0;

	float	d= (DistanceCoarsest - dist) * OODistanceDelta;
	return  (float)pow(d, DistancePow);
}


} // NL3D
