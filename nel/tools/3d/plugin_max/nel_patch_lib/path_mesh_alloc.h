/** \file path_mesh_alloc.h
 * TODO: File description
 *
 * $Id: path_mesh_alloc.h,v 1.3 2004/11/15 10:25:11 lecroart Exp $
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

#ifndef NL_PATH_MESH_ALLOC_H
#define NL_PATH_MESH_ALLOC_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"
#include <vector>
#include <list>

template <class T>
class CArrayElement : public NLMISC::CRefCount
{
public:
	CArrayElement (uint defaultSize)
	{
		_Array.reserve (defaultSize);
		_Allocated=false;
	}
	bool									_Allocated;
	std::vector<T>							_Array;
};

/**
 * TODO Class description
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
template <class T>
class CPathMeshAlloc
{
public:

	/// Constructor
	CPathMeshAlloc(uint defaultSize)
	{
		_DefaultSize=defaultSize;
		_BlockAllocated=0;
	}

	// Allocate a vector
	std::vector<T>* allocate ()
	{
		_BlockAllocated++;

		// Some trace
		nldebug ("Allocate, %d blocks %d max\n", _BlockAllocated, _ArrayList.size());

		// Look for a free element
		ListArray::iterator	ite=_ArrayList.begin();

		// for each element
		while (ite!=_ArrayList.end())
		{
			// Find one ?
			if (!((*ite)->_Allocated))
			{
				(*ite)->_Allocated=true;
				return &((*ite)->_Array);
			}
			ite++;
		}

		// ** Not find, add an entry
		
		// Create
		CArrayElement<T>	*pElement=new CArrayElement<T> (_DefaultSize);

		// Push back the enrty
		_ArrayList.push_back (NLMISC::CSmartPtr<CArrayElement<T> > (pElement));
		ite=_ArrayList.end();
		ite--;
		(*ite)->_Allocated=true;
		return &((*ite)->_Array);
	}

	// Free a vector
	void free (std::vector<T>* ptr)
	{
		_BlockAllocated--;

		// Some trace
		nldebug ("Allocate, %d blocks %d max\n", _BlockAllocated, _ArrayList.size());

		// Look for the good array
		ListArray::iterator	ite=_ArrayList.begin();

		// for each element
		while (ite!=_ArrayList.end())
		{
			// Find one ?
			if (&((*ite)->_Array)==ptr)
			{
				(*ite)->_Allocated=false;
				return;
			}
			ite++;
		}

		// No, should be somewhere
		nlassert (0);		// no!
	}

private:
	// Typedef 
typedef std::list< NLMISC::CSmartPtr<CArrayElement<T> > > ListArray;

	uint										_DefaultSize;
	uint										_BlockAllocated;
	ListArray									_ArrayList;
};

#endif // NL_PATH_MESH_ALLOC_H

/* End of path_mesh_alloc.h */
