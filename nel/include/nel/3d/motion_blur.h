/** \file motion_blur.h
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

#ifndef NL_MOTION_BLUR_H
#define NL_MOTION_BLUR_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"


namespace NL3D {


class IDriver ;
class ITexture ;

/**
 * This class help perfoming motion blur on a portion of the screen
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class CMotionBlur
{
public:
	// ctor
	CMotionBlur() ;
	/** Must be called before performing motion blur on a image sequence. Motion blur is performed
	  * on a rectangular area.
	  * 2 calls -> nlassert. Once motion blur must be stopped, you must call releaseMotionBlur.	  
	  * \param x the x position of the top-left coener of the rectangle on which motion blur apply
	  * \param y the y position of the top-left coener of the rectangle on which motion blur apply
	  * \param width the width of the rectangle on which motion blur apply
	  * \param height the height of the rectangle on which motion blur apply	  
      */
	void startMotionBlur(uint x, uint y, uint width, uint height) ;

	/// release the resources used by motion blur
	void releaseMotionBlur() ;

	/** perform motion blur, using the given driver	 
	  * This can only have been called between a startMotionBlur / releaseMotionBlur pair.
	  * It must be called after the scene has been drawn of course.
	  * WARNING : this change the projection matrix and the frustum in the driver.
	  * \param motionBlurAmount ranges from 0.f to 1.f. Blend using the following : 
	  * motionBlurAmount * previous frame + (1 - motionBlurAmount) * current Frame buffer state
	  */
	void performMotionBlur(IDriver *driver, float motionBlurAmount) ;
protected:
	NLMISC::CSmartPtr<ITexture> _Tex ;
	uint _X, _Y, _W, _H ;
};


} // NL3D


#endif // NL_MOTION_BLUR_H

/* End of motion_blur.h */
