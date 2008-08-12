/** \file historic.h
 *
 * $Id: historic.h,v 1.2 2006/05/31 12:03:13 boucher Exp $
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

#ifndef NL_HISTORIC_H
#define NL_HISTORIC_H

#include "nel/misc/types_nl.h"
#include <deque>

namespace NLMISC
{

/** An historic with user defined size.
  * An historic is just a fifo with constraint on size  
  *
  * \author Nicolas Vizerie
  * \author Nevrax France
  * \date 2004  
  */
template <class T>
class CHistoric
{
public:
	CHistoric(uint maxSize = 0) : _MaxSize(maxSize) {}
	// Add a value at end of historic. If historic is full then the oldest entry is removed
	inline void		push(const T &value);
	// Pop the value at the end of jistoric
	inline void		pop();
	// Return true is there are no values in the historics.
	bool			empty() const { return _Historic.empty(); }
	// Get max number of entries in the historic.
	uint			getMaxSize() const { return _MaxSize; }
	// Set number of entries in the historic. Oldest entries are removed
	inline void		setMaxSize(uint maxSize);
	// Get current size of historic
	uint			getSize() const { return _Historic.size(); }
	// Access to an element in history, 0 being the oldest, size - 1 being the lastest added element
	const T		   &operator[](uint index) const { return _Historic[index]; /* let STL do out of range check */ }
	// Clear historic
	void			clear() { _Historic.clear(); }	
private:
	std::deque<T> _Historic;
	uint		  _MaxSize;
};


////////////////////
// IMPLEMENTATION //
////////////////////

//****************************************************************************************************
template <class T>
inline void	CHistoric<T>::push(const T &value)
{
	nlassert(_Historic.size() <= _MaxSize);
	if (_MaxSize == 0) return; 
	if (getSize() == _MaxSize)
	{
		_Historic.pop_front();	
	}
	_Historic.push_back(value);
}

//****************************************************************************************************
template <class T>
inline void	CHistoric<T>::pop()
{
	nlassert(!_Historic.empty());	
	_Historic.pop_back();
}

//****************************************************************************************************
template <class T>
inline void	CHistoric<T>::setMaxSize(uint maxSize)
{
	if (maxSize < getSize())
	{
		uint toRemove = std::min(getSize() - maxSize, getSize());
		_Historic.erase(_Historic.begin(), _Historic.begin() + toRemove);
	}
	_MaxSize = maxSize;
}

}


#endif
