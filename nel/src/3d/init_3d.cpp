/** \file init_3d.cpp
 *
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


#include "nel/3d/init_3d.h"
#include <cfloat>

namespace NL3D
{

void init3d ()
{
	// Init for windows
#ifdef NL_OS_WINDOWS
	// Enable FPU exceptions

	// Enable divid by zero and  overflow exception
	_control87 (_EM_INVALID|_EM_DENORMAL/*|_EM_ZERODIVIDE|_EM_OVERFLOW*/|_EM_UNDERFLOW|_EM_INEXACT, _MCW_EM);
#endif // NL_OS_WINDOWS
}

} // NL3D
