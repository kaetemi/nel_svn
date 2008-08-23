/** \file bezier_patch.h
 * TODO: File description
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

#ifndef NL_BEZIER_PATCH_H
#define NL_BEZIER_PATCH_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "nel/misc/vectord.h"
#include "nel/misc/matrix.h"


namespace NL3D 
{


using NLMISC::CVector;
using NLMISC::CVectorD;
using NLMISC::CMatrix;


// ***************************************************************************
/**
 * A standard bezier patch of float.  (quadpatch only).
 * QuadPatch layout (same notations as 3ds Max SDK).
 *
 *
 *
 *  0      ---s--->          3
 *
 *    A---> ad ---- da <---D
 *    |                    |
 *  | |                    |
 *  | v                    v
 *  | ab    ia      id     dc
 *  t
 *  | |                    |
 *  | |                    |
 *  v
 *    ba    ib      ic     cd
 *    ^                    ^
 *    |                    |
 *    |                    |
 *    B---> bc ---- cb <---C
 *  1                         2
 * 
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CBezierPatch
{
public:
	/// The vertices a,b,c,d of the quad patch.
	CVector		Vertices[4];		
	/// The tangents ab, ba, bc, cb, cd, dc, da, ad. NB: tangents are points, not vectors.
	CVector		Tangents[8];		
	/// The interiors, ia,ib,ic,id. NB: interiors are points, not vectors.
	CVector		Interiors[4];		


public:
	/// Constructor: undefined Bezier patch!!
	CBezierPatch() {}

	/// complete computation of Vertices, Tangents, and Interiors, provinding the vertices and vertex normals.
	void		make(CVector vertices[4], CVector	normals[4]);
	/// make default Interiors, according to Vertices and Tangents.
	void		makeInteriors();
	/// Do the matrix transformation m*patch.
	void		applyMatrix(const CMatrix &m);

	/// Evaluate.
	CVector		eval(float s, float t) const;			// s,t coordinates for quad.
	/// Evaluate, but return a vector double.
	CVectorD	evalDouble(double s, double t) const;	// s,t coordinates for quad.
	/// Evaluate the normal at (s,t). returned vector is normalized.
	CVector		evalNormal(float s, float t) const;		// s,t coordinates for quad.
	/// Evaluate the tangentS at (s,t). returned vector is normalized.
	CVector		evalTangentS(float s, float t) const;	// s,t coordinates for quad.
	/// Evaluate the tangentT at (s,t). returned vector is normalized.
	CVector		evalTangentT(float s, float t) const;	// s,t coordinates for quad.


	/// \name Subdivision.
	// @{
	/** Subdivide the bezier patch in 2 bezier patch along s, at s (beetween [0,1]).
	 * NB: left goes from 0 to s, right goes from s to 1.
	 */
	void		subdivideS(CBezierPatch &left, CBezierPatch &right, float s=0.5f) const;
	/** Subdivide the bezier patch in 2 bezier patch along t, at t (beetween [0,1]).
	 * NB: top goes from 0 to t, bottom goes from t to 1.
	 */
	void		subdivideT(CBezierPatch &top, CBezierPatch &bottom, float t=0.5f) const;
	// @}


// **********************************
private:
	struct	CBezierCurve
	{
		CVector	P0, P1, P2, P3;
		void	subdivide(CBezierCurve &left, CBezierCurve &right, float t);
		void	set(const CVector &a, const CVector &b, const CVector &c, const CVector &d)
		{
			P0= a; P1= b; P2= c; P3= d;
		}
		void	get(CVector &a, CVector &b, CVector &c, CVector &d)
		{
			a= P0; b= P1; c= P2; d= P3;
		}
	};

};



} // NL3D


#endif // NL_BEZIER_PATCH_H

/* End of bezier_patch.h */
