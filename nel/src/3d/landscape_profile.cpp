/** \file landscape_profile.cpp
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

#include "std3d.h"

#include "nel/3d/landscape_profile.h"


namespace NL3D
{

// ***************************************************************************
// Yoyo: for profile only.
sint		ProfNTessFace= 0;
sint		ProfNRdrFar0= 0;
sint		ProfNRdrFar1= 0;
sint		ProfNRdrTile[NL3D_MAX_TILE_PASS];
sint		ProfNRefineFaces;
sint		ProfNRefineComputeFaces;
sint		ProfNRefineLeaves;
sint		ProfNSplits;
sint		ProfNMerges;
// New PriorityList vars.
sint		ProfNRefineInTileTransition;
sint		ProfNRefineWithLowDistance;
sint		ProfNSplitsPass;
// Material setup Profile
sint		ProfNTileSetupMaterial= 0;
sint		ProfNFar0SetupMaterial= 0;
sint		ProfNFar1SetupMaterial= 0;
// Patch render
sint		ProfNPatchRdrFar0=0;
sint		ProfNPatchRdrFar1=0;

} // NL3D
