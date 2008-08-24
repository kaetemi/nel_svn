/** \file anim_detail_trav.cpp
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

#include "std3d.h"

#include "nel/3d/anim_detail_trav.h"
#include "nel/3d/hrc_trav.h"
#include "nel/3d/transform.h"
#include "nel/3d/skeleton_model.h"
#include "nel/misc/hierarchical_timer.h"
#include "nel/misc/debug.h"


using namespace NLMISC;


namespace NL3D
{


// ***************************************************************************
CAnimDetailTrav::CAnimDetailTrav()
{
	CurrentDate=0;
	// prepare some space
	_VisibleList.resize(1024);
	_CurrentNumVisibleModels= 0;
}

// ***************************************************************************
void				CAnimDetailTrav::clearVisibleList()
{
	_CurrentNumVisibleModels= 0;
}


// ***************************************************************************
void				CAnimDetailTrav::traverse()
{
	H_AUTO( NL3D_TravAnimDetail );

	// Inc the date.
	CurrentDate++;

	// Traverse all nodes of the visibility list.
	for(uint i=0; i<_CurrentNumVisibleModels; i++)
	{
		// NB: some model creation may be done by CParticleSystemModel during this pass.
		// createModel() may resize _VisibleList.
		// Hence, must test the actual _VisibleList vector, and not a temporary pointer.
		CTransform		*model= _VisibleList[i];
		// If this object has an ancestorSkeletonModel
		if(model->_AncestorSkeletonModel)
		{
			// then just skip it! because it will be parsed hierarchically by the first
			// skeletonModel whith _AncestorSkeletonModel==NULL. (only if this one is visible)
			continue;
		}
		else
		{
			// If this is a skeleton model, and because _AncestorSkeletonModel==NULL,
			// then it means that it is the Root of a hierarchy of transform that have
			// _AncestorSkeletonModel!=NULL.
			if( model->isSkeleton() )
			{
				// Then I must update hierarchically me and the sons (according to HRC hierarchy graph) of this model.
				traverseHrcRecurs(model);
			}
			else
			{
				// else, just traverse AnimDetail, an do nothing for Hrc sons
				model->traverseAnimDetail();
			}
		}
	}
}


// ***************************************************************************
void	CAnimDetailTrav::traverseHrcRecurs(CTransform *model)
{
	// first, just doIt me
	model->traverseAnimDetail();


	// then doIt my sons in Hrc.
	uint	num= model->hrcGetNumChildren();
	for(uint i=0;i<num;i++)
		traverseHrcRecurs(model->hrcGetChild(i));
}


// ***************************************************************************
void	CAnimDetailTrav::reserveVisibleList(uint numModels)
{
	// enlarge only.
	if(numModels>_VisibleList.size())
		_VisibleList.resize(numModels);
}


} // NL3D
