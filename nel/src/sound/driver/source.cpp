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

// common method used only with OptionManualRolloff. return the volume in 1/100th DB ( = mB) modified
sint32 ISource::computeManualRollOff(sint32 volumeMB, sint32 mbMin, sint32 mbMax, double alpha, float sqrdist, float distMin, float distMax)
{
	if (sqrdist < distMin * distMin)
	{
		// no attenuation
		return volumeMB;
	}
	else if (sqrdist > distMax * distMax)
	{
		// full attenuation
		return mbMin;
	}
	else
	{
		double dist = (double) sqrt(sqrdist);

		// linearly descending volume on a dB scale
		double db1 = mbMin * (dist - distMin) / (distMax - distMin);

		if (alpha == 0.0) {
			volumeMB += (sint32) db1;

		} else if (alpha > 0.0) {
			double amp2 = 0.0001 + 0.9999 * (distMax - dist) / (distMax - distMin); // linear amp between 0.00001 and 1.0
			double db2 = 2000.0 * log10(amp2); // convert to 1/100th decibels
			volumeMB += (sint32) ((1.0 - alpha) * db1 + alpha * db2);

		} else if (alpha < 0.0) {
			double amp3 = distMin / dist; // linear amplitude is 1/distance
			double db3 = 2000.0 * log10(amp3); // convert to 1/100th decibels
			volumeMB += (sint32) ((1.0 + alpha) * db1 - alpha * db3);
		}
		
		clamp(volumeMB, mbMin, mbMax);
		return volumeMB;
	}
}

// common method used only with OptionManualRolloff. return the rolloff in amplitude ratio (gain)
float ISource::computeManualRolloff(double alpha, float sqrdist, float distMin, float distMax)
{
	static const sint32 mbMin = -10000;
	static const sint32 mbMax = 0;
	sint32 rolloffMb = ISource::computeManualRollOff(mbMax, mbMin, mbMax, alpha, sqrdist, distMin, distMax);
	float rolloffGain = (float)pow(10.0, (double)rolloffMb / 2000.0);
	clamp(rolloffGain, 0.0f, 1.0f);
	return rolloffGain;
}

} // NLSOUND

/* end of file */
