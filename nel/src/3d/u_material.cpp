/** \file u_material.cpp
 * User interface for material.
 *
 * $Id: u_material.cpp,v 1.5 2005/03/11 15:13:05 berenguier Exp $
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


#include "nel/3d/u_material.h"
#include "nel/3d/u_driver.h"
#include "texture_user.h"
#include "driver_user.h"

#define NL3D_MEM_MATERIAL						NL_ALLOC_CONTEXT( 3dMat )

namespace NL3D
{

// ***************************************************************************

bool UMaterial::isSupportedByDriver(UDriver &drv, bool forceBaseCaps)
{
	NL3D_MEM_MATERIAL		
	CMaterial *object = getObjectPtr();
	return object->isSupportedByDriver(*(NLMISC::safe_cast<CDriverUser *>(&drv)->getDriver()), forceBaseCaps);
}

// ***************************************************************************

void UMaterial::setAlphaTest(bool active)
{
	CMaterial *object = getObjectPtr();
	object->setAlphaTest(active);
}

// ***************************************************************************

bool UMaterial::getAlphaTest() const
{
	CMaterial *object = getObjectPtr();
	return object->getAlphaTest();
}

// ***************************************************************************

void UMaterial::setAlphaTestThreshold(float threshold)
{
	CMaterial *object = getObjectPtr();
	object->setAlphaTestThreshold(threshold);
}

// ***************************************************************************

float UMaterial::getAlphaTestThreshold() const
{
	CMaterial *object = getObjectPtr();
	return object->getAlphaTestThreshold();
}

// ***************************************************************************

void UMaterial::setTexture(UTexture* ptex) 
{
	setTexture (0, ptex);
}

// ***************************************************************************

void UMaterial::setTexture(uint stage, UTexture* ptex) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	CTextureUser	*text= dynamic_cast<CTextureUser*>(ptex);
	if (text != NULL)
	{
		object->setTexture (stage, text->getITexture());
	}
	else
	{
		object->setTexture (stage, NULL);
	}
	// NB: _Material smartpoint to this ITexture. But this is correct because so does CTextureUser.
}

// ***************************************************************************

bool UMaterial::texturePresent() 
{
	return texturePresent (0);
}

// ***************************************************************************

bool UMaterial::texturePresent (uint stage) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->texturePresent (stage);
}

// ***************************************************************************

void UMaterial::selectTextureSet(uint id)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->selectTextureSet(id);
}

// ***************************************************************************

void UMaterial::setBlend(bool active) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setBlend(active);
}

// ***************************************************************************

void UMaterial::setBlendFunc(TBlend src, TBlend dst) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setBlendFunc((CMaterial::TBlend)(uint32)src, (CMaterial::TBlend)(uint32)dst);
}

// ***************************************************************************

void UMaterial::setSrcBlend(TBlend val) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setSrcBlend((CMaterial::TBlend)(uint32)val);
}

// ***************************************************************************

void UMaterial::setDstBlend(TBlend val) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setDstBlend((CMaterial::TBlend)(uint32)val);
}

// ***************************************************************************

bool UMaterial::getBlend() const 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getBlend();
}

// ***************************************************************************

UMaterial::TBlend UMaterial::getSrcBlend(void)  const 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return (UMaterial::TBlend)(uint32)object->getSrcBlend();
}

// ***************************************************************************

UMaterial::TBlend UMaterial::getDstBlend(void)  const 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return (UMaterial::TBlend)(uint32)object->getDstBlend();
}

// ***************************************************************************

void UMaterial::texEnvOpRGB(uint stage, TTexOperator ope)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvOpRGB(stage, (CMaterial::TTexOperator)(uint32)ope);
}

// ***************************************************************************

void UMaterial::texEnvArg0RGB (uint stage, TTexSource src, TTexOperand oper)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvArg0RGB (stage, (CMaterial::TTexSource)(uint32)src, (CMaterial::TTexOperand)(uint32)oper);
}

// ***************************************************************************

void UMaterial::texEnvArg1RGB (uint stage, TTexSource src, TTexOperand oper)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvArg1RGB (stage, (CMaterial::TTexSource)(uint32)src, (CMaterial::TTexOperand)(uint32)oper);
}

// ***************************************************************************

void UMaterial::texEnvArg2RGB (uint stage, TTexSource src, TTexOperand oper)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvArg2RGB (stage, (CMaterial::TTexSource)(uint32)src, (CMaterial::TTexOperand)(uint32)oper);
}

// ***************************************************************************

void UMaterial::texEnvOpAlpha(uint stage, TTexOperator ope)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvOpAlpha (stage, (CMaterial::TTexOperator)(uint32)ope);
}

// ***************************************************************************

void UMaterial::texEnvArg0Alpha(uint stage, TTexSource src, TTexOperand oper)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvArg0Alpha (stage, (CMaterial::TTexSource)(uint32)src, (CMaterial::TTexOperand)(uint32)oper);
}

// ***************************************************************************

void UMaterial::texEnvArg1Alpha(uint stage, TTexSource src, TTexOperand oper)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvArg1Alpha (stage, (CMaterial::TTexSource)(uint32)src, (CMaterial::TTexOperand)(uint32)oper);
}

// ***************************************************************************

void UMaterial::texEnvArg2Alpha(uint stage, TTexSource src, TTexOperand oper)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->texEnvArg2Alpha (stage, (CMaterial::TTexSource)(uint32)src, (CMaterial::TTexOperand)(uint32)oper);
}

// ***************************************************************************

void			UMaterial::setZFunc(ZFunc val) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setZFunc((CMaterial::ZFunc)(uint32) val);
}

// ***************************************************************************

void			UMaterial::setZWrite(bool active) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setZWrite(active);
}

// ***************************************************************************

void			UMaterial::setZBias(float val) 
{
	CMaterial *object = getObjectPtr();
	object->setZBias(val);
}

// ***************************************************************************

UMaterial::ZFunc			UMaterial::getZFunc(void)  const  
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return (UMaterial::ZFunc)(uint32)object->getZFunc();
}

// ***************************************************************************

bool			UMaterial::getZWrite(void)  const 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getZWrite();
}

// ***************************************************************************

float			UMaterial::getZBias(void)  const  
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getZBias();
}

// ***************************************************************************

void			UMaterial::setColor(CRGBA rgba) 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setColor(rgba);
}

// ***************************************************************************

CRGBA			UMaterial::getColor(void) const 
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getColor();
}

// ***************************************************************************

void			UMaterial::setDoubleSided(bool doubleSided)
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->setDoubleSided(doubleSided);
}

// ***************************************************************************

bool			UMaterial::getDoubleSided() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getDoubleSided();
}

// ***************************************************************************

void			UMaterial::initUnlit()
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	object->initUnlit();
}


// ***************************************************************************
bool			UMaterial::isLighted() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->isLighted();
}
// ***************************************************************************
CRGBA			UMaterial::getEmissive() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getEmissive();
}
// ***************************************************************************
CRGBA			UMaterial::getAmbient() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getAmbient();
}
// ***************************************************************************
CRGBA			UMaterial::getDiffuse() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getDiffuse();
}
// ***************************************************************************
uint8			UMaterial::getOpacity() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getOpacity();
}
// ***************************************************************************
CRGBA			UMaterial::getSpecular() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getSpecular();
}
// ***************************************************************************
float			UMaterial::getShininess() const
{
	NL3D_MEM_MATERIAL
	CMaterial *object = getObjectPtr();
	return object->getShininess();
}

} // NL3D
