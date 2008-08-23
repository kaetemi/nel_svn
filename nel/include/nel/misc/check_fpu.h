/** \file check_fpu.cpp
 * Check FPU macro
 */

/* Copyright, 2000, 2005 Nevrax Ltd.
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


#ifndef NL_CHECK_FPU_H
#define NL_CHECK_FPU_H


namespace NLMISC
{					  

class CFpuChecker
{
private:
	static int	_RefFpuCtrl;
	void check();
	void dumpFpu(int value);
public:
	CFpuChecker::CFpuChecker();	
	CFpuChecker::~CFpuChecker();	
};

}


// Enable define. Normal State is 0, to save CPU speed.
#define NL_CHECK_FPU_CONTROL_WORD 0

// Use those Macros
#if NL_CHECK_FPU_CONTROL_WORD
#define FPU_CHECKER NLMISC::CFpuChecker __fpc__;
#define FPU_CHECKER_ONCE { NLMISC::CFpuChecker __fpc__; }
#else
#define FPU_CHECKER
#define FPU_CHECKER_ONCE
#endif


#endif	// NL_CHECK_FPU_H

