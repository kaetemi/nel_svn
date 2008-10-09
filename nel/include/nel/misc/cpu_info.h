/** \file cpu_info.h
 * TODO: File description
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_CPU_INFO_H
#define NL_CPU_INFO_H

#include "types_nl.h"


namespace NLMISC {


/**
 * This helps to know whether cpu has some features such as mmx, sse ...
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2001
 */
struct CCpuInfo___
{
	/** test whether the cpuid instruction is supported
	  * (always false on non intel architectures)
	  */
	static bool hasCPUID(void);

	/** helps to know whether the processor features mmx instruction set
	  * This is initialized at startup, so it's fast
	  * (always false on not 0x86 architecture ...)
	  */
	static bool hasMMX(void);

	/** helps to know whether the processor has streaming SIMD instructions (the OS must support it)
	  * This is initialized at startup, so it's fast
	  * (always false on not 0x86 architecture ...)
	  */
	static bool hasSSE(void);
};


} // NLMISC


#endif // NL_CPU_INFO_H

/* End of cpu_info.h */
