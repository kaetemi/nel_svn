/** \file progress_callback.h
 * Progess callback interface
 *
 * $Id: progress_callback.h,v 1.5 2005/02/22 10:14:12 besson Exp $
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

#ifndef NL_PROGRESS_CALLBACK_H
#define NL_PROGRESS_CALLBACK_H

#include "types_nl.h"


namespace NLMISC {


/**
 * Progress callback interface
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class IProgressCallback
{
public:

	IProgressCallback ();
	virtual ~IProgressCallback () {}

	/**
	  * Call back
	  *
	  * progressValue should be 0 ~ 1
	  */
	virtual void progress (float progressValue);

	/**
	  * Push crop values
	  */
	void pushCropedValues (float min, float max);

	/**
	  * Push crop values
	  */
	void popCropedValues ();

	/**
	  * Get croped value
	  */
	float getCropedValue (float value) const;

public:
	
	/// Display string
	std::string		DisplayString;

private:

	class CCropedValues
	{
	public:
		CCropedValues (float min, float max)
		{
			Min = min;
			Max = max;
		}
		float	Min;
		float	Max;
	};

	std::vector<CCropedValues>	_CropedValues;
};


} // NLMISC


#endif // NL_PROGRESS_CALLBACK_H

/* End of progress_callback.h */
