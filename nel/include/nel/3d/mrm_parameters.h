/** \file mrm_parameters.h
 * parameters of MRM build process.
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

#ifndef NL_MRM_PARAMETERS_H
#define NL_MRM_PARAMETERS_H

#include "nel/misc/types_nl.h"


namespace NL3D {


// ***************************************************************************
/**
 * This class is to be used with CMRMBuilder. It describe parameters of MRM build process.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CMRMParameters
{
public:
	/** For skinning, how vertex skinning is degraded, When 2 SkinWeights are blended.
	 * SkinReductionMin is the fastest, and SkinReductionBest is the slowest (but the best).
	 * Default is SkinReductionMax.
	 */
	enum	TSkinReduction
	{
		SkinReductionMin=0,		// NbMatrixOut= min(NbMatrixIn1, NbMatrixIn2).
		SkinReductionMax, 		// NbMatrixOut= max(NbMatrixIn1, NbMatrixIn2).
		SkinReductionBest, 		// NbMatrixOut= min(NbMatrixIn1 "+" NbMatrixIn2, NL3D_MESH_SKINNING_MAX_MATRIX).
	};

public:
	/// numbers of LODs wanted (11 by default).
	uint32			NLods;
	/// minimum faces wanted (a divisor of number of faces in baseMesh, 20 by default)
	uint32			Divisor;
	/// If mesh is skinned, control the quality of the skinning redcution.
	TSkinReduction	SkinReduction;


	/// \Degradation control.
	// @{
	/// The MRM has its max faces when dist<=DistanceFinest. nlassert if <0.
	float			DistanceFinest;		// default : 5.
	/// The MRM has 50% of its faces at dist==DistanceMiddle. nlassert if <= DistanceFinest.
	float			DistanceMiddle;		// default : 30.
	/// The MRM has faces/Divisor when dist>=DistanceCoarsest. nlassert if <= DistanceMiddle.
	float			DistanceCoarsest;	// default : 200.
	// @}


	/// Constructor
	CMRMParameters()
	{
		NLods= 11;
		Divisor= 20;
		SkinReduction= SkinReductionMax;

		DistanceFinest= 5;
		DistanceMiddle= 30;
		DistanceCoarsest= 200;
	}

};


} // NL3D


#endif // NL_MRM_PARAMETERS_H

/* End of mrm_parameters.h */
