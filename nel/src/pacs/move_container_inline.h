/** \file move_container_inline.h
 * Inline functions for movable object
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

#ifndef NL_MOVE_CONTAINER_INLINE_H
#define NL_MOVE_CONTAINER_INLINE_H

#include "nel/misc/types_nl.h"

namespace NLPACS
{

// ***************************************************************************

inline void CMoveContainer::changed (CMovePrimitive* primitive, uint8 worldImage)
{
	// Primitive noncollisionable ?
	if (primitive->isCollisionable())
	{
		// Get the world image
		CPrimitiveWorldImage *wI;

		wI=primitive->getWorldImage (worldImage);

		// Not yet in the list ?
		if (!wI->isInModifiedListFlag ())
		{
			// Flag it
			wI->setInModifiedListFlag (true);

			// Link it
			wI->linkInModifiedList (_ChangedRoot[worldImage]);

			// Change root list
			_ChangedRoot[worldImage]=primitive;
		}
	}
}

// ***************************************************************************

} // NLPACS


#endif // NL_MOVE_CONTAINER_INLINE_H

/* End of move_container.h */
