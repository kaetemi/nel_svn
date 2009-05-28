/** \file color_modifier.h
 * A class describing color modifications
 *
 * $Id: color_modifier.h,v 1.4 2007/03/19 09:55:26 boucher Exp $
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


#ifndef _COLOR_MODIFIER_H
#define _COLOR_MODIFIER_H

#include "nel/misc/types_nl.h"
#include <vector>
#include <string>

namespace NLMISC
{
	class CBitmap;
}

/// This describes how colors of a bitmap must be modified, and provides methos for doing so
struct CColorModifier
{
	float Hue;		  // Hue of the target color [0...360]
					  // The hue delta is deduced by averaging the hue of the source bitmap
	float Lightness;  // Lightness of the target color
	float Saturation; // Saturation of the terget color


	/// luminosity and contrast that are applied after 
	float Luminosity;
	float Contrast;

	std::string  ColID; // used to build the output fileNames

	/** just convert the pixels of a bitmap by using the alpha of the given mask
	 *	\param retDeltaHue take the real delta hue applied to the bitmap.
	 */
	void convertBitmap(NLMISC::CBitmap &destBitmap, const NLMISC::CBitmap &srcBitmap, const NLMISC::CBitmap &mask, 
		float &retDeltaHue) const;

	/** compute the averaged H, S and L from a bitmap	  
	  */
	static void evalBitmapStats(const NLMISC::CBitmap &srcBitmap,
								const NLMISC::CBitmap &mask,
								float &H,
								float &S,
								float &L,
								uint8 &greyLevel
							   );	

};

typedef std::vector<CColorModifier> TColorModifierVect;

#endif