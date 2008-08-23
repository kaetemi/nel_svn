/** \file vegetable_quadrant.cpp
 * TODO: File description
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

#include "std3d.h"

#include "nel/3d/vegetable_quadrant.h"
#include "nel/misc/matrix.h"


using namespace NLMISC;

namespace NL3D 
{


/*
 * Constructor, just used to init quadrants.
 */
CVegetableQuadrant::CVegetableQuadrant()
{
	for(uint i=0;i<NL3D_VEGETABLE_NUM_QUADRANT;i++)
	{
		CMatrix	mat;
		mat.rotateZ(2*(float)Pi * i / NL3D_VEGETABLE_NUM_QUADRANT);
		Dirs[i]= mat.getJ();
	}
}


// Quadrants.
CVector		CVegetableQuadrant::Dirs[NL3D_VEGETABLE_NUM_QUADRANT];

// The variable to init the quadrants.
static	CVegetableQuadrant		InitVegetableQuadrant;


} // NL3D
