/** \file memory_common.h
 * Common definition for memory project
 *
 * $Id: memory_common.h,v 1.5 2005/01/31 13:52:39 lecroart Exp $
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

#ifndef NL_MEMORY_COMMON_H
#define NL_MEMORY_COMMON_H

#include "nel/memory/memory_config.h"

#ifndef MEMORY_API
#ifdef MEMORY_EXPORTS
#define MEMORY_API __declspec(dllexport)
#else
#define MEMORY_API __declspec(dllimport)
#endif
#endif

// Do not force MSVC library name
#define _STLP_DONT_FORCE_MSVC_LIB_NAME

#include <cassert>

// Operating systems definition

#ifdef WIN32
#  define NL_OS_WINDOWS
#  define NL_LITTLE_ENDIAN
#  define NL_CPU_INTEL
#  ifdef _DEBUG
#    define NL_DEBUG
#    define _STLP_USE_DEBUG_LIB		// we have to put this to include the stlport_debug.lib instead of stlport.lib
#  else
#    define NL_RELEASE
#  endif
#else
#  define NL_OS_UNIX
#  ifdef WORDS_BIGENDIAN
#    define NL_BIG_ENDIAN
#  else
#    define NL_LITTLE_ENDIAN
#  endif
#endif

// Remove stupid Visual C++ warning

#ifdef NL_OS_WINDOWS
#  pragma warning (disable : 4503)			// STL: Decorated name length exceeded, name was truncated
#  pragma warning (disable : 4786)			// STL: too long indentifier
#  pragma warning (disable : 4290)			// throw() not implemented warning
#  pragma warning (disable : 4250)			// inherits via dominance (informational warning).
#endif // NL_OS_UNIX

#ifdef NL_OS_WINDOWS

typedef	signed		__int8		sint8;
typedef	unsigned	__int8		uint8;
typedef	signed		__int16		sint16;
typedef	unsigned	__int16		uint16;
typedef	signed		__int32		sint32;
typedef	unsigned	__int32		uint32;
typedef	signed		__int64		sint64;
typedef	unsigned	__int64		uint64;

typedef	signed		int			sint;			// at least 32bits (depend of processor)
typedef	unsigned	int			uint;			// at least 32bits (depend of processor)

#define	NL_I64	\
		"I64"

#elif defined (NL_OS_UNIX)

#include <sys/types.h>

typedef	int8_t		sint8;
typedef	u_int8_t	uint8;
typedef	int16_t		sint16;
typedef	u_int16_t	uint16;
typedef	int32_t		sint32;
typedef	u_int32_t	uint32;
typedef	int64_t		sint64;
typedef	u_int64_t	uint64;

typedef	signed		int			sint;			// at least 32bits (depend of processor)
typedef	unsigned	int			uint;			// at least 32bits (depend of processor)

#define	NL_I64	\
		"ll"

#endif // NL_OS_UNIX

#define memory_assert assert

#endif // NL_MEMORY_COMMON_H

/* End of memory_mutex.h */
