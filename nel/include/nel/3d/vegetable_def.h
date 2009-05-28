/** \file vegetable_def.h
 * Some global definitions for CVegetable*
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

#ifndef NL_VEGETABLE_DEF_H
#define NL_VEGETABLE_DEF_H

#include "nel/misc/types_nl.h"


namespace NL3D
{

// ***************************************************************************
// RdrPass for Vegetables
#define	NL3D_VEGETABLE_NRDRPASS						5
#define	NL3D_VEGETABLE_RDRPASS_LIGHTED				0
#define	NL3D_VEGETABLE_RDRPASS_LIGHTED_2SIDED		1
#define	NL3D_VEGETABLE_RDRPASS_UNLIT				2
#define	NL3D_VEGETABLE_RDRPASS_UNLIT_2SIDED			3
#define	NL3D_VEGETABLE_RDRPASS_UNLIT_2SIDED_ZSORT	4


// 64 LUT entries in constant of VertexProgram.
#define	NL3D_VEGETABLE_VP_LUT_SIZE			64


/// For Landscape Vegetable: Distance Types are: 10m, 20m, 30m, 40m, 50m.
#define	NL3D_VEGETABLE_BLOCK_NUMDIST	5
#define	NL3D_VEGETABLE_BLOCK_ELTDIST	10.0f
/// Blend apperance transition
#define	NL3D_VEGETABLE_BLOCK_BLEND_TRANSITION_DIST	10.0f


/// The number of Quadrant for vegetable sorting.
#define	NL3D_VEGETABLE_NUM_QUADRANT		8


/// The precision of frequency factor: 1/16.
#define	NL3D_VEGETABLE_FREQUENCY_FACTOR_PREC		16


} // NL3D


#endif // NL_VEGETABLE_DEF_H

/* End of vegetable_def.h */
