/** \file driver_opengl_matrix.cpp
 * OpenGL driver implementation : matrix
 *
 * $Id: driver_opengl_matrix.cpp,v 1.21 2005/07/22 12:34:03 legallo Exp $
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

#include "stdopengl.h"

#include "driver_opengl.h"
namespace NL3D {

// ***************************************************************************
void CDriverGL::setFrustum(float left, float right, float bottom, float top, float znear, float zfar, bool perspective)
{
	H_AUTO_OGL(CDriverGL_setFrustum)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (perspective)
	{
		glFrustum(left,right,bottom,top,znear,zfar);
	}
	else
	{
		glOrtho(left,right,bottom,top,znear,zfar);
	}
	_ProjMatDirty = true;

	// Backup znear and zfar for zbias setup
	_OODeltaZ = 1 / (zfar - znear);

	glMatrixMode(GL_MODELVIEW);
}

// ***************************************************************************

void CDriverGL::setFrustumMatrix(CMatrix &frustumMatrix)
{
	H_AUTO_OGL(CDriverGL_setFrustum)
	glMatrixMode(GL_PROJECTION);

	glLoadMatrixf(((GLfloat*)frustumMatrix.get()));

	glMatrixMode(GL_MODELVIEW);
}

// ***************************************************************************

CMatrix CDriverGL::getFrustumMatrix()
{
	H_AUTO_OGL(CDriverGL_getFrustum)

	glMatrixMode(GL_PROJECTION);

	CMatrix frustumMatrix;
	float frustum[16]; 
	glGetFloatv(GL_PROJECTION_MATRIX, ((GLfloat*)&frustum));
	frustumMatrix.set(frustum);

	glMatrixMode(GL_MODELVIEW);

	return frustumMatrix;
}

// ***************************************************************************
void CDriverGL::setupViewMatrixEx(const CMatrix& mtx, const CVector &cameraPos)
{
	H_AUTO_OGL(CDriverGL_setupViewMatrixEx)
	_UserViewMtx= mtx;

	// Setup the matrix to transform the CScene basis in openGL basis.
	CMatrix		changeBasis;
	CVector		I(1,0,0);
	CVector		J(0,0,-1);
	CVector		K(0,1,0);

	changeBasis.identity();
	changeBasis.setRot(I,J,K, true);
	_ViewMtx=changeBasis*mtx;
	// Reset the viewMtx position.
	_ViewMtx.setPos(CVector::Null);
	_PZBCameraPos= cameraPos;

	// Anything that depend on the view martix must be updated.
	_LightSetupDirty= true;
	_ModelViewMatrixDirty= true;
	_RenderSetupDirty= true;
	// All lights must be refresh.
	for(uint i=0;i<MaxLight;i++)
		_LightDirty[i]= true;

	_SpecularTexMtx = _ViewMtx;
	_SpecularTexMtx.setPos(CVector(0.0f,0.0f,0.0f));
	_SpecularTexMtx.invert();
	_SpecularTexMtx = changeBasis *	_SpecularTexMtx;
}


// ***************************************************************************
void CDriverGL::setupViewMatrix(const CMatrix& mtx)
{
	H_AUTO_OGL(CDriverGL_setupViewMatrix)
	_UserViewMtx= mtx;

	// Setup the matrix to transform the CScene basis in openGL basis.
	CMatrix		changeBasis;
	CVector		I(1,0,0);
	CVector		J(0,0,-1);
	CVector		K(0,1,0);

	changeBasis.identity();
	changeBasis.setRot(I,J,K, true);
	_ViewMtx=changeBasis*mtx;
	// Just set the PZBCameraPos to 0.
	_PZBCameraPos= CVector::Null;

	// Anything that depend on the view martix must be updated.
	_LightSetupDirty= true;
	_ModelViewMatrixDirty= true;
	_RenderSetupDirty= true;
	// All lights must be refresh.
	for(uint i=0;i<MaxLight;i++)
		_LightDirty[i]= true;

	_SpecularTexMtx = _ViewMtx;
	_SpecularTexMtx.setPos(CVector(0.0f,0.0f,0.0f));
	_SpecularTexMtx.invert();
	_SpecularTexMtx = changeBasis *	_SpecularTexMtx;

}

// ***************************************************************************
CMatrix CDriverGL::getViewMatrix(void) const
{
	H_AUTO_OGL(CDriverGL_getViewMatrix)
	return _UserViewMtx;
}

// ***************************************************************************
void CDriverGL::setupModelMatrix(const CMatrix& mtx)
{
	H_AUTO_OGL(CDriverGL_setupModelMatrix)
	// profiling
	_NbSetupModelMatrixCall++;


	// Dirt flags.
	_ModelViewMatrixDirty= true;
	_RenderSetupDirty= true;


	// Put the matrix in the opengl eye space, and store it.
	CMatrix		mat= mtx;
	// remove first the _PZBCameraPos
	mat.setPos(mtx.getPos() - _PZBCameraPos);
	_ModelViewMatrix= _ViewMtx*mat;
}

// ***************************************************************************
void CDriverGL::doRefreshRenderSetup()
{
	H_AUTO_OGL(CDriverGL_doRefreshRenderSetup)
	// Check if the light setup has been modified first
	if (_LightSetupDirty)
		// Recompute light setup
		cleanLightSetup ();

	// Check light setup is good
	nlassert (_LightSetupDirty==false);


	// Check if must update the modelViewMatrix
	if( _ModelViewMatrixDirty )
	{
		// By default, the first model matrix is active
		glLoadMatrixf( _ModelViewMatrix.get() );
		// enable normalize if matrix has scale.
		enableGlNormalize( _ModelViewMatrix.hasScalePart() || _ForceNormalize );
		// clear.
		_ModelViewMatrixDirty= false;
	}

	// render setup is cleaned.
	_RenderSetupDirty= false;
}


} // NL3D
