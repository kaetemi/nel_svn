/** \file logic_info.cpp
 * TODO: File description
 *
 * $Id: logic_info.cpp,v 1.4 2004/11/15 10:24:41 lecroart Exp $
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

#include "nel/3d/logic_info.h"


namespace NL3D {


ILogicInfo::ILogicInfo()
{
	NL3D_MEM_LOGIC
}
ILogicInfo::~ILogicInfo()
{
	NL3D_MEM_LOGIC
}


} // NL3D
