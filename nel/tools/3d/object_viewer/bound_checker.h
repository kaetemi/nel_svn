/** \file bound_checker.h
 * class that helps to check bounds
 *
 * $Id: bound_checker.h,v 1.1 2001/09/12 13:25:35 vizerie Exp $
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef BOUND_CHECKER_H
#define BOUND_CHECKER_H

#include <nel/misc/types_nl.h>


/// This class implement bound checking for values. Can be used in an edition dialog
template <class T>
class CBoundChecker
{
public:
	/** ctor
	  * the default doesn't enable bound checking
	  */
	CBoundChecker() : _UpperBoundEnabled(false), _LowerBoundEnabled(false) {}

	/** enable upper bound use (e.g. value must be < or <= upper bound )
	 *  \param upperBoundExcluded if true then the test is <, otherwise its <=
	 */
	void enableUpperBound(T upperBound, bool upperBoundExcluded) 
	{ 
		_UpperBoundEnabled = true;
		_UpperBoundExcluded = upperBoundExcluded;
		_UpperBound = upperBound; 
	}

	// disable upper bound usage
	void disableUpperBound(void) { _UpperBoundEnabled = false; }

	// get the upper bound
	T getUpperBound(void) const { return _UpperBound; }

	// test wether the upper bound is excluded of the test
	bool isUpperBoundExcluded(void) const
	{
		return _UpperBoundExcluded;
	}

	/** enable lower bound use (e.g. value must be < or <= lower bound )
	 *  \param lowerBoundExcluded if true then the test is <, otherwise its <=
	 */
	void enableLowerBound(T lowerBound, bool lowerBoundExcluded) 
	{ 
		_LowerBoundEnabled = true;
		_LowerBoundExcluded = lowerBoundExcluded;
		_LowerBound = lowerBound; 
	}
	
	// disable lower bound
	void disableLowerBound(void) { _LowerBoundEnabled = false; }
	
	// get the lower bound
	T getLowerBound(void) const { return _LowerBound; }

	// test wether the lower bound is excluded of the test
	bool isLowerBoundExcluded(void) const
	{
		return _LowerBoundExcluded;
	}

	/** validate a value against upper bound. (if an upper bound was set
	 *  \return NULL if ok or an error message
	 */
	const char *validateUpperBound(T v)
	{
		if (!_UpperBoundEnabled) return NULL;
		if (_UpperBoundExcluded && v < _UpperBound) return NULL;
		if (!_UpperBoundExcluded && v <= _UpperBound) return NULL;
		return "value too high";
	}

	
	/** validate a value against lower bound. (if an lower bound was set
	 *  \return NULL if ok or an error message
	 */
	const char *validateLowerBound(T v)
	{
		if (!_LowerBoundEnabled) return NULL;
		if (_LowerBoundExcluded && v > _LowerBound) return NULL;
		if (!_LowerBoundExcluded && v >= _LowerBound) return NULL;
		return "value too low";
	}

	/// copy this bound checker object to another one
	void duplicateBoundChecker(CBoundChecker<T> &dup)
	{
		dup._LowerBound				= _LowerBound;
		dup._LowerBoundEnabled		= _LowerBoundEnabled;
		dup._LowerBoundExcluded     = _LowerBoundExcluded;
		dup._UpperBound				= _UpperBound;
		dup._UpperBoundEnabled		= _UpperBoundEnabled;
		dup._UpperBoundExcluded     = _UpperBoundExcluded;
	}	
protected:

	bool _UpperBoundEnabled;
	bool _UpperBoundExcluded;
	T _UpperBound;

	bool _LowerBoundEnabled;
	bool _LowerBoundExcluded;
	T _LowerBound;
};


/// some typedefs
typedef CBoundChecker<float> CBoundCheckerFloat;
typedef CBoundChecker<uint32> CBoundCheckerUInt;
typedef CBoundChecker<sint32> CBoundCheckerInt;




#endif