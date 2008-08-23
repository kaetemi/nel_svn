/** \file vegetable_clip_block.h
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

#ifndef NL_VEGETABLE_CLIP_BLOCK_H
#define NL_VEGETABLE_CLIP_BLOCK_H

#include "nel/misc/types_nl.h"
#include "nel/misc/aabbox.h"
#include "nel/misc/bsphere.h"
#include "nel/3d/tess_list.h"
#include "nel/3d/vegetable_sort_block.h"


namespace NL3D 
{


using NLMISC::CVector;
using NLMISC::CPlane;


// ***************************************************************************
/**
 *	A block of vegetable instance groups (via sortBlocks) which are clipped in frustum together
 *	Internal to VegetableManager. Just an Handle for public.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CVegetableClipBlock : public CTessNodeList
{
public:

	/// Constructor
	CVegetableClipBlock();


// ***************
private:
	friend class	CVegetableManager;


	/// \name Fast clipping.
	// @{
	bool				_Empty;
	NLMISC::CAABBox		_BBox;
	NLMISC::CBSphere	_BSphere;

	// extend sphere
	void			extendSphere(const CVector &vec);
	// extend bbox. Must not be empty. NB: do not modify the sphere
	void			extendBBoxOnly(const CVector &vec);
	// compute the sphere according to the bbox.
	void			updateSphere();
	// return false if empty or out of frustum
	bool			clip(const std::vector<CPlane>	&pyramid);

	// @}


private:

	// List of SortBlocks.
	CTessList<CVegetableSortBlock>		_SortBlockList;

	// The number of instanceGroups created in this clipBlock.
	uint					_NumIgs;

	// RenderList
	CVegetableClipBlock		*_RenderNext;
};


} // NL3D


#endif // NL_VEGETABLE_CLIP_BLOCK_H

/* End of vegetable_clip_block.h */
