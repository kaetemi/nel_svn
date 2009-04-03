/** \file fast_floor.h
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

#ifndef NL_FAST_FLOOR_H
#define NL_FAST_FLOOR_H

#include "types_nl.h"
#include <cmath>

namespace NLMISC
{

// fastFloor function.
// Actually, it seems to be bugged on VC7 (functions returns bad values)
// TODO: fix that
#if defined(NL_OS_WINDOWS) && !defined(NL_NO_ASM)
	// && defined(NL_COMP_VC6)

#include <cfloat>

// The magic constant value. support both positive and negative numbers.
extern double	OptFastFloorMagicConst ;
const uint		OptFastFloorCWStackSize = 10;
extern int      OptFastFloorCWStack[OptFastFloorCWStackSize];
extern int      *OptFastFloorCWStackPtr;
extern int      *OptFastFloorCWStackEnd;

inline void OptFastFloorPushCW(int ctrl)
{
	nlassert(OptFastFloorCWStackPtr < OptFastFloorCWStackEnd);
	*OptFastFloorCWStackPtr++ = _controlfp(0, 0);
	_controlfp( ctrl, _MCW_RC|_MCW_PC );
}

inline void OptFastFloorPopCW()
{
	nlassert(OptFastFloorCWStackPtr >=  OptFastFloorCWStack);
	_controlfp(*(--OptFastFloorCWStackPtr), _MCW_RC|_MCW_PC);
}


// init float CW.
inline void  OptFastFloorBegin()
{
	OptFastFloorPushCW(_RC_DOWN|_PC_53);
}

// reset float CW.
inline void  OptFastFloorEnd()
{
	OptFastFloorPopCW();
}

// Force __stdcall to not pass parameters in registers.
inline sint32 __stdcall OptFastFloor(float x)
{
	static __int64	res;
	__asm
	{
		fld		x
		fadd	qword ptr OptFastFloorMagicConst
		fstp	qword ptr res
	}

	return (sint32) (res&0xFFFFFFFF);
}


// Force __stdcall to not pass parameters in registers.
inline float __stdcall OptFastFractionnalPart(float x)
{
	static double res;
	__asm
	{
		fld		x
		fld     st(0)
		fadd	qword ptr OptFastFloorMagicConst
		fstp	qword ptr res
		fisub   dword ptr res
		fstp    dword ptr res
	}

	return * (float *) &res;
}


// The magic constant value, for 24 bits precision support positive numbers only
extern float	OptFastFloorMagicConst24 ;
// init float CW. Init with float 24 bits precision, for faster float operation.
inline void  OptFastFloorBegin24()
{
	OptFastFloorPushCW(_RC_DOWN|_PC_24);
}

// reset float CW.
inline void  OptFastFloorEnd24()
{
	OptFastFloorPopCW();
}

// Force __stdcall to not pass parameters in registers.
/// Same method as OptFastFloor, but result are always positive and should never be bigger than 2^23-1
inline uint32 __stdcall OptFastFloor24(float x)
{
	static uint32	res;
	__asm
	{
		fld		x
		fadd	dword ptr OptFastFloorMagicConst24
		fstp	dword ptr res
	}

	return res;
}



#else
inline void  OptFastFloorBegin() {}
inline void  OptFastFloorEnd() {}
inline sint  OptFastFloor(float x)
{
	return (sint)floor(x);
}

inline float  OptFastFractionnalPart(float x)
{
	return x - (sint) x ;
}


inline void  OptFastFloorBegin24() {}
inline void  OptFastFloorEnd24() {}
inline uint32 OptFastFloor24(float x)
{
	return (uint32)floor(x);
}


#endif



} // NLMISC


#endif // NL_FAST_FLOOR_H

/* End of fast_floor.h */
