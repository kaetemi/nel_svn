/** \file range_manager.h
 * the range manager helps to store user defined preference in an CEditableRange dialog
 *
 * $Id: range_manager.h,v 1.5 2001/09/12 13:34:52 vizerie Exp $
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

#ifndef RANGE_MANAGER_H
#define RANGE_MANAGER_H

#include <map>
#include <string>

#include "nel/misc/stream.h"

/** This class records the ranges used for edition (for a given slider).
 *  It enables the user to set the range that match best what he wants
 *  full ASCII names are used as identifier
 */

template <class T> class CRangeManager
{
public:
	/** retrieve the range used for a given ID.
	 *  If the ID wasn't present, a new entry is created, and the given values are returned
	 */
	static std::pair<T, T> GetRange(const std::string &id, const T &minRange, const T &maxRange)
	{
		nlassert(id != "");
		if (_RangeMap.count(id) == 0) // not present yet ?
		{
			_RangeMap[id] = std::pair<T, T>(minRange, maxRange);			
		}
		return _RangeMap[id];
	}

	/** the same but no default values are provided. An assertion  occurs if not present.
	 *  In release build, the entrie is created, but with uninitialized values ...
	 */
	
	static std::pair<T, T> GetRange(const std::string &id)
	{
		nlassert(id != "");
		return _RangeMap[id];
	}

	/// set a new value for the given range

	static void SetRange(const std::string &id, const T &minRange, const T &maxRange)
	{
		nlassert(id != "");
		_RangeMap[id] = std::pair<T, T>(minRange, maxRange);	
	}

	/// serialization
	static void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		uint32 size;		
		if (!f.isReading())
		{
			size = _RangeMap.size();
			f.serial(size);
			for (TRangeMap::const_iterator it = _RangeMap.begin(); it != _RangeMap.end(); ++it)
			{	
				std::string s = it->first;
				f.serial(s);
				std::pair<T , T> value = it->second;
				f.serial(value.first);
				f.serial(value.second);
			}
		}
		else
		{
			_RangeMap.clear();
			f.serial(size);
			while (size --)
			{
				std::string id;
				std::pair<T , T> value;
				f.serial(id);
				f.serial(value.first);
				f.serial(value.second);
				_RangeMap[id] = value;
			}
		}
	}

	typedef std::map< std::string, std::pair<T, T> > TRangeMap;

protected:
	
	// the map that contains the ID, and their range values
	static TRangeMap _RangeMap;
	
};




#endif
