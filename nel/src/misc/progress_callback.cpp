/** \file progress_callback.cpp
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

#include "stdmisc.h"
#include "nel/misc/progress_callback.h"


namespace NLMISC
{

float IProgressCallback::getCropedValue (float value) const
{
	nlassert (_CropedValues.size ()>0);
	const CCropedValues &values = _CropedValues.back ();
	return value*(values.Max-values.Min)+values.Min;
}

IProgressCallback::IProgressCallback ()
{
	_CropedValues.push_back (CCropedValues (0, 1));
}

void IProgressCallback::pushCropedValues (float min, float max)
{
	nlassert (_CropedValues.size ()>0);
	//const CCropedValues &values = _CropedValues.back ();
	_CropedValues.push_back (CCropedValues (getCropedValue (min), getCropedValue (max)));
}

void IProgressCallback::popCropedValues ()
{
	nlassert (_CropedValues.size ()>1);
	_CropedValues.pop_back ();
}

void IProgressCallback::progress (float /* progressValue */)
{
}

} // NLMISC
