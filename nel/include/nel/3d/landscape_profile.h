/** \file landscape_profile.h
 * Yoyo: for landscape profile only.
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

#ifndef NL_LANDSCAPE_PROFILE_H
#define NL_LANDSCAPE_PROFILE_H

#include "nel/misc/types_nl.h"
#include "nel/3d/tessellation.h"


// Yoyo: hide this if do not want to profile landscape.
#define		NL3D_PROFILE_LAND
// Hidden in release.
#ifdef NL_RELEASE
#undef		NL3D_PROFILE_LAND
#endif

#ifdef	NL3D_PROFILE_LAND
#define	NL3D_PROFILE_LAND_SET(_x_, _y_)	_x_=_y_
#define	NL3D_PROFILE_LAND_ADD(_x_, _y_)	_x_+=_y_
#else
#define	NL3D_PROFILE_LAND_SET(_x_, _y_)
#define	NL3D_PROFILE_LAND_ADD(_x_, _y_)
#endif


namespace NL3D
{

// ***************************************************************************
// Yoyo: for profile only.
extern	sint		ProfNTessFace;
extern	sint		ProfNRdrFar0;
extern	sint		ProfNRdrFar1;
extern	sint		ProfNRdrTile[NL3D_MAX_TILE_PASS];
extern	sint		ProfNRefineFaces;
extern	sint		ProfNRefineComputeFaces;
extern	sint		ProfNRefineLeaves;
extern	sint		ProfNSplits;
extern	sint		ProfNMerges;
// New PriorityList vars.
extern	sint		ProfNRefineInTileTransition;
extern	sint		ProfNRefineWithLowDistance;
extern	sint		ProfNSplitsPass;
// Material setup Profile
extern	sint		ProfNTileSetupMaterial;
extern	sint		ProfNFar0SetupMaterial;
extern	sint		ProfNFar1SetupMaterial;
// Patch render
extern	sint		ProfNPatchRdrFar0;
extern	sint		ProfNPatchRdrFar1;


} // NL3D


#endif // NL_LANDSCAPE_PROFILE_H

/* End of landscape_profile.h */
