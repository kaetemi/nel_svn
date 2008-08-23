/** \file fast_floor.cpp
 * TODO: File description
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#include "nel/misc/fast_floor.h"
#include <cmath>

namespace NLMISC {

#if defined(NL_OS_WINDOWS)

double	OptFastFloorMagicConst = pow(2.0,52) + pow(2.0,51);
float	OptFastFloorMagicConst24 = (float)pow(2.0,23);
int      OptFastFloorCWStack[OptFastFloorCWStackSize];
int      *OptFastFloorCWStackEnd = OptFastFloorCWStack + OptFastFloorCWStackSize;
int		 *OptFastFloorCWStackPtr = OptFastFloorCWStack;

#endif

} // NLMISC
