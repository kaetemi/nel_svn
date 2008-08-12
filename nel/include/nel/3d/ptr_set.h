/** \file ptr_set.h
 * TODO: File description
 *
 * $Id: ptr_set.h,v 1.3 2004/11/15 10:24:47 lecroart Exp $
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

#ifndef NL_PTR_SET_H
#define NL_PTR_SET_H

#include "nel/misc/types_nl.h"
#include <set>


namespace NL3D
{


// ***************************************************************************
/**
 * This is a Tool class. A ptr set is simply a set of object Pointer, with simple insert/erase/clear.
 * The allocation is made at insertion by client, but deletion is automatically done by erase/clear.
 * You got public acces to the STL set, so be aware of what you do!!
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
template<class T>	class CPtrSet
{
public:
	std::set<T*>	Set;

public:

	/// \name Object
	// @{
	CPtrSet() {}
	~CPtrSet() {clear();}
	// @}

	/// \name insertion/deletion.
	// @{
	/** insert a new element to the set. You should pass a conventionnal allocated object.
	 * For simplicity, return newObject!!!
	 */
	T				*insert(T *newObject)
	{
		Set.insert(newObject);
		return newObject;
	}
	/** erase an element from the set. nlerror(errorString) if not found!! NO OP if NULL.
	 * For simplicity, return newObject!!!
	 */
	void			erase(T *objectToRemove, const char *errorString= "Object do not exist in the set")
	{
		if(!objectToRemove)
			return;
		if(Set.erase(objectToRemove)!=1)
			nlerror(errorString);
		else
			delete objectToRemove;
	}
	/** Delete all element from the set, and clear the set
	 */
	void			clear()
	{
		typename std::set<T*>::iterator it;
		for(it= Set.begin();it!=Set.end();it++)
		{
			delete *it;
		}

		Set.clear();
	}

	// @}

};


} // NL3D


#endif // NL_PTR_SET_H

/* End of ptr_set.h */
