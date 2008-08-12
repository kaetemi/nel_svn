/** \file light_trav.h
 * TODO: File description
 *
 * $Id: light_trav.h,v 1.10 2005/02/22 10:19:10 besson Exp $
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

#ifndef NL_LIGHT_TRAV_H
#define NL_LIGHT_TRAV_H

#include "trav_scene.h"
#include "lighting_manager.h"
#include "fast_ptr_list.h"


namespace	NL3D
{


using NLMISC::CVector;
using NLMISC::CPlane;
using NLMISC::CMatrix;

	
class	CTransform;
class	CPointLightModel;



// ***************************************************************************
/**
 * The light traversal.
 * The purpose of this traversal is to compute lighting on lightable objects.
 *
 * Lightable objects can be CTransform only.
 *
 * NB: see CScene for 3d conventions (orthonormal basis...)
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CLightTrav : public CTraversal
{
public:

	/// Constructor
	CLightTrav(bool bSmallScene);

	/// ITrav/ITravScene Implementation.
	//@{
	void				traverse();
	//@}

	/// \name LightingList. Filled during clip traversal.
	//@{
	/// Clear the list of lighted models.
	void				clearLightedList();
	/// Add a model to the list of lighted models. \b DOESN'T \b CHECK if already inserted.
	void				addLightedModel(CTransform *m)
	{
		_LightedList[_CurrentNumVisibleModels]= m;
		_CurrentNumVisibleModels++;
	}
	// for createModel().
	void				reserveLightedList(uint numModels);
	//@}

	/// \name LightingList. Add a PointLightModel to the list.
	//@{
	void				addPointLightModel(CPointLightModel *pl);
	//@}


public:
	// False by default. setuped by CScene
	bool				LightingSystemEnabled;

	/// The lightingManager, where objects/lights are inserted, and modelContributions are computed
	CLightingManager	LightingManager;


// ********************
private:

	// A grow only list of models to be lighted.
	std::vector<CTransform*>		_LightedList;
	uint32							_CurrentNumVisibleModels;

	// A fast linked list of models to be lighted.
	CFastPtrList<CPointLightModel>	_DynamicLightList;

};



}


#endif // NL_LIGHT_TRAV_H

/* End of light_trav.h */
