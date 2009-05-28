/** \file hrc_trav.h
 * TODO: File description
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef NL_HRC_TRAV_H
#define NL_HRC_TRAV_H

#include "nel/3d/trav_scene.h"
#include "nel/misc/matrix.h"
#include "nel/misc/debug.h"


namespace	NL3D
{


using NLMISC::CVector;
using NLMISC::CPlane;
using NLMISC::CMatrix;


class	CTransformShape;


// ***************************************************************************
/**
 * The hierarchy traversal.
 *
 * NB: see CScene for 3d conventions (orthonormal basis...)
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CHrcTrav : public CTraversal
{
public:
	/// The visibility flag. In the root case, Herit means Show.
	enum	TVisibility
	{
		Show=0,		// The model is shown in hte hierarchy
		Hide,		// The model is hidden in hte hierarchy
		Herit,		// The model herit the visibilty from his father

		VisibilityCount
	};

public:

	/// Constructor
	CHrcTrav()
	{
		// NB: Now, models update is done before ALL traversals.
		// Hence, we must inc the value before scene rendering. This is equivalent to start with 1, and inc at end of traverse().
		CurrentDate= 1;
	}


	/// \name ITrav/ITravScene Implementation.
	//@{
	void				traverse();
	//@}


public:

	// ClusterSystem. The moving object for the current frame (only TransformShape can be inserted dynamiccaly in Clusters).
	std::vector<CTransformShape*> _MovingObjects;

	// ONLY FOR MODELS.

	sint64		CurrentDate;	// The current date of the traversal, useful for matrix update.
};


}


#endif // NL_HRC_TRAV_H

/* End of hrc_trav.h */
