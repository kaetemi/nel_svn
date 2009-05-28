/** \file s3tc_compressor.h
 * TODO: File description
 *
 * $Id: s3tc_compressor.h,v 1.2 2004/11/15 10:25:11 lecroart Exp $
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

#ifndef NL_S3TC_COMPRESSOR_H
#define NL_S3TC_COMPRESSOR_H

#include "nel/misc/types_nl.h"
#include "nel/misc/bitmap.h"
#include "nel/misc/stream.h"


// ***************************************************************************
#define	DXT1	1
#define	DXT1A	11
#define	DXT3	3
#define	DXT5	5


// ***************************************************************************
/**
 * From a bitmap, build the high quality DDS, and output in a stream
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CS3TCCompressor
{
public:
	/// Constructor
	CS3TCCompressor();

	void		compress(const NLMISC::CBitmap &bmpSrc, bool optMipMap, uint algo, NLMISC::IStream &output);

};


#endif // NL_S3TC_COMPRESSOR_H

/* End of s3tc_compressor.h */
