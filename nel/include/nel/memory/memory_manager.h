/** \file memory_manager.h
 * A new memory manager
 *
 * $Id: memory_manager.h,v 1.25 2007/03/09 09:49:29 boucher Exp $
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

#ifndef NL_MEMORY_MANAGER_H
#define NL_MEMORY_MANAGER_H

#include "nel/misc/types_nl.h"

// CONFIGURATION
#include "nel/memory/memory_config.h"

/*	Doc:
	----

	// Allocate memory
	void*		MemoryAllocate (unsigned int size);

	// Allocate debug memory : specify a filename, the line and the category of allocation (7 letters max)
	void*		MemoryAllocateDebug (unsigned int size, const char *filename, unsigned int line, const char *category);

	// Deallocation
	void		MemoryDeallocate (void *p);

	// Returns the amount of allocated memory
	// Works only with nel memory allocator
	unsigned int GetAllocatedMemory ();

	// Returns the amount of free memory inside the allocator. This is not the amount of free system memory.
	// Works only with nel memory allocator
	unsigned int GetFreeMemory ();

	// Returns the total of memory used by the allocator
	// Works only with nel memory allocator
	unsigned int GetTotalMemoryUsed ();

	// Returns the amount of memory used by debug purpose
	// Works only with nel memory allocator
	unsigned int GetDebugInfoSize ();

	// Returns the amount of memory used by a category
	// Works only with nel memory allocator with debug features activated
	unsigned int GetAllocatedMemoryByCategory (const char *category);

	// Returns the size of a memory block
	// Works only with nel memory allocator
	unsigned int GetBlockSize (void *pointer);

	// Returns the fragentation ratio. 0 : no fragmentation, 1 : heavy fragmentation
	// Works only with nel memory allocator
	float		GetFragmentationRatio ();

	// Returns the amount of system memory allocated by the allocator tracing the process heap
	// Works only with nel memory allocator
	unsigned int GetAllocatedSystemMemoryByAllocator ();

	// Returns the amount of system memory allocated tracing the process heap
	// Works only with nel memory allocator
	unsigned int GetAllocatedSystemMemory ();
	
	// Get the amount of system memory allocated since the dll as been loaded. Use memory hook, available only in _DEBUG mode.
	// Works only with nel memory allocator
	unsigned int GetAllocatedSystemMemoryHook ();
	  
	// Check the heap
	bool		CheckHeap (bool stopOnError);
	  
	// Check block by size
	// Works only with nel memory allocator with debug features activated
	bool		CheckHeapBySize (bool stopOnError, unsigned int blockSize);

	// Make a statistic report
	// Works only with nel memory allocator with debug features activated
	bool		StatisticsReport (const char *filename, bool memoryDump);

	// Report memory leaks in debug window
	// Works with standard memory allocator in _DEBUG and with nel memory allocator with debug features activated
	bool		ReportMemoryLeak ();

	// Set the flag to check memory at each allocation / deallocation (warning, very slow)
	// Works with standard memory allocator in _DEBUG and with nel memory allocator with debug features activated
	void		AlwaysCheckMemory(bool alwaysCheck);

	// Get the flag
	// Works with standard memory allocator in _DEBUG and with nel memory allocator with debug features activated
	bool		IsAlwaysCheckMemory();

	// Set a out of memory callback
	// Works only with nel memory allocator
	void		SetOutOfMemoryHook(void (*outOfMemoryCallback)());

	 * Start/End the memory allocation loging
	 * Works only with nel memory allocator with debug features activated
	 * blockSize is the size of the block to log
	 *
	 * Log format : 
	 * 4 bytes : uint32 size of the logged blocks.
	 * n bytes : log entries
	 *
	 * Log entry format :
	 * 4 bytes : start address of the bloc data
	 * \0 terminated string : context where the bloc has been allocated
	 *
	bool		StartAllocationLog (const char *filename, uint blockSize);
	bool		EndAllocationLog ();
*/

// Memory debug for windows
#ifdef WIN32
#include <crtdbg.h>
#endif // WIN32

#undef MEMORY_API
#ifdef MEMORY_EXPORTS
 #ifdef WIN32
  #define MEMORY_API __declspec(dllexport)
 #else 
  #define MEMORY_API
 #endif // WIN32
#else
 #ifdef WIN32
  #define MEMORY_API __declspec(dllimport)
 #else 
  #define MEMORY_API
 #endif // WIN32
#endif

#ifdef __cplusplus

/* Define this to use the default memory allocator for new, delete and STL allocator. It is defined only if _STLP_USE_NEL
 * is not defined in the STlport site config file "stl/_site_config.h". To use the NeL memory manager, you need a modified 
 * version of STLport */

