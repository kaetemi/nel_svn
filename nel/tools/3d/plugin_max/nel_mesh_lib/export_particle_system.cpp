/** \file export_particle_system.cpp
 *
 * $Id: export_particle_system.cpp,v 1.6 2007/03/19 09:55:27 boucher Exp $
 */

/* Copyright, 2000, 2001, 2002 Nevrax Ltd.
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

#include "StdAfx.h"
#include "nel/3d/particle_system_model.h"
#include "nel/3d/particle_system_shape.h"
#include "nel/misc/path.h"
#include "export_appdata.h"
#include "export_nel.h"


using namespace NL3D;

IShape* CExportNel::buildParticleSystem(INode& node, TimeValue time)
{
	Object *obj = node.EvalWorldState(time).obj;
	nlassert(obj);
	std::string shapeName;
	// try to get the complete path	
	if (!CExportNel::getValueByNameUsingParamBlock2(node, "ps_file_name", (ParamType2) TYPE_STRING, &shapeName, 0))
	{
		// if not found, get from the APP_DATAS
		shapeName = CExportNel::getNelObjectName(node);
		if (shapeName.empty()) return NULL;
		shapeName = NLMISC::CPath::lookup("shapeName", false);
		if (shapeName.empty()) return NULL;
	}
	
	//
	
	if (!shapeName.empty())
	{											
		NL3D::CShapeStream ss;
		NLMISC::CIFile iF;
		if (iF.open(shapeName.c_str()))
		{
			iF.serial(ss);
			if (!dynamic_cast<CParticleSystemShape *>(ss.getShapePointer()))
			{
				mprintf("Error : Object shape %s isn't a particle system", shapeName.c_str());
				return NULL;
			}

			CParticleSystemShape *pss = static_cast<CParticleSystemShape *>(ss.getShapePointer());

			// ********************************
			// *** Export default transformation
			// ********************************

			// Get the node matrix
			Matrix3 localTM;
			getLocalMatrix (localTM, node, time);

			// Get the translation, rotation, scale of the node
			CVector pos, scale;
			CQuat rot;
			decompMatrix (scale, rot, pos, localTM);

			// Set the default values
			pss->getDefaultPos()->setDefaultValue(pos);					
			pss->getDefaultScale()->setDefaultValue(scale);					
			pss->getDefaultRotQuat()->setDefaultValue(rot);												
			return pss;
		}
		else
		{
			mprintf("Error : Can't find %s while exporting a particle system \n", shapeName.c_str());
			return NULL;
		}				
	}
	return NULL;
}