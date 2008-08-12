/** \file tile_vegetable_desc.cpp
 * TODO: File description
 *
 * $Id: tile_vegetable_desc.cpp,v 1.7 2005/02/22 10:19:12 besson Exp $
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

#include "std3d.h"

#include "nel/3d/tile_vegetable_desc.h"
#include "nel/misc/common.h"
#include "nel/3d/vegetable_manager.h"


using namespace NLMISC;
using namespace std;


namespace NL3D 
{



// ***************************************************************************
CTileVegetableDesc::CTileVegetableDesc()
{
	_Empty= true;
}

// ***************************************************************************
void		CTileVegetableDesc::clear()
{
	for(sint i=0; i<NL3D_VEGETABLE_BLOCK_NUMDIST; i++)
	{
		_VegetableList[i].clear();
	}
	_Empty= true;
}

// ***************************************************************************
void		CTileVegetableDesc::build(const std::vector<CVegetable> &vegetables)
{
	uint	i;

	// first clear().
	clear();

	// Parse all landscape vegetables, and store them in appropriate distance Type.
	for(i=0;i<vegetables.size();i++)
	{
		uint	distType= vegetables[i].DistType;
		distType= min(distType, (uint)(NL3D_VEGETABLE_BLOCK_NUMDIST-1));
		_VegetableList[distType].push_back(vegetables[i]);
	}

	// Compute Seed such that creation of one vegetable for a tile will never receive same seed.
	uint	sumVeget= 0;
	for(i=0; i<NL3D_VEGETABLE_BLOCK_NUMDIST; i++)
	{
		_VegetableSeed[i]= sumVeget;
		// add number of vegetable for next seed.
		sumVeget+= _VegetableList[i].size();
	}

	// compile some data
	compileRunTime();
}

// ***************************************************************************
void		CTileVegetableDesc::registerToManager(CVegetableManager *vegetableManager)
{
	// Pasre all distanceType.
	for(uint i=0; i<NL3D_VEGETABLE_BLOCK_NUMDIST; i++)
	{
		// Parse all vegetables of the list.
		for(uint j=0; j<_VegetableList[i].size(); j++)
		{
			// register the vegetable to the manager
			_VegetableList[i][j].registerToManager(vegetableManager);
		}
	}
}

// ***************************************************************************
void		CTileVegetableDesc::serial(NLMISC::IStream &f)
{
	(void)f.serialVersion(0);

	nlassert(NL3D_VEGETABLE_BLOCK_NUMDIST==5);
	for(uint i=0; i<NL3D_VEGETABLE_BLOCK_NUMDIST; i++)
	{
		f.serialCont(_VegetableList[i]);
		f.serial(_VegetableSeed[i]);
	}

	// compile some data
	if(f.isReading())
		compileRunTime();
}

// ***************************************************************************
const	std::vector<CVegetable>		&CTileVegetableDesc::getVegetableList(uint distType) const
{
	nlassert(distType < NL3D_VEGETABLE_BLOCK_NUMDIST);

	return _VegetableList[distType];
}

// ***************************************************************************
uint		CTileVegetableDesc::getVegetableSeed(uint distType) const
{
	nlassert(distType < NL3D_VEGETABLE_BLOCK_NUMDIST);

	return _VegetableSeed[distType];
}

// ***************************************************************************
void		CTileVegetableDesc::compileRunTime()
{
	// Compute _Empty flag
	_Empty= true;
	for(uint i=0; i<NL3D_VEGETABLE_BLOCK_NUMDIST; i++)
	{
		if(!_VegetableList[i].empty())
		{
			_Empty= false;
			break;
		}
	}
}



} // NL3D
