/** \file viewport.cpp
 * TODO: File description
 *
 * $Id: viewport.cpp,v 1.8 2004/11/15 10:24:53 lecroart Exp $
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

#include "nel/3d/viewport.h"
#include "nel/misc/common.h"

using namespace NLMISC;


namespace NL3D
{

CViewport::CViewport()
{
	initFullScreen ();
}


void CViewport::init (float x, float y, float width, float height)
{
	// Simply copy
	_X=x;
	clamp (_X, 0.f, 1.f);
	_Y=y;
	clamp (_Y, 0.f, 1.f);
	_Width=width;
	clamp (_Width, 0.f, 1.f-_X);
	_Height=height;
	clamp (_Height, 0.f, 1.f-_Y);
}


void CViewport::initFullScreen ()
{
	// Very easy
	_X=0.f;
	_Y=0.f;
	_Width=1.f;
	_Height=1.f;
}


void CViewport::init16_9 ()
{
	// Very easy
	_X=0.f;
	_Y=(1.f-0.75f)/2;
	_Width=1.f;
	_Height=0.75f;
}


void CViewport::getRayWithPoint (float x, float y, CVector& pos, CVector& dir, const CMatrix& camMatrix, const CFrustum& camFrust) const
{
	float xVP=(x-_X)/_Width;
	float yVP=(y-_Y)/_Height;

	// Pos of the ray
	pos= camMatrix.getPos();

	// Get camera frustrum
	float left;
	float right;
	float bottom;
	float top;
	float znear;
	float zfar;
	camFrust.getValues (left, right, bottom, top, znear, zfar);

	// Get a local direction
	dir.x=left+(right-left)*xVP;
	dir.y=znear;
	dir.z=bottom+(top-bottom)*yVP;

	// Get a world direction
	CMatrix mat=camMatrix;
	mat.setPos (CVector (0,0,0));
	dir=mat*dir;
}


} // NL3D

