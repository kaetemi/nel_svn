/** \file vegetable_uv8.h
 * TODO: File description
 *
 * $Id: vegetable_uv8.h,v 1.2 2004/11/15 10:24:53 lecroart Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_VEGETABLE_UV8_H
#define NL_VEGETABLE_UV8_H

#include "nel/misc/types_nl.h"


namespace NL3D 
{


/**
 * A simple tuple UV in 8 bits, for Dynamic Lightmap encoding in Alpha components of colors 
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CVegetableUV8
{
public:

	uint8	U,V;

};


} // NL3D


#endif // NL_VEGETABLE_UV8_H

/* End of vegetable_uv8.h */
