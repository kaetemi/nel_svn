/** \file shape_info.h
 *
 */

/* Copyright, 2000-2006 Nevrax Ltd.
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

#ifndef NL_SHAPE_INFO_H
#define NL_SHAPE_INFO_H


#include "nel/misc/triangle.h"
#include "nel/misc/aabbox.h"
//
#include <vector>


namespace NL3D
{

class CMeshGeom;
class CMeshMRMGeom;
class IShape;
class CMeshBase;

// Mesh or mrm mesh as a bunch of triangles
class CShapeInfo
{
public:
	NLMISC::CAABBox					LocalBBox;
	std::vector<NLMISC::CTriangle>	Tris;
public:
	void build(const NL3D::IShape &shape);
	void swap(CShapeInfo &other);
private:
	void build(const NL3D::CMeshBase &meshBase, const NL3D::CMeshGeom &meshGeom);
	void build(const NL3D::CMeshBase &meshBase, const NL3D::CMeshMRMGeom &meshGeom);
};

// a shape cache, sorted by names
typedef std::map<std::string, CShapeInfo> TShapeCache;

// format a shape name to have lowercase + extension, for lookup in shape cache
std::string standardizeShapeName(const std::string &name);

} // NL3D


#endif
