/** \file vegetable_quadrant.h
 * TODO: File description
 *
 * $Id: vegetable_quadrant.h,v 1.3 2005/02/22 10:19:12 besson Exp $
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

#ifndef NL_VEGETABLE_QUADRANT_H
#define NL_VEGETABLE_QUADRANT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "vegetable_def.h"


namespace NL3D 
{


using NLMISC::CVector;


// ***************************************************************************
/**
 * Static Quadrant direction for Vegetable ZSort rdrPass.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CVegetableQuadrant
{
public:

	/// Constructor
	CVegetableQuadrant();

	// Directions of quadrants
	static CVector		Dirs[NL3D_VEGETABLE_NUM_QUADRANT];
};


} // NL3D


#endif // NL_VEGETABLE_QUADRANT_H

/* End of vegetable_quadrant.h */
