/** \file object_arena_allocator.h
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

#ifndef NL_OBJECT_ARENA_ALLOCATOR_H
#define NL_OBJECT_ARENA_ALLOCATOR_H

#include "singleton.h"

namespace NLMISC
{


class CFixedSizeAllocator;

/** An allocator that can allocate/release in O(1) for a finite number of possible blocks size (usually small)..
  * For a given block size, a fixed size allocator is used.
  * One possible use is with a family of class for which new and delete have been redefined at the top of the hierarchy  
  * (which the NL_USES_DEFAULT_ARENA_OBJECT_ALLOCATOR macro does)
  *
  * \author Nicolas Vizerie
  * \author Nevrax France
  * \date 2004
  */
class CObjectArenaAllocator
{
public:
	/** ctor
	  * \param maxAllocSize maximum intended size of allocation.	  
	  */
	CObjectArenaAllocator(uint maxAllocSize, uint granularity = 4);
	// dtor
	~CObjectArenaAllocator();	
	/** Allocate a block with the given size. 0 is an invalid size an will cause an assert.
	  * If the size is > to the max size given at init, the allocation will succeed, but will use the standard allocator.
	  */
	void *alloc(uint size);
	// free an object that has previously been allocated with alloc. size should be remembered by the caller.
	void free(void *);
	// get the number of allocated objects
	uint getNumAllocatedBlocks() const;
#	ifdef NL_DEBUG
		// for debug, useful to catch memory leaks
		void dumpUnreleasedBlocks();
		// set a break for the given allocation
		void setBreakForAllocID(bool enabled, uint id);
#	endif
	// for convenience, a default allocator is available
	static CObjectArenaAllocator &getDefaultAllocator();	

private:
	std::vector<CFixedSizeAllocator *> _ObjectSizeToAllocator;
	uint							 _MaxAllocSize;
	uint							 _Granularity;
#	ifdef NL_DEBUG
		uint							 _AllocID;	
		std::map<void *, uint>			 _MemBlockToAllocID;
		bool							 _WantBreakOnAlloc;
		uint							 _BreakAllocID;
#	endif
	static CObjectArenaAllocator		 *_DefaultAllocator;
};

// Macro that redefines the new & delete operator of a class so that the default arena object allocator is used.
// This should be used inside the definition of the class.
// All derived class will use the same allocator, so this definition can be used only at the top of the hierarchy of class for
// which it is of interest.
//
// NL_USES_DEFAULT_ARENA_OBJECT_ALLOCATOR // for fast alloc
#	define NL_USES_DEFAULT_ARENA_OBJECT_ALLOCATOR \
		void *operator new(size_t size) { return NLMISC::CObjectArenaAllocator::getDefaultAllocator().alloc((uint) size); }\
		void operator delete(void *block) { NLMISC::CObjectArenaAllocator::getDefaultAllocator().free(block); }

}

#endif
