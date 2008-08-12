/** \file tangent_space_build.h
 * A function that add tangent space information to a vertex buffer
 *
 * $Id: tangent_space_build.h,v 1.3 2005/02/22 10:19:12 besson Exp $
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



#ifndef NL_TANGENT_SPACE_BUILD_H
#define NL_TANGENT_SPACE_BUILD_H

#include "nel/misc/types_nl.h"
#include "mesh.h"

namespace NL3D
{

class CVertexBuffer;
class CIndexBuffer;
	
/** This add tangent space information to a vertex buffer. The result is an added 3d texture coordinate
  * that contains the T vector of the tangent space basis (T is oriented toward increasing s coordinates). The binormal can be computed in a vertex program
  * by doing B = N ^ T. The input mesh build must provide a normal component.
  * Moreover it must have at least one texture coordinate applied (this is needed to build coherent tangent space basis)    
  * \return true if the conversion was possible
  */


bool	BuildTangentSpace(CMesh::CMeshBuild &outMeshBuild, const CMesh::CMeshBuild &inMeshBuild);




} // NL3D

#endif