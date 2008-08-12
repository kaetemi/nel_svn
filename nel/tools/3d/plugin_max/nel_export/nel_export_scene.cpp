/** \file nel_export_scene.cpp
 * TODO: File description
 *
 * $Id: nel_export_scene.cpp,v 1.12 2007/03/19 09:55:26 boucher Exp $
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

// Scene Exportation

// A scene is made of virtual object instance
// An object instance is 
// - A reference to a mesh (refered by the name of the node)
// - The transformations to get it to the world
// - The parent


#include "std_afx.h"
#include "nel_export.h"
#include "../nel_mesh_lib/export_nel.h"
#include "../nel_patch_lib/rpo.h"
#include "nel/../../src/3d/scene_group.h"

#include <vector>

using namespace std;
using namespace NL3D;
using namespace NLMISC;

// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------
bool CNelExport::exportInstanceGroup(string filename, vector<INode*>& vectNode)
{
	vector<INode*> resultInstanceNode;
	CInstanceGroup *pIG = _ExportNel->buildInstanceGroup (vectNode, resultInstanceNode, _Ip->GetTime());

	if (pIG != NULL)
	{
		COFile file;
		
		if (file.open (filename))
		{
			try
			{
				// Serial the skeleton
				pIG->serial (file);
				// All is good
			}
			catch (Exception &c)
			{
				// Cannot save the file
				MessageBox (NULL, c.what(), "NeL export", MB_OK|MB_ICONEXCLAMATION);
				return false;
			}
		}

		delete	pIG;
	}
	else
	{
		// No node found with a SWT Modifier
	}
	return true;
}
