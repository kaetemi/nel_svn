/** \file coarse_mesh_manager.cpp
 * Management of coarse meshes.
 *
 * $Id: coarse_mesh_manager.cpp,v 1.22 2005/02/22 10:19:10 besson Exp $
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

#include "std3d.h"

#include "nel/3d/coarse_mesh_manager.h"
#include "nel/3d/mesh.h"
#include "nel/3d/texture_file.h"
#include "nel/misc/hierarchical_timer.h"
#include "nel/3d/clip_trav.h"
#include "nel/misc/fast_mem.h"


using namespace NLMISC;

namespace NL3D 
{


H_AUTO_DECL( NL3D_StaticLod_AddMesh )


// ***************************************************************************
CCoarseMeshManager::CCoarseMeshManager()
{
	// ** Init texture

	_Texture=new CTextureFile ();
	_TextureCategory= new ITexture::CTextureCategory("COARSE MESH MANAGER");
	_Texture->setTextureCategory(_TextureCategory);

	// ** Init material

	// Double sided
	_Material.initUnlit ();
	_Material.setDoubleSided (true);
	_Material.setAlphaTest (true);
	_Material.setColor (CRGBA (255, 255, 255));
	// Init blend Factors, for possible Alpha transition
	_Material.setSrcBlend(CMaterial::srcalpha);
	_Material.setDstBlend(CMaterial::invsrcalpha);

	// Texture
	_Material.setTexture (0, _Texture);

	// ** Init Geometry
	_VBuffer.setVertexFormat(NL3D_COARSEMESH_VERTEX_FORMAT_MGR);
	_VBuffer.setNumVertices(NL3D_COARSEMESH_VERTEXBUFFER_SIZE);
	_VBuffer.setName("CCoarseMeshManager");
	_VBuffer.setPreferredMemory(CVertexBuffer::AGPVolatile, false);
	_Triangles.setFormat(NL_COARSE_MESH_INDEX_FORMAT);
	_Triangles.setNumIndexes(NL3D_COARSEMESH_TRIANGLE_SIZE*3);
	_Triangles.setPreferredMemory(CIndexBuffer::RAMVolatile, false); // TODO : see if agp index is better	
	_CurrentNumVertices= 0;
	_CurrentNumTriangles= 0;
	NL_SET_IB_NAME(_Triangles, "CCoarseMeshManager");	
}

// ***************************************************************************

void CCoarseMeshManager::setTextureFile (const char* file)
{
	_Texture->setFileName (file);
}

// ***************************************************************************

bool CCoarseMeshManager::addMesh (uint numVertices, const uint8 *vBuffer, uint numTris, const TCoarseMeshIndexType *indexBuffer)
{	
	H_AUTO_USE( NL3D_StaticLod_AddMesh );

	// if 0 mesh, quit
	if(numTris==0 || numVertices==0)
		return true;

	// check vertex size
	if(_CurrentNumVertices + numVertices > NL3D_COARSEMESH_VERTEXBUFFER_SIZE)
		return false;

	// check tri size
	if(_CurrentNumTriangles + numTris> NL3D_COARSEMESH_TRIANGLE_SIZE)
		return false;
	
	CMeshInfo mi;
	mi.NumVertices = numVertices;
	mi.VBuffer = vBuffer;
	mi.NumTris = numTris;
	mi.IndexBuffer = indexBuffer;
	_Meshs.push_back(mi);
	_CurrentNumVertices+= numVertices;
	_CurrentNumTriangles+= numTris;
	

	return true;
}

// ***************************************************************************

void CCoarseMeshManager::flushRender (IDriver *drv)
{
	H_AUTO( NL3D_StaticLod_Render );
	if (_Meshs.empty()) return;

	// if the driver is BGRA (Direct3D), then invert color format 
	if(!_VBuffer.isResident() && drv->getVertexColorFormat()==CVertexBuffer::TBGRA)
	{
		// since actually empty, no need to swap current memory
		_VBuffer.setNumVertices(0);
		_VBuffer.setVertexColorFormat(CVertexBuffer::TBGRA);
	}

	// init
	_VBuffer.setNumVertices(_CurrentNumVertices);
	_Triangles.setNumIndexes(_CurrentNumTriangles * 3);
	_VBuffer.lock (_VBA);
	_Triangles.lock(_IBA);
	uint currentNumVertices = 0;
	uint currentNumTriangles = 0;
	for(std::vector<CMeshInfo>::iterator it = _Meshs.begin(); it != _Meshs.end(); ++it)
	{
		// Copy Vertices to VBuffer
		uint	baseVertex= currentNumVertices;	
		CHECK_VBA_RANGE(_VBA, _VBA.getVertexCoordPointer(baseVertex), it->NumVertices*_VBuffer.getVertexSize());
		CFastMem::memcpy(_VBA.getVertexCoordPointer(baseVertex), it->VBuffer, it->NumVertices*_VBuffer.getVertexSize());
		
		// next
		currentNumVertices+= it->NumVertices;
		
		// Copy tris to triangles, adding baseVertex to index		
		TCoarseMeshIndexType	*triDst= (TCoarseMeshIndexType *) _IBA.getPtr()+currentNumTriangles*3;
		const TCoarseMeshIndexType	*triSrc= it->IndexBuffer;
		uint	numIdx= it->NumTris*3;
		// NB: for the majority of CoarseMesh (4 faces==48 bytes of indices), not interressant to use CFastMem::precache()
		for(;numIdx>0;numIdx--, triSrc++, triDst++)
		{
			CHECK_IBA(_IBA, triDst)
			*triDst= *triSrc + baseVertex;
		}
		// next
		currentNumTriangles+= it->NumTris;
	}	
	_VBA.unlock();
	_IBA.unlock();	

	// If not empty, render
	if(_CurrentNumVertices && _CurrentNumTriangles)
	{
		// Set Ident matrix
		drv->setupModelMatrix (CMatrix::Identity);

		// Set VB
		drv->activeVertexBuffer(_VBuffer);
		drv->activeIndexBuffer(_Triangles);

		// render
		drv->renderTriangles(_Material, 0, _CurrentNumTriangles);
	}

	// reset
	_CurrentNumVertices= 0;
	_CurrentNumTriangles= 0;

	_Meshs.clear();
}



} // NL3D
