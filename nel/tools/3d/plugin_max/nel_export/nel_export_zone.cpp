/** \file nel_export_zone.cpp
 * TODO: File description
 *
 * $Id: nel_export_zone.cpp,v 1.7 2007/03/19 09:55:26 boucher Exp $
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

#include "std_afx.h"
#include "nel_export.h"
#include "nel/3d/zone.h"
#include "nel/3d/zone_symmetrisation.h"
#include "../nel_patch_lib/rpo.h"

using namespace NL3D;
using namespace NLMISC;

// --------------------------------------------------

bool CNelExport::exportZone (const char *sPath, INode& node, TimeValue time)
{
	// Result to return
	bool bRet=false;

	// Eval the object a time
	ObjectState os = node.EvalWorldState(time);

	// Object exist ?
	if (os.obj)
	{
		// Object can convert itself to NeL patchmesh ?
		RPO* pPatchObject = (RPO*) os.obj->ConvertToType(time, RYKOLPATCHOBJ_CLASS_ID);

		// Conversion success ?
		if (pPatchObject)
		{
			// Build the zone
			CZone zone;
			CZoneSymmetrisation zoneSymmetry;
			if (pPatchObject->rpatch->exportZone (&node, &pPatchObject->patch, zone, zoneSymmetry, 0, 160, 1, false))
			{
				// Open a file
				COFile file;
				if (file.open (sPath))
				{
					try
					{
						// Serial the zone
						zone.serial (file);

						// All is good
						bRet=true;
					}
					catch (...)
					{
					}
				}
				file.close ();
			}

#ifdef NL_DEBUG
			// load the zone
			CZone checkZone;
			CIFile inputFile;
			if (inputFile.open (sPath))
			{
				checkZone.serial (inputFile);

				// Check zone
				std::vector<CPatchInfo> patchs;
				std::vector<CBorderVertex> borderVertices;
				checkZone.retrieve(patchs, borderVertices);

				// Get Center and scal
				float fScale=checkZone.getPatchScale();
				CVector vCenter=checkZone.getPatchBias();

				// Watch points
				for (sint nPatch=0; nPatch<(sint)patchs.size(); nPatch++)
				{
					for (sint nVert=0; nVert<4; nVert++)
					{
						CVector v=patchs[nPatch].Patch.Vertices[nVert];
					}
				}
			}
#endif // NL_DEBUG


		}
	}
	return bRet;
}



