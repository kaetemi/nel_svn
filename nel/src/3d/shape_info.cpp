/** \file shape_info.cpp
 * Collision on a set of packed zones (packed representation)
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


#include "std3d.h"
//
#include "nel/3d/shape_info.h"
#include "nel/3d/mesh.h"
#include "nel/3d/mesh_geom.h"
#include "nel/3d/mesh_mrm.h"
#include "nel/3d/mesh_multi_lod.h"
//
#include "nel/misc/path.h"
//

using namespace NLMISC;


namespace NL3D
{

// ***************************************************************************
void CShapeInfo::swap(CShapeInfo &other)
{
	Tris.swap(other.Tris);
	std::swap(LocalBBox, (other.LocalBBox));
}


// ***************************************************************************
void CShapeInfo::build(const IShape &shape)
{
	LocalBBox.setMinMax(CVector::Null, CVector::Null);
	// Cast to CMesh
	const CMesh *mesh=dynamic_cast<const CMesh*>(&shape);

	// Cast to CMeshMultiLod
	const CMeshMultiLod *meshMulti=dynamic_cast<const CMeshMultiLod*>(&shape);

	// Cast to CMeshMultiLod
	const CMeshMRM *meshMRM=dynamic_cast<const CMeshMRM*>(&shape);

	// It is a mesh ?
	if (mesh)
	{
		// Add its triangles
		build(*mesh, mesh->getMeshGeom());
	}
	// It is a CMeshMultiLod ?
	else if (meshMulti)
	{
		// Get the first geommesh
		const IMeshGeom *meshGeom=&meshMulti->getMeshGeom (0);

		// Dynamic cast
		const CMeshGeom *geomMesh=dynamic_cast<const CMeshGeom*>(meshGeom);
		if (geomMesh)
		{
			build(*meshMulti, *geomMesh);
		}

		// Dynamic cast
		const CMeshMRMGeom *mrmGeomMesh=dynamic_cast<const CMeshMRMGeom*>(meshGeom);
		if (mrmGeomMesh)
		{
			build(*meshMulti, *mrmGeomMesh);
		}
	}
	// It is a CMeshMultiLod ?
	else if (meshMRM)
	{
		// Get the first lod mesh geom
		build(*meshMRM, meshMRM->getMeshGeom ());
	}
	// compute bbox
	if (Tris.empty())
	{
		LocalBBox.setMinMax(CVector::Null, CVector::Null);
	}
	else
	{
		LocalBBox.setMinMax(Tris[0].V0, Tris[0].V0);
		LocalBBox.extend(Tris[0].V1);
		LocalBBox.extend(Tris[0].V2);
		for(uint k = 1; k < Tris.size(); ++k)
		{
			LocalBBox.extend(Tris[k].V0);
			LocalBBox.extend(Tris[k].V1);
			LocalBBox.extend(Tris[k].V2);
		}
	}
}

// ***************************************************************************
void CShapeInfo::build(const CMeshBase &meshBase, const CMeshGeom &meshGeom)
{
	// Get the vertex buffer
	const CVertexBuffer &vb=meshGeom.getVertexBuffer();
	CVertexBufferRead vba;
	vb.lock (vba);

	// For each matrix block
	uint numBlock=meshGeom.getNbMatrixBlock();
	for (uint block=0; block<numBlock; block++)
	{
		// For each render pass
		uint numRenderPass=meshGeom.getNbRdrPass(block);
		for (uint pass=0; pass<numRenderPass; pass++)
		{
			// Get the material
			const CMaterial &material = meshBase.getMaterial (meshGeom.getRdrPassMaterial ( block, pass));

			if (material.getBlend()) continue; // don't test against transparent materials
			//if (material.getAlphaTest()) continue; // don't test against transparent materials



			// Get the primitive block
			const CIndexBuffer &primitive=meshGeom.getRdrPassPrimitiveBlock ( block, pass);
			// Copy triangles
			CIndexBufferRead iba;
			primitive.lock (iba);
			if (iba.getFormat() == CIndexBuffer::Indices32)
			{
				const uint32* triIndex= (const uint32*) iba.getPtr ();
				uint numTri=primitive.getNumIndexes ()/3;
				uint tri;
				for (tri=0; tri<numTri; tri++)
				{
					// Vertex
					CVector v0= *vba.getVertexCoordPointer (triIndex[tri*3]);
					CVector v1= *vba.getVertexCoordPointer (triIndex[tri*3+1]);
					CVector v2= *vba.getVertexCoordPointer (triIndex[tri*3+2]);
					Tris.push_back(NLMISC::CTriangle (v0, v1, v2));
				}
			}
			else
			{
				const uint16* triIndex= (const uint16*) iba.getPtr ();
				uint numTri=primitive.getNumIndexes ()/3;
				uint tri;
				for (tri=0; tri<numTri; tri++)
				{
					// Vertex
					CVector v0= *vba.getVertexCoordPointer (triIndex[tri*3]);
					CVector v1= *vba.getVertexCoordPointer (triIndex[tri*3+1]);
					CVector v2= *vba.getVertexCoordPointer (triIndex[tri*3+2]);
					Tris.push_back(NLMISC::CTriangle (v0, v1, v2));
				}
			}
		}
	}
}


// ***************************************************************************
void CShapeInfo::build(const CMeshBase &meshBase, const CMeshMRMGeom &meshGeom)
{
	// Get the vertex buffer
	const CVertexBuffer &vb=meshGeom.getVertexBuffer();
	CVertexBufferRead vba;
	vb.lock (vba);

	// For each render pass
	uint numRenderPass=meshGeom.getNbRdrPass(0);
	for (uint pass=0; pass<numRenderPass; pass++)
	{
		// Get the material
		const CMaterial &material = meshBase.getMaterial (meshGeom.getRdrPassMaterial ( 0, pass));

		if (material.getBlend()) continue; // don't test against transparent materials
		//if (material.getAlphaTest()) continue; // don't test against transparent materials


		// Get the primitive block
		const CIndexBuffer &primitive=meshGeom.getRdrPassPrimitiveBlock ( 0, pass);

		// Copy triangles
		CIndexBufferRead iba;
		primitive.lock (iba);
		if (iba.getFormat() == CIndexBuffer::Indices32)
		{
			const uint32* triIndex= (const uint32 *) iba.getPtr ();
			uint numTri=primitive.getNumIndexes ()/3;
			uint tri;
			for (tri=0; tri<numTri; tri++)
			{
				// Vertex
				CVector v0 = *vba.getVertexCoordPointer (triIndex[tri*3]);
				CVector v1 = *vba.getVertexCoordPointer (triIndex[tri*3+1]);
				CVector v2 = *vba.getVertexCoordPointer (triIndex[tri*3+2]);
				Tris.push_back (NLMISC::CTriangle (v0, v1, v2));
			}
		}
		else
		{
			const uint16* triIndex= (const uint16 *) iba.getPtr ();
			uint numTri=primitive.getNumIndexes ()/3;
			uint tri;
			for (tri=0; tri<numTri; tri++)
			{
				// Vertex
				CVector v0 = *vba.getVertexCoordPointer (triIndex[tri*3]);
				CVector v1 = *vba.getVertexCoordPointer (triIndex[tri*3+1]);
				CVector v2 = *vba.getVertexCoordPointer (triIndex[tri*3+2]);
				Tris.push_back (NLMISC::CTriangle (v0, v1, v2));
			}
		}
	}
}


// ***************************************************************************
std::string standardizeShapeName(const std::string &name)
{
	std::string result = NLMISC::strlwr(name);
	if (CFile::getExtension(result).empty())
	{
		result += ".shape";
	}
	return result;
}

} // NL3D