/* To active Nel allocator in STLport, add the following code at the end of "stl/_site_cfg.h" and rebuild STLPort */

#define NL_USE_DEFAULT_MEMORY_MANAGER

// *********************************************************
#ifdef NL_USE_DEFAULT_MEMORY_MANAGER
// *********************************************************

// Malloc
#include <malloc.h>

#ifdef NL_OS_UNIX
#include <new>
#endif // NL_OS_UNIX

namespace NLMEMORY
{

inline void*		MemoryAllocate (unsigned int size) {return malloc(size);}
inline void*		MemoryAllocateDebug (unsigned int size, const char *filename, unsigned int line, const char *category)
{
#ifdef WIN32
	return _malloc_dbg(size, _NORMAL_BLOCK, filename, line);
#else // WIN32
	return malloc(size);
#endif // WIN32
}
inline void			MemoryDeallocate (void *p)
{
	free(p);
}
inline void*		MemoryReallocate (void *p, unsigned int size) {return realloc(p, size);}
inline unsigned int GetAllocatedMemory () { return 0;}
inline unsigned int GetFreeMemory () { return 0;}
inline unsigned int GetTotalMemoryUsed () { return 0;}
inline unsigned int GetDebugInfoSize () { return 0;}
inline unsigned int GetAllocatedMemoryByCategory (const char *category) { return 0;}
inline bool			StartAllocationLog (const char *category, unsigned int blockSize) { return false;}
inline bool			EndAllocationLog () { return false;}
inline unsigned int GetBlockSize (void *pointer) { return 0;}
inline bool			CheckHeapBySize (bool stopOnError, unsigned int blockSize) { return true; }
inline const char * GetCategory (void *pointer) { return 0; }
inline float		GetFragmentationRatio () { return 0.0f;}
inline unsigned int GetAllocatedSystemMemoryByAllocator () { return 0;}
inline unsigned int GetAllocatedSystemMemory () { return 0;}
inline unsigned int GetAllocatedSystemMemoryHook () { return 0; }
inline void			ReportMemoryLeak() 
{
#ifdef WIN32
	_CrtDumpMemoryLeaks();
#endif // WIN32
}
inline bool			CheckHeap (bool stopOnError) 
{ 
#ifdef WIN32
	if (!_CrtCheckMemory())
	{
		if (stopOnError)
			// ***************
			// Invalide heap !
			// ***************
			_ASSERT(0);
		return false;
	}
#endif // WIN32
	return true;
}
inline void			AlwaysCheckMemory(bool alwaysCheck)
{
#ifdef WIN32
	int previous = _CrtSetDbgFlag (0);
	_CrtSetDbgFlag (alwaysCheck?(previous|_CRTDBG_CHECK_ALWAYS_DF):(previous&(~_CRTDBG_CHECK_ALWAYS_DF)));
#endif // WIN32
}
inline bool			IsAlwaysCheckMemory()
{
#ifdef WIN32
	int previous = _CrtSetDbgFlag (0);
	_CrtSetDbgFlag (previous);
	return (previous&_CRTDBG_CHECK_ALWAYS_DF) != 0;
#else // WIN32
	return false;
#endif // WIN32
}
inline bool			StatisticsReport (const char *filename, bool memoryDump) { return true; }
inline void			SetOutOfMemoryHook (void (*outOfMemoryCallback)()) { }

}

// *********************************************************
#else // NL_USE_DEFAULT_MEMORY_MANAGER
// *********************************************************

namespace NLMEMORY
{

MEMORY_API void*		MemoryAllocate (unsigned int size);
MEMORY_API void*		MemoryAllocateDebug (unsigned int size, const char *filename, unsigned int line, const char *category);
MEMORY_API void*		MemoryReallocate (void *p, unsigned int size);
MEMORY_API void			MemoryDeallocate (void *p);
MEMORY_API unsigned int GetAllocatedMemory ();
MEMORY_API unsigned int GetFreeMemory ();
MEMORY_API unsigned int GetTotalMemoryUsed ();
MEMORY_API unsigned int GetDebugInfoSize ();
MEMORY_API unsigned int GetAllocatedMemoryByCategory (const char *category);
MEMORY_API unsigned int GetBlockSize (void *pointer);
MEMORY_API const char * GetCategory (void *pointer);
MEMORY_API float		GetFragmentationRatio ();
MEMORY_API unsigned int GetAllocatedSystemMemoryByAllocator ();
MEMORY_API unsigned int GetAllocatedSystemMemory ();
MEMORY_API unsigned int GetAllocatedSystemMemoryHook ();
MEMORY_API bool			CheckHeap (bool stopOnError);
MEMORY_API bool			CheckHeapBySize (bool stopOnError, unsigned int blockSize);
MEMORY_API bool			StatisticsReport (const char *filename, bool memoryDump);
MEMORY_API void			ReportMemoryLeak ();
MEMORY_API void			AlwaysCheckMemory(bool alwaysCheck);
MEMORY_API bool			IsAlwaysCheckMemory();
MEMORY_API void			SetOutOfMemoryHook (void (*outOfMemoryCallback)());
MEMORY_API bool			StartAllocationLog (const char *category, unsigned int blockSize);
MEMORY_API bool			EndAllocationLog ();

