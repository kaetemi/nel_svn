/** \file memory_manager.cpp
 * A new memory manager
 *
 * $Id: memory_manager.cpp,v 1.11 2005/05/16 09:12:34 distrib Exp $
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

#include "memory_common.h"
#include "../../include/nel/memory/memory_manager.h"
#include "heap_allocator.h"
#include <memory.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef NL_OS_WINDOWS
#include <windows.h>
#endif // NL_OS_WINDOWS

#undef new

// *********************************************************

// Exported functions

namespace NLMEMORY
{

// Global allocator
CHeapAllocator *GlobalHeapAllocator = NULL;
sint32			GlobalHeapAllocatorSystemAllocated = 0;

// *********************************************************

inline CHeapAllocator*	getGlobalHeapAllocator()
{
#ifndef NL_OS_WINDOWS
	// check GlobalHeapAllocator is allocated...
	if (GlobalHeapAllocator == NULL)
	{
		GlobalHeapAllocator = (CHeapAllocator*)malloc (sizeof (CHeapAllocator));
		new (GlobalHeapAllocator) CHeapAllocator (1024*1024*10, 1);
	}
#endif
	// under windows, NeL memory is used as a DLL, and global heap allocator is allocated in dll_main
	return GlobalHeapAllocator;
}

#ifndef NL_USE_DEFAULT_MEMORY_MANAGER

#ifdef NL_HEAP_ALLOCATION_NDEBUG

MEMORY_API void* MemoryAllocate (unsigned int size)
{
	return getGlobalHeapAllocator()->allocate (size);
}

MEMORY_API void* MemoryAllocateDebug (uint size, const char *filename, uint line, const char *category)
{
	return getGlobalHeapAllocator()->allocate (size);
}

#else // NL_HEAP_ALLOCATION_NDEBUG

MEMORY_API void* MemoryAllocate (unsigned int size)
{
	return getGlobalHeapAllocator()->allocate (size, "", 0, 0);
}

MEMORY_API void* MemoryAllocateDebug (uint size, const char *filename, uint line, const char *category)
{
	return getGlobalHeapAllocator()->allocate (size, filename, line, category);
}

#endif // NL_HEAP_ALLOCATION_NDEBUG

MEMORY_API unsigned int GetAllocatedMemory ()
{
	return getGlobalHeapAllocator()->getAllocatedMemory ();
}

// *********************************************************

MEMORY_API unsigned int GetFreeMemory ()
{
	return getGlobalHeapAllocator()->getFreeMemory ();
}

// *********************************************************

MEMORY_API unsigned int GetTotalMemoryUsed ()
{
	return getGlobalHeapAllocator()->getTotalMemoryUsed ();
}

// *********************************************************

MEMORY_API unsigned int GetDebugInfoSize ()
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return getGlobalHeapAllocator()->debugGetDebugInfoSize ();
#else // NL_HEAP_ALLOCATION_NDEBUG
	return 0;
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API unsigned int GetAllocatedMemoryByCategory (const char *category)
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return getGlobalHeapAllocator()->debugGetAllocatedMemoryByCategory (category);
#else // NL_HEAP_ALLOCATION_NDEBUG
	return 0;
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API bool StartAllocationLog (const char *filename, uint blockSize)
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return getGlobalHeapAllocator()->debugStartAllocationLog (filename, blockSize);
#else // NL_HEAP_ALLOCATION_NDEBUG
	return false;
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API bool EndAllocationLog ()
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return getGlobalHeapAllocator()->debugEndAllocationLog ();
#else // NL_HEAP_ALLOCATION_NDEBUG
	return false;
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API float GetFragmentationRatio ()
{
	return getGlobalHeapAllocator()->getFragmentationRatio ();
}

// *********************************************************

MEMORY_API unsigned int GetAllocatedSystemMemoryByAllocator ()
{
	return getGlobalHeapAllocator()->getAllocatedSystemMemoryByAllocator ();
}

// *********************************************************

MEMORY_API unsigned int GetAllocatedSystemMemory ()
{
	return getGlobalHeapAllocator()->getAllocatedSystemMemory ();
}

// *********************************************************

MEMORY_API unsigned int GetAllocatedSystemMemoryHook ()
{
	return GlobalHeapAllocatorSystemAllocated;
}

// *********************************************************

MEMORY_API bool CheckHeap (bool stopOnError)
{
	return getGlobalHeapAllocator()->checkHeap (stopOnError);
}

// *********************************************************

MEMORY_API bool			CheckHeapBySize (bool stopOnError, uint blockSize)
{
	return getGlobalHeapAllocator()->checkHeapBySize (stopOnError, blockSize);
}

// *********************************************************

MEMORY_API bool StatisticsReport (const char *filename, bool memoryDump)
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return getGlobalHeapAllocator()->debugStatisticsReport (filename, memoryDump);
#else // NL_HEAP_ALLOCATION_NDEBUG
	return false;
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API void	ReportMemoryLeak ()
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	getGlobalHeapAllocator()->debugReportMemoryLeak ();
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API void			AlwaysCheckMemory(bool alwaysCheck)
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	getGlobalHeapAllocator()->debugAlwaysCheckMemory (alwaysCheck);
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

// *********************************************************

MEMORY_API bool			IsAlwaysCheckMemory()
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return getGlobalHeapAllocator()->debugIsAlwaysCheckMemory ();
#endif // NL_HEAP_ALLOCATION_NDEBUG
	return false;
}

// *********************************************************

MEMORY_API void			SetOutOfMemoryHook (void (*outOfMemoryCallback)())
{
	getGlobalHeapAllocator()->setOutOfMemoryHook (outOfMemoryCallback);
}

// *********************************************************

MEMORY_API unsigned int GetBlockSize (void *pointer)
{
	return getGlobalHeapAllocator()->getBlockSize (pointer);
}

// *********************************************************

MEMORY_API const char * GetCategory (void *pointer)
{
	return getGlobalHeapAllocator()->getCategory (pointer);
}

// *********************************************************

MEMORY_API void MemoryDeallocate (void *p)
{
	getGlobalHeapAllocator()->free (p);
}

// *********************************************************

MEMORY_API NLMEMORY::CHeapAllocator* GetGlobalHeapAllocator ()
{
	return getGlobalHeapAllocator();
}

// *********************************************************

MEMORY_API void* NLMEMORY::MemoryReallocate (void *p, unsigned int size)
{
	// Get the block size
/*	uint oldSize = NLMEMORY::GetBlockSize (p);
	if (size > oldSize)
	{
		void *newPtr = MemoryAllocate (size);
		memcpy (newPtr, p, oldSize);
		MemoryDeallocate (p);
		p = newPtr;
	}
	return p;*/

	uint oldSize = NLMEMORY::GetBlockSize (p);
	
	void *newPtr = MemoryAllocate (size);
	memcpy (newPtr, p, (size<oldSize) ? size : oldSize);
	
	MemoryDeallocate (p);
	return newPtr;
	
}

