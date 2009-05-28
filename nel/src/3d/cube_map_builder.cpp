/** \file cube_map_builder.cpp
 * a function that helps to build cube maps
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

#include "std3d.h"



#include "nel/3d/cube_map_builder.h"
#include "nel/3d/texture_cube.h"
#include "nel/3d/texture_mem.h"
#include "nel/misc/vector.h"
#include "nel/misc/rgba.h"




namespace NL3D
{


// utility function : build  a side of a cube map
static uint8 *BuildCubeMapTex(const NLMISC::CVector &start,
							  const NLMISC::CVector &uDir,
							  const NLMISC::CVector &vDir,
							  uint size,
							  ICubeMapFunctor &f
							 )
{
	NLMISC::CRGBA *map = new NLMISC::CRGBA[size * size];
	NLMISC::CRGBA *destTexel = map;
	NLMISC::CVector currN = start;
	NLMISC::CVector uStep = (2.f / size) * uDir;
	NLMISC::CVector vStep = (2.f / size) * vDir;

	for (uint y = 0; y < size; ++y)
	{
		NLMISC::CVector hCurrN = currN;
		for (uint x = 0; x < size; ++x)
		{
			destTexel[x + y *size] = f(hCurrN.normed());
			hCurrN += uStep;
		}
		currN += vStep;
	}
	return (uint8 *) map;
}

// utility function : build  a side of a cube map, with luminance only
static uint8 *BuildCubeMapTexLuminance(const NLMISC::CVector &start,
							  const NLMISC::CVector &uDir,
							  const NLMISC::CVector &vDir,
							  uint size,
							  ICubeMapFunctor &f
							 )
{
	uint8 *map = new uint8[size * size];
	uint8 *destTexel = map;
	NLMISC::CVector currN = start;
	NLMISC::CVector uStep = (2.f / size) * uDir;
	NLMISC::CVector vStep = (2.f / size) * vDir;

	for (uint y = 0; y < size; ++y)
	{
		NLMISC::CVector hCurrN = currN;
		for (uint x = 0; x < size; ++x)
		{
			destTexel[x + y *size] = f(hCurrN.normed()).A;
			hCurrN += uStep;
		}
		currN += vStep;
	}
	return map;
}



CTextureCube *BuildCubeMap(sint mapSize, ICubeMapFunctor &f, bool luminanceOnly /* = false*/, const std::string &shareName /* = "" */)
{
	std::auto_ptr<CTextureCube> cubeMap(new CTextureCube);
	std::auto_ptr<CTextureMem> faces[6];

	/// this gives the start (unormalized normal for each face for u,v = 0, 0)
	static const NLMISC::CVector start[] =
	{
		NLMISC::CVector(1, 1, 1),		/// positive_x
		NLMISC::CVector(-1, 1, -1),		/// negative_x
		NLMISC::CVector(-1, 1, -1),		/// positive_y
		NLMISC::CVector(-1, -1, 1),		/// negative_y
		NLMISC::CVector(-1, 1, 1),		/// positive_z
		NLMISC::CVector(1, 1, -1)		/// negative_z
	};


	static const NLMISC::CVector uDir[] =
	{
		NLMISC::CVector::K,		/// positive_x
		- NLMISC::CVector::K,			/// negative_x
		- NLMISC::CVector::I,			/// positive_y
		- NLMISC::CVector::I,			/// negative_y
		NLMISC::CVector::I,			/// positive_z
		-NLMISC::CVector::I,			/// negative_z
	};

	static const NLMISC::CVector vDir[] =
	{
		- NLMISC::CVector::J,		/// positive_x
		- NLMISC::CVector::J,		/// negative_x
		NLMISC::CVector::K,			/// positive_y
		- NLMISC::CVector::K,		/// negative_y
		NLMISC::CVector::J,		/// positive_z
		NLMISC::CVector::J,		/// negative_z
	};


	uint k;

	/// build all faces
	for (k = 0;  k < 6; ++k)
	{
		faces[k].reset(new CTextureMem);
		uint8 *map = luminanceOnly ?	BuildCubeMapTexLuminance(start[k], uDir[k], vDir[k], mapSize, f)
							   :	BuildCubeMapTex(start[k], uDir[k], vDir[k], mapSize, f);
		faces[k]->setPointer(map,
							 mapSize * mapSize * sizeof(uint8) * (luminanceOnly ? 1 : 4),
							 true,
							 false,
							 mapSize,
							 mapSize,
							 luminanceOnly ? CBitmap::Luminance : CBitmap::RGBA
							);
		if (!shareName.empty())
		{
			faces[k]->setShareName(shareName + (char) ('0' + k));
		}
	}

	static const CTextureCube::TFace toTC[] = { CTextureCube::positive_x, CTextureCube::negative_x,
												CTextureCube::positive_z, CTextureCube::negative_z,
												CTextureCube::negative_y, CTextureCube::positive_y };
	/// assign faces
	for (k = 0;  k < 6; ++k)
	{
		cubeMap->setTexture(toTC[k], faces[k].release());
	}

	return cubeMap.release();
}

} // NL3D
