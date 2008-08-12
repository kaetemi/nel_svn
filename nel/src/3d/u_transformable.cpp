/** \file u_transformable.cpp
 * Interface for transformable objects.
 *
 * $Id: u_transformable.cpp,v 1.2 2005/02/22 10:19:12 besson Exp $
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

#include "nel/3d/u_transformable.h"
#include "nel/3d/transformable.h"

#define NL3D_MEM_TRANSFORMABLE						NL_ALLOC_CONTEXT( 3dTrabl )

namespace NL3D 
{

// ***************************************************************************

const char *UTransformable::getPosValueName ()
{
	NL3D_MEM_TRANSFORMABLE
	return ITransformable::getPosValueName ();
}

// ***************************************************************************

const char *UTransformable::getRotEulerValueName()
{
	NL3D_MEM_TRANSFORMABLE
	return ITransformable::getRotEulerValueName();
}

// ***************************************************************************

const char *UTransformable::getRotQuatValueName()
{
	NL3D_MEM_TRANSFORMABLE
	return ITransformable::getRotQuatValueName();
}

// ***************************************************************************

const char *UTransformable::getScaleValueName()
{
	NL3D_MEM_TRANSFORMABLE
	return ITransformable::getScaleValueName();
}

// ***************************************************************************

const char *UTransformable::getPivotValueName()
{
	NL3D_MEM_TRANSFORMABLE
	return ITransformable::getPivotValueName();
}

// ***************************************************************************

void UTransformable::setMatrix(const CMatrix &mat)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->setMatrix(mat);
}

// ***************************************************************************

const CMatrix &UTransformable::getMatrix() const	
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getMatrix();
}

// ***************************************************************************

void UTransformable::setTransformMode(TTransformMode mode, CMatrix::TRotOrder ro)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->setTransformMode((ITransformable::TTransformMode)(uint)mode, ro);
}

// ***************************************************************************

void UTransformable::setPos(const CVector &pos)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->setPos(pos);
}

// ***************************************************************************

void UTransformable::setRotEuler(const CVector &rot)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->setRotEuler(rot);
}

// ***************************************************************************

void UTransformable::setRotQuat(const CQuat &quat)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->setRotQuat(quat);
}

// ***************************************************************************

void UTransformable::setRotQuat(const CVector &jdir)
{
	NL3D_MEM_TRANSFORMABLE
	CMatrix	mat;
	mat.setRot(CVector::I, jdir, CVector::K);
	mat.normalize(CMatrix::YZX);
	setRotQuat(mat.getRot());
}

// ***************************************************************************

void UTransformable::setRotQuat(const CVector &jdir, const CVector &vup)
{
	NL3D_MEM_TRANSFORMABLE
	CMatrix	mat;
	mat.setRot(CVector::I, jdir, vup);
	mat.normalize(CMatrix::YZX);
	setRotQuat(mat.getRot());
}

// ***************************************************************************

void UTransformable::setScale(const CVector &scale)
{
	_Object->setScale(scale);
}

// ***************************************************************************

void UTransformable::setPivot(const CVector &pivot)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->setPivot(pivot);
}

// ***************************************************************************

UTransformable::TTransformMode UTransformable::getTransformMode()
{
	NL3D_MEM_TRANSFORMABLE
	return (TTransformMode)(uint)_Object->getTransformMode();
}

// ***************************************************************************

CMatrix::TRotOrder UTransformable::getRotOrder()
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getRotOrder();
}

// ***************************************************************************

void UTransformable::getPos(CVector &pos)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->getPos(pos);
}

// ***************************************************************************

void UTransformable::getRotEuler(CVector &rot)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->getRotEuler(rot);
}

// ***************************************************************************

void UTransformable::getRotQuat(CQuat &quat)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->getRotQuat(quat);
}

// ***************************************************************************

void UTransformable::getScale(CVector &scale)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->getScale(scale);
}

// ***************************************************************************

void UTransformable::getPivot(CVector &pivot)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->getPivot(pivot);
}


// ***************************************************************************

CVector	UTransformable::getPos()
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getPos();
}

// ***************************************************************************

CVector	UTransformable::getRotEuler()
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getRotEuler();
}

// ***************************************************************************

CQuat UTransformable::getRotQuat()
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getRotQuat();
}

// ***************************************************************************

CVector	UTransformable::getScale()
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getScale();
}

// ***************************************************************************

CVector	UTransformable::getPivot()
{
	NL3D_MEM_TRANSFORMABLE
	return _Object->getPivot();
}

// ***************************************************************************

void UTransformable::lookAt (const CVector& eye, const CVector& target, float roll)
{
	NL3D_MEM_TRANSFORMABLE
	_Object->lookAt(eye, target, roll);
}

// ***************************************************************************


} // NL3D
