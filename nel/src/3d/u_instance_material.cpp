/** \file u_instance_material.cpp
 * TODO: File description
 *
 * $Id: u_instance_material.cpp,v 1.5 2006/05/31 12:03:14 boucher Exp $
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

#include "nel/3d/u_instance_material.h"
#include "nel/3d/async_texture_block.h"
#include "nel/3d/mesh_base_instance.h"
#include "nel/3d/driver.h"
#include "nel/3d/texture_mem.h"
#include "nel/3d/texture_file.h"

#define NL3D_MEM_MATERIAL_INSTANCE						NL_ALLOC_CONTEXT( 3dMatI )

namespace NL3D
{


// ***************************************************************************
bool				UInstanceMaterial::isTextureFile(uint stage) const
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::isTextureFile : invalid stage");
		return false;
	}
	return dynamic_cast<CTextureFile *>(_Object->getTexture(stage)) != NULL;
}

// ***************************************************************************
std::string			UInstanceMaterial::getTextureFileName(uint stage) const
{		
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::getTextureFileName : invalid stage");
		return "";
	}

	// If Async mode
	if(_MBI->getAsyncTextureMode())
	{
		nlassert(_AsyncTextureBlock->isTextureFile(stage));
		// return name of the async one.
		return _AsyncTextureBlock->TextureNames[stage];
	}
	else
	{
		// return the name in the material
		return NLMISC::safe_cast<CTextureFile *>(_Object->getTexture(stage))->getFileName();
	}
}

// ***************************************************************************
void				UInstanceMaterial::setTextureFileName(const std::string &fileName, uint stage)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::setTextureFileName : invalid stage");
		return;
	}

	// If Async mode
	if(_MBI->getAsyncTextureMode())
	{
		if(!_AsyncTextureBlock->isTextureFile(stage))
		{
			nlwarning("UInstanceMaterialUser::setTextureFileName : the texture is not a texture file");
			return;
		}
		// replace the fileName
		_AsyncTextureBlock->TextureNames[stage]= fileName;
		// Flag the instance.
		_MBI->setAsyncTextureDirty(true);
	}
	else
	{
		CTextureFile *otherTex = dynamic_cast<CTextureFile *>(_Object->getTexture(stage));
		if (!otherTex)
		{
			nlwarning("UInstanceMaterialUser::setTextureFileName : the texture is not a texture file");
			return;
		}
		CTextureFile *tf = new CTextureFile(*otherTex);
		tf->setFileName(fileName);
		NLMISC::CSmartPtr<ITexture> old = _Object->getTexture(stage);
		_Object->setTexture(stage, tf);
	}
}

// ***************************************************************************
void UInstanceMaterial::emptyTexture(uint stage /*=0*/)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::emptyTexture : invalid stage");
		return;
	}
	_Object->setTexture(stage, NULL);
}

// ***************************************************************************
/*bool UInstanceMaterial::isSupportedByDriver(UDriver &drv, bool forceBaseCaps)
{	
	IDriver *idrv = NLMISC::safe_cast<CDriverUser *>(&drv)->getDriver();
	return _Object->isSupportedByDriver(*idrv, forceBaseCaps);	
}*/

// ***************************************************************************
void UInstanceMaterial::setTextureMem(uint stage, uint8 *data, uint32 length, bool _delete, bool isFile /*=true*/, uint width /*=0*/, uint height /*=0*/, CBitmap::TType texType /*=CBitmap::RGBA*/)
{
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::emptyTexture : invalid stage");
		return;
	}	
	_Object->setTexture((uint8) stage, new CTextureMem(data, length, _delete, isFile, width, height, texType));
}

// ***************************************************************************
bool				UInstanceMaterial::isLighted() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->isLighted();
}

// ***************************************************************************
void UInstanceMaterial::setLighting(bool active,
									CRGBA emissive /*=CRGBA(0,0,0)*/,
									CRGBA ambient /*=CRGBA(0,0,0)*/,
									CRGBA diffuse /*=CRGBA(0,0,0)*/,
									CRGBA specular /*=CRGBA(0,0,0)*/,
									float shininess /*=10*/)
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setLighting(active, emissive, ambient, diffuse, specular, shininess);
}

