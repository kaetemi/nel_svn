/** \file move_cell.h
 * TODO: File description
 *
 * $Id: move_cell.h,v 1.3 2004/11/15 10:25:05 lecroart Exp $
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

#ifndef NL_MOVE_CELL_H
#define NL_MOVE_CELL_H

#include "nel/misc/types_nl.h"


namespace NLPACS 
{

class CMoveElement;

/**
 * Move cell
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CMoveCell
{
public:

	/// Constructor
	CMoveCell();

	/// Update sorted lists for an element
	void linkFirstX (CMoveElement *element)
	{
		linkX (NULL, element, _FirstX);
	}

	/// Update sorted lists for an element
	void linkLastX (CMoveElement *element)
	{
		linkX (_LastX, element, NULL);
	}

	/*/// Update sorted lists for an element
	void linkFirstY (CMoveElement *element)
	{
		linkY (NULL, element, _FirstY);
	}

	/// Update sorted lists for an element
	void linkLastY (CMoveElement *element)
	{
		linkY (_LastY, element, NULL);
	}*/

	/// Update sorted lists for an element
	void updateSortedLists (CMoveElement *element, uint8 worldImage);

	// Link / unlink method
	void unlinkX (CMoveElement *element);

	// Link / unlink method
	//void unlinkY (CMoveElement *element);

	// Get first X
	CMoveElement	*getFirstX () const
	{
		return _FirstX;
	}

	// Get last X
	CMoveElement	*getLastX () const
	{
		return _LastX;
	}

	// Get root X
	CMoveElement		*getRootX ()
	{
		return _FirstX;
	}

private:

	// Link / unlink method
	void linkX (CMoveElement *previous, CMoveElement *element, CMoveElement *next);

	// Link / unlink method
	//void linkY (CMoveElement *previous, CMoveElement *element, CMoveElement *next);

	CMoveElement		*_FirstX;
	CMoveElement		*_LastX;
	/*CMoveElement		*_FirstY;
	CMoveElement		*_LastY;*/
};


} // NLPACS


#endif // NL_MOVE_CELL_H

/* End of move_cell.h */
