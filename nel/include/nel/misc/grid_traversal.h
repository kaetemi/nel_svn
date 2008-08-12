/** \file grid_traversal.h
 * Utility class for incremental grid traversal
 *
 * $Id: grid_traversal.h
 */

/* Copyright, 2000, 2006 Nevrax Ltd.
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

#ifndef _GRID_TRAVERSAL_H
#define _GRID_TRAVERSAL_H

namespace NLMISC
{

class CVector2f;

/** Utility class for incremental grid traversal
  * 
  * \author Nicolas Vizerie
  * \author Nevrax France
  * \date 2005
  */
class CGridTraversal
{
public:
	/** begin to traverse a grid along the given segments
	  * \return first location in the grid
	  */
	static void startTraverse(const NLMISC::CVector2f &start, sint &nextX, sint &nextY);
	/** continue grid traversal from the given position
	  * If there are remaingind cells to traverse then true is returned, x & y are updated
	  */
	static bool traverse(const NLMISC::CVector2f &start, const NLMISC::CVector2f &dir, sint &x, sint &y);
};


} // NLMISC

#endif
