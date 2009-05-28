/** \file fasthls_modifier.h
 * TODO: File description
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_FASTHLS_MODIFIER_H
#define NL_FASTHLS_MODIFIER_H

#include "nel/misc/types_nl.h"


namespace NLMISC
{
	class	CBitmap;
}


namespace NL3D
{


// ***************************************************************************
/**
 * Singleton. allow to apply HLS coloring as fast as possible (MMX...).
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CFastHLSModifier
{
public:

	/// get the singleton
	static CFastHLSModifier	&getInstance();

	// release singleton
	static void releaseInstance();

	/// convert a HLS (0..255) to a RGBA.
	CRGBA		convert(uint H, uint L, uint S);

	/// convert a RGBA bitmap into another RGBA, with HLS decal (0..255, -255..+255, -255..+255).
	void		convertRGBABitmap(NLMISC::CBitmap &dst, const NLMISC::CBitmap &src, uint8 dh, sint dl, sint ds);

	/// convert a DDS bitmap into another DDS, with HLS decal (0..255, -255..+255, -255..+255).
	void		convertDDSBitmap(NLMISC::CBitmap &dst, const NLMISC::CBitmap &src, uint8 dh, sint dl, sint ds);

	/** convert a uint16 color into the uint16 with HLS decal.
	 *	WARNING: this code use MMX when possible, but doesn't call emms!!! It is User job to do it.
	 *	dLum must be actually 0xFFFFFF00 + realDLum (where realDLum== -255..+255)
	 *	dSat must be actually 0xFFFFFF00 + realDSat (where realDSat== -255..+255)
	 */
	uint16		applyHLSMod(uint16 colorIn, uint8 dHue, uint dLum, uint dSat);


// ****************
private:

	static	CFastHLSModifier	*_Instance;

	enum	{HueTableSize= 256};
	struct	CHLSA
	{
		uint8	H,L,S,A;
	};

	CRGBA		_HueTable[HueTableSize];
	CHLSA		_Color16ToHLS[65536];

	/// Constructor
	CFastHLSModifier();
	~CFastHLSModifier();

	void		convertDDSBitmapDXTC1Or1A(NLMISC::CBitmap &dst, const NLMISC::CBitmap &src, uint8 dh, uint dLum, uint dSat);
	void		convertDDSBitmapDXTC3Or5(NLMISC::CBitmap &dst, const NLMISC::CBitmap &src, uint8 dh, uint dLum, uint dSat);
};


} // NL3D


#endif // NL_FASTHLS_MODIFIER_H

/* End of fasthls_modifier.h */
