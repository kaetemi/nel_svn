/** \file vector_inline.h
 * CVector class inline definitions
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


#ifndef NL_VECTOR_INLINE_H
#define NL_VECTOR_INLINE_H


#include "types_nl.h"
#include "common.h"


namespace	NLMISC
{


// ============================================================================================
// Base Maths.
inline	CVector	&CVector::operator+=(const CVector &v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}
inline	CVector	&CVector::operator-=(const CVector &v)
{
	x-=v.x;
	y-=v.y;
	z-=v.z;
	return *this;
}
inline	CVector	&CVector::operator*=(float f)
{
	x*=f;
	y*=f;
	z*=f;
	return *this;
}
inline	CVector	&CVector::operator/=(float f)
{
	return *this*= (1.0f/f);
}
inline	CVector	CVector::operator+(const CVector &v) const
{
	CVector	ret(x+v.x, y+v.y, z+v.z);
	return ret;
}
inline	CVector	CVector::operator-(const CVector &v) const
{
	CVector	ret(x-v.x, y-v.y, z-v.z);
	return ret;
}
inline	CVector	CVector::operator*(float f) const
{
	CVector	ret(x*f, y*f, z*f);
	return ret;
}
inline	CVector	CVector::operator/(float f) const
{
	return *this*(1.0f/f);
}
inline	CVector	CVector::operator-() const
{
	return CVector(-x,-y,-z);
}
inline CVector	operator*(float f, const CVector &v)
{
	CVector	ret(v.x*f, v.y*f, v.z*f);
	return ret;
}


// ============================================================================================
// Advanced Maths.
inline	float	CVector::operator*(const CVector &v) const
{
	return x*v.x + y*v.y + z*v.z;
}
inline	CVector	CVector::operator^(const CVector &v) const
{
	CVector	ret;

	ret.x= y*v.z - z*v.y;
	ret.y= z*v.x - x*v.z;
	ret.z= x*v.y - y*v.x;

	return ret;
}
inline	float	CVector::sqrnorm() const
{
	return (float)(x*x + y*y + z*z);
}
inline	float	CVector::norm() const
{
	return (float)sqrt(x*x + y*y + z*z);
}
inline	void	CVector::normalize()
{
	float	n=norm();
	if(n)
		*this/=n;
}
inline	CVector	CVector::normed() const
{
	CVector	ret;
	ret= *this;
	ret.normalize();
	return ret;
}


// ============================================================================================
// Misc.
inline	void	CVector::set(float _x, float _y, float _z)
{
	x=_x; y=_y; z=_z;
}
inline	bool	CVector::operator==(const CVector &v) const
{
	return x==v.x && y==v.y && z==v.z;
}
inline	bool	CVector::operator!=(const CVector &v) const
{
	return !(*this==v);
}
inline	bool	CVector::isNull() const
{
	return *this==CVector::Null;
}
inline	bool	CVector::operator<(const CVector &v) const
{
	if(x!=v.x)
		return x<v.x;
	if(y!=v.y)
		return y<v.y;
	return z<v.z;
}

inline	void	CVector::cartesianToSpheric(float &r, float &theta,float &phi) const
{
	CVector v;

	r= norm();
	v= normed();

	// phi E [-PI/2 et PI/2]
	clamp(v.z, -1.0f, 1.0f);
	phi= (float)asin(v.z);

	// theta [-PI,PI]
	theta= (float)atan2(v.y,v.x);
}
inline	void	CVector::sphericToCartesian(float r, float theta,float phi)
{
	double	ct= cos(theta);
	double	st= sin(theta);
	double	cp= cos(phi);
	double	sp= sin(phi);

	x= (float)(r*ct*cp);
	y= (float)(r*st*cp);
	z= (float)(r*sp);
}
inline	void	CVector::minof(const CVector &a, const CVector &b)
{
	x= std::min(a.x, b.x);
	y= std::min(a.y, b.y);
	z= std::min(a.z, b.z);
}
inline	void	CVector::maxof(const CVector &a, const CVector &b)
{
	x= std::max(a.x, b.x);
	y= std::max(a.y, b.y);
	z= std::max(a.z, b.z);
}
inline	void	CVector::serial(IStream &f)
{
	f.serial(x,y,z);
}


}


#endif

