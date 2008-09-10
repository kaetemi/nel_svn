/** \file mesh_vertex_program.h
 * TODO: File description
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

#ifndef NL_MESH_VERTEX_PROGRAM_H
#define NL_MESH_VERTEX_PROGRAM_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/smart_ptr.h"

#include "nel/3d/material.h"


namespace NLMISC
{
	class CMatrix;
}

namespace NL3D
{


class	IDriver;
class	CScene;
class	CMeshBaseInstance;
class	CLight;
class	CVertexBuffer;


/**
 * Interface to a CMeshGeom/CMeshMRMGeom Special VertexProgram Effect.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class IMeshVertexProgram : public NLMISC::IStreamable, public NLMISC::CRefCount
{
public:

	/// Constructor
	IMeshVertexProgram() {}
	virtual ~IMeshVertexProgram() {}

	/** Called at creation of an instance, to setup some information directly in the CMeshBaseInstance
	 */
	virtual	void	initInstance(CMeshBaseInstance *mbi) =0;


	/** Called to setup constant / activate VertexProgram. (called before activate of the VB).
	 *  The result tells wether the vertex program will be used in the given context.
	 *  If this is the case, a call to setupMaterial must be done for each material being rendered with this V.P.
	 *  After all primitive have been rendered, end() must be called.
	 *	\param drv driver where to setup VP.
	 *	\param scene retrieve some useFull scene info (windPower, time ...)
	 *	\param mbi the mesh instance to retrieve some instance setup.
	 *  \param mat the matrix to use (may not be the one of mbi)
	 *  \param viewerPos position of the viewer in world space.
	 */
	virtual	bool	begin(IDriver *drv,
						  CScene *scene,
						  CMeshBaseInstance *mbi,
						  const NLMISC::CMatrix &invertedModelMat,
						  const NLMISC::CVector &viewerPos
						 ) =0;
	/** Typically disable the VertexProgram, or do some uninit.
	 */
	virtual	void	end(IDriver *drv) =0;

	/** Setup this shader for the given material. This may disable the shader if necessary.
	  * This is why the vertex buffer is needed : when disabling the v.p we may need to reactivate it
	  */
	virtual void	setupForMaterial(const CMaterial &mat,
									 IDriver *drv,
									 CScene *scene,
									 CVertexBuffer *vb) = 0;

	// Test wether this vertex program need tangent space informations (stored in the last texture coordinate of the mesh)
	virtual	bool	needTangentSpace() const { return false; }


	/** \name MBR support.
	 *	Actually, it's targeted to work optimally with WindTree.
	 *	Requirement are:
	 *		- No special Validity test per instance (hence isMBRVpOk() takes only the driver).
	 *		- begin(), end(), setupForMaterial() is replaced with the following interface.
	 *		- there is no setupMBRMaterial(), because the caller has just to call per material (and must do it):
	 *			renderTrav->changeVPLightSetupMaterial(mat, false);
	 *		- beginMBRMesh MUST activate the VertexProgram, because called before VB activation
	 *		- beginMBRInstance still can change of VertexProgram, but cannot disable VP!!
	 */
	// @{
	virtual	bool	supportMeshBlockRendering() const { return false; }
	virtual	bool	isMBRVpOk(IDriver *drv) const {return false;}
	virtual	void	beginMBRMesh(IDriver *drv, CScene *scene) {}
	virtual	void	beginMBRInstance(IDriver *drv, CScene *scene, CMeshBaseInstance *mbi, const NLMISC::CMatrix &invertedModelMat) {}
	virtual	void	endMBRMesh(IDriver *drv) {}
	// @}


	/** This return the (over-evaluated) max delta the VertexProgram apply to vertex (in world basis)
	 *	NB: This method call is relevant only after begin() or beginMBRInstance()
	 */
	virtual float	getMaxVertexMove() {return 0;}


};


} // NL3D


#endif // NL_MESH_VERTEX_PROGRAM_H

/* End of mesh_vertex_program.h */
