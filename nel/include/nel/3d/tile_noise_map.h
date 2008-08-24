/** \file tile_noise_map.h
 * A Noise Map for landscape.
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

#ifndef NL_TILE_NOISE_MAP_H
#define NL_TILE_NOISE_MAP_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"


namespace NL3D
{

// ***************************************************************************
// How many pixels per tile. must be a power of 2.
#define	NL3D_TILE_NOISE_MAP_TILE_FACTOR	4
// size of the map. must be a power of 2.
#define	NL3D_TILE_NOISE_MAP_SIZE		32


// ***************************************************************************
/**
 * A Noise Map for landscape.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CTileNoiseMap
{
public:

	// The array of pixels. -127 is mapped to -NL3D_NOISE_MAX, and +127 is mapped to NL3D_NOISE_MAX.
	sint8		Pixels[NL3D_TILE_NOISE_MAP_SIZE * NL3D_TILE_NOISE_MAP_SIZE];


	void		serial(NLMISC::IStream &f);

};


} // NL3D


#endif // NL_TILE_NOISE_MAP_H

/* End of tile_noise_map.h */
