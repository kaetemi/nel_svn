/** \file ig_lighter_lib.h
 * TODO: File description
 *
 * $Id: ig_lighter_lib.h,v 1.5 2007/03/19 09:55:26 boucher Exp $
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

#ifndef NL_IG_LIGHTER_LIB_H
#define NL_IG_LIGHTER_LIB_H

#include "nel/misc/types_nl.h"
#include "nel/../../src/3d/instance_lighter.h"

namespace NLPACS
{
	class	CRetrieverBank;
	class	CLocalRetriever;
	class	CGlobalRetriever;
	class	ULocalPosition;
};

// ***************************************************************************
/**
 * Ig Lighting with Pacs and 3D information.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CIgLighterLib
{
public:

	struct	CSurfaceLightingInfo
	{
		// Pacs information. set to NULL if don't want IgSurfaceLighting.
		NLPACS::CRetrieverBank		*RetrieverBank;
		NLPACS::CGlobalRetriever	*GlobalRetriever;
		float					CellSurfaceLightSize;
		float					CellRaytraceDeltaZ; 
		// FileName without the extension
		std::string				IgFileName;
		std::string				ColIdentifierPrefix;
		std::string				ColIdentifierSuffix;

		// Debug.
		bool					BuildDebugSurfaceShape;
		std::string				DebugSunName;
		std::string				DebugPLName;

		CSurfaceLightingInfo()
		{
			BuildDebugSurfaceShape= false;
		}
	};


	/**	light an Ig with all PACS / 3D informations:
	 *	\param instanceLighter used to light the ig. Should not be reused for successive lightIg()
	 *	\param igIn is the ig which contains all light/object information.
	 *	\param igOut is the ig resulting of lighting
	 *	\param lightDesc is options for lighting.
	 *	\param slInfo is the necessary info to build IGSurfaceLight grids.
	 */
	static void	lightIg(NL3D::CInstanceLighter &instanceLighter,
		const NL3D::CInstanceGroup &igIn, NL3D::CInstanceGroup &igOut, NL3D::CInstanceLighter::CLightDesc &lightDesc, 
		CSurfaceLightingInfo &slInfo, const char *igName);


// ******************************
private:

	// OverSample a cell, skipping samples not in Surface.
	static void	overSampleCell(NL3D::CIGSurfaceLightBuild::CCellCorner &cell, uint nSampleReq, 
		const NLPACS::CLocalRetriever &localRetriever, NLPACS::CGlobalRetriever &globalRetriever, 
		sint retrieverInstanceId, const NLPACS::ULocalPosition &localPos, float cellSize,
		float cellRaytraceDeltaZ);

};




#endif // NL_IG_LIGHTER_LIB_H

/* End of ig_lighter_lib.h */
