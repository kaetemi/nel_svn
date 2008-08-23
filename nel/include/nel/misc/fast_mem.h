/** \file fast_mem.h
 * Fast memory copy and precache
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

#ifndef NL_FAST_MEM_H
#define NL_FAST_MEM_H

#include "types_nl.h"


namespace NLMISC
{

//typedef void  *memcpyptr(void *dts, const void *src, size_t nbytes);

/**
 * Functions for Fast Memory manipulation with Pentium-class processors.
 * From http://www.sgi.com/developers/technology/irix/resources/asc_cpu.html
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CFastMem
{
public:

	/**
	 *	This is a function pointer that points on the best memcpy function available depending of the OS and proc.
	 *  In the best case, it will use memcpySSE(), and in worst case, it'll use the libc memcpy()
	 *  Simply use it this way: CFastMem::memcpy(dst, src, size);
	 */
	static void  *(*memcpy)(void *dts, const void *src, size_t nbytes);

	/**
	 *	Fast precaching of memory in L1 cache using SSE or MMX where available 
	 *	(NB: others methods don't do the test)
	 *	nbytes should not override 4K
	 */
	static void		precache(const void *src, uint nbytes);

	/////////////////////////////////////////////

	/**
	 *	Fast memcpy using SSE instructions: prefetchnta and movntq. Can be called only if SSE and MMX is supported
	 *	NB: Copy per block of 4K through L1 cache
	 *	Result is typically 420 Mo/s instead of 150 Mo/s.
	 */
	static void		*memcpySSE(void *dst, const void *src, size_t nbytes);

	/**
	 *	Fast precaching of memory in L1 cache using MMX/SSE instructions: movq and prefetchnta
	 *	Result is typically 880 Mo/s (surely slower because of overhead).
	 *	nbytes should not override 4K
	 */
	static void		precacheSSE(const void *src, uint nbytes);

	/**
	 *	Fast precaching of memory in L1 cache using MMX instructions only: movq 
	 *	Result is typically 720 Mo/s (surely slower because of overhead).
	 *	Hence prefer precacheSSE() when available.
	 *	nbytes should not override 4K
	 */
	static void		precacheMMX(const void *src, uint nbytes);
};


} // NLMISC


#endif // NL_FAST_MEM_H

/* End of fast_mem.h */
