/** \file deform_2d.h
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

#ifndef NL_DEFORM_2D_H
#define NL_DEFORM_2D_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"
#include "nel/misc/vector_2f.h"
#include "nel/3d/vertex_buffer.h"

namespace NL3D
{

class IDriver ;
class ITexture ;
/**
 * This perform  a 2d deformation effect on the frame buffer, by using the given function and surface.
 * This is intended to be used on small surfaces only (getting back data from the frame buffer to build
 * a texture is really slow...)
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class CDeform2d
{
public:
	typedef std::vector<NLMISC::CVector2f> TPoint2DVect ;

	/// an interface to compute the u,v perturbations at a given point (x and and y range from 0 to 1)
	struct IPerturbUV
	{
		virtual ~IPerturbUV() {}
		virtual void perturbUV(float x, float y, float &du, float &dv) const = 0 ;
	};

	// perform the fx on the given surface of the screen
	static void				doDeform(const TPoint2DVect &surf, IDriver *drv, IPerturbUV *uvp) ;
	/** resize the granularity of buffers for fxs
	  * \param width			frameBuffer width
	  * \param height			framebuffer height
	  * \param xGranularity     width of the quads taken from the framebuffer
	  * \param yGranularity     height of the quads taken from the framebuffer
	  * \param xQuad			width  of the quads used to draw the fx (this is usually lower than xGanularity)
  	  * \param yQuad			height of the quads used to draw the fx (this is usually lower than yGanularity)
	  */
	static void				setupBuffer(uint width, uint height, uint xGranularity, uint yGranularity
										, uint xQuad, uint yQuad) ;







protected:
	static uint _Width;
	static uint _Height;
	static uint _XGranularity;
	static uint _YGranularity;
	static uint _XQuad;
	static uint _YQuad;
	static NLMISC::CSmartPtr<ITexture> _Tex ; // the texture used to get back datas from the framebuffer

};



} // NL3D


#endif // NL_DEFORM_2D_H

/* End of deform_2d.h */
