/** \file stop_watch.h
 * Performance stopwatch
 *
 * $Id: stop_watch.h,v 1.2 2005/02/22 10:14:12 besson Exp $
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_STOP_WATCH_H
#define NL_STOP_WATCH_H

#include "types_nl.h"
#include "time_nl.h"
#include <deque>


namespace NLMISC {


typedef uint32 TTickDuration;
typedef uint32 TMsDuration;


/**
 * Stopwatch class used for performance measurements and statistics.
 * To measure the duration of a cycle, call stop(), get the results, then call start().
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CStopWatch
{
public:

	/// Constructor. Set a non-zero queueLength for partial average calculation
	CStopWatch( uint queueLength=0 );


	
	/// Begin measurement
	void						start();

	/// Pause
	void						pause();

	/// Resume
	void						resume();

	/// Add time (in ticks unit) to the current measurement
	void						addTime( TTickDuration t );

	/// End measurement
	void						stop();

	/// Add an external duration (in ticks unit) to the average queue
	void						addMeasurement( TTickDuration t );



	/// Elapsed time in millisecond (call it after stop())
	TMsDuration					getDuration() const;

	/// Average duration of the queueLength last durations (using the queueLength argument specified in the constructor)
	TMsDuration					getPartialAverage() const;

	/// Average of the duration
	TMsDuration					getAverageDuration() const;


	
	/// Sum of the measured durations (in ticks)
	TTickDuration				sumTicks() const { return _SumTicks; }

	/// Number of measurements
	uint32						measurementNumber() const { return _MeasurementNumber; }

private:

	TTicks						_BeginTime;
	TTickDuration				_ElapsedTicks;

	TTickDuration				_SumTicks;
	uint32						_MeasurementNumber;

	std::deque<TTickDuration>	_Queue;
	uint						_QLength;
};


} // NLMISC


#endif // NL_STOP_WATCH_H

/* End of stop_watch.h */
