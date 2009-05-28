/** \file u_collision_desc.h
 * Description of the contact of a collision
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

#ifndef NL_U_COLLISION_DESC_H
#define NL_U_COLLISION_DESC_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vectord.h"

#include "u_move_primitive.h"

#include <vector>

namespace NLMISC
{
	class IStream;
}

namespace NLPACS
{

/**
 * Description of the contact of a collision
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class UCollisionDesc
{
public:
	NLMISC::CVectorD		ContactPosition;
	NLMISC::CVectorD		ContactNormal0;
	NLMISC::CVectorD		ContactNormal1;
	double					ContactTime;

	// Serial method
	void serial (NLMISC::IStream& stream);
};

/**
 * Description of the contact of a collision
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class UTriggerInfo
{
public:
	enum
	{
		In = 0,
		Inside,
		Out
	};

	UMovePrimitive::TUserData	Object0;
	UMovePrimitive::TUserData	Object1;
	UCollisionDesc				CollisionDesc;
	uint8						CollisionType;

	// Serial method
	void serial (NLMISC::IStream& stream);
};

} // NLPACS


#endif // NL_U_COLLISION_DESC_H

/* End of collision_desc.h */
