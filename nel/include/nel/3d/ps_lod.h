/** \file ps_lod.h
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

#ifndef NL_PS_LOD_H
#define NL_PS_LOD_H

#include "nel/misc/types_nl.h"


namespace NL3D {


/// lod for located bindables. (see ps_located.h)
enum TPSLod
{
	PSLod1n2 = 0, // the object is dealt with for every distance (his is the default)
	PSLod1,  // the object is dealt when the system center is near
	PSLod2,  // the object is dealt when the system center is far
};







} // NL3D


#endif // NL_PS_LOD_H

/* End of ps_lod.h */
