/** \file vectord.cpp
 * CVectorD class
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

#include "stdmisc.h"

#include	"../../include/nel/misc/vectord.h"


namespace	NLMISC
{

const CVectorD	CVectorD::Null(0,0,0);
const CVectorD	CVectorD::I(1,0,0);
const CVectorD	CVectorD::J(0,1,0);
const CVectorD	CVectorD::K(0,0,1);

}

