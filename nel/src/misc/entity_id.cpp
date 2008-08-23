/** \file entity_id.cpp
 * TODO: File description
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

#include "stdmisc.h"

#include "nel/misc/entity_id.h"

using namespace std;

namespace NLMISC {

	const uint64 CEntityId::MaxEntityId = ((uint64)1 << (CEntityId::ID_SIZE + 1)) - (uint64)1;

	CEntityId CEntityId::_NextEntityId;

	uint8 CEntityId::_ServerId = 0;

	const CEntityId CEntityId::Unknown (CEntityId::UNKNOWN_TYPE, 0, 0, 0);

} // NLMISC
