/** \file tds.cpp
 * Thread dependant storage class
 *
 * $Id: tds.cpp,v 1.5 2007/03/09 09:49:30 boucher Exp $
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

#include "stdmisc.h"

#include "nel/misc/tds.h"

#ifdef NL_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#endif // NL_OS_WINDOWS

namespace NLMISC 
{

// *********************************************************

CTDS::CTDS ()
{
	/* Please no assert in the constructor because it is called by the NeL memory allocator constructor */
#ifdef NL_OS_WINDOWS
	_Handle = TlsAlloc ();
	TlsSetValue (_Handle, NULL);
#else // NL_OS_WINDOWS
//	nldebug("CTDS::CTDS...");
	nlverify(pthread_key_create (&_Key, NULL) == 0);
//	nldebug("CTDS::CTDS : create a new key %u", _Key);
	pthread_setspecific(_Key, NULL);
#endif // NL_OS_WINDOWS
}

// *********************************************************

CTDS::~CTDS ()
{
#ifdef NL_OS_WINDOWS
	nlverify (TlsFree (_Handle) != 0);
#else // NL_OS_WINDOWS
//	nldebug("CTDS::~CTDS : deleting key %u", _Key);
	nlverify (pthread_key_delete (_Key) == 0);
#endif // NL_OS_WINDOWS
}

// *********************************************************

void *CTDS::getPointer () const
{
#ifdef NL_OS_WINDOWS
	return TlsGetValue (_Handle);
#else // NL_OS_WINDOWS
//	nldebug("CTDS::getPointer for key %u...", _Key);
	void *ret = pthread_getspecific (_Key);
//	nldebug("CTDS::getPointer returing value %p", ret);
	return ret; 
#endif // NL_OS_WINDOWS
}

// *********************************************************

void CTDS::setPointer (void* pointer)
{
#ifdef NL_OS_WINDOWS
	nlverify (TlsSetValue (_Handle, pointer) != 0);
#else // NL_OS_WINDOWS
//	nldebug("CTDS::setPointer for key %u to value %p", _Key, pointer);
	nlverify (pthread_setspecific (_Key, pointer) == 0);
#endif // NL_OS_WINDOWS
}

// *********************************************************

} // NLMISC
