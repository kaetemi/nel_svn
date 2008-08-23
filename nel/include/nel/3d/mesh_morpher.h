/** \file mesh_morpher.h
 * TODO: File description
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

#ifndef NL_MESH_MORPHER_H
#define NL_MESH_MORPHER_H

#include "nel/3d/animated_morph.h"
#include "nel/misc/types_nl.h"
#include "nel/misc/uv.h"
#include "nel/misc/object_vector.h"
#include <vector>

namespace NL3D 
{

class CVertexBuffer;
class CRawSkinVertex;

// ***************************************************************************
class CBlendShape
{
public:
	std::string			Name;

	std::vector<NLMISC::CVector>	deltaPos;
	std::vector<NLMISC::CVector>	deltaNorm;
	std::vector<NLMISC::CVector>	deltaTgSpace;
	std::vector<NLMISC::CUV>		deltaUV;
	std::vector<NLMISC::CRGBAF>		deltaCol;

	std::vector<uint32>	VertRefs;	// Array of vertices reference

	void serial (NLMISC::IStream &f) throw(NLMISC::EStream);
};

// ***************************************************************************
/**
 * Utility to blend shapes
 * \author Matthieu 'TrapII' Besson
 * \author Nevrax France
 * \date 2001
 */
class CMeshMorpher
{
	/* ***********************************************
	 *	WARNING: This Class/Method must be thread-safe (ctor/dtor/serial): no static access for instance
	 *	It can be loaded/called through CAsyncFileManager for instance
	 * ***********************************************/
	
	typedef enum
	{
		OriginalAll=0,		// The vertex is the same as original into VBDst and VBHard
		OriginalVBDst,		// The vertex is the same as original into VBDst
		Modified,			// Vertex modified
	} TState;

public:

	std::vector<CBlendShape>			BlendShapes;

	CMeshMorpher();
	// The allocation of the buffers must be managed by the caller
	void init (CVertexBuffer *vbOri, CVertexBuffer *vbDst, bool hasTgSpace);
	void initSkinned (CVertexBuffer *vbOri,
				  CVertexBuffer *vbDst,
				  bool hasTgSpace,
				  std::vector<CVector> *vVertices,
				  std::vector<CVector> *vNormals,
				  std::vector<CVector> *vTgSpace, /* NULL if none */
				  bool bSkinApplied);

	void update (std::vector<CAnimatedMorph> *pBSFactor);
	void updateSkinned (std::vector<CAnimatedMorph> *pBSFactor);
	
	// For RawSkin case.
	void updateRawSkin (CVertexBuffer *vbOri,
						NLMISC::CObjectVector<CRawSkinVertex*, false>	&vertexRemap, 
						std::vector<CAnimatedMorph> *pBSFactor);

	void serial (NLMISC::IStream &f) throw(NLMISC::EStream);

private:

	CVertexBuffer			*_VBOri;
	CVertexBuffer			*_VBDst;

	std::vector<CVector>	*_Vertices;
	std::vector<CVector>	*_Normals;
	std::vector<CVector>	*_TgSpace;


	bool					_SkinApplied : 1;
	bool					_UseTgSpace  : 1;

	std::vector<uint8>	_Flags;	// 0 - OriginalAll  (vbDst & vbDstHrd original)
								// 1 - OriginalVBDst  (vbDst original)
								// 2 - Modified
};

} // NL3D


#endif // NL_MESH_MORPHER_H
            
/* End of mesh_morpher.h */
