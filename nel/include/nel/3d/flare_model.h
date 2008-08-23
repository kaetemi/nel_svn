/** \file flare_model.h
 * TODO: File description
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_FLARE_MODEL_H
#define NL_FLARE_MODEL_H

#include "nel/misc/types_nl.h"
#include "nel/3d/transform_shape.h"
#include "nel/3d/vertex_buffer.h"


namespace NL3D {

struct IOcclusionQuery;
class CMesh;

/**
 * TODO Class description
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class CFlareModel : public CTransformShape
{
public:
	enum { MaxNumContext = 4 };
	enum { OcclusionTestFrameDelay = 2 }; // number of frame to wait before occlusion result is collected
	/// Constructor
	CFlareModel();
	// dtor
	~CFlareModel();
	// register this model
	static void registerBasic();	
	static CTransform *creator() { return new CFlareModel; }
	/// \name CTransform traverse specialisation
	// @{
	virtual void	traverseRender();
	// @}		
	// From CTransform
	virtual	bool isFlare() const { return true; }
	// Debugging aid : if an occlusion test mesh is used, display it using the current material
	void renderOcclusionTestMesh(IDriver &drv);
private:
	friend class CFlareShape;
	float					 _Intensity[MaxNumContext];	
	CScene					 *_Scene;	
	IOcclusionQuery			 *_OcclusionQuery[MaxNumContext][OcclusionTestFrameDelay]; // delay real test by a whole frame to avoid any stall
	IOcclusionQuery			 *_DrawQuery[MaxNumContext][OcclusionTestFrameDelay]; // querries to retrieve the surface that would have been drawned if there were no occlusion
	NLMISC::CRefPtr<IDriver> _LastDrv; // last driver used for render
	uint64					 _LastRenderIntervalBegin[MaxNumContext]; // Interval of frames during which this flare was traversed for render
	uint64					 _LastRenderIntervalEnd[MaxNumContext];
	uint64					 _NumFrameForOcclusionQuery[MaxNumContext]; // number of frames that were necessary to get the occlusion query result
	static CMaterial		 _OcclusionQueryMaterial;
	static CMaterial		 _DrawQueryMaterial;
	static bool				 _OcclusionQuerySettuped;
	static CVertexBuffer	 _OcclusionQueryVB;
private:
	void resetOcclusionQuerries();
	// Issue an occlusion query with the given mesh to get the visibility ratio
	void occlusionTest(CMesh &mesh, IDriver &drv);
public:
	CFlareModel *Next; // linked list of flare model to test at each frame
public:
	static void initStatics();
	static void updateOcclusionQueryBegin(IDriver *drv);
	static void updateOcclusionQueryEnd(IDriver *drv);
	/** Update state of occlusion query at the end of the frame. For private use by the CScene class
	  * updateOcclusionQueryBegin() should have been called	  
	  */
	void updateOcclusionQuery(IDriver *drv);
	/** Render all primitives of a mesh using the current material / metrix etc ...
	  * NB : this does NOT activate the vertex buffer of the mesh
	  * it must be activated prior to the call
	  */
	void renderOcclusionMeshPrimitives(CMesh &mesh, IDriver &drv);
	// setup matrix of the occlusion test mesh in the driver
	void    setupOcclusionMeshMatrix(IDriver &drv, CScene &scene) const;
};


} // NL3D


#endif // NL_FLARE_MODEL_H

/* End of flare_model.h */