 /* Allocation context
 */
 class CAllocContext
 {
 public:
	 MEMORY_API CAllocContext::CAllocContext (const char* str);
	 MEMORY_API CAllocContext::~CAllocContext ();
 };
}

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	MEMORY_API void*		NelMemoryAllocate (unsigned int size);
	MEMORY_API void*		NelMemoryAllocateDebug (unsigned int size, const char *filename, unsigned int line, const char *category);
	MEMORY_API void			NelMemoryDeallocate (void *pointer);

#ifdef __cplusplus
}
#endif // __cplusplus

// *********************************************************
#endif // NL_USE_DEFAULT_MEMORY_MANAGER
// *********************************************************

// *********************************************************
// New operators
// *********************************************************

#ifndef NL_USE_DEFAULT_MEMORY_MANAGER

#ifdef NL_OS_UNIX
#include <new>
#define NL_MEMORY_THROW_BAD_ALLOC throw (std::bad_alloc)
#define NL_MEMORY_THROW throw ()
#else
#define NL_MEMORY_THROW_BAD_ALLOC
#define NL_MEMORY_THROW
#endif

inline void* operator new(unsigned int size, const char *filename, int line)
{
	return NLMEMORY::MemoryAllocateDebug (size, filename, line, 0);
}

// *********************************************************

inline void* operator new(unsigned int size) NL_MEMORY_THROW_BAD_ALLOC
{
	return NLMEMORY::MemoryAllocateDebug (size, "::new (unsigned int size) operator", 0, 0);
}

// *********************************************************

inline void* operator new[](unsigned int size, const char *filename, int line)
{
	return NLMEMORY::MemoryAllocateDebug (size, filename, line, 0);
}

// *********************************************************

inline void* operator new[](unsigned int size) NL_MEMORY_THROW_BAD_ALLOC
{
	return NLMEMORY::MemoryAllocateDebug (size, "::new (unsigned int size) operator", 0, 0);
}

// *********************************************************

inline void operator delete(void* p) NL_MEMORY_THROW
{
	NLMEMORY::MemoryDeallocate (p);
}

// *********************************************************

inline void operator delete(void* p, const char *filename, int line)
{
	NLMEMORY::MemoryDeallocate (p);
}

// *********************************************************

inline void operator delete[](void* p) NL_MEMORY_THROW
{
	NLMEMORY::MemoryDeallocate (p);
}

// *********************************************************

inline void operator delete[](void* p, const char *filename, int line)
{
	NLMEMORY::MemoryDeallocate (p);
}

#endif // NL_USE_DEFAULT_MEMORY_MANAGER

// *********************************************************
// Macros
// *********************************************************

/* New operator in debug mode
 * Doesn't work with placement new. To do a placement new, undef new, make your placement new, and redefine new with the macro NL_NEW */


#if !defined (NL_USE_DEFAULT_MEMORY_MANAGER) && !defined (NL_NO_DEFINE_NEW)
	#define NL_NEW new(__FILE__, __LINE__)
	#define new NL_NEW
#else
	#define NL_NEW new
#endif


// Use allocation context ?
#define NL_ALLOC_CONTEXT(str) ((void)0);

#ifndef NL_USE_DEFAULT_MEMORY_MANAGER
 #ifndef NL_HEAP_ALLOCATION_NDEBUG
  #undef NL_ALLOC_CONTEXT
  #define NL_ALLOC_CONTEXT(__name) NLMEMORY::CAllocContext _##__name##MemAllocContext##__name (#__name);
 #endif // NL_HEAP_ALLOCATION_NDEBUG
#endif // NL_USE_DEFAULT_MEMORY_MANAGER


namespace NLMEMORY
{
	class CHeapAllocator;
};

#endif // __cplusplus

#endif // NL_MEMORY_MANAGER_H
