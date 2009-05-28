/** \file zone_utility.h
 * Tool for welding zones exported from 3dsMax
 *
 * $Id: zone_utility.h,v 1.1 2002/04/02 15:28:26 vizerie Exp $
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

#ifndef NL_ZONE_UTILITY
#define NL_ZONE_UTILITY

#include "nel/misc/types_nl.h"
#include <vector>
#include <set>

bool getZoneCoordByName(const char * name, uint16& x, uint16& y);
void getZoneNameByCoord(uint16 x, uint16 y, std::string& zoneName);

#endif // NL_ZONE_UTILITY
