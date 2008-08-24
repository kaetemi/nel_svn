/** \file ps_attrib_maker_bin_op.cpp
 * TODO: File description
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

#include "nel/3d/ps_attrib_maker_bin_op.h"


namespace NL3D
{

	void MakePrivate(uint8 * dest, const NLMISC::CRGBA *src1, const NLMISC::CRGBA *src2, uint32 stride, uint32 numAttrib, CPSBinOp::BinOp op)
	{
		switch (op)
		{
			case CPSBinOp::modulate:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::modulateColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride);
			}
			break;
			case CPSBinOp::add:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::addColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride);
			}
			break;
			case CPSBinOp::subtract:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::subtractColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride);
			}
			break;
			default: break;
		}
	}

	void Make4Private(uint8 * dest, const NLMISC::CRGBA *src1, const NLMISC::CRGBA *src2, uint32 stride, uint32 numAttrib, CPSBinOp::BinOp op)
	{
		switch (op)
		{
			case CPSBinOp::modulate:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::modulateColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride, 4);
			}
			break;
			case CPSBinOp::add:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::addColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride, 4);
			}
			break;
			case CPSBinOp::subtract:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::subtractColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride, 4);
			}
			break;
			default: break;
		}
	}


	void MakeNPrivate(uint8 * dest, const NLMISC::CRGBA *src1, const NLMISC::CRGBA *src2, uint32 stride, uint32 numAttrib, CPSBinOp::BinOp op, uint nbReplicate)
	{
		switch (op)
		{
			case CPSBinOp::modulate:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::modulateColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride, nbReplicate);
			}
			break;
			case CPSBinOp::add:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::addColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride, nbReplicate);
			}
			break;
			case CPSBinOp::subtract:
			{
				// CRGBA OPTIMISATION
				NLMISC::CRGBA::subtractColors((NLMISC::CRGBA *) dest, src1, src2, numAttrib, sizeof(NLMISC::CRGBA), stride, nbReplicate);
			}
			break;
			default: break;
		}
	}
} // NL3D
