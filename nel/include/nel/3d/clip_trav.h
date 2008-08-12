/** \file clip_trav.h
 * TODO: File description
 *
 * $Id: clip_trav.h,v 1.25 2005/02/22 10:19:09 besson Exp $
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

#ifndef NL_CLIP_TRAV_H
#define NL_CLIP_TRAV_H

#include "trav_scene.h"
#include "quad_grid.h"
#include "transform.h"
#include "nel/misc/vector.h"
#include "nel/misc/plane.h"
#include "nel/misc/matrix.h"


namespace	NL3D
{

using NLMISC::CVector;
using NLMISC::CPlane;
using NLMISC::CMatrix;


class	CRenderTrav;
class	CAnimDetailTrav;
class	CLoadBalancingTrav;
class	CHrcTrav;
class	CLightTrav;
class	CCluster;
class	CInstanceGroup;
class	CCamera;
class	CQuadGridClipManager;
class	CTransform;
class	CSkeletonModel;


// ***************************************************************************
// This is the order of clip planes.
#define	NL3D_CLIP_PLANE_NEAR	0
#define	NL3D_CLIP_PLANE_FAR		1
#define	NL3D_CLIP_PLANE_LEFT	2
#define	NL3D_CLIP_PLANE_TOP		3
#define	NL3D_CLIP_PLANE_RIGHT	4
#define	NL3D_CLIP_PLANE_BOTTOM	5


// ***************************************************************************
/**
 * The clip traversal.
 * The purpose of this traversal is to insert in the post-clip Traversal the models which are 
 * said to be not clipped.
 *
 * Models should use the CTransform->clip() method to implement their models, or completly redefine the traverseClip() method.
 *
 * \b USER \b RULES: Before using traverse() on a clip traversal, you should:
 *	- setFrustum() the camera shape (focale....)
 *	- setCamMatrix() for the camera transform
 *
 * NB: see CScene for 3d conventions (orthonormal basis...)
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CClipTrav : public CTravCameraScene
{
public:

	/// Constructor
	CClipTrav();
	~CClipTrav();

	/// traverse
	void				traverse ();

	void registerCluster (CCluster* pCluster);
	void unregisterCluster (CCluster* pCluster);

	/// Setup the render traversal (else traverse() won't work)
	void setQuadGridClipManager(CQuadGridClipManager *mgr);
	const CQuadGridClipManager *getQuadGridClipManager() const {return _QuadGridClipManager;}

	/// \name Visible List mgt. Those visible modles are updated each traverse().
	//@{
	// NB: list is cleared at begining of traverse().
	void				addVisibleModel(CTransform *model)
	{
		model->_IndexInVisibleList= _CurrentNumVisibleModels;
		_VisibleList[_CurrentNumVisibleModels]= model;
		_CurrentNumVisibleModels++;
	}
	// for createModel().
	void				reserveVisibleList(uint numModels);
	//@}


	/// \name Cluster system related methods.
	//@{
	/** Retreive a list of cluster for witch the position is inside. At least return the RootCluster one
	*/
	bool fullSearch (std::vector<CCluster*>& result, const CVector& pos);

	/// Set cluster tracking on/off (ie storage of thje visible cluster during clip traversal)
	void setClusterVisibilityTracking(bool track);
	/// Check the activation of cluster visibility tracking.
	bool getClusterVisibilityTracking();
	/// Add a visible cluster to the list
	void addVisibleCluster(CCluster *cluster);
	/** Return the list of cluster visible after the clip traversal
	 *	You must activate the cluster tracking to obtain a result.
	*/
	const std::vector<CCluster*> &getVisibleClusters();

	bool						_TrackClusterVisibility;
	std::vector<CCluster*>		_VisibleClusters;
	//@}


public:

	/** \name FOR MODEL TRAVERSAL ONLY.  (Read only)
	 * Those variables are valid only in traverse*().
	 */
	//@{
	/// Vision Pyramid (6 normalized planes) in the view basis.
	std::vector<CPlane>	ViewPyramid;
	/// Vision Pyramid (6 normalized planes) in the world basis. NB: NOT modified by the ClusterSystem.
	std::vector<CPlane>	WorldFrustumPyramid;
	/// Vision Pyramid in the world basis. NB: may be modified by the ClusterSystem.
	std::vector<CPlane>	WorldPyramid;	
	//@}
	sint64				CurrentDate;

	CCluster			*RootCluster;
	CCamera				*Camera;
	
	CQuadGrid<CCluster*> Accel;

	/** for CQuadGridClipClusterClip only. This flag means models traversed do not need to clip,
	 *	they are sure to be visible.
	 */
	bool				ForceNoFrustumClip;


// **********************
private:
	friend	class	CTransform;
	std::vector<CTransform*>	_VisibleList;
	uint32						_CurrentNumVisibleModels;

	CQuadGridClipManager		*_QuadGridClipManager;

	// For skeleton CLod Load balancing
	struct	CSkeletonKey
	{
		uint				Priority;
		CSkeletonModel		*SkeletonModel;

		bool	operator<(const CSkeletonKey &k) const
		{
			return Priority<k.Priority;
		}
	};
	std::vector<CSkeletonKey>	_TmpSortSkeletons;

	void	loadBalanceSkeletonCLod();

	// clip the shadow casters to know if they still need some process
	void	clipShadowCasters();
};



}


#endif // NL_CLIP_TRAV_H

/* End of clip_trav.h */
