/** \file system_info.h
 * Retrieves system information (OS, processor, memory, etc...)
 *
 * $Id: system_info.h,v 1.16 2006/01/10 17:38:46 boucher Exp $
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

#ifndef NL_SYSTEM_INFO_H
#define NL_SYSTEM_INFO_H

#include "types_nl.h"

#include <string>

namespace NLMISC {


/**
 * TODO Class description
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2000
 */
class CSystemInfo
{
public:

	static std::string getOS ();
	static std::string getProc ();

	/** Gives an evalutation of the processor frequency, in hertz
	  * \param quick true to do quick frequency evaluation
	  * \warning Supports only intel architectures for now. Returns 0 if not implemented.
	  */
	static uint64 getProcessorFrequency (bool quick = false);

	/** test wether the cpuid instruction is supported
	  * (always false on non intel architectures)
	  */
	static bool hasCPUID ();

	/** helps to know wether the processor features mmx instruction set 
	  * This is initialized at started, so its fast
	  * (always false on non 0x86 architecture ...)
	  */	  
	static bool hasMMX () {return _HaveMMX;}

	/** helps to know wether the processor has streaming SIMD instructions (the OS must supports it)
	  * This is initialized at started, so its fast
	  * (always false on non 0x86 architecture ...)
	  */
	static bool hasSSE () {return _HaveSSE;}

	/** get the CPUID (if available). Usefull for debug info
	 */
	static uint32 getCPUID();

	/** true if the Processor has HyperThreading
	 */
	static bool hasHyperThreading();
	
	/** true if running under NT
	 */
	static bool isNT();

	/* returns the space left on the hard drive that contains the filename
	 */
	static std::string availableHDSpace (const std::string &filename);

	/** returns all the physical memory available on this computer
	  */
	static uint32 availablePhysicalMemory ();

	/** returns all the physical memory on this computer
	  */
	static uint32 totalPhysicalMemory ();

	/* Return the amount of allocated system memory */
	static uint32 getAllocatedSystemMemory ();

	/** returns all the virtual memory used by this process
	  */
	static uint32 virtualMemory ();

	/** Return the main video card name and the video driver version
	  */
	static bool getVideoInfo (std::string &deviceName, uint64 &driverVersion);

private:
	static bool _HaveMMX;
	static bool _HaveSSE;
	
};


} // NLMISC


#endif // NL_SYSTEM_INFO_H

/* End of system_info.h */
