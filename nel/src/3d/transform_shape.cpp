/** \file transform_shape.cpp
 * TODO: File description
 *
 * $Id: transform_shape.cpp,v 1.44 2005/02/22 10:19:12 besson Exp $
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

#include "std3d.h"

#include "nel/misc/hierarchical_timer.h"
#include "nel/misc/debug.h"
#include "driver.h"
#include "transform_shape.h"
#include "skeleton_model.h"
#include "mesh_base_instance.h"
#include "clip_trav.h"
#include "render_trav.h"
#include "load_balancing_trav.h"
#include "quad_grid_clip_cluster.h"
#include "scene.h"

#define NL3D_MEM_INSTANCE					NL_ALLOC_CONTEXT( 3dIns )

using namespace NLMISC;


namespace NL3D 
{


// ***************************************************************************
void		CTransformShape::registerBasic()
{
	CScene::registerModel(TransformShapeId, TransformId, CTransformShape::creator);
}


// ***************************************************************************
CTransformShape::CTransformShape()
{
	_NumTrianglesAfterLoadBalancing= 100;
	_CurrentLightContribution= NULL;
	_CurrentUseLocalAttenuation= false;
	_DistMax = -1.f;
	// By default all transformShape are LoadBalancable
	CTransform::setIsLoadbalancable(true);

	// The model is renderable
	CTransform::setIsRenderable(true);

	// I am a CTransformShape
	CTransform::setIsTransformShape(true);
}


// ***************************************************************************
float		CTransformShape::getNumTriangles (float distance)
{
	// Call shape method
	return Shape->getNumTriangles (distance);
}


// ***************************************************************************
void		CTransformShape::getAABBox(NLMISC::CAABBox &bbox) const
{
	if(Shape)
	{
		Shape->getAABBox(bbox);
	}
	else
	{
		bbox.setCenter(CVector::Null);
		bbox.setHalfSize(CVector::Null);
	}
}


// ***************************************************************************
void		CTransformShape::setupCurrentLightContribution(CLightContribution *lightContrib, bool useLocalAtt)
{
	_CurrentLightContribution= lightContrib;
	_CurrentUseLocalAttenuation= useLocalAtt;
}

// ***************************************************************************
void		CTransformShape::changeLightSetup(CRenderTrav *rdrTrav)
{
	// setup the instance lighting.
	rdrTrav->changeLightSetup(_CurrentLightContribution, _CurrentUseLocalAttenuation);
}


// ***************************************************************************
uint		CTransformShape::getNumMaterial () const
{
	return 0;
}


// ***************************************************************************
const CMaterial *CTransformShape::getMaterial (uint materialId) const
{
	return NULL;
}


// ***************************************************************************
CMaterial *CTransformShape::getMaterial (uint materialId)
{
	return NULL;
}

// ***************************************************************************
void	CTransformShape::unlinkFromQuadCluster()
{
	// if linked to a quadGridClipCluster, unlink it
	_QuadClusterListNode.unlink();
}


// ***************************************************************************
bool	CTransformShape::clip() 
{
	H_AUTO( NL3D_TrShape_Clip );

	CClipTrav			&clipTrav= getOwnerScene()->getClipTrav();

	if(Shape)
	{
		// first test DistMax (faster).
		float maxDist = getDistMax();
		// if DistMax test enabled
		if(maxDist!=-1)
		{
			// Calc the distance
			float sqrDist = (clipTrav.CamPos - getWorldMatrix().getPos()).sqrnorm ();
			maxDist*=maxDist;
			
			// if dist > maxDist, skip
			if (sqrDist > maxDist)
			{
				// Ok, not shown
				return false;
			}
		}

		// Else finer clip with pyramid, only if needed
		if(clipTrav.ForceNoFrustumClip)
			return true;
		else
			return Shape->clip(clipTrav.WorldPyramid, getWorldMatrix());
	}
	else
		return false;
}


// ***************************************************************************
void	CTransformShape::traverseRender()
{
	NL_ALLOC_CONTEXT( RdrShap )
	H_AUTO( NL3D_TrShape_Render );


	// Compute the current lighting setup for this instance
	//===================


	// if the transform is lightable (ie not a fully lightmaped model), setup lighting
	if(isLightable())
	{
		// useLocalAttenuation for this shape ??
		if(Shape)
			_CurrentUseLocalAttenuation= Shape->useLightingLocalAttenuation ();
		else
			_CurrentUseLocalAttenuation= false;

		// the std case is to take my model lightContribution
		if(_AncestorSkeletonModel==NULL)
			_CurrentLightContribution= &getLightContribution();
		// but if skinned/sticked (directly or not) to a skeleton, take its.
		else
			_CurrentLightContribution= &((CTransformShape*)_AncestorSkeletonModel)->getLightContribution();
	}
	// else must disable the lightSetup
	else
	{
		// setting NULL will disable all lights
		_CurrentLightContribution= NULL;
		_CurrentUseLocalAttenuation= false;
	}


	// render the shape.
	//=================
	if(Shape)
	{
		CRenderTrav			&rdrTrav= getOwnerScene()->getRenderTrav();
		bool				currentPassOpaque= rdrTrav.isCurrentPassOpaque();

		// shape must be rendered in a CMeshBlockManager ??
		float polygonCount;
		IMeshGeom	*meshGeom= NULL;
		// true only if in pass opaque
		if( currentPassOpaque )
			meshGeom= Shape->supportMeshBlockRendering(this, polygonCount);

		// if ok, add the meshgeom to the block manager.
		if(meshGeom)
		{
			CMeshBaseInstance	*inst= safe_cast<CMeshBaseInstance*>(this);
			rdrTrav.MeshBlockManager.addInstance(meshGeom, inst, polygonCount);
		}
		// else render it.
		else
		{
			// setup the lighting
			changeLightSetup( &rdrTrav );

			// render the shape.
			IDriver				*drv= rdrTrav.getDriver();
			Shape->render( drv, this, currentPassOpaque );
		}
	}
}


// ***************************************************************************
void	CTransformShape::profileRender()
{
	// profile the shape.
	if(Shape)
	{
		CRenderTrav			&rdrTrav= getOwnerScene()->getRenderTrav();
		bool				currentPassOpaque= rdrTrav.isCurrentPassOpaque();

		Shape->profileSceneRender( &rdrTrav, this, currentPassOpaque );
	}
}


// ***************************************************************************
void	CTransformShape::traverseLoadBalancing()
{
	CLoadBalancingTrav		&loadTrav= getOwnerScene()->getLoadBalancingTrav();
	if(loadTrav.getLoadPass()==0)
		traverseLoadBalancingPass0();
	else
		traverseLoadBalancingPass1();
}



// ***************************************************************************
void	CTransformShape::traverseLoadBalancingPass0()
{
	CLoadBalancingTrav		&loadTrav= getOwnerScene()->getLoadBalancingTrav();
	CSkeletonModel			*skeleton= getSkeletonModel();

	// World Model position
	const CVector		*modelPos;

	// If this isntance is binded or skinned to a skeleton, take the world matrix of this one as
	// center for LoadBalancing Resolution.
	if(skeleton)
	{
		// Take the root bone of the skeleton as reference (bone 0)
		// And so get our position.
		modelPos= &skeleton->Bones[0].getWorldMatrix().getPos();
	}
	else
	{
		// get our position from 
		modelPos= &getWorldMatrix().getPos();
	}


	// Then compute distance from camera.
	float	modelDist= ( loadTrav.CamPos - *modelPos).norm();


	// Get the number of triangles this model use now.
	_FaceCount= getNumTriangles(modelDist);	
	_LoadBalancingGroup->addNbFacesPass0(_FaceCount);
}


// ***************************************************************************
void	CTransformShape::traverseLoadBalancingPass1()
{
	// Set the result into the isntance.
	_NumTrianglesAfterLoadBalancing= _LoadBalancingGroup->computeModelNbFace(_FaceCount);

}

// ***************************************************************************
void	CTransformShape::getLightHotSpotInWorld(CVector &modelPos, float &modelRadius) const
{
	/*
	// get the untransformed bbox from the model.
	CAABBox		bbox;
	getAABBox(bbox);
	// get transformed center pos of bbox
	modelPos= getWorldMatrix() * bbox.getCenter();
	// If the model is a big lightable, must take radius from aabbox, else suppose 0 radius.
	if(isBigLightable())
	{
		// get size of the bbox (bounding sphere)
		modelRadius= bbox.getRadius();
	}
	else
	{
		// Assume 0 radius => faster computeLinearAttenuation()
		modelRadius= 0;
	}
	*/

	// This method works well for Big Trees.
	// TODO: generalize, saving a LightHotSpot per shape.

	// get pos of object. Ie the hotSpot is the pivot.
	modelPos= getWorldMatrix().getPos();
	// If the model is a big lightable, must take radius from aabbox, else suppose 0 radius.
	if(isBigLightable())
	{
		// get the untransformed bbox from the model.
		CAABBox		bbox;
		getAABBox(bbox);
		// get size of the bbox (bounding sphere)
		modelRadius= bbox.getRadius();
	}
	else
	{
		// Assume 0 radius => faster computeLinearAttenuation()
		modelRadius= 0;
	}

}


} // NL3D
