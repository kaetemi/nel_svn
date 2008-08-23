/** \file quad.h
 * TODO: File description
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

#ifndef NL_QUAD_H
#define NL_QUAD_H

#include "types_nl.h"
#include "vector.h"


namespace NLMISC {


// ***************************************************************************
/**
 * A simple quad of vertex.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CQuad
{
public:
	CVector		V0, V1, V2, V3;


public:

	/// Constructor
	CQuad() {}

	/// Constructor
	CQuad(const NLMISC::CVector &v0, const NLMISC::CVector &v1, const NLMISC::CVector &v2, const NLMISC::CVector &v3) 
		: V0(v0), V1(v1), V2(v2), V3(v3)
	{}

	void set(const NLMISC::CVector &v0, const NLMISC::CVector &v1, const NLMISC::CVector &v2, const NLMISC::CVector &v3)
	{
		V0 = v0;
		V1 = v1;
		V2 = v2;
		V3 = v3;
	}

	const CQuad &operator = ( const CQuad& q)
	{ 
		V0 = q.V0;
		V1 = q.V1;
		V2 = q.V2;
		V3 = q.V3;
		return *this;
	}
	
};


} // NLMISC


#endif // NL_QUAD_H

/* End of quad.h */
