/** \file vectord_inline.h
 * CVectorD class inline definitions.
 *
 * $Id: vectord_inline.h,v 1.9 2005/02/22 10:14:12 besson Exp $
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


#ifndef NL_VECTORD_INLINE_H
#define NL_VECTORD_INLINE_H


#include "common.h"


namespace	NLMISC
{


// ============================================================================================
// Base Maths.
inline	CVectorD	&CVectorD::operator+=(const CVectorD &v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}
inline	CVectorD	&CVectorD::operator-=(const CVectorD &v)
{
	x-=v.x;
	y-=v.y;
	z-=v.z;
	return *this;
}
inline	CVectorD	&CVectorD::operator*=(double f)
{
	x*=f;
	y*=f;
	z*=f;
	return *this;
}
inline	CVectorD	&CVectorD::operator/=(double f)
{
	return *this*= (1.0f/f);
}
inline	CVectorD	CVectorD::operator+(const CVectorD &v) const
{
	CVectorD	ret(x+v.x, y+v.y, z+v.z);
	return ret;
}
inline	CVectorD	CVectorD::operator-(const CVectorD &v) const
{
	CVectorD	ret(x-v.x, y-v.y, z-v.z);
	return ret;
}
inline	CVectorD	CVectorD::operator*(double f) const
{
	CVectorD	ret(x*f, y*f, z*f);
	return ret;
}
inline	CVectorD	CVectorD::operator/(double f) const
{
	return *this*(1.0f/f);
}
inline	CVectorD	CVectorD::operator-() const
{
	return CVectorD(-x,-y,-z);
}
inline CVectorD	operator*(double f, const CVectorD &v)
{
	CVectorD	ret(v.x*f, v.y*f, v.z*f);
	return ret;
}


// ============================================================================================
// Advanced Maths.
inline	double	CVectorD::operator*(const CVectorD &v) const
{
	return x*v.x + y*v.y + z*v.z;
}
inline	CVectorD	CVectorD::operator^(const CVectorD &v) const
{
	CVectorD	ret;

	ret.x= y*v.z - z*v.y;
	ret.y= z*v.x - x*v.z;
	ret.z= x*v.y - y*v.x;

	return ret;
}
inline	double	CVectorD::sqrnorm() const
{
	return (double)(x*x + y*y + z*z);
}
inline	double	CVectorD::norm() const
{
	return (double)sqrt(x*x + y*y + z*z);
}
inline	void	CVectorD::normalize()
{
	double	n=norm();
	if(n)
		*this/=n;
}
inline	CVectorD	CVectorD::normed() const
{
	CVectorD	ret;
	ret= *this;
	ret.normalize();
	return ret;
}


// ============================================================================================
// Misc.
inline	void	CVectorD::set(double _x, double _y, double _z)
{
	x=_x; y=_y; z=_z;
}
inline	bool	CVectorD::operator==(const CVectorD &v) const 
{
	return x==v.x && y==v.y && z==v.z;
}
inline	bool	CVectorD::operator!=(const CVectorD &v) const 
{
	return !(*this==v);
}
inline	bool	CVectorD::isNull() const
{
	return *this==CVectorD::Null;
}
inline	void	CVectorD::cartesianToSpheric(double &r, double &theta,double &phi) const
{
	CVectorD v;

	r= norm();
	v= normed();

	// phi E [-PI/2 et PI/2]
	clamp(v.z, -1.0, 1.0);
	phi=asin(v.z);

	// theta [-PI,PI]
	theta=atan2(v.y,v.x);
}
inline	void	CVectorD::sphericToCartesian(double r, double theta,double phi)
{
	x= r*cos(theta)*cos(phi);
	y= r*sin(theta)*cos(phi);
	z= r*sin(phi);
}
inline CVectorD &CVectorD::operator=(const CVector &v)
{
	x=v.x;
	y=v.y;
	z=v.z;
	return *this;
}
inline CVectorD::operator CVector() const
{
	return CVector((float)x, (float)y, (float)z);
}
inline	void	CVectorD::serial(IStream &f)
{
	f.serial(x,y,z);
}
inline	void CVectorD::copyTo(CVector &dest) const
{
	dest.set((float) x, (float) y, (float) z);
}
inline CVector CVectorD::asVector() const
{
	return CVector((float) x, (float) y, (float) z);
}



}


#endif

