/** \file hls_bank_texture_info.h
 * TODO: File description
 *
 * $Id: hls_bank_texture_info.h,v 1.2 2004/11/15 10:25:09 lecroart Exp $
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

#ifndef NL_HLS_BANK_TEXTURE_INFO_H
#define NL_HLS_BANK_TEXTURE_INFO_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "nel/misc/rgba.h"
#include "nel/misc/bitmap.h"


using NLMISC::CRGBA;


// ***************************************************************************
/**
 * .hlsinfo file. used to build .hlsbank
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CHLSBankTextureInfo
{
public:

	struct	CMaskBitmap
	{
		uint32				Width, Height;
		std::vector<uint8>	Pixels;

		void		serial(NLMISC::IStream &f)
		{
			sint	ver= f.serialVersion(0);
			f.serial(Width, Height);
			f.serialCont(Pixels);
		}

		/// Compress a bitmap in a Alpha map
		void		build(const NLMISC::CBitmap &src);
		/// build a RGBA bitmap.
		void		buildBitmap(NLMISC::CBitmap &dst);
	};

	class	CDXTCBitmap
	{
	public:
		/// Compress a bitmap in DXTC5/mipmap
		void		build(const NLMISC::CBitmap &src);
		/// build a DXTC5 bitmap.
		void		buildBitmap(NLMISC::CBitmap &dst);
		/// save/load
		void		serial(NLMISC::IStream &f);

	private:
		std::vector<uint8>	_Data;
	};

	struct	CHLSMod
	{
		float	DHue;
		float	DLum;
		float	DSat;

		void		serial(NLMISC::IStream &f)
		{
			sint	ver= f.serialVersion(0);
			f.serial(DHue, DLum, DSat);
		}
	};

	struct	CTextureInstance
	{
		/// name of the texture (with .tga)
		std::string				Name;
		/// List of modifier for each mask.
		std::vector<CHLSMod>	Mods;

		void		serial(NLMISC::IStream &f)
		{
			sint	ver= f.serialVersion(0);
			f.serial(Name);
			f.serialCont(Mods);
		}
	};

public:
	// Info for panoply_maker. Tells if the original texture was in dir d4/ at the last compute
	bool							DividedBy2;
	// The LowDef version of the Bitmap. Compressed in DXTC5 with mipmaps
	CDXTCBitmap						SrcBitmap;
	// Array of Masks.
	std::vector<CMaskBitmap>		Masks;
	// Array of colored version info
	std::vector<CTextureInstance>	Instances;

public:
	/// Constructor
	CHLSBankTextureInfo();

	void			serial(NLMISC::IStream &f);
};


#endif // NL_HLS_BANK_TEXTURE_INFO_H

/* End of hls_bank_texture_info.h */
