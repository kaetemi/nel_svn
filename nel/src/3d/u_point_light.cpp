/** \file u_point_light.cpp
 * User interface for point lights.
 *
 * $Id: u_point_light.cpp,v 1.5 2005/02/22 10:19:12 besson Exp $
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

#include "nel/misc/debug.h"
#include "nel/3d/u_point_light.h"
#include "point_light_model.h"

#define NL3D_MEM_POINTLIGHT						NL_ALLOC_CONTEXT( 3dPtLgt )

using namespace NLMISC;

namespace NL3D 
{

// ***************************************************************************

void UPointLight::setAmbient (NLMISC::CRGBA ambient)
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->PointLight.setAmbient(ambient);
}

// ***************************************************************************

void UPointLight::setDiffuse (NLMISC::CRGBA diffuse)
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->PointLight.setDiffuse (diffuse);
}

// ***************************************************************************

void UPointLight::setSpecular (NLMISC::CRGBA specular)
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->PointLight.setSpecular (specular);
}

// ***************************************************************************

void UPointLight::setColor (NLMISC::CRGBA color)
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->PointLight.setColor (color);
}

// ***************************************************************************

NLMISC::CRGBA UPointLight::getAmbient () const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getAmbient();
}

// ***************************************************************************

NLMISC::CRGBA UPointLight::getDiffuse () const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getDiffuse ();
}

// ***************************************************************************

NLMISC::CRGBA UPointLight::getSpecular () const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getSpecular();
}

// ***************************************************************************

void UPointLight::setupAttenuation(float attenuationBegin, float attenuationEnd)
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->PointLight.setupAttenuation(attenuationBegin, attenuationEnd);
}

// ***************************************************************************

float UPointLight::getAttenuationBegin() const
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getAttenuationBegin();
}

// ***************************************************************************

float UPointLight::getAttenuationEnd() const
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getAttenuationEnd();
}

// ***************************************************************************

void UPointLight::enableSpotlight(bool enable) 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	if(enable)
		object->PointLight.setType(CPointLight::SpotLight);
	else
		object->PointLight.setType(CPointLight::PointLight);
}

// ***************************************************************************

bool UPointLight::isSpotlight() const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getType() == CPointLight::SpotLight;
}

// ***************************************************************************

void UPointLight::setupSpotAngle(float spotAngleBegin, float spotAngleEnd) 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->PointLight.setupSpotAngle(spotAngleBegin, spotAngleEnd);
}

// ***************************************************************************

float UPointLight::getSpotAngleBegin() const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getSpotAngleBegin();
}

// ***************************************************************************

float UPointLight::getSpotAngleEnd() const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->PointLight.getSpotAngleEnd();
}

// ***************************************************************************

void UPointLight::setDeltaPosToSkeletonWhenOutOfFrustum(const CVector &deltaPos) 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->setDeltaPosToSkeletonWhenOutOfFrustum(deltaPos) ;
}

// ***************************************************************************

const CVector &UPointLight::getDeltaPosToSkeletonWhenOutOfFrustum() const 
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->getDeltaPosToSkeletonWhenOutOfFrustum() ;
}

// ***************************************************************************
void			UPointLight::setInfluenceLightMap(bool enable)
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	object->setInfluenceLightMap(enable);
}

// ***************************************************************************
bool			UPointLight::getInfluenceLightMap() const
{
	NL3D_MEM_POINTLIGHT
	CPointLightModel	*object = getObjectPtr();
	return object->getInfluenceLightMap() ;
}


} // NL3D
