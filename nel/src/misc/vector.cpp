/** \file vector.cpp
 * CVector class
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

#include "stdmisc.h"

#include	"../../include/nel/misc/vector.h"

using namespace std;


namespace	NLMISC
{

const CVector	CVector::Null(0,0,0);
const CVector	CVector::I(1,0,0);
const CVector	CVector::J(0,1,0);
const CVector	CVector::K(0,0,1);


/*
 * Returns the contents as a printable string "x y z"
 */
string CVector::toString() const
{
	string str;
	str = NLMISC::toString(x) + " " + NLMISC::toString(y) + " " + NLMISC::toString(z);
	return str;
}


}

