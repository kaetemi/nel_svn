/** \file plane_inline.h
 * class CPlane
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

#ifndef NL_PLANE_INLINE_H
#define NL_PLANE_INLINE_H


namespace NLMISC
{


//============================================================
inline	CVector	CPlane::getNormal() const
{
	return CVector(a,b,c);
}
//============================================================
inline	float	CPlane::distance(const CVector &v) const
{
	CPlane	p= normed();
	return (float)fabs(p*v);
}
//============================================================
inline	float	CPlane::operator*(const CVector &p) const
{
	return a*p.x + b*p.y + c*p.z + d;
}
//============================================================
inline	CVector CPlane::intersect(const CVector &p0,const CVector &p1) const
{
	float decal;
	float	da= (*this)*p0;
	float	db= (*this)*p1;
	if(db-da == 0)
		return p0;
	decal= ( 0-da ) / ( db - da );
	return p0 + (p1-p0)*decal;
}
//============================================================
inline	CVector CPlane::project(const CVector &p0) const
{
	return intersect(p0, p0+getNormal());
}

//============================================================
inline	void	CPlane::normalize()
{
	float	n= getNormal().norm();
	if(n)
	{
		float	oon= 1.0f/n;
		a*= oon;
		b*= oon;
		c*= oon;
		d*= oon;
	}
}
//============================================================
inline	CPlane	CPlane::normed() const
{
	CPlane	ret= *this;
	ret.normalize();
	return ret;
}


}


#endif // NL_PLANE_H

/* End of plane.h */
