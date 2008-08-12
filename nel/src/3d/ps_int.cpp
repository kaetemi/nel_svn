/** \file ps_int.cpp
 * TODO: File description
 *
 * $Id: ps_int.cpp,v 1.9 2005/02/22 10:19:11 besson Exp $
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

#include "ps_int.h"
#include "ps_register_int_attribs.h"


namespace NL3D {


sint32 CPSIntGradient::_DefaultGradient[] = { 0, 10 };
uint32 CPSUIntGradient::_DefaultGradient[] = { 0, 10 };


CPSIntGradient::CPSIntGradient(const sint32 *intTab, uint32 nbValues, uint32 nbStages, float nbCycles) 
				: CPSValueGradient<sint32>(nbCycles)
{
	_F.setValues(intTab, nbValues, nbStages);
}


CPSUIntGradient::CPSUIntGradient(const uint32 *intTab, uint32 nbValues, uint32 nbStages, float nbCycles) 
				: CPSValueGradient<uint32>(nbCycles)
{
	_F.setValues(intTab, nbValues, nbStages);
}


/// Register attribute makers based on int (used in particle systems)
void PSRegisterIntAttribs()
{
	NLMISC_REGISTER_CLASS(CPSIntBlender);		
	NLMISC_REGISTER_CLASS(CPSIntMemory);		
	NLMISC_REGISTER_CLASS(CPSIntBinOp);		
	NLMISC_REGISTER_CLASS(CPSIntGradient);
	NLMISC_REGISTER_CLASS(CPSUIntBlender);		
	NLMISC_REGISTER_CLASS(CPSUIntMemory);		
	NLMISC_REGISTER_CLASS(CPSUIntBinOp);		
	NLMISC_REGISTER_CLASS(CPSUIntGradient);
}


} // NL3D
