/** \file stdfmod.h
 * FMod precompiled header
 */

/* Copyright, 2004 Nevrax Ltd.
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

#ifdef NL_OS_WINDOWS
#	pragma include_alias(<fmod.h>, <fmod3\fmod.h>)
#endif
#include <fmod.h>

#include <nel/misc/common.h>
#include <nel/misc/time_nl.h>
#include <nel/misc/singleton.h>
#include <nel/misc/fast_mem.h>
#include <nel/misc/debug.h>
#include <nel/misc/vector.h>

#include "../sound_driver.h"
#include "../buffer.h"
#include "../source.h"
#include "../listener.h"

/* end of file */
