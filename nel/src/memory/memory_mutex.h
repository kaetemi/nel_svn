/** \file memory_mutex.h
 * Mutex used by the memory manager
 *
 * $Id: memory_mutex.h,v 1.4 2004/06/07 16:52:00 corvazier Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_MEMORY_MUTEX_H
#define NL_MEMORY_MUTEX_H

#include "memory_common.h"

#ifdef NL_OS_WINDOWS
#include <windows.h>
#include <winbase.h>
#endif

#ifdef NL_OS_UNIX
#include <pthread.h> // PThread
#include <semaphore.h> // PThread POSIX semaphores
#endif

namespace NLMEMORY 
{

/**
 * Mutex used by the memory manager
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class CMemoryMutex
{
public:

#ifdef NL_OS_WINDOWS

	/// Constructor
	CMemoryMutex();

	__forceinline static bool atomic_swap (volatile uint32 *lockPtr)
	{
		uint32 result;
#ifdef NL_DEBUG_FAST
		// Workaround for dumb inlining bug (returning of function goes into the choux): push/pop registers
		__asm
		{
				push eax
				push ecx
			mov ecx,lockPtr
			mov eax,1
			xchg [ecx],eax
			mov [result],eax
				pop ecx
				pop eax
		}
#else
		__asm
		{
			mov ecx,lockPtr
			mov eax,1
			xchg [ecx],eax
			mov [result],eax
		}
#endif
		return result != 0;
	}

	__forceinline void enter ()
	{
		if (atomic_swap (&_Lock))
		{
			// First test
			uint i;
			for (i = 0 ;; ++i)
			{
				uint wait_time = i + 6;

				// Increment wait time with a log function
				if (wait_time > 27) 
					wait_time = 27;

				// Sleep
				if (wait_time <= 20) 
					wait_time = 0;
				else
					wait_time = 1 << (wait_time - 20);

				if (!atomic_swap (&_Lock))
					break;

				Sleep (wait_time);
			}
		}
	}

	__forceinline void leave ()
	{
		_Lock = 0;
	}

	volatile uint32 _Lock;

#else // NL_OS_WINDOWS

public:

	/// Constructor
	CMemoryMutex();

	/// Destructor
	~CMemoryMutex();

	void enter ();
	void leave ();

private:

	sem_t			_Sem;

#endif // NL_OS_WINDOWS

};


} // NLMEMORY


#endif // NL_MEMORY_MUTEX_H

/* End of memory_mutex.h */
