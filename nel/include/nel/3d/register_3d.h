/** \file register_3d.h
 * TODO: File description
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

#ifndef NL_REGISTER_3D_H
#define NL_REGISTER_3D_H

#include "nel/misc/types_nl.h"


namespace NL3D
{


//****************************************************************************
/**
 * This global function register all Serialisable Polymorphic 3D classes.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
void	registerSerial3d();


} // NL3D


#endif // NL_REGISTER_3D_H

/* End of register_3d.h */