// *********************************************************

#ifndef NL_HEAP_ALLOCATION_NDEBUG

// *********************************************************

// Class to report memory leak at exit
class CReportMemoryLeak 
{
public:
	~CReportMemoryLeak ()
	{
		// Report memory leak
		getGlobalHeapAllocator()->debugReportMemoryLeak ();
	}
};

// *********************************************************

// Singleton
CReportMemoryLeak	ReportMemoryLeakSingleton;

// *********************************************************

#endif // NL_HEAP_ALLOCATION_NDEBUG

#endif // NL_USE_DEFAULT_MEMORY_MANAGER

} // NLMEMORY

extern "C"
{

MEMORY_API void* NelMemoryAllocate (unsigned int size)
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return NLMEMORY::getGlobalHeapAllocator()->allocate (size, "", 0, 0);
#else // NL_HEAP_ALLOCATION_NDEBUG
	return NLMEMORY::getGlobalHeapAllocator()->allocate (size);
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

MEMORY_API void* NelMemoryAllocateDebug (uint size, const char *filename, uint line, const char *category)
{
#ifndef NL_HEAP_ALLOCATION_NDEBUG
	return NLMEMORY::getGlobalHeapAllocator()->allocate (size, filename, line, category);
#else // NL_HEAP_ALLOCATION_NDEBUG
	return NLMEMORY::getGlobalHeapAllocator()->allocate (size);
#endif // NL_HEAP_ALLOCATION_NDEBUG
}

MEMORY_API void NelMemoryDeallocate (void *pointer)
{
	NLMEMORY::getGlobalHeapAllocator()->free (pointer);
}

}

// *********************************************************

#ifndef NL_USE_DEFAULT_MEMORY_MANAGER

// Need a debug new ?
#ifdef NL_HEAP_ALLOCATION_NDEBUG

// *********************************************************

#undef new

#define new NL_NEW

#else // NL_HEAP_ALLOCATION_NDEBUG

// *********************************************************

NLMEMORY::CAllocContext::CAllocContext (const char* str)
{
	getGlobalHeapAllocator()->debugPushCategoryString (str);
}

// *********************************************************

NLMEMORY::CAllocContext::~CAllocContext ()
{
	getGlobalHeapAllocator()->debugPopCategoryString ();
}

// *********************************************************

#undef new

// *********************************************************

#define new NL_NEW

#endif // NL_HEAP_ALLOCATION_NDEBUG

// *********************************************************
#endif // NL_USE_DEFAULT_MEMORY_MANAGER
