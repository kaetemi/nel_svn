/** \file height_map.h
 * TODO: File description
 *
 * $Id: height_map.h,v 1.5 2004/11/15 10:24:16 lecroart Exp $
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

#ifndef NL_HEIGHT_MAP_H
#define NL_HEIGHT_MAP_H

#include "nel/misc/types_nl.h"
#include "nel/misc/bitmap.h"
#include <vector>

#define NL3D_MEM_HMAP						NL_ALLOC_CONTEXT( 3dHMap )

namespace NL3D
{


// ***************************************************************************
/**
 * A HeightMap. The heightMap is oriented left-right(X+) / bottom-top(Y+).
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CHeightMap
{
public:
	std::vector<uint8>		Heights;

	/// The origin of the bottom-left corner of this heightmap.
	float					OriginX, OriginY;
	/// The size of one Element ot this HeightMap (eg: 160x160 for a zone).
	float					SizeX, SizeY;
	/// The range of heights: 0 to MaxZ.
	float					MaxZ;

public:
	/// Constructor
	CHeightMap()
	{
		NL3D_MEM_HMAP
		SizeX= SizeY= 160;
		OriginX= OriginY= 0;
		MaxZ= 100;
	}


	/// resize the heightmap. resize Heights too.
	void			resize(uint w, uint h);
	uint			getWidth() const {return _Width;}
	uint			getHeight() const {return _Height;}


	/// return the ZValue, interval is: 0-MaxZ. nlassert(x,y).
	float			getZ(uint x, uint y) const;


	/** This tool method build a HeightMap, from a bitmap, resize(), and fill Heights.
	 * value are read from bitmap luminance value. NB: Lines are inverted, because bitmap definition is left-right / top-bottom.
	 */
	void			buildFromBitmap(const NLMISC::CBitmap &bitmap);

private:
	/// The size of this array. Heights.size
	uint			_Width, _Height;
};


} // NL3D


#endif // NL_HEIGHT_MAP_H

/* End of height_map.h */
