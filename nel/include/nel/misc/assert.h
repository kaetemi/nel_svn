/*// ============================================================================================
	This assert macro stop you in your source code and not in the _assert() ASM code.
	You can also use ASSERT or assert.
*/// ============================================================================================


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******* OUT OF DATE, THIS FILE WILL BE DESTROY SOON, LOOK IN DEBUG.H *********/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

#ifndef _COMMON_ASSERT_H
#define _COMMON_ASSERT_H

// Hulud 07/13/00, uncomment when types.h system works properly
//#include "common/types.h"
//#ifdef OS_WINDOWS

	#include <crtdbg.h>

	#undef  assert

	#ifdef  NDEBUG

		#define assert(exp)     ((void)0)

	#else	/* NDEBUG */

		#define assert(f) \
			do \
			{ \
			if (!(f) && (_CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, NULL)==1)) \
				_CrtDbgBreak(); \
			} while (0) \

	#endif  /* NDEBUG */

// Hulud 07/13/00, uncomment when types.h system works properly
/*#else // OS_WINDOWS

	#include <assert.h>

#endif // OS_WINDOWS*/

	#undef ASSERT
	#define ASSERT assert

#endif // _COMMON_ASSERT_H
