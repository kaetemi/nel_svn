/** \file line.h
 * A simple couple of vertex.
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

#ifndef NL_LINE_H
#define NL_LINE_H

#include "types_nl.h"
#include "vector.h"


namespace NLMISC 
{



// ***************************************************************************
/**
 * A simple couple of vertex.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CLine
{
public:
	CVector		V0, V1;

public:
	/// default ctor
	CLine() {}
	// ctor from 2 points
	CLine(const CVector &v0, const CVector &v1) : V0(v0), V1(v1)
	{}
	/// Project a vector on this line
	void project(const CVector &inV, CVector &outV);

};


} // NLMISC


#endif // NL_LINE_H

/* End of line.h */
