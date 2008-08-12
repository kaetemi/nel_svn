/** \file memory_mutex.cpp
 * Mutex used by the memory manager
 *
 * $Id: memory_mutex.cpp,v 1.4 2005/04/05 10:25:06 legros Exp $
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

#include "nel/memory/memory_manager.h"
#include "memory_mutex.h"


namespace NLMEMORY 
{

#ifdef NL_OS_WINDOWS

// *********************************************************

CMemoryMutex::CMemoryMutex ()
{
	_Lock = 0;
}

#else // NL_OS_WINDOWS

/*
 * Unix version
 */

// *********************************************************

CMemoryMutex::CMemoryMutex()
{
	sem_init( const_cast<sem_t*>(&_Sem), 0, 1 );
}

// *********************************************************

CMemoryMutex::~CMemoryMutex()
{
	sem_destroy( const_cast<sem_t*>(&_Sem) ); // needs that no thread is waiting on the semaphore
}

// *********************************************************

void CMemoryMutex::enter()
{
	sem_wait( const_cast<sem_t*>(&_Sem) );
}

// *********************************************************

void CMemoryMutex::leave()
{
	sem_post( const_cast<sem_t*>(&_Sem) );
}

// *********************************************************

#endif // NL_OS_WINDOWS

} // NLMEMORY
