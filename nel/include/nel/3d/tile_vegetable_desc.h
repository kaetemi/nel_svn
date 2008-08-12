/** \file tile_vegetable_desc.h
 * TODO: File description
 *
 * $Id: tile_vegetable_desc.h,v 1.5 2005/02/22 10:19:12 besson Exp $
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

#ifndef NL_TILE_VEGETABLE_DESC_H
#define NL_TILE_VEGETABLE_DESC_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "landscape_def.h"
#include "vegetable.h"
#include "vegetable_def.h"
#include <vector>

namespace NL3D 
{


class	CVegetableManager;


// ***************************************************************************
/**
 * A descriptor of vegetables for a tile.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CTileVegetableDesc
{
public:

	/// Constructor
	CTileVegetableDesc();

	/// clear lists.
	void		clear();

	/// Build the CTileVegetableDesc.
	void		build(const std::vector<CVegetable> &vegetables);

	/// register all Vegetables in this to the manager.
	void		registerToManager(CVegetableManager *vegetableManager);

	/// serial.
	void		serial(NLMISC::IStream &f);

	/// get the vegetable list for a specific distanceType
	const	std::vector<CVegetable>		&getVegetableList(uint distType) const;

	/// get the vegetable seed for a specific distanceType
	uint		getVegetableSeed(uint distType) const;

	/// return true if no vegetable at all for any DistType
	bool		empty() const {return _Empty;}

private:

	/** List of vegetable to instanciate for a specific tile
	 *	Grouped by distance Type.
	 */
	std::vector<CVegetable>		_VegetableList[NL3D_VEGETABLE_BLOCK_NUMDIST];

	uint32						_VegetableSeed[NL3D_VEGETABLE_BLOCK_NUMDIST];

	// to know if no vegetable at all
	bool						_Empty;

	void	compileRunTime();
};


} // NL3D


#endif // NL_TILE_VEGETABLE_DESC_H

/* End of tile_vegetable_desc.h */
