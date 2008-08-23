/** \file motion_blur.cpp
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

#include "std3d.h"

#include "nel/misc/common.h"
#include "nel/3d/motion_blur.h"
#include "nel/3d/driver.h"
#include "nel/3d/texture.h"
#include "nel/3d/texture_blank.h"
#include "nel/3d/material.h"


namespace NL3D {


CMotionBlur::CMotionBlur() : _Tex(NULL), _X(0), _Y(0), _W(0), _H(0)
{
}



void CMotionBlur::startMotionBlur(uint x, uint y, uint width, uint height)
{
	nlassert(width > 0 && height > 0) ;
	_X = x ;
	_Y = y ;
	_W = width ;
	_H = height ;
	_Tex = new CTextureBlank ;
	_Tex->resize(NLMISC::raiseToNextPowerOf2(width), NLMISC::raiseToNextPowerOf2(height)) ;
}

void CMotionBlur::releaseMotionBlur()
{
	_Tex = NULL ;
	_X = _Y = _W = _H = 0 ;
}

void CMotionBlur::performMotionBlur(IDriver *driver, float motionBlurAmount)
{
	nlassert(_Tex) ;  //start motion blur has not been called !!
	nlassert(driver) ;
	nlassert(motionBlurAmount >= 0.f && motionBlurAmount <= 1.f) ;
	
	static CVertexBuffer  vb ;
	vb.setVertexFormat(CVertexBuffer::PositionFlag | CVertexBuffer::TexCoord0Flag ) ;
	vb.setNumVertices(4) ;

	uint32 width, height ;
	driver->getWindowSize(width, height) ;

	float widthRatio = _W / (float) NLMISC::raiseToNextPowerOf2 (_W) ;
	float heightRatio = _H / (float) NLMISC::raiseToNextPowerOf2 (_H) ;

	driver->setFrustum(0, (float) width, 0, (float) height, -1, 1, false) ;

	static CMaterial mbMat ;
	{
		CVertexBufferReadWrite vba;
		vb.lock (vba);
		for (uint sn = 0 ; sn < 2 ; ++sn)
		{
			vba.setTexCoord(0, sn, CUV(0, 0)) ; 
			vba.setTexCoord(1, sn, CUV(widthRatio, 0)) ; 
			vba.setTexCoord(2, sn, CUV(widthRatio, heightRatio)) ; 
			vba.setTexCoord(3, sn, CUV(0, heightRatio)) ; 
		}


		static bool matSetup = false ; // set to true when mbMat has Been setup
		if (!matSetup)
		{
			mbMat.setBlend(true) ;
			mbMat.setBlendFunc(CMaterial::srcalpha, CMaterial::invsrcalpha) ;	
			mbMat.setZWrite(false) ;
			mbMat.setZFunc(CMaterial::always) ;	
			// stage 0	    
			mbMat.setTexture(0, _Tex) ;
			mbMat.texEnvOpRGB(0, CMaterial::Replace );

			mbMat.texEnvArg0Alpha(0, CMaterial::Diffuse, CMaterial::SrcAlpha);
			mbMat.texEnvOpAlpha(0, CMaterial::Replace);
			
			mbMat.setDoubleSided(true) ;
			matSetup = true ;
		}


		mbMat.setColor(CRGBA(255, 255, 255, (uint8) (255.f * motionBlurAmount) ) ) ;		


		vba.setVertexCoord(0, CVector((float) _X, 0, 0) ) ;
		vba.setVertexCoord(1, CVector((float) (_X + _W), 0 ,0) ) ;
		vba.setVertexCoord(2, CVector((float) (_X + _W), 0, (float) (_Y + _H) ) );
		vba.setVertexCoord(3, CVector(0 , 0, (float) (_Y + _H) ) ) ;
	}

	driver->setupViewMatrix(CMatrix::Identity) ;
	driver->setupModelMatrix(CMatrix::Identity) ;
	

	driver->activeVertexBuffer(vb) ;
	driver->renderRawQuads(mbMat, 0, 1) ;

	// blit back frame buffer to save this frame



	// todo hulud : use the new render to texture interface
	// driver->copyFrameBufferToTexture(_Tex, 0, 0, 0, _X, _Y, _W, _H) ;
}


} // NL3D
