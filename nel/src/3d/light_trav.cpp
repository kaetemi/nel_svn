/** \file light_trav.cpp
 * TODO: File description
 *
 * $Id: light_trav.cpp,v 1.18 2005/03/29 13:53:46 berenguier Exp $
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

#include "nel/3d/light_trav.h"
#include "nel/3d/hrc_trav.h"
#include "nel/3d/clip_trav.h"
#include "nel/3d/root_model.h"
#include "nel/misc/hierarchical_timer.h"
#include "nel/3d/point_light_model.h"
#include "nel/3d/scene.h"

using namespace std;
using namespace NLMISC;


namespace	NL3D
{

using namespace	NLMISC;

// ***************************************************************************
CLightTrav::CLightTrav(bool bSmallScene) : LightingManager(bSmallScene)
{
	_LightedList.resize(1024);
	_CurrentNumVisibleModels= 0;

	LightingSystemEnabled= false;
}

// ***************************************************************************
void		CLightTrav::clearLightedList()
{
	_CurrentNumVisibleModels= 0;
}


// ***************************************************************************
void		CLightTrav::addPointLightModel(CPointLightModel *pl)
{
	_DynamicLightList.insert(pl, &pl->_PointLightNode);
}


// ***************************************************************************
void		CLightTrav::traverse()
{
	H_AUTO( NL3D_TravLight );

	uint i;


	// If lighting System disabled, skip
	if(!LightingSystemEnabled)
		return;

	/* for each visible lightable transform, reset them only if they have MergedPointLight.
		NB: dynamic objetcs don't need it because already done in traverseHRC() 
		(but don't worry, reset state is flagged, so resetLighting() no op...)
		This is important only for static object (freezeHRC()).
		Why? because we are not sure the MergedPointLight does not represent moving DynamicPointLights.
		Actually, it surely does. Because most of the static light setup return<=2 lights, and MaxLightContribution 
		is typically==3. So any additional light may surely be a dynamic one.
		NB: this may not be usefull since dynamicLights resetLighting() of all models in range. But this is important
		when the dynamic light leave the model quiclky! (because don't dirt the model).
		NB: this is also usefull only if there is no dynamic light but the ones merged in MergedPointLight. 
		Because dynamic always reset their old attached models (see below). This still can arise if for example 
		_MaxLightContribution=2 and there is a FrozenStaticLightSetup of 2 lights....
	*/
	for(i=0; i<_CurrentNumVisibleModels; i++ )
	{
		// if the model has a MergedPointLight, reset him (NB: already done for dynamics models) 
		if(_LightedList[i]->useMergedPointLight())
		{
			_LightedList[i]->resetLighting();
		}
	}


	// By default, lightmaped objects are not lit by any light
	CLight	noLight;
	noLight.setupDirectional(CRGBA::Black, CRGBA::Black, CRGBA::Black, CVector::K);
	Scene->getDriver()->setLightMapDynamicLight(false, noLight);

	// clear the quadGrid of dynamicLights
	LightingManager.clearDynamicLights();

	// for each lightModel, process her: recompute position, resetLightedModels(), and append to the quadGrid.
	CPointLightModel	**pLight= _DynamicLightList.begin();
	uint	numPls= _DynamicLightList.size();
	for(;numPls>0;numPls--, pLight++)
	{
		(*pLight)->traverseLight();
	}

	// for each visible lightable transform
	for(i=0; i<_CurrentNumVisibleModels; i++ )
	{
		// traverse(), to recompute light contribution (if needed).
		_LightedList[i]->traverseLight();
	}

}


// ***************************************************************************
void		CLightTrav::reserveLightedList(uint numModels)
{
	// enlarge only.
	if(numModels>_LightedList.size())
		_LightedList.resize(numModels);
}


}
