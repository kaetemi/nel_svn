/** \file heat_haze.h
 * TODO: File description
 *
 * $Id: heat_haze.h,v 1.3 2005/02/22 10:19:10 besson Exp $
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_HEAT_HAZE_H
#define NL_HEAT_HAZE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"
#include "nel/3d/vertex_buffer.h"

namespace NL3D {

class IDriver ;
class CScene ;

/**
 * This perform  a heat haze effect at the horizon of the scene.
 * This make use of 2d deformation of the frame buffer
 * \param width  : viewport width
 * \param height : viewport height
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
class CHeatHaze
{
public:	
	// you must have setup effect2d before calling this
	static void performHeatHaze(uint width, uint height, CScene &s, IDriver *drv);
};


} // NL3D


#endif // NL_HEAT_HAZE_H

/* End of heat_haze.h */
