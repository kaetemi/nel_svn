/** \file vectord.h
 * CVectorD class
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

#ifndef NL_VECTORD_H
#define NL_VECTORD_H

#include	<cmath>
#include	"vector.h"


namespace	NLMISC
{


// ======================================================================================================
/**
 * A 3D vector of double.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CVectorD
{
public:		// Attributes.
	double	x,y,z;

public:		// const.
	/// Null vector (0,0,0).
	static const	CVectorD		Null;
	/// I vector (1,0,0).
	static const	CVectorD		I;
	/// J vector (0,1,0).
	static const	CVectorD		J;
	/// K vector (0,0,1).
	static const	CVectorD		K;

public:		// Methods.
	/// @name Object.
	//@{
	/// Constructor which does nothing.
	CVectorD() {}
	/// Constructor .
	CVectorD(double	_x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	/// Constructor with a CVector.
	CVectorD(const CVector &v) : x(v.x), y(v.y), z(v.z) {}
	/// Copy Constructor.
	CVectorD(const CVectorD &v) : x(v.x), y(v.y), z(v.z) {}
	//@}

	/// @name Base Maths.
	//@{
	CVectorD	&operator+=(const CVectorD &v);
	CVectorD	&operator-=(const CVectorD &v);
	CVectorD	&operator*=(double f);
	CVectorD	&operator/=(double f);
	CVectorD	operator+(const CVectorD &v) const;
	CVectorD	operator-(const CVectorD &v) const;
	CVectorD	operator*(double f) const;
	CVectorD	operator/(double f) const;
	CVectorD	operator-() const;
	//@}

	/// @name Advanced Maths.
	//@{
	/// Dot product.
	double	operator*(const CVectorD &v) const;
	/** Cross product.
	 * compute the cross product *this ^ v.
	 */
	CVectorD	operator^(const CVectorD &v) const;
	/// Return the norm of the vector.
	double	norm() const;
	/// Return the square of the norm of the vector.
	double	sqrnorm() const;
	/// Normalize the vector.
	void	normalize();
	/// Return the vector normalized.
	CVectorD	normed() const;
	//@}

	/// @name Misc.
	//@{
	void	set(double _x, double _y, double _z);
	bool	operator==(const CVectorD &v) const;
	bool	operator!=(const CVectorD &v) const;
	bool	isNull() const;
	/**
	 * Setup the vector with spheric coordinates.
	 * sphericToCartesian(1,0,0) build the I vector  ((1,0,0)).
	 * the formula is:  \n
	 * x= r*cos(theta)*cos(phi) \n
	 * y= r*sin(theta)*cos(phi) \n
	 * z= r*sin(phi) \n
	 * \sa cartesianToSpheric()
	 */
	void	sphericToCartesian(double r, double theta,double phi);
	/**
	 * Get the sphreic coordinates of the vector.
	 * See sphericToCartesian() to know coordinates conventions.
	 * \sa sphericToCartesian()
	 */
	void	cartesianToSpheric(double &r, double &theta,double &phi) const;
	void	serial(IStream &f);
	CVectorD &operator=(const CVector &v);
	operator CVector() const;
	// copy content into a CVector
	void copyTo(CVector &dest) const;
	// conersion to a CVector
	CVector asVector() const;
	//@}

	// friends.
	friend	CVectorD	operator*(double f, const CVectorD &v0);
};


}


#include "vectord_inline.h"


#endif // NL_VECTOR_H

/* End of vector.h */
