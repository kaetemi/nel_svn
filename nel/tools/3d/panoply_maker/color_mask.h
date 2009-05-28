/** \file color_mask.h
 * A class for describing colors masks (file extension, and what colors they support)
 *
 * $Id: color_mask.h,v 1.1 2002/02/06 10:12:55 vizerie Exp $
 */

/* Copyright, 2000, 2001, 2002 Nevrax Ltd.
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

#ifndef _COLOR_MASK_H
#define _COLOR_MASK_H

#include "color_modifier.h"
#include <string>

struct CColorMask
{
	// the extension used for this color mask.
	// Example : if this is named 'mask1', a base texture 
	// 'tex.tga' will use this mask if there's a tex_mask1.tga file
	std::string			MaskExt;

	/// the various color modifiers that must be applied on textures
	TColorModifierVect	CMs;
};

typedef std::vector<CColorMask> TColorMaskVect;



#endif

