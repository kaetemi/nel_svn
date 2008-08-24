/** \file u_camera.cpp
 * User interface for camera.
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

#include "nel/3d/u_camera.h"
#include "nel/3d/camera.h"


namespace NL3D
{

const float		UCamera::DefLx=0.26f;
const float		UCamera::DefLy=0.2f;
const float		UCamera::DefLzNear=0.15f;
const float		UCamera::DefLzFar=1000.0f;

// ***************************************************************************

void UCamera::setFrustum(const CFrustum &f)
{
	CCamera	*object = getObjectPtr();
	object->setFrustum(f);
}

// ***************************************************************************

const CFrustum &UCamera::getFrustum() const
{
	CCamera	*object = getObjectPtr();
	return object->getFrustum();
}

// ***************************************************************************

void UCamera::setFrustum(float left, float right, float bottom, float top, float znear, float zfar, bool perspective)
{
	CCamera	*object = getObjectPtr();
	object->setFrustum(left, right, bottom, top, znear, zfar, perspective);
}

// ***************************************************************************

void UCamera::setFrustum(float width, float height, float znear, float zfar, bool perspective)
{
	CCamera	*object = getObjectPtr();
	object->setFrustum(width, height, znear, zfar, perspective);
}

// ***************************************************************************

void UCamera::getFrustum(float &left, float &right, float &bottom, float &top, float &znear, float &zfar) const
{
	CCamera	*object = getObjectPtr();
	object->getFrustum(left, right, bottom, top, znear, zfar);
}

// ***************************************************************************

bool UCamera::isOrtho() const
{
	CCamera	*object = getObjectPtr();
	return object->isOrtho();
}

// ***************************************************************************

bool UCamera::isPerspective() const
{
	CCamera	*object = getObjectPtr();
	return object->isPerspective();
}

// ***************************************************************************

void UCamera::setPerspective(float fov, float aspectRatio, float znear, float zfar)
{
	CCamera	*object = getObjectPtr();
	object->setPerspective(fov, aspectRatio, znear, zfar);
}

// ***************************************************************************

void UCamera::buildCameraPyramid(std::vector<NLMISC::CPlane>	&pyramid, bool useWorldMatrix)
{
	CCamera	*object = getObjectPtr();
	object->buildCameraPyramid(pyramid, useWorldMatrix);
}

// ***************************************************************************
void UCamera::buildCameraPyramidCorners(std::vector<NLMISC::CVector>	&pyramidCorners, bool useWorldMatrix)
{
	CCamera	*object = getObjectPtr();
	object->buildCameraPyramidCorners(pyramidCorners, useWorldMatrix);
}

// ***************************************************************************

} // NL3D
