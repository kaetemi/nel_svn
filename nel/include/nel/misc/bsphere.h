/** \file bsphere.h
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

#ifndef NL_BSPHERE_H
#define NL_BSPHERE_H

#include "types_nl.h"
#include "vector.h"
#include "plane.h"
#include "matrix.h"


namespace NLMISC
{


/**
 * A bounding Sphere.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CBSphere
{
public:
	CVector			Center;
	float			Radius;

	/// Empty Constructor.
	CBSphere() {}
	/// Constructor.
	CBSphere(const CVector & center, float radius) : Center(center), Radius(radius) {}


	/// \name transform
	// @{

	/** compute res= mat * this. NB: radius is maximized, taking max of the 3 axis of the matrix.
	 * NB: this may be false if the matrix is not orthogonal...
	 */
	void	applyTransform(const CMatrix &mat, CBSphere &res);

	// @}

	/// \name Clip
	// @{
	/// Is the bbox partially in front of the plane??  p MUST be normalized.
	bool	clipFront(const CPlane &p) const;
	/// Is the bbox partially in back of the plane??  p MUST be normalized.
	bool	clipBack(const CPlane &p) const;
	// @}

	/// Does the sphere include this point?
	bool	include(const CVector &p) const;
	/// Does the sphere include TOTALY this sphere?
	bool	include(const CBSphere &s) const;
	/// Does the sphere intersect the other?
	bool	intersect(const CBSphere &s) const;

	/// Build the union of the 2 sphere ans set to *this. work if this==s1 || this==s2.
	void	setUnion(const CBSphere &sa, const CBSphere &sb);
};


} // NLMISC


#endif // NL_BSPHERE_H

/* End of bsphere.h */