// ***************************************************************************

bool				UInstanceMaterial::isUserColor() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getShader()==CMaterial::UserColor;
}

// ***************************************************************************

void				UInstanceMaterial::setEmissive( CRGBA emissive )
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setEmissive(emissive);
}

// ***************************************************************************

void				UInstanceMaterial::setAmbient( CRGBA ambient )
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setAmbient( ambient);
}

// ***************************************************************************

void				UInstanceMaterial::setDiffuse( CRGBA diffuse )
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setDiffuse( diffuse);
}

// ***************************************************************************

void				UInstanceMaterial::setOpacity( uint8	opa )
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setOpacity( opa );
}

// ***************************************************************************

void				UInstanceMaterial::setSpecular( CRGBA specular )
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setSpecular( specular);
}

// ***************************************************************************

void				UInstanceMaterial::setShininess( float shininess )
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setShininess( shininess );
}

// ***************************************************************************

CRGBA				UInstanceMaterial::getEmissive() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getEmissive();
}

// ***************************************************************************

CRGBA				UInstanceMaterial::getAmbient() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getAmbient();
}

// ***************************************************************************

CRGBA				UInstanceMaterial::getDiffuse() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getDiffuse();
}

// ***************************************************************************

uint8				UInstanceMaterial::getOpacity() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getOpacity();
}

// ***************************************************************************

CRGBA				UInstanceMaterial::getSpecular() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getSpecular();
}

// ***************************************************************************

float				UInstanceMaterial::getShininess() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getShininess();
}

// ***************************************************************************

void				UInstanceMaterial::setColor(CRGBA rgba) 
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setColor(rgba) ;
}

// ***************************************************************************

CRGBA				UInstanceMaterial::getColor(void) const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getColor();
}

// ***************************************************************************

void				UInstanceMaterial::setUserColor(CRGBA userColor)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if(isUserColor())
		_Object->setUserColor(userColor);
}

// ***************************************************************************

CRGBA				UInstanceMaterial::getUserColor() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	if(isUserColor())
		return _Object->getUserColor();
	else
		return CRGBA(0,0,0,0);
}

// ***************************************************************************

void				UInstanceMaterial::setConstantColor(uint stage, NLMISC::CRGBA color)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::setConstantColor : invalid stage");
		return;
	}
	_Object->texConstantColor(stage, color);
}

// ***************************************************************************

NLMISC::CRGBA		UInstanceMaterial::getConstantColor(uint stage) const
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterialUser::getConstantColor : invalid stage");
		return NLMISC::CRGBA::Black;
	}
	return _Object->getTexConstantColor(stage);

}

// ***************************************************************************

sint				UInstanceMaterial::getLastTextureStage() const
{
	NL3D_MEM_MATERIAL_INSTANCE
	sint lastStage = -1;
	for(uint k = 0; k < IDRV_MAT_MAXTEXTURES; ++k)
	{
		if (_Object->getTexture(k) != NULL)
		{
			lastStage = k;
		}
	}
	return lastStage;
}

// ***************************************************************************

void			UInstanceMaterial::setBlend(bool active) 
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setBlend(active);
}

// ***************************************************************************

void			UInstanceMaterial::setBlendFunc(TBlend src, TBlend dst) 
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setBlendFunc((CMaterial::TBlend)(uint32)src, (CMaterial::TBlend)(uint32)dst);
}

// ***************************************************************************

void			UInstanceMaterial::setSrcBlend(TBlend val) 
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setSrcBlend((CMaterial::TBlend)(uint32)val);
}

// ***************************************************************************

void			UInstanceMaterial::setDstBlend(TBlend val) 
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setDstBlend((CMaterial::TBlend)(uint32)val);
}

// ***************************************************************************

void			UInstanceMaterial::setAlphaTestThreshold(float at)
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setAlphaTestThreshold(at);
}

// ***************************************************************************
float UInstanceMaterial::getAlphaTestThreshold() const
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getAlphaTestThreshold();
}

// ***************************************************************************
void UInstanceMaterial::setAlphaTest(bool active)
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setAlphaTest(active);
}

// ***************************************************************************

