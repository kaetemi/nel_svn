/** \file stdopenal.h
 * OpenAL precompiled header
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

#include <nel/misc/types_nl.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <exception>
#include <utility>
#include <deque>

#ifdef NL_OS_WINDOWS
#	define XRAM_AVAILABLE 1
#	define EFX_AVAILABLE 1
#	define EAX_AVAILABLE 0
#else
#	define XRAM_AVAILABLE 1
#	define EFX_AVAILABLE 0
#	define EAX_AVAILABLE 0
#endif

#include <AL/al.h>
#include <AL/alc.h>
// #if XRAM_AVAILABLE
// #	include <AL/xram.h>
typedef ALboolean (__cdecl *EAXSetBufferMode)(ALsizei n, ALuint *buffers, ALint value);
typedef ALenum (__cdecl *EAXGetBufferMode)(ALuint buffer, ALint *value);
// #endif
#if EAX_AVAILABLE
#	define OPENAL
#	ifdef NL_OS_WINDOWS
#		include <objbase.h>
#	endif
#	include <eax.h>
#endif
#if EFX_AVAILABLE
// #	include <AL/efx.h>
#	include <AL/EFX-Util.h>
#endif

#include <nel/misc/common.h>
#include <nel/misc/debug.h>
#include <nel/misc/vector.h>
#include <nel/misc/singleton.h>

#include "../sound_driver.h"
#include "../buffer.h"
#include "../source.h"
#include "../listener.h"

/* end of file */
