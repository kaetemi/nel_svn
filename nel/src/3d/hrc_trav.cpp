/** \file hrc_trav.cpp
 * TODO: File description
 *
 * $Id: hrc_trav.cpp,v 1.14 2005/02/22 10:19:10 besson Exp $
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

#include "std3d.h"

#include "nel/3d/hrc_trav.h"
#include "nel/misc/hierarchical_timer.h"
#include "nel/3d/scene.h"

using namespace std;
using namespace NLMISC;


namespace	NL3D
{


// ***************************************************************************
void				CHrcTrav::traverse()
{
	H_AUTO( NL3D_TravHRC );

	_MovingObjects.clear();

	// Traverse the graph.
	if(Scene->getRoot())
		Scene->getRoot()->traverseHrc();

	// Inc the date.
	// NB: Now, models update is done before ALL traversals.
	// Hence, we must inc the value before scene rendering. This is equivalent to start with 1, and inc at end of traverse().
	CurrentDate++;
}


}
