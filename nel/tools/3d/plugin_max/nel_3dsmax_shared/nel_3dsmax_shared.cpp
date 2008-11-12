/** \file nel_3dsmax_shared.cpp
 * Defines the entry point for the DLL application.
 *
 * $Id: nel_3dsmax_shared.cpp,v 1.3 2005/06/23 18:18:10 boucher Exp $
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

#include "stdafx.h"
#include "..\nel_patch_lib\rpo.h"
#include "nel_3dsmax_shared.h"
#include "nel/misc/app_context.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	// initialize nel context
	if (!NLMISC::INelContext::isContextInitialised())
		new NLMISC::CApplicationContext();

    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------

void init ()
{
}

// ------------------------------------------------------------------------------------------------------------------------------------------------

// The static allocator
static CPatchAllocator Allocator;

NEL_3DSMAX_SHARED_API CPatchAllocator& GetAllocator ()
{
	// Init fonction
	init ();

	return Allocator;
}
