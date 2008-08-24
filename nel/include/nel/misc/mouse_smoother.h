/** \file mouse_smoother.h
 */

/* Copyright, 2000, 2001, 2002, 2003 Nevrax Ltd.
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

#ifndef NL_MOUSE_SMOOTHER_H
#define NL_MOUSE_SMOOTHER_H

#include "types_nl.h"
#include "vector_2f.h"

namespace NLMISC
{

/**
 * This smooth position of mouse using cubic splines.
 * The mouse is sampled at the given period. The higher the period, the smoother the movement.
 * However there is a delay of 2 * samplingPeriod between the user moving the mouse and the pointer reaching
 * the wanted poistion.
 *
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 1/2004
 */
class CMouseSmoother
{
public:
	// create a mouse smoother with the given sampling period.
	CMouseSmoother(double samplingPeriod = 0.2);
	/** Change the sampling period. The longer it lasts, the more smooth the movement.
	  * NB : this reset the smoother
	  */
	void				setSamplingPeriod(double period);
	// Get the sampling period
	double				getSamplingPeriod() const { return _SamplingPeriod; }
	// Reset smoother. The next returned position will be the exact position of mouse (no smoothing with previous position is done)
	void				reset();
	// \return trueif no sampling has occured since last resetor construction
	bool				isReseted() const { return !_Init; }
	// Sample pos, and return smoothed position
	CVector2f			samplePos(const CVector2f &wantedPos, double date);
private:
	// sample of mouse position
	class CSample
	{
	public:
		double		      Date;
		CVector2f		  Pos;
	public:
		// default ctor
		CSample() {}
		// ctor with pos & date
		CSample(double date, const NLMISC::CVector2f &pos) : Date(date), Pos(pos)
		{
		}
	};
	double		_SamplingPeriod;
	bool		_Init;
	/** 4 samples are needed to compute smoothed position :
	  * Sample 0 & 2 are used to compute tangent at sample 1
	  * Sample 1 & 3 are used to compute tangent at sample 2
	  */
	CSample _Sample[4];
};

} // NLMISC

#endif
