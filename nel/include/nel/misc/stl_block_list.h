/** \file stl_block_list.h
 * TODO: File description
 *
 * $Id: stl_block_list.h,v 1.5 2005/02/22 10:14:12 besson Exp $
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

#ifndef NL_STL_BLOCK_LIST_H
#define NL_STL_BLOCK_LIST_H

#include "types_nl.h"
#include "stl_block_allocator.h"
#include <list>


namespace NLMISC {


// ***************************************************************************
/**
 * This class is a list<> which use CSTLBlockAllocator
 *
 * You construct such a list like this:
 *	CSTLBlockList<uint>		myList(ptrOnBlockMemory);
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
/*
template <class T>
class CSTLBlockList : public std::list<T, CSTLBlockAllocator<T> >
{
public:

	typedef typename NLMISC::CSTLBlockList<T>::size_type TSizeType;
	typedef typename NLMISC::CSTLBlockList<T>::const_iterator TBlockListConstIt;

	explicit CSTLBlockList(CBlockMemory<T, false> *bm ) :
	std::list<T, CSTLBlockAllocator<T> >(CSTLBlockAllocator<T>(bm))
	{
	}

	explicit CSTLBlockList(TSizeType n, CBlockMemory<T, false> *bm ) :
	std::list<T, CSTLBlockAllocator<T> >(n,T(),CSTLBlockAllocator<T>(bm))
	{
	}

	explicit CSTLBlockList(TSizeType n, const T& v, CBlockMemory<T, false> *bm ) :
	std::list<T, CSTLBlockAllocator<T> >(n,v,CSTLBlockAllocator<T>(bm))
	{
	}


	CSTLBlockList(TBlockListConstIt first,TBlockListConstIt last, CBlockMemory<T, false> *bm ):
	std::list<T, CSTLBlockAllocator<T> >(first,last,CSTLBlockAllocator<T>(bm))
	{
	}
};
*/


} // NLMISC


#endif // NL_STL_BLOCK_LIST_H

/* End of stl_block_list.h */
