/** \file stripifier.h
 * TODO: File description
 *
 * $Id: stripifier.h,v 1.4 2005/02/22 10:19:12 besson Exp $
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

#ifndef NL_STRIPIFIER_H
#define NL_STRIPIFIER_H

#include "nel/misc/types_nl.h"
#include "nel/3d/index_buffer.h"


namespace NL3D {


// ***************************************************************************
/**
 * Wrapper to NVidia(tm) Stripifier 
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CStripifier
{
public:

	/// Constructor
	CStripifier();

	/** reorganize triangles to get efficiency of GPU vertex-cache. Default vertex cache is 10.
	 *	out get the same list of triangles, but in different order.
	 *	any list of lines / quads in out are not modified.
	 *	NB: &in == &out is possible.
	 */
	void		optimizeTriangles(const CIndexBuffer &in, CIndexBuffer &out, uint cacheSize= 10);

};


} // NL3D


#endif // NL_STRIPIFIER_H

/* End of stripifier.h */
