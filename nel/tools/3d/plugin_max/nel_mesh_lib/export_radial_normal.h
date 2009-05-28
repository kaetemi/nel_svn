/** \file export_radial_normal.h
 * Compute radial normales
 *
 * $Id: export_radial_normal.h,v 1.2 2002/08/27 12:40:45 corvazier Exp $
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

#ifndef NL_EXPORT_RADIAL_NORMAL_H
#define NL_EXPORT_RADIAL_NORMAL_H

#include "export_appdata.h"

class CExportNel;

class CRadialVertices
{
public:
	CRadialVertices ();
	void init (INode *node, Mesh *mesh, TimeValue time, Interface &ip, CExportNel &nelExport);
	bool isUsingRadialNormals (uint face);
	Point3 getLocalNormal (uint vertex, uint face);
private:
	uint32				_SmoothingGroupMask;
	NLMISC::CVector		_Pivot[NEL3D_RADIAL_NORMAL_COUNT];
	INode				*_NodePtr;
	Mesh				*_MeshPtr;
};

#endif // NL_EXPORT_RADIAL_NORMAL_H