void			UInstanceMaterial::setZWrite(bool active)
{
	NL3D_MEM_MATERIAL_INSTANCE
	_Object->setZWrite(active);
}

// ***************************************************************************
void UInstanceMaterial::setZFunc(ZFunc val)
{
	NL3D_MEM_MATERIAL_INSTANCE
		_Object->setZFunc((CMaterial::ZFunc) val);
}

// ***************************************************************************

bool			UInstanceMaterial::getBlend() const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return _Object->getBlend();
}

// ***************************************************************************

UInstanceMaterial::TBlend			UInstanceMaterial::getSrcBlend(void)  const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return (UInstanceMaterial::TBlend)(uint32)_Object->getSrcBlend();
}

// ***************************************************************************

UInstanceMaterial::TBlend			UInstanceMaterial::getDstBlend(void)  const 
{
	NL3D_MEM_MATERIAL_INSTANCE
	return (UInstanceMaterial::TBlend)(uint32)_Object->getDstBlend();
}

// ***************************************************************************

void                    UInstanceMaterial::enableUserTexMat(uint stage, bool enabled)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterial::enableUserTexMat : stage %d is invalid", stage);
		return;
	}
	_Object->enableUserTexMat(stage, enabled);
}

// ***************************************************************************

bool                    UInstanceMaterial::isUserTexMatEnabled(uint stage) const
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterial::enableUserTexMat : stage %d is invalid", stage);
		return false;
	}
	return _Object->isUserTexMatEnabled(stage);
}

// ***************************************************************************

void					UInstanceMaterial::setUserTexMat(uint stage, const NLMISC::CMatrix &m)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterial::enableUserTexMat : stage %d is invalid", stage);
		return;
	}
	if (!_Object->isUserTexMatEnabled(stage))
	{
		nlwarning("UInstanceMaterial::setUserTexMat : texture stage %d has no user matrix.", stage);
	}
	_Object->setUserTexMat(stage, m);
}

// ***************************************************************************

const NLMISC::CMatrix  &UInstanceMaterial::getUserTexMat(uint stage) const
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES)
	{
		nlwarning("UInstanceMaterial::enableUserTexMat : stage %d is invalid", stage);
		return CMatrix::Identity;
	}
	if (!_Object->isUserTexMatEnabled(stage))
	{
		nlwarning("UInstanceMaterial::setUserTexMat : texture stage %d has no user matrix.", stage);
		return CMatrix::Identity;
	}
	return _Object->getUserTexMat(stage);
}

// ***************************************************************************

void				UInstanceMaterial::setWrapS(uint stage, TWrapMode mode)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES || _Object->getTexture(stage) == NULL)
	{
		nlwarning("UInstanceMaterial::setWrapS : stage %d is invalid or there's no texture", stage);
		return;
	}
	_Object->getTexture(stage)->setWrapS((ITexture::TWrapMode) mode);
}

// ***************************************************************************

void				UInstanceMaterial::setWrapT(uint stage, TWrapMode mode)
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES || _Object->getTexture(stage) == NULL)
	{
		nlwarning("UInstanceMaterial::setWrapT : stage %d is invalid or there's no texture", stage);
		return;
	}
	_Object->getTexture(stage)->setWrapT((ITexture::TWrapMode) mode);
}

// ***************************************************************************

UInstanceMaterial::TWrapMode			UInstanceMaterial::getWrapS(uint stage) const
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES || _Object->getTexture(stage) == NULL)
	{
		nlwarning("UInstanceMaterial::getWrapS : stage %d is invalid or there's no texture", stage);
		return Repeat;
	}
	return (TWrapMode) _Object->getTexture(stage)->getWrapS();
}

// ***************************************************************************

UInstanceMaterial::TWrapMode			UInstanceMaterial::getWrapT(uint stage) const
{
	NL3D_MEM_MATERIAL_INSTANCE
	if (stage >= IDRV_MAT_MAXTEXTURES || _Object->getTexture(stage) == NULL)
	{
		nlwarning("UInstanceMaterial::getWrapT : stage %d is invalid or there's no texture", stage);
		return Repeat;
	}
	return (TWrapMode) _Object->getTexture(stage)->getWrapT();
}

// ***************************************************************************

} // NL3D
