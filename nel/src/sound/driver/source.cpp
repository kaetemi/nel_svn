/** \file source.cpp
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

#include "source.h"
#include "nel/misc/common.h"

using namespace NLMISC;

namespace NLSOUND
{

// ***************************************************************************
sint32 ISource::computeManualRollOff(sint32 volumeDB, sint32 dbMin, sint32 dbMax, double alpha, float sqrdist) const
{
	float min, max;
	getMinMaxDistances(min, max);

	if (sqrdist < min * min)
	{
		// no attenuation
		return volumeDB;
	}
	else if (sqrdist > max * max)
	{
		// full attenuation
		return dbMin;
	}
	else
	{
		double dist = (double) sqrt(sqrdist);

		// linearly descending volume on a dB scale
		double db1 = dbMin * (dist - min) / (max - min);

		if (alpha == 0.0) {
			volumeDB += (sint32) db1;

		} else if (alpha > 0.0) {
			double amp2 = 0.0001 + 0.9999 * (max - dist) / (max - min); // linear amp between 0.00001 and 1.0
			double db2 = 2000.0 * log10(amp2); // convert to 1/100th decibels
			volumeDB += (sint32) ((1.0 - alpha) * db1 + alpha * db2);

		} else if (alpha < 0.0) {
			double amp3 = min / dist; // linear amplitude is 1/distance
			double db3 = 2000.0 * log10(amp3); // convert to 1/100th decibels
			volumeDB += (sint32) ((1.0 + alpha) * db1 - alpha * db3);
		}

		clamp(volumeDB, dbMin, dbMax);

		return volumeDB;
	}
}

} // NLSOUND

/* end of file */
